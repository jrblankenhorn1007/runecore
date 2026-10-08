# TODO Execution Checklist

This is the executable order derived from `TODO.md`. Each item must have a focused `test_<workflow>` process or a mirrored unit test before it is marked complete.

## 1. Combat Feedback
- [x] `fct`: add typed combat text colors for physical, elemental, critical, healing, and XP events; verify fade, upward drift, and gravity in `test_feedback`.
- [x] `death_fx`: defer enemy removal for a short death animation with family-specific squash/stretch; verify entity lifecycle in `test_melee`.
- [x] `weapon_visuals`: draw equipped weapon rotation and attack/recoil states; verify aim and attack state in `test_melee` and `test_projectile`.
- [x] `boss_telegraphs`: add one-second expanding warning rings and player-directed red danger lanes, enrage hazards, summons, and defeat loot burst; verify AI/render behavior and `test_boss`.

## 2. GUI Workflows
- [x] `inventory_drag`: finish mouse drag/drop, paperdoll labels, rarity tooltips, and consumable feedback; verify through game-launched clicks.
- [x] `crafting_gui`: add category tabs, craftable-only filter, recipe requirements, and click-to-craft; verify in `test_crafting`.
- [x] `augmentations_gui`: add 11-slot body doll, humanity/power meters, and install confirmation; verify in `test_ui`.
- [x] `character_sheet`: add derived stats and full attribute previews; verify in `test_ui`.
- [x] `skill_tree`: add graph edges, hover details, confirmation, and respec; verify in `test_ui`.

## 3. Enemies and World Presentation
- [x] `enemy_roster`: implement the remaining slime, harpy, raptor, gunner, and carapace behaviors; verify each family in isolated scenarios.
- [x] `parallax`: add four scrolling background layers and biome theme selection; verify with renderer tests.
- [x] `weather_particles`: add biome weather particles; verify in a fresh simulation/render test.
- [x] `sky_transitions`: add dynamic sky color transitions driven by day/night state.
- [x] `tile_palette`: add autotile accents and slope collision/rendering; verify in world interaction tests.

## 4. Exploration and Settlement
- [x] `dungeon_props`: add chests, keycards, levers, and traps; verify with `test_dungeon` sub-scenarios.
- [x] `map_fog`: add fog-of-war state and map icons; verify in `test_dungeon`.
- [x] `building_tools`: differentiate pickaxe/axe/hammer and add placement ghost; verify in `test_mining`.
- [x] `npc_services`: add recruited blacksmith, surgeon, alchemist, and guide service interactions; verify in `test_settlement`.

## 5. Audio and Persistence
- [x] `audio_scenes`: add movement, mining, environment, and dynamic combat music states; verify in `test_AudioEngine` and game-launched scenarios.
- [x] `audio_boot`: keep normal windowed gameplay on the SDL playback device while retaining headless audio for QA and benchmark runs.
- [ ] `settings`: finish video toggles, music/ambience persistence, and control rebinding; verify in `test_settings`.
- [ ] `character_creation`: add title screen, three save slots, class selection, and visor color; verify in `test_character_creation`.
- [ ] `respawn`: add death overlay, recovery drone/drop materials, and bed/clinic spawn selection; verify in `test_respawn`.

## 6. Playable Complete-Game Acceptance (User Target: 9/10)
- [x] `interactive_launch`: default startup is player-controlled and indefinite; automated bot, timed, and scripted QA modes are opt-in.
- [x] `pause_resume`: Escape pauses simulation and suppresses gameplay input until settings closes; verify with simulation and launch tests.
- [ ] `save_resume`: title flow selects a save slot, loads existing progress, and saves changes across sessions.
- [ ] `new_player_onboarding`: explain the immediate objective and essential controls in-game.
- [ ] `complete_game_loop`: manually play a fresh character from start through progression and final boss victory with a clear ending.
- [ ] `release_playtest_and_rating`: conduct and record a direct end-to-end playable build assessment; rate the complete game at least 9/10 only when supported by that playtest. Test coverage and scripted captures alone are insufficient evidence.

## Execution Rule
After each item: update this checklist, update `TODO.md`, run the focused test, then continue to the next unchecked item. A passing test is a checkpoint, not the end of the work.
