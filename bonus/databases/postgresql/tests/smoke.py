#!/usr/bin/env python3
"""Build and exercise the PostgreSQL lessons against the dedicated running lab."""
import os
from pathlib import Path
import socket
import subprocess
import tempfile

ROOT = Path(__file__).resolve().parents[4]
BASE = ROOT / "bonus/databases/postgresql"
WINDOWS = os.name == "nt"
BASH = os.environ.get("BASH", "C:/msys64/usr/bin/bash.exe" if WINDOWS else "/bin/bash")
ENV = os.environ.copy()
if WINDOWS:
    ENV["PATH"] = "C:/msys64/mingw64/bin;" + ENV.get("PATH", "")

EXPECTED = {
    "01": ["Connected: cpp_lessons", "Answer: 5"],
    "02": ["1 | Notebook | 12.50 | t"],
    "03": ["1 | Learn SQL", "2 | Learn C++", "3 | Practice"],
    "04": ["Bag | 90", "Book | 70"],
    "05": ["Deleted: 1", "Missing id affected: 0"],
    "06": ["Stored literally: O'Reilly; DROP TABLE notes; --"],
    "07": ["1: Pen", "2: Book"],
    "08": ["1: <NULL>", "2: <empty string>", "NULL count: 1"],
    "09": ["Rejected: 23505", "Rejected: 23514", "Rejected: 23502", "Valid rows: 1"],
    "10": ["Alice | 10 | 100", "Bob | NULL", "Foreign key rejected: 23503"],
    "11": ["books | 2 | 300"],
    "12": ["Second transfer rolled back", "1 | 70", "2 | 130"],
    "13": ["Committed ids:\n1\n2"],
    "14": ["book | 2", "book | 5", "DO NOTHING affected: 0"],
    "15": ["Before index:", "After index:", "Scan"],
    "16": ["sensor | 25", "Threshold: 30"],
    "17": ["READ COMMITTED: 10 -> 20", "REPEATABLE READ: 10 -> 10"],
    "18": ["Plain SELECT: 10", "Contender timed out: 55P03", "Retry after COMMIT: 11"],
    "19": ["Imported rows: 3", "Exported CSV:\n1,10\n2,20\n3,30"],
    "20": ["1 | Learn PostgreSQL", "2 | Verify restore"],
}

def call(args, *, env=None, success=True, timeout=120):
    result = subprocess.run([str(arg) for arg in args], cwd=ROOT,
                            env=env or ENV, capture_output=True, text=True,
                            encoding="utf-8", errors="replace", timeout=timeout)
    if success and result.returncode:
        raise RuntimeError(f"Command failed ({result.returncode}): {args}\n"
                           f"{result.stdout}\n{result.stderr}")
    return result

def main():
    call([BASH, BASE / "scripts/lab.sh", "status"])
    sources = sorted(BASE.glob("lesson-*/main.cpp"))
    assert len(sources) == 20, f"Expected 20 lessons, found {len(sources)}"
    executables = []
    for source in sources:
        call([BASH, ROOT / f"scripts/build-{'windows' if WINDOWS else 'linux'}.sh", source])
        output = ROOT / "build" / source.relative_to(ROOT).with_suffix(".exe" if WINDOWS else "")
        result = call([output], timeout=15)
        number = source.parent.name.split("-")[1]
        for expected in EXPECTED[number]:
            assert expected in result.stdout, (number, expected, result.stdout, result.stderr)
        executables.append(output)
        print(f"PASS {source.parent.name}", flush=True)

    # Wrong password must fail. Keep fixtures inside ignored build/, never touch the real passfile.
    fixtures = ROOT / "build/bonus/databases/postgresql/test-fixtures"
    fixtures.mkdir(parents=True, exist_ok=True)
    with tempfile.TemporaryDirectory(dir=fixtures) as temporary:
        passfile = Path(temporary) / "pgpass.conf"
        secret = "intentionally_wrong_password_for_test"
        port = ENV.get("PGLESSONS_PORT", "55432")
        passfile.write_text(f"127.0.0.1:{port}:*:cpp_student:{secret}\n", encoding="utf-8")
        passfile.chmod(0o600)
        wrong_env = ENV.copy()
        wrong_env["PGLESSONS_HOME"] = temporary
        result = call([executables[0]], env=wrong_env, success=False, timeout=10)
        assert result.returncode != 0 and "authentication failed" in result.stderr, result
        assert secret not in result.stdout + result.stderr, "Password was printed"
    print("PASS wrong password is rejected without printing it", flush=True)

    # A currently unused local TCP port must produce a bounded connection failure.
    with socket.socket() as reserved:
        reserved.bind(("127.0.0.1", 0))
        unused = reserved.getsockname()[1]
        unavailable_env = ENV.copy()
        unavailable_env["PGLESSONS_PORT"] = str(unused)
        result = call([executables[0]], env=unavailable_env, success=False, timeout=10)
        assert result.returncode != 0, result
    print("PASS unavailable server fails", flush=True)

    restored = call([BASH, BASE / "scripts/backup-restore.sh"])
    assert "Backup verified:" in restored.stdout, restored
    assert "1:Learn PostgreSQL\n2:Verify restore" in restored.stdout, restored
    print(restored.stdout, end="")
    print("PASS all 20 PostgreSQL lessons and backup/restore", flush=True)

if __name__ == "__main__":
    main()
