"""Offline regression checks for pinned downloads and safe archive extraction."""
import hashlib
import importlib.util
import io
import json
from pathlib import Path
import tarfile
import tempfile
import unittest
from unittest.mock import patch

SPEC = importlib.util.spec_from_file_location('reference', Path(__file__).with_name('prepare-reference-libraries.py'))
MODULE = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(MODULE)


class ReferenceLibraries(unittest.TestCase):
    def setUp(self):
        self.temporary = tempfile.TemporaryDirectory()
        self.addCleanup(self.temporary.cleanup)
        self.root = Path(self.temporary.name)
        (self.root / 'scripts').mkdir()
        self.base = self.root / 'build/dependencies/reference'
        self.base.mkdir(parents=True)
        self.patch_root = patch.object(MODULE, 'ROOT', self.root)
        self.patch_base = patch.object(MODULE, 'BASE', self.base)
        self.patch_root.start()
        self.patch_base.start()
        self.addCleanup(self.patch_root.stop)
        self.addCleanup(self.patch_base.stop)

    def archive(self, name='package/include/experimental/__p1673_bits/linalg_config.h.in'):
        stream = io.BytesIO()
        with tarfile.open(fileobj=stream, mode='w:gz') as archive:
            member = tarfile.TarInfo(name)
            data = b'#pragma once\n#cmakedefine LINALG_ENABLE_BLAS\n'
            member.size = len(data)
            archive.addfile(member, io.BytesIO(data))
        content = stream.getvalue()
        (self.base / 'stdblas.tar.gz').write_bytes(content)
        row = dict(name='stdblas', revision='a' * 40, url='https://invalid.example/offline',
                   sha256=hashlib.sha256(content).hexdigest())
        (self.root / 'scripts/reference-libraries.json').write_text(json.dumps([row]))
        return row

    def test_cached_archive_needs_no_network_and_generates_serial_config(self):
        self.archive()
        with patch.object(MODULE.urllib.request, 'urlopen', side_effect=AssertionError('network called')):
            MODULE.main()
            MODULE.main()
        self.assertEqual((self.base / 'stdblas/.revision').read_text().strip(), 'a' * 40)
        self.assertIn('/* #undef LINALG_ENABLE_BLAS */',
                      (self.base / 'config/experimental/__p1673_bits/linalg_config.h').read_text())

    def test_bad_checksum_does_not_extract(self):
        self.archive()
        (self.base / 'stdblas.tar.gz').write_bytes(b'corrupt')
        with self.assertRaisesRegex(SystemExit, 'checksum'):
            MODULE.main()
        self.assertFalse((self.base / 'stdblas').exists())

    def test_parent_path_is_rejected_before_writing_outside_unpack_directory(self):
        self.archive('package/../../escape')
        with self.assertRaisesRegex(SystemExit, 'Unsafe archive entry'):
            MODULE.main()
        self.assertFalse((self.base / 'escape').exists())
        self.assertFalse((self.base / 'stdblas').exists())

    def test_existing_different_revision_is_preserved(self):
        self.archive()
        target = self.base / 'stdblas'
        target.mkdir()
        (target / '.revision').write_text('old')
        (target / 'valuable').write_text('keep')
        with self.assertRaisesRegex(SystemExit, 'different revision'):
            MODULE.main()
        self.assertEqual((target / 'valuable').read_text(), 'keep')


if __name__ == '__main__':
    unittest.main()
