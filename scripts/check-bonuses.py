"""Build and run the language, I/O and reflection lessons on Windows or Linux."""
from __future__ import annotations

import argparse
from concurrent.futures import ThreadPoolExecutor
import json
import os
from pathlib import Path
import shutil
import subprocess
import sys

ROOT = Path(__file__).resolve().parents[1]
SECTIONS = ("basics/bonus", "io/bonus", "bonus/reflection")
WINDOWS = os.name == "nt"


def execute(arguments, *, cwd=ROOT, data=None, timeout=180, environment=None):
    return subprocess.run(arguments, cwd=cwd, input=data, stdout=subprocess.PIPE,
                          stderr=subprocess.PIPE, timeout=timeout, env=environment)


def text(value):
    return value.decode("utf-8", errors="replace").replace("\r\n", "\n")


def compiler(modern):
    default = "C:/msys64/mingw64/bin/g++.exe" if WINDOWS else (
        "/opt/gcc-16/bin/g++" if modern else "/usr/bin/g++")
    return os.environ.get("CXX_MODERN", os.environ.get("CXX", default)) if modern else os.environ.get("CXX", default)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--section", choices=(*SECTIONS, "all"), default="all")
    parser.add_argument("--portable-only", action="store_true", help="Skip lessons requiring GCC newer than 11")
    parser.add_argument("--jobs", type=int, choices=range(1, 5), default=2)
    arguments = parser.parse_args()
    sections = SECTIONS if arguments.section == "all" else (arguments.section,)
    bash = "C:/msys64/usr/bin/bash.exe" if WINDOWS else shutil.which("bash")
    if not bash or not Path(bash).is_file():
        raise SystemExit("Bash not found. Windows requires MSYS2 at C:/msys64, Linux requires bash.")
    script = ROOT / "scripts" / ("build-windows.sh" if WINDOWS else "build-linux.sh")
    work = ROOT / "build/bonus-checks"
    work.mkdir(parents=True, exist_ok=True)
    records = []
    skipped = []
    for section in sections:
        items = json.loads((ROOT / section / "lessons.json").read_text(encoding="utf-8"))
        for item in items:
            if arguments.portable_only and item["minimum_gcc"] > 11:
                skipped.append(item["folder"])
                continue
            folder = ROOT / item["folder"]
            sources = sorted(folder.rglob("main*.cpp"))
            if not sources:
                raise SystemExit(f"Lesson has no main source: {folder}")
            for source in sources:
                records.append((item, source))

    for modern in {item["minimum_gcc"] >= 13 for item, _ in records}:
        selected = compiler(modern)
        if not shutil.which(selected):
            raise SystemExit(f"Compiler not found: {selected}. Configure CXX_MODERN/CXX or use --portable-only.")

    def check_one(record):
        item, source = record
        relative = source.relative_to(ROOT)
        name = relative.as_posix()
        directory = work / relative.parent / source.stem
        directory.mkdir(parents=True, exist_ok=True)
        environment = dict(os.environ)
        environment["CPP_LESSON_WORK_DIR"] = str(directory)
        if WINDOWS:
            # Applications also need the DLL directory of the selected compiler.
            environment["PATH"] = str(Path(compiler(item["minimum_gcc"] >= 13)).parent) + os.pathsep + environment.get("PATH", "")
        try:
            result = execute([bash, str(script), str(source)], environment=environment)
            if result.returncode:
                raise RuntimeError("build failed:\n" + text(result.stderr))
            build_warnings = text(result.stderr)
            binary = ROOT / "build" / relative.with_suffix(".exe" if WINDOWS else "")
            data = None
            if item["folder"].endswith("01-constexpr-consteval") and source.name == "main2.cpp":
                data = b"7\n"
            if item["folder"].endswith("01-stream-state") and source.name == "main2.cpp":
                data = b"bad\n-1\n3\nthree items\n"
            result = execute([str(binary)], cwd=directory, data=data, timeout=20, environment=environment)
            if result.returncode:
                raise RuntimeError(f"exit {result.returncode}:\n{text(result.stderr)}\n{text(result.stdout)}")
            output = text(result.stdout)
            if item["number"] > 2 or item["folder"].startswith("bonus/reflection/"):
                if "OK " not in output:
                    raise RuntimeError("success marker missing:\n" + output)
            if item["folder"].endswith("01-constexpr-consteval") and source.name == "main2.cpp":
                if "runtime square: 49" not in output:
                    raise RuntimeError("runtime constexpr result mismatch")
                for bad in (b"bad\n", b"101\n", b""):
                    invalid = execute([str(binary)], cwd=directory, data=bad, environment=environment)
                    if invalid.returncode != 1:
                        raise RuntimeError("invalid constexpr input was accepted")
            if item["folder"].endswith("01-stream-state") and source.name == "main2.cpp":
                if "count: 3, label: three items" not in output:
                    raise RuntimeError("input recovery failed")
                for bad in (b"", b"bad", b"3\n"):
                    if execute([str(binary)], cwd=directory, data=bad, environment=environment).returncode != 1:
                        raise RuntimeError("missing stream input was accepted")
            if item["folder"].endswith("02-portable-binary"):
                expected = bytes.fromhex("50543031e7010000d4000000b2030000")
                if (directory / "point-v1.bin").read_bytes() != expected:
                    raise RuntimeError("binary format bytes mismatch")
                for filename, content in (("empty", b""), ("short", expected[:-1]),
                    ("version", b"PT02" + expected[4:]), ("extra", expected + b"!")):
                    (directory / filename).write_bytes(content)
                    invalid = execute([str(binary), "--read", filename], cwd=directory, environment=environment)
                    if invalid.returncode != 1:
                        raise RuntimeError(f"corrupted binary accepted: {filename}")
            if item["folder"].endswith("19-console-tool"):
                cli = execute([str(binary), "--scale", "2"], cwd=directory, data=b"1 2 3\n", environment=environment)
                if cli.returncode or text(cli.stdout) != "12\n" or cli.stderr:
                    raise RuntimeError("CLI stdout/stderr protocol failed")
                for bad in (b"1 bad", b"1 999999999999999999999", b"1000001"):
                    cli = execute([str(binary), "--scale", "2"], cwd=directory, data=bad, environment=environment)
                    if cli.returncode != 1 or cli.stdout or not cli.stderr:
                        raise RuntimeError("invalid CLI token or range accepted")
                cli = execute([str(binary), "--scale", "2oops"], cwd=directory, data=b"1", environment=environment)
                if cli.returncode != 1:
                    raise RuntimeError("invalid CLI argument accepted")
            return {"source": name, "ok": True, "warnings": build_warnings, "stdout": output}
        except (OSError, RuntimeError, subprocess.TimeoutExpired) as error:
            return {"source": name, "ok": False, "error": str(error)}

    results = []
    with ThreadPoolExecutor(max_workers=arguments.jobs) as pool:
        for result in pool.map(check_one, records):
            results.append(result)
            print(("PASS " if result["ok"] else "FAIL ") + result["source"], flush=True)
            if not result["ok"]:
                print(result["error"], flush=True)

    # Negative cases stay outside *.cpp so ordinary source discovery never builds them.
    negative = ROOT / "bonus/reflection/checks/negative.json"
    if "bonus/reflection" in sections and not arguments.portable_only and negative.is_file():
        for case in json.loads(negative.read_text(encoding="utf-8")):
            args = [compiler(True), "-std=c++26", "-freflection", "-x", "c++", "-fsyntax-only", "-"]
            result = execute(args, data=case["source"].encode("utf-8"))
            ok = result.returncode != 0 and any(word in text(result.stderr).lower() for word in case["diagnostic_words"])
            results.append({"source": "negative/" + case["name"], "ok": ok, "error": "" if ok else text(result.stderr)})
            print(("PASS " if ok else "FAIL ") + "negative/" + case["name"], flush=True)
    report = {"platform": sys.platform, "passed": sum(r["ok"] for r in results),
              "failed": sum(not r["ok"] for r in results), "skipped": skipped, "results": results}
    report_path = work / "report.json"
    report_path.write_text(json.dumps(report, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")
    print(f"Passed: {report['passed']}; failed: {report['failed']}; skipped lessons: {len(skipped)}")
    print(f"Report: {report_path}")
    return 1 if report["failed"] else 0


if __name__ == "__main__":
    raise SystemExit(main())
