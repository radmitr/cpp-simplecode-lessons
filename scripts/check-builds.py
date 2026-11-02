"""Build every program through the shared Windows/Linux lesson build script."""
from __future__ import annotations

import argparse
from concurrent.futures import ThreadPoolExecutor, as_completed
import json
import os
from pathlib import Path
import re
import shutil
import subprocess
import sys

ROOT = Path(__file__).resolve().parents[1]
TOPS = ("basics", "templates", "exceptions", "io", "oop", "stl",
        "multithreading", "bonus", "examples", "_template")
LITERALS_AND_COMMENTS = re.compile(
    r'R"(?P<delimiter>[^\s()\\]{0,16})\(.*?\)(?P=delimiter)"'
    r'|"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\'|//[^\n]*|/\*.*?\*/', re.S)


def programs():
    """Ignore helper translation units and main() text inside comments/strings."""
    for top in TOPS:
        for source in sorted((ROOT / top).rglob("*.cpp")):
            code = LITERALS_AND_COMMENTS.sub("", source.read_text(encoding="utf-8-sig"))
            if re.search(r"\b(?:int|auto)\s+main\s*\(", code):
                yield source


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--jobs", type=int, choices=range(1, 5), default=2)
    parser.add_argument("--source", action="append", help="Build only this repository-relative program; repeatable")
    arguments = parser.parse_args()
    windows = os.name == "nt"
    bash = "C:/msys64/usr/bin/bash.exe" if windows else shutil.which("bash")
    if not bash or not Path(bash).is_file():
        raise SystemExit("Bash not found. Windows requires MSYS2 at C:/msys64.")
    discovered = list(programs())
    if arguments.source:
        requested = {(ROOT / name).resolve() for name in arguments.source}
        missing = requested - set(discovered)
        if missing:
            raise SystemExit("No main() program found: " + ", ".join(map(str, sorted(missing))))
        discovered = [source for source in discovered if source in requested]
    script = ROOT / "scripts" / ("build-windows.sh" if windows else "build-linux.sh")
    output = ROOT / "build/all-builds"
    output.mkdir(parents=True, exist_ok=True)

    def build(source):
        name = source.relative_to(ROOT).as_posix()
        try:
            result = subprocess.run(
                [bash, str(script), str(source)], cwd=ROOT,
                stdout=subprocess.PIPE, stderr=subprocess.PIPE, timeout=240)
            return {"source": name, "ok": result.returncode == 0,
                    "stdout": result.stdout.decode("utf-8", errors="replace"),
                    "stderr": result.stderr.decode("utf-8", errors="replace")}
        except (OSError, subprocess.TimeoutExpired) as error:
            return {"source": name, "ok": False, "stderr": str(error)}

    results = []
    with ThreadPoolExecutor(max_workers=arguments.jobs) as pool:
        pending = [pool.submit(build, source) for source in discovered]
        for future in as_completed(pending):
            result = future.result()
            results.append(result)
            if not result["ok"]:
                print("FAIL " + result["source"] + "\n" + result["stderr"], flush=True)
            elif len(results) % 25 == 0:
                print(f"Built {len(results)}/{len(discovered)}", flush=True)
    report = {"platform": sys.platform, "passed": sum(r["ok"] for r in results),
              "failed": sum(not r["ok"] for r in results),
              "results": sorted(results, key=lambda r: r["source"])}
    report_path = output / ("selected-report.json" if arguments.source else "report.json")
    report_path.write_text(json.dumps(report, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")
    print(f"Passed: {report['passed']}; failed: {report['failed']}")
    print(f"Report: {report_path}")
    return 1 if report["failed"] else 0


if __name__ == "__main__":
    raise SystemExit(main())
