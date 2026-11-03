# Repository instructions

## Questions are read-only

If the user's latest message contains a question, treat the entire turn as
read-only. A question includes a question mark or wording that asks for an
explanation, diagnosis, opinion, confirmation, or recommendation.

- Do not create, edit, delete, format, stage, or commit files.
- Do not run commands that may modify generated files or the working tree.
- Inspect the repository and answer the question using read-only commands only.
- Make changes only after a later user message explicitly requests the change
  and contains no question.

## Short Git commands

Treat the following words as direct authorization to run the corresponding
Git command immediately, without asking for confirmation or adding preliminary
explanation:

- If the user's message is `commit` or `коммит`, stage all current repository
  changes and create a commit using the most recent commit title suggested by
  the assistant in the current conversation.
- If the message starts with `commit ` or `коммит ` followed by a title, stage
  all current repository changes and create the commit using that supplied
  title instead of the previously suggested title.
- If the user's message is `push` or `пуш`, run `git push`.
- If the user's message is `pull` or `пул`, run `git pull`.

Match these command words case-insensitively after trimming surrounding
whitespace. After running one of these commands, reply only with its concise
result. If the requested operation cannot be completed, reply only with the
blocking error or condition.

## Commit title suggestion

After completing a turn that changes code, inspect the repository's current
state with `git status --short`, `git diff`, `git diff --cached`, and recent
subjects from `git log`. Inspect relevant untracked files as well.

At the end of the final response, provide one aggregate commit title. Put the
label outside the code block so copying the block copies only the title:

Suggested commit title:

```text
<title>
```

Requirements:

- Write the title in English.
- Describe only the current unstaged, staged, and untracked changes relative
  to `HEAD`, including changes left uncommitted from earlier turns.
- Do not include work that is already present in `HEAD`, even when that work
  was performed earlier in the same conversation.
- Compare the proposed title with recent subjects from `git log`. If an exact
  or similar title already exists, re-check the diff and describe only the
  remaining follow-up change.
- Follow the style of recent commit subjects from `git log`.
- Use the repository's existing scopes, such as `fw:`, `ui:`, `fw/ui:`,
  `docs:`, `test:`, or `build:`.
- Use concise descriptive wording consistent with recent commits.
- Keep the complete title at 72 characters or fewer.
- Do not create the commit unless the user explicitly requests it.
- Omit the title when there are no uncommitted changes.

## Self-contained lesson explanations

Keep lesson documentation and code comments self-contained. Do not mention
the user's other projects, repositories, their internal class names, or local
paths as sources of inspiration or comparisons unless explicitly requested.
Describe reused techniques generically without references to unrelated projects.

## README quality for the reference project

Treat this repository as a self-contained learning and reference project.
Write lesson explanations in clear Russian for a reader learning the topic.

- Provide a README for every lesson and standalone example; section READMEs
  should give a learning order and links, rather than replace lesson explanations.
- Inspect the actual source and every independent main variant before documenting
  them. Distinguish current code from additional illustrative snippets.
- Explain the purpose, prerequisites, key syntax and execution step by step:
  what happens, when it happens, why it is needed, and what changes if omitted
  or replaced by a commonly confused alternative.
- Show small concrete examples and explain their results. Cover ordering,
  lifetimes, ownership, synchronization, errors and cleanup when relevant.
- Explain common API variants and useful rare cases, limitations, invalid
  operations, version requirements and typical mistakes. Define unfamiliar terms.
- Include reproducible build/run guidance or a precise local setup link. Identify
  interactive input, required files/services, generated data and nontermination.
- Keep explanations concise but sufficiently complete to use without opening
  another reference. Avoid repetitive filler and arbitrary length targets.
  External primary-source links supplement the explanation, not replace it.
- Preserve accurate explanations and expand genuine gaps. Check claims, local
  links and commands against the source and current build scripts. Never claim
  execution or platform verification that was not performed.

## SimpleCode course material and bonus additions

- Keep SimpleCode course examples with their original lesson directory names,
  numbering and variants. An explicitly requested thematic reorganization may
  move a whole lesson to another section; update all links and build metadata.
  A file name such as main2.cpp does
  not establish whether a program belongs to the course; inspect its origin.
