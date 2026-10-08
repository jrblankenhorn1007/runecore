# Progress Log

## 2026-10-08 - Iteration 2 kickoff

- Selected the remaining player-facing title and persistence criteria:
  three-slot selection, new-character class/visor selection, and resuming
  meaningful saved progress across sessions.
- The project already has checksummed, atomic three-slot serialization, but
  ordinary launch bypasses it and the current exit save hard-codes slot 1 in
  the working directory.
- Acceptance remains broader than this increment: onboarding, a complete
  start-to-final-boss ending, and direct end-to-end playtesting are still
  required before any 9/10 rating.
- Resource Manager inventory: 3 active sessions, 2-agent maximum, 0 available
  slots. No worker was launched; this iteration is proceeding serially.
- Initial fetched `origin/main`: `3bc7f08e50ca35923a7ccd4309333bab273941ca`.
- Scope revision 5 was published before implementation edits:
  status commit `c773f203b301a7c6ec7333ea7db92f31103f5d69`, with STATUS lease
  sign-in `ae433e158a003e4fafd2fc3f77a141c54eca07fb` and sign-out
  `7a0d6753e208bc3549c2d9dc20e7bdbad6030e13`.
- Fresh branch `ralph/runecore-title-save-resume-20261008-035221` and worktree
  `/Users/jrblankenhorn/Documents/runecore.worktrees/ralph-runecore-title-save-resume-20261008-035221`
  start at the verified post-status `origin/main` SHA
  `7a0d6753e208bc3549c2d9dc20e7bdbad6030e13`.
- The headless new-character save regression was added first and recorded its
  expected Red before game-source changes.

## TDD Red - New character save slot

- Added a headless launch regression that chooses an empty slot, selects the
  Berserker class, and expects the interactive session to persist that
  character to the configured save directory.
- Command:
  `SDL_VIDEODRIVER=dummy SDL_AUDIODRIVER=dummy ./build/test_MainRunner 'MainRunner Headless and CLI Argument Variations' -c 'Interactive title flow creates and saves the selected character'`
  — **EXPECTED FAIL** at `slotSaved`; normal launch currently writes a
  hard-coded Juggernaut save to the working directory and never creates the
  selected save slot. The failing assertion is the missing requested
  behavior, not a build, SDL, or test-runner failure.
- Setup:
  `cmake -S . -B build -G Ninja` and
  `cmake --build build --target test_MainRunner -j 4` — **PASS**.
- No production source has been changed yet.

## Implementation and Green verification

- Added a keyboard-driven title screen for three save slots, new-character
  class and visor selection, existing-save resume, and corrupt-save feedback.
- New sessions save the selected character immediately, autosave every 30
  seconds, and save again on exit. The save directory uses the SDL
  application-preferences location by default and `RUNECORE_SAVE_DIR` for
  isolated tests.
- Save snapshots now preserve and restore character identity/appearance,
  progression, attributes, vitals, position/dungeon state, inventory,
  equipment, survival state, and audio levels.
- Extended the headless default-launch test to navigate the title screen,
  enter gameplay, and verify the session persists its save slot.
- Added a headless cross-session resume scenario that selects slot 2 and
  verifies the resumed character's level, XP, attributes, position, inventory,
  and equipped item survive the session.
- Initial build exposed a Catch2 assertion-macro parse error in the visor-color
  disjunction. Parenthesizing the expression resolved the test compilation
  error; no production fallback was introduced.
- The first focused CTest run then found the pre-existing default-launch test
  assumed gameplay started immediately. Updated its scripted input to use the
  title flow before asserting gameplay control and save creation.
- Focused Green command:
  `cmake --build build --target test_MainRunner test_GameSimulation test_SaveManager test_TitleFlow test_Renderer untitled_rpg -j 4 && ctest --test-dir build -R '^(test_MainRunner|test_GameSimulation|test_SaveManager|test_TitleFlow|test_Renderer)$' --output-on-failure`
  — **PASS**, all 5 focused headless CTest targets passed (31.18 seconds).
- Isolated resume integration command:
  `SDL_VIDEODRIVER=dummy SDL_AUDIODRIVER=dummy ./build/test_MainRunner 'MainRunner Headless and CLI Argument Variations' -c 'Interactive title flow resumes progress from the selected save slot'`
  — **PASS**, 21 assertions in 1 test case.
- Full build and headless regression command:
  `cmake --build build -j 4 && ctest --test-dir build --output-on-failure`
  — **PASS**, full build succeeded and all 88/88 CTest targets passed in
  43.59 seconds.
- `git diff --check` — **PASS**.
- Test environment uses SDL dummy video and audio; no interactive unit-test
  window is opened. No full-game playtest or 9/10 rating has been claimed.

## Remaining acceptance and iteration status

- This iteration's title, character creation (class/visor selection), and
  save/resume checklist items are verified. The detailed production roadmap
  still requires custom character naming and save-slot playtime display.
- New-player onboarding, a fully winnable start-to-ending loop, and direct
  complete-game playtesting remain open. The requested 9/10 rating remains
  gated on that playtest.
- The run remains blocked on the prior iteration's required dedicated Project
  Memory Update review; Resource Manager had no free worker slot at kickoff.
- At the time this section was first recorded, implementation was not yet
  committed, published, integrated, or verified on remote `main`.

## Implementation sign-off

- Implementation commit:
  `f32c6247e45a2e90aaaf07988f2ff9f9de2cc4aa` (`feat: add title and
  save-resume flow`).
- The full 88/88 CTest suite and the targeted headless tests all passed before
  this documentation-only sign-off update. `git diff --check` passed for the
  staged implementation commit.
- **SELF_ATTESTATION:** I, coordinator, sign off iteration 2 at the exact
  implementation commit above. This statement is not cryptographically signed.
- Branch status is now `AWAITING_MERGE`; the implementation has not yet been
  published or integrated.
