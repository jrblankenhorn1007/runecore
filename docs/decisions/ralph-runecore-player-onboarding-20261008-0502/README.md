# Decisions: `ralph/runecore-player-onboarding-20261008-0502`

- Run: `runecore-boss-telegraphs-20261007-0510`
- Task: `boss-warning-telegraphs`
- Worker: `coordinator`
- Branch: `ralph/runecore-player-onboarding-20261008-0502`
- Base `origin/main`: `c72c8c2484ddcb456e809af506ad33d3a6baad8a`
- Rebased onto STATUS sign-out: `5607ad0541a7a97fe5aa7b8e6a183c6dc267385d`
- Rebased onto MERGE sign-in: `f28f6b75005e7658384d2127782557c3f0c373b2`
- Implementation commit: `e146bea8e78dd02ab0c07498eac28e32002818d7`
- Pull request: `NOT_OPENED`

## Decisions

- Advance the explicit `new_player_onboarding` acceptance item rather than
  expanding already-implemented systems. The onboarding must appear in the
  game world, explain an actionable first objective and correct controls, and
  keep simulation/gameplay input paused until the player continues.
- Persist onboarding completion so an unfinished briefing reappears on resume,
  while completed characters are not interrupted on later sessions.
- Keep the complete-game 9/10 gate open. A clear ending and direct
  start-to-finish playtest remain unverified.
- Preserve the dedicated post-merge memory-review blocker for iterations 1
  and 2. Continue serially because Resource Manager has no available slot;
  do not substitute coordinator self-review.
- The pre-reservation implementation commit was rebased without conflicts
  onto the authorized MERGE sign-in commit; the four focused headless tests
  passed again on the exact implementation SHA.
