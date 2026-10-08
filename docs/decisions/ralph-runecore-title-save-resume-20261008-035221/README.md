# Decisions: `ralph/runecore-title-save-resume-20261008-035221`

- Run: `runecore-boss-telegraphs-20261007-0510`
- Task: `boss-warning-telegraphs`
- Branch: `ralph/runecore-title-save-resume-20261008-035221`
- Initial `origin/main`: `3bc7f08e50ca35923a7ccd4309333bab273941ca`
- Effective iteration base after task-scope publication:
  `7a0d6753e208bc3549c2d9dc20e7bdbad6030e13`
- Pull request: `NOT_OPENED`

## Decisions

- Continue the user's explicit complete-game acceptance gate with the next
  unchecked player-facing flow: title, three save slots, new-character class
  and visor selection, and cross-session save/resume.
- Use one isolated coordinator branch because Resource Manager has no free
  slot; do not claim parallel work.
- Keep the direct fast-forward integration path conditional on the existing
  main-ownership lease and a fresh `origin/main` verification. Stop if current
  repository policy no longer permits it.
- Do not assign the requested 9/10 rating. The onboarding, complete-game
  ending, and direct full playtest criteria remain open.
- The prior iteration's required dedicated Project Memory Update review
  remains pending due Resource Manager capacity; do not substitute a
  coordinator self-review or record `NO_UPDATE`.
