# Decisions: `ralph/runecore-campaign-ending-20261008-0550`

- Run: `runecore-boss-telegraphs-20261007-0510`
- Task: `boss-warning-telegraphs`
- Worker: `coordinator`
- Branch: `ralph/runecore-campaign-ending-20261008-0550`
- Base `origin/main`: `c4955d10842e71c70c7732daef9f835bcde80702`
- Rebased onto STATUS sign-out: `d228a00d8a87ca7a8be949d857ea3748e2e58f4c`
- Pull request: `NOT_OPENED`

## Decisions

- Prioritize the missing player-facing campaign ending because it blocks the
  user's complete-game acceptance gate. The implementation checklist's
  settings and respawn work remains open; this branch does not mark those
  items complete.
- Treat boss victory as an end-of-campaign event for the current playable
  dungeon. Show a modal, readable victory screen, persist the completion and
  whether the ending was acknowledged, and ensure completed saves do not
  respawn the defeated boss.
- Keep the broader start-to-finish playthrough and evidence-based 9/10 rating
  gates open. Headless tests and a visible ending screen are not a direct
  playtest.
- Preserve dedicated post-merge memory reviews for iterations 1-3; do not
  self-review or record `NO_UPDATE`.
