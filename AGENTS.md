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
