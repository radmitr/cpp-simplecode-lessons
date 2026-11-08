"""Verify contract semantics in isolated subprocesses, including expected termination."""
from pathlib import Path
import json
import os
import shutil
import subprocess

ROOT = Path(__file__).resolve().parents[1]
SOURCE = 'additions/contracts/02-evaluation-modes/main.cpp'


def main():
    bash = 'C:/msys64/usr/bin/bash.exe' if os.name == 'nt' else shutil.which('bash')
    script = 'scripts/build-windows.sh' if os.name == 'nt' else 'scripts/build-linux.sh'
    binary = ROOT / 'build' / SOURCE.removesuffix('.cpp')
    if os.name == 'nt':
        binary = binary.with_suffix('.exe')
    preexec = None
    if os.name != 'nt':
        import resource
        def no_core():
            resource.setrlimit(resource.RLIMIT_CORE, (0, 0))
        preexec = no_core
    results = []
    for mode in ('ignore', 'observe', 'enforce', 'quick_enforce'):
        env = dict(os.environ, CONTRACT_SEMANTIC=mode)
        subprocess.run([bash, script, SOURCE], cwd=ROOT, env=env, check=True, capture_output=True, timeout=180)
        valid = subprocess.run([str(binary)], cwd=ROOT, capture_output=True, timeout=10, env=env, preexec_fn=preexec)
        assert valid.returncode == 0, (mode, valid.stderr)
        invalid = subprocess.run([str(binary), '--violate'], cwd=ROOT, capture_output=True,
                                 timeout=10, env=env, preexec_fn=preexec)
        terminating = mode in ('enforce', 'quick_enforce')
        handler = b'handler:' in invalid.stderr
        assert (invalid.returncode != 0) == terminating, (mode, invalid.returncode, invalid.stderr)
        assert handler == (mode in ('observe', 'enforce')), (mode, invalid.stderr)
        if not terminating:
            assert b'value=-1' in invalid.stdout, (mode, invalid.stdout)
        results.append(dict(mode=mode, valid=valid.returncode, invalid=invalid.returncode, handler=handler))
        print('PASS', mode)
    output = ROOT / 'build/contract-checks'
    output.mkdir(parents=True, exist_ok=True)
    (output / 'report.json').write_text(json.dumps(results, indent=2) + '\n')


if __name__ == '__main__':
    main()
