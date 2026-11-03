"""Build 71 introductory course programs and check their runtime behavior."""
from __future__ import annotations
import argparse
from concurrent.futures import ThreadPoolExecutor
import json
import os
from pathlib import Path
import re
import subprocess

ROOT = Path(__file__).resolve().parents[1]
WINDOWS = os.name == "nt"


def validate(result, case):
    if result.returncode != case.get("exit", 0):
        raise RuntimeError(f"exit={result.returncode}, stderr={result.stderr!r}")
    raw = result.stdout.replace(b"\r\n", b"\n")
    if case.get("byte_table"):
        expected = b"\n CHAR = 1 byte\n\n" + b"".join(
            f"code = {i}\tchar = ".encode() + bytes([i]) + b"\n" for i in range(256))
        if raw != expected:
            raise RuntimeError("The 0..255 byte table differs")
        return
    text = raw.decode("utf-8")
    if result.returncode == 0 and "stderr_contains" not in case and result.stderr:
        raise RuntimeError(f"Unexpected stderr: {result.stderr!r}")
    for value in case.get("contains", []):
        if value not in text:
            raise RuntimeError(f"Missing stdout fragment {value!r}: {text!r}")
    for value in case.get("stderr_contains", []):
        if value not in result.stderr.decode("utf-8"):
            raise RuntimeError(f"Missing stderr fragment {value!r}")
    if "exact" in case and text != case["exact"]:
        raise RuntimeError(f"stdout={text!r}")
    for check in case.get("matches", []):
        found = [list(x) if isinstance(x, tuple) else x
                 for x in re.findall(check["pattern"], text)]
        if "expected" in check and found != check["expected"]:
            raise RuntimeError(f"{check['pattern']}: {found!r}")
        if "count" in check and len(found) != check["count"]:
            raise RuntimeError(f"{check['pattern']}: count={len(found)}")
    for pattern in case.get("equal_groups", []):
        groups = re.findall(pattern, text)
        if not groups or any(len(set(group)) != 1 for group in groups):
            raise RuntimeError(f"Expected equal captured values: {pattern}: {groups}")
    if "addresses" in case:
        check = case["addresses"]
        addresses = re.findall(r"0x[0-9a-fA-F]+", text)
        if len(addresses) != check["count"]:
            raise RuntimeError(f"Address count differs: {addresses}")
        for indices in check.get("equal", []):
            if len({addresses[i] for i in indices}) != 1:
                raise RuntimeError("Expected equal addresses: " + str(indices))
        for indices in check.get("distinct", []):
            if len({addresses[i] for i in indices}) != len(indices):
                raise RuntimeError("Expected distinct addresses: " + str(indices))
    if "random" in case:
        check = case["random"]
        values = [int(x) for x in re.findall(check.get("pattern", r"(?m)^\s*(\d+)\s*$"), text)]
        if len(values) != check["count"] or any(not check["min"] <= x <= check["max"] for x in values):
            raise RuntimeError(f"random count/range mismatch: {values}")


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--jobs", type=int, choices=range(1, 5), default=2)
    parser.add_argument("--build-only", action="store_true")
    options = parser.parse_args()
    records = json.loads((ROOT / "scripts/intro-lessons.json").read_text(encoding="utf-8"))
    bash = "C:/msys64/usr/bin/bash.exe" if WINDOWS else "/bin/bash"
    builder = ROOT / "scripts" / ("build-windows.sh" if WINDOWS else "build-linux.sh")
    environment = dict(os.environ)
    if WINDOWS:
        compiler = Path(environment.get("CXX", "C:/msys64/mingw64/bin/g++.exe"))
        environment["PATH"] = str(compiler.parent) + os.pathsep + environment.get("PATH", "")

    def execute(command, *, data="", cwd=ROOT, timeout=90):
        return subprocess.run(command, cwd=cwd, input=data.encode("utf-8"),
                              capture_output=True, timeout=timeout, env=environment)

    def check(record):
        source = Path(record["source"])
        try:
            built = execute([bash, str(builder), str(ROOT / source)])
            if built.returncode:
                raise RuntimeError(built.stderr.decode("utf-8", errors="replace"))
            result = {"source": source.as_posix(), "ok": True,
                      "warnings": built.stderr.decode("utf-8", errors="replace")}
            if not options.build_only:
                binary = ROOT / "build" / source.with_suffix(".exe" if WINDOWS else "")
                work = ROOT / "build/intro-checks" / source.parent
                work.mkdir(parents=True, exist_ok=True)
                cases = record.get("cases", [record])
                outputs = []
                for case in cases:
                    run = execute([str(binary), *case.get("args", [])],
                                  data=case.get("input", ""), cwd=work, timeout=5)
                    validate(run, case)
                    outputs.append({"stdout": run.stdout.decode("utf-8", errors="backslashreplace"),
                                    "stderr": run.stderr.decode("utf-8", errors="backslashreplace"),
                                    "exit": run.returncode})
                result["runs"] = outputs
            return result
        except (OSError, RuntimeError, subprocess.TimeoutExpired, UnicodeError) as error:
            return {"source": source.as_posix(), "ok": False, "error": str(error)}

    with ThreadPoolExecutor(max_workers=options.jobs) as pool:
        results = list(pool.map(check, records))
    for result in results:
        print(("PASS " if result["ok"] else "FAIL ") + result["source"])
        if not result["ok"]:
            print(result["error"])
    failed = sum(not r["ok"] for r in results)
    report = {"platform": os.name, "build_only": options.build_only,
              "checked": len(results), "failed": failed, "results": results}
    target = ROOT / "build/intro-checks"
    target.mkdir(parents=True, exist_ok=True)
    (target / ("build-report.json" if options.build_only else "report.json")).write_text(
        json.dumps(report, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")
    print(f"Checked {len(results)} lessons; failures: {failed}")
    return bool(failed)


if __name__ == "__main__":
    raise SystemExit(main())
