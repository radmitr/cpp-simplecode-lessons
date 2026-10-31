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

- Keep SimpleCode course examples in their original lesson directories with
  their original numbering and variants. A file name such as main2.cpp does
  not establish whether a program belongs to the course; inspect its origin.
- Place all new educational examples and scenarios outside the course in the
  relevant section's bonus directory, even when they extend an existing topic.
  This includes additional main*.cpp files and new demonstration blocks in a
  course main.cpp. Entire new subject areas belong under the root bonus/.
- Course lesson directories may contain documentation clarifications,
  correctness/build/portability fixes and links to bonus examples. Do not mix
  new teaching scenarios into their source files just to avoid a new directory.
- Reuse an existing bonus lesson when the topic fits; otherwise create a
  numbered bonus lesson without renumbering the original course. Add its README,
  Windows/Linux VS Code configurations, catalog links and required build markers.
- The bonus placement rule takes precedence over the preference for runnable
  documentation snippets. Link to existing code before adding a duplicate.

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
- For ordinary VS Code examples mention both F5 (debugging) and Ctrl+F5
  (without debugging). Explain special launch requirements when they differ.
- When revisiting documentation across the project, check runnable coverage,
  explanation clarity, code formatting and launch instructions together.
