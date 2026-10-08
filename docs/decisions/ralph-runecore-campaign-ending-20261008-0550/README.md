# Decisions: `ralph/runecore-campaign-ending-20261008-0550`

- Run: `runecore-boss-telegraphs-20261007-0510`
- Task: `boss-warning-telegraphs`
- Worker: `coordinator`
- Branch: `ralph/runecore-campaign-ending-20261008-0550`
- Base `origin/main`: `c4955d10842e71c70c7732daef9f835bcde80702`
- Rebased onto STATUS sign-out: `d228a00d8a87ca7a8be949d857ea3748e2e58f4c`
- Final rebase onto MERGE sign-in: `f9ca6c805ec40f11ede98e03b0fe51273f315dde`
- Pull request: `NOT_OPENED`
- Implementation commit: `d831a5d37d6db60caad0ce70b46dd14326998354`
- Fast-forward result: `bf3a896f11963345b8b0a67ce076c3b01038e4e0`
- Verified fetched `origin/main`: `a8623784e9f405726f25ee9fab4c6e62367ee5a5`

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

## Integration

- The iteration branch was published without force and fast-forwarded to
  `origin/main` under the repository's active MERGE lease; no pull request was
  opened because the normal integration path is an authorized no-PR
  fast-forward.
- The fetched remote tip `a8623784e9f405726f25ee9fab4c6e62367ee5a5` contains
  both implementation commit `d831a5d37d6db60caad0ce70b46dd14326998354` and
  fast-forward result `bf3a896f11963345b8b0a67ce076c3b01038e4e0`. The lease
  was released and its ownership record is `FREE` at revision 34.
- The iteration's post-merge memory review remains pending alongside the
  reviews for iterations 1-3; the direct playthrough and 9/10 rating gate also
  remain open.
