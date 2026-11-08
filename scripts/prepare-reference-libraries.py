"""Download pinned reference libraries into build/; never modify a system SDK."""
from pathlib import Path
import hashlib
import json
import re
import shutil
import tarfile
import tempfile
import urllib.request

ROOT = Path(__file__).resolve().parents[1]
BASE = ROOT / 'build/dependencies/reference'


def main():
    BASE.mkdir(parents=True, exist_ok=True)
    lock = json.loads((ROOT / 'scripts/reference-libraries.json').read_text())
    for item in lock:
        target = BASE / item['name']
        marker = target / '.revision'
        if marker.is_file() and marker.read_text().strip() == item['revision']:
            print('READY', item['name'], item['revision'])
            continue
        if target.exists():
            raise SystemExit(f'{target} exists with a different revision; move it aside before preparing dependencies.')
        archive = BASE / (item['name'] + '.tar.gz')
        if not archive.exists():
            with urllib.request.urlopen(item['url'], timeout=60) as response:
                data = response.read()
            if hashlib.sha256(data).hexdigest() != item['sha256']:
                raise SystemExit('Archive checksum mismatch: ' + item['name'])
            archive.write_bytes(data)
        if hashlib.sha256(archive.read_bytes()).hexdigest() != item['sha256']:
            raise SystemExit('Cached archive checksum mismatch: ' + str(archive))
        with tempfile.TemporaryDirectory(dir=BASE, prefix='unpack-') as directory:
            unpacked = Path(directory)
            with tarfile.open(archive) as package:
                for member in package.getmembers():
                    original = Path(member.name)
                    parts = original.parts[1:]
                    if original.is_absolute() or '..' in original.parts or member.issym() or member.islnk():
                        raise SystemExit('Unsafe archive entry: ' + member.name)
                    if not parts:
                        continue
                    destination = unpacked.joinpath(*parts)
                    if member.isdir():
                        destination.mkdir(parents=True, exist_ok=True)
                    elif member.isfile():
                        destination.parent.mkdir(parents=True, exist_ok=True)
                        destination.write_bytes(package.extractfile(member).read())
                    else:
                        raise SystemExit('Unsupported archive entry: ' + member.name)
            (unpacked / '.revision').write_text(item['revision'] + '\n')
            shutil.move(str(unpacked), str(target))
        print('READY', item['name'], item['revision'])
    # Serial header-only stdBLAS profile: no BLAS, Kokkos runtime or TBB backend.
    template = BASE / 'stdblas/include/experimental/__p1673_bits/linalg_config.h.in'
    config = BASE / 'config/experimental/__p1673_bits/linalg_config.h'
    config.parent.mkdir(parents=True, exist_ok=True)
    config.write_text(re.sub(r'^#cmakedefine (\w+)$', r'/* #undef \1 */',
                             template.read_text(), flags=re.M))
    (BASE / '.ready').write_text(hashlib.sha256(
        (ROOT / 'scripts/reference-libraries.json').read_bytes()).hexdigest() + '\n')


if __name__ == '__main__':
    main()
