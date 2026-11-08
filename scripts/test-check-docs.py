"""Regression checks for lesson links; temporary documents stay inside build/."""
from __future__ import annotations

from contextlib import redirect_stdout
from io import StringIO
import os
from pathlib import Path
from tempfile import TemporaryDirectory
import unittest

ROOT = Path(__file__).resolve().parents[1]
CHECKER_PATH = ROOT / "scripts/check-docs.py"
# The script name contains a hyphen. Loading its source this way creates no bytecode files.
CHECKER = {"__file__": str(CHECKER_PATH), "__name__": "check_docs"}
exec(compile(CHECKER_PATH.read_text(encoding="utf-8"), str(CHECKER_PATH), "exec"), CHECKER)


def link(source, target, label):
    relative = Path(os.path.relpath(target, Path(source).parent)).as_posix()
    return f"[{label}]({relative})\n"


class LessonLinkTests(unittest.TestCase):
    def check_documents(self, documents):
        (ROOT / "build").mkdir(exist_ok=True)
        with TemporaryDirectory(prefix="check-docs-", dir=ROOT / "build") as directory:
            workspace = Path(directory)
            for name, contents in documents.items():
                path = workspace / name
                path.parent.mkdir(parents=True, exist_ok=True)
                path.write_text(contents, encoding="utf-8")
            previous = CHECKER["ROOT"]
            CHECKER["ROOT"] = workspace
            try:
                output = StringIO()
                with redirect_stdout(output):
                    status = CHECKER["main"]()
                return status, output.getvalue()
            finally:
                CHECKER["ROOT"] = previous

    def test_foreign_number_collision_in_every_topic(self):
        for topic in ("basics/additions", "templates/additions", "exceptions/additions", "io/additions",
                      "oop/additions", "stl/additions", "multithreading/additions", "additions/networking",
                      "additions/reflection", "additions/databases/postgresql"):
            with self.subTest(topic=topic):
                source = f"{topic}/dependencies.md"
                foreign = "stl" if topic == "basics/additions" else "basics"
                target = f"{foreign}/lesson-015-other/README.md"
                status, output = self.check_documents({
                    f"{topic}/15-local-topic/README.md": "# 15. Собственная тема\n",
                    target: "# Урок 15. Другая тема\n",
                    source: link(source, target, "«015. Другая тема»"),
                })
                self.assertTrue(status, output)
                self.assertIn("qualify the cross-topic link", output)

    def test_parent_section_also_sees_bonus_numbers(self):
        for source in ("io/README.md", "io/additions/dependencies.md"):
            with self.subTest(source=source):
                target = "basics/lesson-015-do-while/README.md"
                status, output = self.check_documents({
                    "io/additions/15-json/README.md": "# 15. JSON\n",
                    target: "# Урок 15. Цикл do-while\n",
                    source: "JSON требует nlohmann/json: "
                            + link(source, target, "«015. Цикл do-while»"),
                })
                self.assertTrue(status, output)
                self.assertIn("qualify the cross-topic link", output)

    def test_number_must_match_target_directory(self):
        status, output = self.check_documents({
            "io/additions/15-json/README.md": "# 15. JSON\n",
            "io/additions/README.md": "[«16. JSON»](15-json/)\n",
        })
        self.assertTrue(status, output)
        self.assertIn("lesson number 16 does not match target 15", output)

    def test_heading_number_must_match_directory(self):
        status, output = self.check_documents({
            "io/additions/15-json/README.md": "# 16. JSON\n",
        })
        self.assertTrue(status, output)
        self.assertIn("lesson heading number 16 does not match directory 15", output)

    def test_code_identifiers_in_titles_are_preserved(self):
        status, output = self.check_documents({
            "io/additions/21-format/README.md": "# 21. `std::format`\n",
            "io/additions/README.md": "[«21. `std::print`»](21-format/README.md)\n",
        })
        self.assertTrue(status, output)
        self.assertIn("numbered lesson title does not match target heading", output)

    def test_qualified_cross_topic_link_is_allowed(self):
        source = "io/additions/dependencies.md"
        target = "basics/lesson-015-do-while/README.md"
        status, output = self.check_documents({
            "io/additions/15-json/README.md": "# 15. JSON\n",
            target: "# Урок 15. Цикл do-while\n",
            source: link(source, target, "Основы C++: «015. Цикл do-while»"),
        })
        self.assertFalse(status, output)

    def test_qualification_does_not_hide_wrong_numbers_or_titles(self):
        source = "io/additions/dependencies.md"
        target = "basics/lesson-015-do-while/README.md"
        for label in ("Основы C++: «016. Цикл do-while»", "Основы C++: «015. JSON»"):
            with self.subTest(label=label):
                status, output = self.check_documents({
                    "io/additions/15-json/README.md": "# 15. JSON\n",
                    target: "# Урок 15. Цикл do-while\n",
                    source: link(source, target, label),
                })
                self.assertTrue(status, output)
                self.assertNotIn("qualify the cross-topic link", output)

    def test_course_and_bonus_links_share_their_topic(self):
        status, output = self.check_documents({
            "multithreading/lesson-10-unique-lock/README.md": "# 10. `std::unique_lock`\n",
            "multithreading/additions/10-queue/README.md": "# 10. Очередь\n",
            "multithreading/additions/README.md":
                "[«10. `std::unique_lock`»](../lesson-10-unique-lock/)\n",
        })
        self.assertFalse(status, output)

    def test_directory_links_and_source_annotations_are_allowed(self):
        status, output = self.check_documents({
            "basics/additions/02-raii/README.md": "# 02. RAII\n",
            "basics/additions/README.md": "[«2. RAII» — `main3.cpp`](02-raii/)\n",
        })
        self.assertFalse(status, output)

    def test_descriptive_labels_need_no_literal_title(self):
        status, output = self.check_documents({
            "io/additions/15-json/README.md": "# 15. JSON: типы и обязательные поля\n",
            "io/additions/README.md": "[Работа с JSON](15-json/README.md)\n",
        })
        self.assertFalse(status, output)

    def test_brackets_and_operator_symbols_in_code_labels(self):
        for label, should_fail in (("operator[]", False), ("operator()", True)):
            with self.subTest(label=label):
                status, output = self.check_documents({
                    "oop/additions/01-indexing/README.md": "# 01. `operator[]`\n",
                    "oop/additions/README.md": f"[«01. `{label}`»](01-indexing/)\n",
                })
                self.assertEqual(status, should_fail, output)

    def test_links_inside_code_are_ignored(self):
        status, output = self.check_documents({
            "README.md": "`[«15. JSON»](missing/README.md)`\n\n"
                         "```cpp\n[example](also-missing)\n```\n",
        })
        self.assertFalse(status, output)

    def test_author_order_is_consecutive_and_matches_catalog(self):
        status, output = self.check_documents({
            "stl/additions/01-first/README.md": "# 01. Первая тема\n",
            "stl/additions/02-second/README.md": "# 02. Вторая тема\n",
            "stl/additions/README.md": "## Уроки\n\n[Первая](01-first/)\n[Вторая](02-second/)\n",
            "stl/lesson-019-course/README.md": "# 19. Урок курса\n",
        })
        self.assertFalse(status, output)

    def test_author_order_rejects_gaps_and_reversed_catalog(self):
        for number, links in ((3, "[Первая](01-first/)\n[Другая](03-second/)\n"),
                              (2, "[Другая](02-second/)\n[Первая](01-first/)\n")):
            with self.subTest(number=number):
                status, output = self.check_documents({
                    "stl/additions/01-first/README.md": "# 01. Первая тема\n",
                    f"stl/additions/{number:02}-second/README.md": f"# {number:02}. Другая тема\n",
                    "stl/additions/README.md": "## Уроки\n\n" + links,
                })
                self.assertTrue(status, output)
                self.assertIn("consecutive from 01" if number == 3 else "match directory order", output)

    def test_author_order_rejects_stale_metadata(self):
        status, output = self.check_documents({
            "stl/additions/01-first/README.md": "# 01. Первая тема\n",
            "stl/additions/README.md": "## Уроки\n\n[Первая](01-first/)\n",
            "stl/additions/lessons.json": '[{"folder":"stl/additions/01-first","number":9}]',
        })
        self.assertTrue(status, output)
        self.assertIn("wrong number", output)


if __name__ == "__main__":
    unittest.main()
