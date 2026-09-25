# Runecore Game-Completion Ralph Loop

Use this file as the project-specific kickoff prompt and runbook for bounded
Ralph Loop work on Runecore. The goal is to finish verified, player-facing
work from the current game-completion backlog without reimplementing features
that already exist or treating old plan boxes as current status.

## Mission and scope

You are the Ralph Loop coordinator or an assigned worker for Runecore, a
C++20/SDL3 sidescrolling action RPG. Each dispatch performs **exactly one
bounded, independently verifiable game-completion iteration**. Select one
unchecked leaf task from Section 5 of [`TODO.md`](../TODO.md), or one smaller
vertical slice of that task when it is too broad. Do not bundle unrelated
items or start another backlog item in the same dispatch.

Use these sources carefully:

- The unchecked **leaf tasks** in Section 5 of `TODO.md` are the candidate
  backlog for this game-completion run. An unchecked child is still open even
  when its parent is checked.
- [`TODO_EXECUTION.md`](../TODO_EXECUTION.md) is the completed baseline
  checklist, not the live backlog. Its checked items are useful context, but
  they are not proof that current source behavior or tests still pass.
- Section 12 of [`PLAN.md`](../PLAN.md) is historical design and
  implementation planning. Its phase boxes are not current status and are
  not an executable backlog.
- [`README.md`](../README.md) and [`CMakeLists.txt`](../CMakeLists.txt)
  describe the project and currently registered build/test workflows.

Some Section 5 descriptions overlap features recorded as complete in the
baseline checklist. Do not infer that an unchecked task is missing—or that a
checked baseline entry makes it done—without checking current source and test
evidence.

## Relevant skills

There is no project-local `.github/skills/` catalog in the current project
checkout. Use these canonical Copilot skills; the file paths exist in the
`jrblankenhorn1007/copilot_skills` repository:

- [Ralph Loop](https://github.com/jrblankenhorn1007/copilot_skills/blob/main/.github/skills/ralph-loop/SKILL.md)
  — applies to every dispatch: refresh instructions, establish a fresh
  worktree, keep branch-scoped status and decision records, verify integration,
  and stop at the iteration boundary.
- [Test-Driven Development (TDD)](https://github.com/jrblankenhorn1007/copilot_skills/blob/main/.github/skills/tdd/SKILL.md)
  — required before gameplay or other behavior-changing code: write and run a
  focused failing test, implement to Green, then refactor with targeted tests
  passing. Do not invent Red/Green phases for documentation-only work.
- [Project Memory](https://github.com/jrblankenhorn1007/copilot_skills/blob/main/.github/skills/project-memory/SKILL.md)
  — applies after the implementation merge is verified on fetched
  `origin/main`: review for durable lessons, integrate any warranted memory
  update through a fresh branch, and verify that merge. In an orchestrated run,
  the coordinator owns shared memory and records a no-new-lesson outcome when
  appropriate.

## One-dispatch workflow

1. **Refresh instructions and inspect state.** At the start of every
   iteration, identify the canonical skills checkout and the clean, attached
   project integration worktree from their Git remotes. Pull each primary
   integration worktree with `git pull --ff-only` (once if they are the same
   repository), never pull in a dirty or feature worktree, then reopen the
   current Ralph Loop skill, applicable skills, project instructions, and this
   runbook. Stop and report if a safe refresh is not possible. Read the
   current plan, relevant status/progress/decision records, and memory index
   and categories if present.
2. **Verify one candidate before coding.** Inspect the relevant current
   implementation in `src/`, the registered tests in `tests/` and
   `CMakeLists.txt`, and any applicable QA scenario. Run the closest existing
   test against the current source before changing behavior. Establish what
   the game actually does now; checklist text alone is not evidence.
3. **Bound the work.** Choose one observable behavior from that candidate.
   If a roadmap leaf describes several separable features, implement only the
   smallest coherent slice and leave the unfinished work unchecked. If the
   candidate is already implemented, verify it with a relevant passing test
   (add focused coverage first if the behavior lacks it), then update only the
   corresponding `TODO.md` tracking after the evidence exists. Do not flip
   boxes based on assumptions, a parent checkbox, or `TODO_EXECUTION.md`.
   Keep unverifiable or obsolete-looking items open and ask for direction
   rather than claiming completion.
4. **Use an isolated Git iteration.** Verify
   `git var GIT_AUTHOR_IDENT` and `git var GIT_COMMITTER_IDENT`, fetch `origin`,
   confirm `origin/main` and a clean integration worktree, and record the full
   base SHA. Create a fresh, unique worktree and branch from the latest
   `origin/main` before editing, for example:
   `git worktree add -b <unique-branch> <unique-worktree-path> origin/main`.
   Never work directly on shared `main`, reuse another task's worktree, or
   overwrite another worker's scope.
5. **Apply TDD and project conventions.** For behavior changes, use
   Red-Green-Refactor: the Red result must be caused by the missing or
   incorrect behavior, not a setup failure; implement minimally; then refactor
   while targeted checks stay green. Preserve existing behavior and tests.
   For documentation-only work, run documentation checks without fabricating
   a behavior-test failure.
6. **Verify and record evidence.** Run the narrowest relevant focused test
   after the change, then run the headless suite below before integration when
   practical. GUI work should also use the relevant `--visual-qa` scenario
   and/or manual in-game verification when applicable; record any platform or
   environment gap. Inspect every failure and the resulting diff. A test
   launched in the background is not complete until its exit status is
   checked and failures in its log are inspected.
7. **Commit and integrate normally.** Before publishing, fetch `origin`
   again. If `origin/main` advanced, rebase the iteration onto it, inspect
   the diff, rerun targeted checks, and update the recorded base and
   implementation SHAs. Commit with the repository's style and include
   `Co-authored-by: Copilot <223556219+Copilot@users.noreply.github.com>`.
   Publish using existing authentication and the normal pull-request process;
   do not use a browser for GitHub operations or write directly to `main`.
   In a multi-agent run, the worker opens its PR and remains
   `AWAITING_MERGE` until the coordinator authorizes the worker-owned merge.
   If PR tooling is unavailable, preserve the branch, record `NOT_OPENED` and
   the blocker, and report it.
8. **Verify merge and review memory.** Fetch `origin` after the authorized
   merge and verify the resulting merge SHA is reachable from `origin/main`.
   Then perform the Project Memory review; complete any warranted memory-only
   follow-up on a fresh branch and verify its merge too. A pushed branch or
   open PR is not a completed iteration.

## Build and headless test checks

From the repository root, configure and build when needed:

```sh
cmake -S . -B build -G Ninja
cmake --build build
```

For the current headless CTest suite, use this direct command:

```sh
SDL_VIDEODRIVER=dummy SDL_AUDIODRIVER=dummy ctest --test-dir build --quiet --output-log build/ctest.log
```

Use a focused registered CTest target (for example,
`ctest --test-dir build --quiet --output-log build/ctest.log -R '^test_<scenario>$'`)
or run the corresponding fresh-simulation scenario directly with
`./build/untitled_rpg --qa <scenario>`. For a relevant GUI scenario, the
README documents `./build/untitled_rpg --visual-qa <scenario>`.

Check the command's final exit status. Because the headless command writes
CTest output to `build/ctest.log` and runs quietly, inspect that log whenever
the command fails; do not report a backgrounded run as passed until it exits
and its failures have been inspected.

## Status and decision records

This project currently has no Ralph runner, status snapshot, progress history,
decision log, or project-memory index. Use an agent-managed run and keep
records in the repository:

- The coordinator owns the aggregate `docs/ralph-status.md`; workers must not
  edit it. The first coordinator initializes it and indexes every branch/agent
  leaf.
- Each worker updates only its own
  `docs/ralph/<branch-slug>/agents/<worker-id>/status.md` and
  `progress.md`. Derive `branch-slug` by lowercasing the exact branch and
  replacing `/` with `-`. Keep current status, next action, blockers, checks,
  merge/memory state, and the exact implementation SHA in `status.md`.
  Append dated iteration evidence to `progress.md`, including exact
  verification commands/results and platform gaps. Do not fabricate TDD
  phases for documentation-only work.
- Keep branch decisions under `docs/decisions/<branch-slug>/README.md` and
  `agents/<worker-id>/pr-<number>.md`. Use `pr-pending.md` while a PR number
  is pending, or `pr-not-opened.md` when no PR was opened; record the reason.
  Never put credentials or secret-bearing output in these records.
- Use `IN_PROGRESS` while implementing, `AWAITING_MERGE` after sign-off when a
  PR is open, and `BLOCKED` when an unresolved external issue prevents
  progress. A worker becomes `COMPLETE` only after the coordinator verifies
  the remote merge and completes the required memory review.

## Stop and completion conditions

Stop this dispatch after its one assigned bounded task is verified and handed
off for integration, or as soon as an unresolved blocker prevents safe
progress. Do not continue to a second backlog item on the same branch. Keep
the task's checkbox open until current source and relevant passing test
evidence justify closing it; never mark an unverifiable task complete.

The game-completion run is complete only when every Section 5 unchecked leaf
has been implemented or verified against current behavior, the corresponding
tracking is supported by relevant test evidence, all required checks pass,
all implementation and any memory follow-up merges are verified on fetched
`origin/main`, and the post-merge memory review is recorded. Otherwise the
coordinator records `IN_PROGRESS` or `BLOCKED` and may schedule another
**fresh** one-iteration dispatch. Do not report overall game completion just
because a parent task is checked, a branch was pushed, or a PR was opened.