- Place all new educational examples and scenarios outside the course in the
  relevant section's bonus directory, even when they extend an existing topic.
  This includes additional main*.cpp files and new demonstration blocks in a
  course main.cpp. Entire new subject areas belong under the root bonus/.
- Course lesson directories may contain documentation clarifications,
  correctness/build/portability fixes and links to bonus examples. Do not mix
  new teaching scenarios into their source files just to avoid a new directory.
- When importing missing course examples, inspect the actual referenced code
  and pin its commit. Preserve its demonstrations, values and call order; do
  not present an independently written implementation of a topic as restored
  source material. Document concrete correctness/portability changes in each
  README and keep a reviewable comparison with the source. If extracting a
  combined file, state which fragment is used and which parts are omitted.
- Reuse an existing bonus lesson when the topic fits; otherwise create a
  numbered bonus lesson without renumbering the original course. Add its README,
  Windows/Linux VS Code configurations, catalog links and required build markers.
- The bonus placement rule takes precedence over the preference for runnable
  documentation snippets. Link to existing code before adding a duplicate.

## Proofreading and shared console setup

- Review imported comments, headings and displayed text; do not copy spelling
  mistakes, misleading explanations, empty topic headings or decorative end
  markers. Keep educational explanations in Russian and translate Ukrainian
  messages in the adapted programs. Preserve the exact external source only
  in provenance records used to compare adaptations.
- Use at most one consecutive blank line in ordinary source code. Do not leave
  an empty line before a closing brace or print a final empty line merely to
  accompany an end marker. Preserve significant whitespace in string literals,
  embedded data and multiline macros.
- Share ordinary Windows UTF-8 console setup through `common/console.hpp` and
  keep the function in `namespace console`. Call `console::setupConsoleEncoding()`
  explicitly; do not add `using namespace console`. Do not duplicate its Windows
  API implementation in lesson files. Use a relative include appropriate to
  the source location.
  Keep specialized demonstrations of wide streams or console modes separate.

## C++ include order and direct dependencies

- Apply this convention to all teaching `.cpp` files and helper headers,
  including `_template/`. Keep feature-version comments first and preserve
  header guards, conditional branches and comments explaining dependencies.
- Order ordinary include groups as follows: the implementation's matching
  header (when present, such as `SimpleTimer.hpp` in `SimpleTimer.cpp`);
  standard C/C++ headers; third-party and platform headers; other project headers.
  A helper included by `main.cpp` is not its matching implementation header.
- Separate nonempty groups with exactly one blank line. Within a group sort
  case-sensitively by the complete header path, without the quotes or brackets.
  Keep `common/console.hpp` with other project headers, not in a separate group.
- Include the header declaring each standard-library facility used by the file
  directly. For example, include `<chrono>` for `std::chrono`, `<utility>` for
  `std::move`, and `<string>` for `std::string`; do not depend on incidental
  includes of another lesson's helper. Headers must include their own dependencies.
- Correct platform setup takes precedence over sorting. Keep required feature
  macros and Windows/WinSock setup before the headers they configure. In Asio
  examples keep `common/boost_net.hpp` as an explicitly commented platform
  preamble before Boost and `common/console.hpp`; inside `boost_net.hpp` keep
  `net.hpp` before Boost. Preserve the WinSock/POSIX conditional preamble in
  `net.hpp`. Separate such a preamble from ordinary includes by one blank line.
- Never move includes across conditional branches or configuration macros just
  to obtain alphabetical order. Document any required ordering exception beside
  the affected block. These are project conventions, not language requirements.

## Explanations, runnable examples and Markdown

- Explain a mechanism through a small concrete example and the order of events
  before introducing abstract terminology. Define terms such as shared state,
  ownership and readiness; do not replace an explanation with a dense summary.
- For every substantive API example, link to existing runnable code or provide
  a runnable source in the appropriate bonus lesson (main2.cpp, main3.cpp, etc.).
  Prefer a separate focused program for a distinct behavior, subject to the
  course/bonus separation rule above.
- Link C++ snippets to their full source. Label omitted surrounding code,
  deliberately invalid examples and pseudocode explicitly. Keep snippets and
  the actual source consistent; do not add duplicate programs just for renaming.
