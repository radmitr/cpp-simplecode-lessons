"""Check module dependency order, CMI rebuilding and manifest validation."""
from pathlib import Path
import os
import shutil
import subprocess
import tempfile

ROOT = Path(__file__).resolve().parents[1]


def main():
    work = ROOT / 'build/module-checks'
    work.mkdir(parents=True, exist_ok=True)
    original = ROOT / 'additions/modules/02-reexport-and-templates'
    bash = 'C:/msys64/usr/bin/bash.exe' if os.name == 'nt' else shutil.which('bash')
    builder = ROOT / 'scripts' / ('build-windows.sh' if os.name == 'nt' else 'build-linux.sh')
    with tempfile.TemporaryDirectory(dir=work, prefix='source-') as folder:
        folder = Path(folder)
        for name in ('main.cpp', 'numbers.cppm', 'facade.cppm', 'module-units.txt',
                     'language-feature.txt', 'cxx-standard.txt', 'gcc-min-version.txt'):
            shutil.copyfile(original / name, folder / name)
        def build():
            return subprocess.run([bash, str(builder), str(folder / 'main.cpp')], cwd=ROOT,
                                  capture_output=True, text=True, timeout=180)
        initial = build()
        assert initial.returncode == 0, initial.stderr
        # Reverse dependency order after a successful build; stale CMIs must not mask it.
        (folder / 'module-units.txt').write_text('facade.cppm\nnumbers.cppm\n')
        wrong_order = build()
        assert wrong_order.returncode != 0, 'stale CMI concealed dependency order'
        (folder / 'module-units.txt').write_text('numbers.cppm\nfacade.cppm\n')
        assert build().returncode == 0
        (folder / 'module-units.txt').write_text('../numbers.cppm\n')
        traversal = build()
        assert traversal.returncode == 2 and 'Invalid module unit' in traversal.stderr
        (folder / 'module-units.txt').write_text('')
        (folder / 'header-units.txt').write_text('../settings.hpp\n')
        invalid_header = build()
        assert invalid_header.returncode == 2 and 'Invalid header unit' in invalid_header.stderr
        print('PASS ordered build / stale CMI / restored build / unsafe module and header paths')
        output = ROOT / 'build' / (folder / 'main').relative_to(ROOT)
        # Only generated objects of this temporary source fixture are removed.
        shutil.rmtree(output.parent, ignore_errors=True)


if __name__ == '__main__':
    main()
