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
LESSON_DIRECTORY = re.compile(r"(?:lesson-)?(\d+)-", re.I)
LINK_OR_CODE = re.compile(
    r"`+[^`\n]*`+|!?\[((?:`+[^`\n]*`+|[^\]`\n])+)\]\(([^\n]+?)\)")


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


def links(text):
    # Match links before their inner code spans, but skip links quoted as code.
    for match in LINK_OR_CODE.finditer(text):
        if match[1] is not None:
            yield match[1], match[2].strip().strip("<>")


def numbered_title(text):
    quoted = re.search(r"«([^»]+)»", text)
    title = (quoted[1] if quoted else text).replace("`", "")
    match = re.match(r"(?:(?:урок|бонус)\s+)?(\d+)\.\s*(.+)", title, re.I)
    if not match:
        return None
    qualifier = text[:quoted.start()].strip(" :—-").casefold() if quoted else ""
    qualified = qualifier not in ("", "урок", "уроки", "бонус", "бонусы")
    normalized = re.sub(r"\s+", " ", match[2]).strip().casefold()
    return int(match[1]), normalized, qualified


def lesson_catalog(markdown):
    lessons = {}
    topics = {}
    for path in markdown:
        match = LESSON_DIRECTORY.match(path.parent.name)
        if path.name != "README.md" or not match:
            continue
        scope = path.parent.parent
        # Course lessons and their bonuses share a topic; each topic has its own numbers.
        topic = scope.parent if scope.name == "bonus" else scope
        number = int(match[1])
        text = path.read_text(encoding="utf-8-sig")
        heading = re.search(r"^#\s+(.+)$", prose(text), re.M)
        title = numbered_title(heading[1]) if heading else None
        lessons[path.parent] = topic, number, title
        topics.setdefault(topic, set()).add(number)
    return lessons, topics


def lesson_link_errors(path, label, destination, catalog, topics):
    numbered = numbered_title(label)
    if not numbered:
        return []
    lesson = next((catalog[parent] for parent in (destination, *destination.parents)
                   if parent in catalog), None)
    if lesson is None:
        return []
    topic, number, title = lesson
    errors = []
    if numbered[0] != number:
        errors.append(f"lesson number {numbered[0]} does not match target {number}: {label}")
    if title and numbered[1] != title[1]:
        errors.append(f"numbered lesson title does not match target heading: {label}")
    source_topic = next((parent for parent in path.parents if parent in topics), None)
    if (source_topic is not None and source_topic != topic
            and numbered[0] in topics[source_topic] and not numbered[2]):
        errors.append(f"lesson {numbered[0]} also exists in {source_topic.relative_to(ROOT)}; "
                      f"qualify the cross-topic link: {label}")
    return errors


def author_order_errors(catalog):
    """Check the declared learning sequence; original course IDs are independent."""
    sections = {}
    for folder in catalog:
        if "bonus" in folder.parent.relative_to(ROOT).parts:
            sections.setdefault(folder.parent, []).append(folder)
    errors = []
    for section, folders in sections.items():
        guide = section / "README.md"
        visible = prose(guide.read_text(encoding="utf-8-sig")) if guide.is_file() else ""
        # A link-only reference need not declare a section catalog. Runnable
        # lessons, or an explicitly declared index, require the full sequence.
        has_sources = any(list(folder.glob("*.cpp")) + list((folder / "src").glob("*.cpp"))
                          for folder in folders)
        declared = re.search(r"^## Уроки\s*$", visible, re.M)
        if not has_sources and not declared:
            continue
        ordered = sorted(folders, key=lambda folder: catalog[folder][1])
        numbers = [catalog[folder][1] for folder in ordered]
        if numbers != list(range(1, len(ordered) + 1)):
            errors.append(f"{section.relative_to(ROOT)}: author lesson numbers must be consecutive from 01")
        if any(not re.fullmatch(fr"{catalog[folder][1]:02}-.+", folder.name) for folder in folders):
            errors.append(f"{section.relative_to(ROOT)}: author directory names must use NN-topic")
        if not declared:
            errors.append(f"{guide.relative_to(ROOT)}: missing ordered Уроки catalog")
        else:
            body = re.split(r"^## ", visible[declared.end():], maxsplit=1, flags=re.M)[0]
            targets = []
            for _, target in links(body):
                parsed = urlsplit(target)
                if parsed.scheme:
                    continue
                destination = (section / unquote(parsed.path)).resolve()
                folder = destination.parent if destination.name == "README.md" else destination
                if folder in folders:
                    targets.append(folder)
            if targets != ordered:
                errors.append(f"{guide.relative_to(ROOT)}: lesson catalog must match directory order exactly")
        metadata = section / "lessons.json"
        if metadata.exists():
            try:
                items = json.loads(metadata.read_text(encoding="utf-8-sig"))
                expected = [folder.relative_to(ROOT).as_posix() for folder in ordered]
                if [item["folder"] for item in items] != expected:
                    errors.append(f"{metadata.relative_to(ROOT)}: metadata must match directory order exactly")
                for item in items:
                    folder = ROOT / item["folder"]
                    if folder in catalog and item["number"] != catalog[folder][1]:
                        errors.append(f"{metadata.relative_to(ROOT)}: wrong number for {item['folder']}")
            except (ValueError, KeyError, TypeError) as error:
                errors.append(f"{metadata.relative_to(ROOT)}: invalid lesson metadata: {error}")
    return errors


def main():
    paths = list(files())
    markdown = [p for p in paths if p.suffix == ".md"]
    catalog, topics = lesson_catalog(markdown)
    errors = author_order_errors(catalog)
    for folder, (_, number, title) in catalog.items():
        if title and title[0] != number:
            errors.append(f"{(folder / 'README.md').relative_to(ROOT)}: "
                          f"lesson heading number {title[0]} does not match directory {number}")
    lessons = 0
    for path in markdown:
        text = path.read_text(encoding="utf-8-sig")
        visible = prose(text)
        for label, target in links(visible):
            parsed = urlsplit(target)
            if "vscode-resource" in target or "vscode-cdn.net" in target:
                errors.append(f"{path.relative_to(ROOT)}: nonportable webview URL {target}")
            if "команды" in label.lower() and unquote(parsed.fragment) == "требования":
                errors.append(f"{path.relative_to(ROOT)}: commands link points at requirements")
            if re.fullmatch(r"(?:урок|бонус)[а-я]*\s+\d+", label.replace("`", ""), re.I):
                errors.append(f"{path.relative_to(ROOT)}: use a descriptive lesson title")
            if parsed.scheme or target.startswith("//"):
                continue
            destination = (path.parent / unquote(parsed.path)).resolve()
            for error in lesson_link_errors(path, label, destination, catalog, topics):
                errors.append(f"{path.relative_to(ROOT)}: {error}")
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
            local_targets = [unquote(urlsplit(target).path) for _, target in links(visible)
                             if not urlsplit(target).scheme]
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
