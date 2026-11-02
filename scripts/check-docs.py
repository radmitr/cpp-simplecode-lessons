"""Check local Markdown links, lesson structure and Windows/Linux VS Code files."""
from __future__ import annotations

import json
import os
from pathlib import Path
import re
from urllib.parse import unquote, urlsplit

ROOT = Path(__file__).resolve().parents[1]
EXCLUDED = {".git", ".local", ".agents", ".codex", ".aws", "build", ".vscode", "__pycache__"}
ORDER = ["Версия C++", "Что изучаем", "Примеры", "Как это работает",
         "Сборка и запуск", "Типичные ошибки", "Связанные темы и источники"]


def files():
    for directory, folders, names in os.walk(ROOT):
        folders[:] = [folder for folder in folders if folder not in EXCLUDED]
        for name in names:
            yield Path(directory) / name


def prose(text):
    result = []
    fence = None
    for line in text.splitlines():
        match = re.match(r"^\s*([\x60]{3,}|~{3,})", line)
        if match:
            symbol = match[1][0]
            fence = None if fence == symbol else symbol
            continue
        if fence is None:
            result.append(line)
    return "\n".join(result)


def anchors(text):
    found = set()
    counters = {}
    for heading in re.findall(r"^#{1,6}\s+(.+)$", prose(text), re.M):
        heading = re.sub(r"\[([^]]+)\]\([^)]*\)", r"\1", heading)
        heading = re.sub(r"<[^>]*>", "", heading).lower()
        heading = "".join(character for character in heading
                          if character.isalnum() or character in "_- " or character.isspace())
        slug = re.sub(r"\s", "-", heading.strip())
        count = counters.get(slug, 0)
        counters[slug] = count + 1
        found.add(slug + (f"-{count}" if count else ""))
    return found


def main():
    paths = list(files())
    markdown = [p for p in paths if p.suffix == ".md"]
    errors = []
    lessons = 0
    for path in markdown:
        text = path.read_text(encoding="utf-8-sig")
        visible = prose(text)
        link_text = re.sub(r"[\x60]+[^\x60\n]*[\x60]+", "code", visible)
        for match in re.finditer(r"!?\[([^\]\n]+)\]\(([^\n]+?)\)", link_text):
            label = match[1]
            target = match[2].strip().strip("<>")
            parsed = urlsplit(target)
            if "vscode-resource" in target or "vscode-cdn.net" in target:
                errors.append(f"{path.relative_to(ROOT)}: nonportable webview URL {target}")
            if "команды" in label.lower() and unquote(parsed.fragment) == "требования":
                errors.append(f"{path.relative_to(ROOT)}: commands link points at requirements")
            if re.fullmatch(r"(?:урок|бонус)[а-я]*\s+\d+", label, re.I):
                errors.append(f"{path.relative_to(ROOT)}: use a descriptive lesson title")
            if parsed.scheme or target.startswith("//"):
                continue
            destination = (path.parent / unquote(parsed.path)).resolve()
            context = path.relative_to(ROOT).as_posix()
            topic = next((prefix for prefix in (
                "bonus/networking", "bonus/databases/postgresql", "bonus/reflection"
            ) if context.startswith(prefix + "/")), None)
            numbered = re.match(r"«(?:Урок\s+)?(\d+)[.]", label)
            if topic and numbered and destination.is_relative_to(ROOT / "basics"):
                number = int(numbered[1])
                own_lesson = list((ROOT / topic).glob(f"lesson-{number:02d}-*/README.md"))
                own_lesson += list((ROOT / topic).glob(f"{number:02d}-*/README.md"))
                if own_lesson:
                    errors.append(f"{path.relative_to(ROOT)}: numbered lesson links outside its topic; "
                                  "qualify a deliberate reference to basics in its label")
            if not destination.exists():
                errors.append(f"{path.relative_to(ROOT)}: missing {target}")
            elif parsed.fragment and destination.is_file() and destination.suffix == ".md":
                if unquote(parsed.fragment) not in anchors(destination.read_text(encoding="utf-8-sig")):
                    errors.append(f"{path.relative_to(ROOT)}: missing anchor {target}")
        if path.name != "README.md":
            continue
        candidates = list(path.parent.glob("*.cpp")) + list((path.parent / "src").glob("*.cpp"))
        sources = [p for p in candidates if re.search(
            r"\b(?:int|void)\s+main\s*\(", p.read_text(encoding="utf-8-sig"))]
        if not sources:
            continue
        lessons += 1
        headings = re.findall(r"^## (.+)$", visible, re.M)
        required = [h for h in ORDER if h != "Типичные ошибки"]
        for heading in required:
            if heading not in headings:
                errors.append(f"{path.relative_to(ROOT)}: missing section {heading}")
        indices = [ORDER.index(h) for h in headings if h in ORDER]
        if indices != sorted(indices) or len(indices) != len(set(indices)):
            errors.append(f"{path.relative_to(ROOT)}: inconsistent section order")
        launch_link = "#сборка-и-запуск-в-vs-code)" in visible
        if not launch_link and not ("F5" in visible and "Ctrl+F5" in visible):
            errors.append(f"{path.relative_to(ROOT)}: link to VS Code launch guide")
        for source in sources:
            target = source.relative_to(path.parent).as_posix()
            if target not in text:
                errors.append(f"{path.relative_to(ROOT)}: undocumented source {target}")
            local_targets = [unquote(link.split("#", 1)[0]) for link in re.findall(
                r"\]\(([^\n]+?)\)", visible) if not urlsplit(link).scheme]
            if not any((path.parent / item).resolve() == source.resolve() for item in local_targets):
                errors.append(f"{path.relative_to(ROOT)}: missing full-source link {target}")
        for name in ("tasks.json", "launch.json"):
            config = path.parent / ".vscode" / name
            if not config.is_file():
                errors.append(f"{path.relative_to(ROOT)}: missing {config.name}")
                continue
            try:
                contents = json.loads(config.read_text(encoding="utf-8-sig"))
                # Reorganization can leave valid JSON pointing at another lesson.
                def strings(value):
                    if isinstance(value, str):
                        yield value
                    elif isinstance(value, dict):
                        for item in value.values():
                            yield from strings(item)
                    elif isinstance(value, list):
                        for item in value:
                            yield from strings(item)

                for value in strings(contents):
                    if not value.startswith("${workspaceFolder}/"):
                        continue
                    resolved = value.replace("${workspaceFolder}", path.parent.as_posix())
                    if "/scripts/" in value and "${" not in resolved:
                        if not Path(resolved).is_file():
                            errors.append(f"{config.relative_to(ROOT)}: missing script {value}")
                    if "/build/" in value:
                        prefix = resolved.split("${", 1)[0].rstrip("/")
                        expected = ROOT / "build" / path.parent.relative_to(ROOT)
                        if not Path(prefix).resolve().is_relative_to(expected.resolve()):
                            errors.append(f"{config.relative_to(ROOT)}: wrong output directory {value}")
            except ValueError as error:
                errors.append(f"{config.relative_to(ROOT)}: invalid JSON: {error}")
    for error in errors:
        print("FAIL " + error)
    print(f"Checked {len(markdown)} Markdown files, {lessons} lessons; errors: {len(errors)}")
    return bool(errors)


if __name__ == "__main__":
    raise SystemExit(main())