- Document each program's input, expected output/allowed variation and exit
  status. Demonstrations of failure must identify the expected failure clearly.
  Test concurrent examples using synchronization, not assumed scheduling delays.
- Format identifiers, types, functions, expressions, headers and file names in
  prose as inline code, for example `std::thread`, `std::future<T>`, `join()`,
  `worker.request_stop()`, `<future>` and `main.cpp`. Preserve Markdown links
  and fenced code; apply this consistently throughout all README files.
- Explain F5 (debugging) and Ctrl+F5 (without debugging) in the root setup guide.
  Ordinary lesson READMEs may link directly to that guide without repeating the
  same sentence. Keep lesson-specific source, arguments, input, services,
  expected output and nontermination instructions in the lesson itself.
- When revisiting documentation across the project, check runnable coverage,
  explanation clarity, code formatting and launch instructions together.

## Runnable API coverage and meaningful links

- A substantive explanation of an API or behavior needs a linked runnable
  example. Merely naming an API in a README does not demonstrate it in code.
  Audit prose as well as fenced snippets, and inspect all main variants and
  relevant helper headers before claiming coverage.
- For a distinct mechanism, add main2.cpp/main3.cpp in the appropriate bonus,
  or link to an existing example. A short cross-reference may point to another
  lesson without duplicating its program. Deliberately invalid operations must
  be labelled; never execute UB just to tick a coverage box.
- During whole-project audits record uncovered behaviors and resolve genuine
  teaching gaps. Automated token matching supplies candidates for review, not
  proof of semantic coverage. Do not claim that all of C++ is covered.
- Refer to lessons by descriptive title and a link. A number may supplement
  the title but must not be the only navigation clue (including prose such as
  "lesson 10"). Link to the section that actually answers the stated question:
  requirements, terminal commands and VS Code launch are different targets.
- Resolve numbers within the current topic. Networking, PostgreSQL, reflection,
  STL and multithreading have independent numbering; never map their "lesson 10"
  to basics solely by its number. Qualify intentional cross-topic references.
- Store portable relative Markdown links in repository files. Do not copy
  file+.vscode-resource/vscode-cdn webview URLs into source documentation.

## Consistent reference layout and language versions

- Root READMEs describe the project's purpose, authorship, setup and navigation.
  Section READMEs give prerequisites, learning order and links. Lesson READMEs
  use: title; Language version; Purpose and prerequisites; Examples; Explanation;
  Build and run; Common mistakes; Related lessons and sources. Omit an empty
  section or combine closely related sections; do not pad a short lesson.
- Use Russian section names consistently: «Версия C++», «Что изучаем»,
  «Примеры», «Как это работает», «Сборка и запуск», «Типичные ошибки»,
  «Связанные темы и источники». Keep the title free of version suffixes.
- Separate feature introduction from the project's build mode. For example,
  jthread was introduced in C++20; a program built with C++23 still uses that
  C++20 feature. Identify different versions for different APIs in one lesson.
  Design guidelines such as the rule of three are not language features with
  a standardization date. Mark experimental and compiler-specific facilities.
- Start each teaching C++ source and helper header, before includes or include
  guards, with feature-version comments in the form
  `// C++98 — шаблоны функций; C++17 — std::string_view.`
  Split a long list into lines using the same `// C++NN — ...` format. Name the
  main mechanisms demonstrated and features that raise the required standard;
  do not replace them with generic wording or a catalog of incidental APIs.
  Keep build mode, source links and concrete portability changes in the README.
  A nearby version comment may clarify an individual API using the same format.
  Mark experimental or compiler-specific features explicitly. Do not imply
  that every feature in a C++17 build is C++17.
- Explain concurrency with an order of events and concrete variables before
  terms such as ownership, readiness or synchronization. Explain automatic
  destructor actions, blocking, joinable state and scope boundaries explicitly.
- Link related lessons by descriptive title and path, never by number alone.
  Use primary sources for exact contracts; explain that eel.is/c++draft is an
  HTML working draft, not a beginner tutorial or the published ISO standard.
- Keep _template/ as the visible lesson scaffold. Use root .local/ for private
  notes, prompts and local service data; ignore the whole directory. Use build/
  for generated executables and verification output. Never inspect or modify
  private service data merely while auditing teaching material.
