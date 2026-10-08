# Decisions: `ralph/runecore-title-save-resume-successor-20261008-0425`

- Run: `runecore-boss-telegraphs-20261007-0510`
- Task: `boss-warning-telegraphs`
- Worker: `coordinator`
- Branch: `ralph/runecore-title-save-resume-successor-20261008-0425`
- Original iteration base: `7a0d6753e208bc3549c2d9dc20e7bdbad6030e13`
- Successor base before source carry-forward:
  `90c07dd694052254f8ed731f5eb7646b0ddfc8fb`
- Current implementation commit:
  `d9fa3d2ebbbd2773b7f841f718f1ae1663f1e29d`
- Pull request: `NOT_OPENED`

## Decisions

- Preserve the already-published title/save/resume branch when its base became
  stale after the main ownership lease advanced `origin/main`. Carry its
  implementation to this unique successor branch; do not force-push or merge
  the stale tip.
- Use the repository's authorized no-PR fast-forward only after a fresh MERGE
  lease, post-lease verification, and a new sign-off bound to the exact
  successor implementation commit.
- Keep the complete-game gate open. Onboarding, the clear ending, direct
  start-to-finish playtesting, and evidence-based 9/10 rating remain required.
- The prior dedicated Project Memory Update review remains pending due
  Resource Manager capacity; do not replace it with coordinator self-review.
