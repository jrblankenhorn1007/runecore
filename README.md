# Runecore

Runecore is a 2D pixel-art action RPG where ancient fantasy collides with fallen science. Explore a procedurally generated world, fight through biome-specific dungeons, build and defend a settlement, and reshape your character with bionic and magitech augmentations.

The game is being developed as a single-player experience with a simulation architecture that can support a future client/server split.

## Current Status

Runecore is in active development. The engine, gameplay systems, content specifications, and automated test suites are evolving together. Some systems described in the design documentation are planned rather than complete.

## Highlights

- Fast 2D sidescrolling combat with melee, ranged, energy, and magical weapons.
- Nine character classes with class-specific progression and cross-class mastery.
- Eleven augmentation slots with separate bionic and magitech tradeoffs.
- Survival systems including hunger, thirst, temperature, farming, and settlement building.
- Procedural biomes, dungeons, loot, crafting, and an uncapped endgame.
- No permadeath: equipped gear and augmentations persist after defeat.
- C++20 engine built around SDL3, EnTT, CMake, Ninja, and Catch2.

## Requirements

- macOS with an Apple Silicon or compatible C++ toolchain
- CMake 3.28 or newer
- Ninja
- A C++20 compiler

The primary development target is macOS. Portability to Windows and Linux is part of the technical direction but is not currently the primary supported platform.

## Build

From the repository root:

```sh
cmake -S . -B build -G Ninja
cmake --build build
```

The game executable is written to `build/untitled_rpg` while the internal CMake target is being migrated to the Runecore brand.

## Run

```sh
./build/untitled_rpg
```

For headless bot and QA workflows:

```sh
./build/untitled_rpg --bot
./build/untitled_rpg --qa movement
./build/untitled_rpg --qa-list
./build/untitled_rpg --qa all
./build/untitled_rpg --visual-qa movement
./build/untitled_rpg --visual-qa all
```

Every name printed by `--qa-list` is an independent fresh-simulation mini-run. Run any one with
`--qa <scenario>`; use `--qa all` to execute the complete focused workflow set and print one result per scenario.
The same scenarios are registered as individual `test_<scenario>` CTest processes in `CMakeLists.txt`.

For a watchable SDL run, use `--visual-qa <scenario>`. Visual mini-runs currently include
`movement`, `jump`, `mining`, `projectile`, `melee`, `feedback`, `dungeon`, `inventory_drag`,
`crafting_gui`, `augmentations_gui`, `character_sheet`, and `skill_tree`. Each opens the game window,
`farming`. Each opens the game window, shows a `VISUAL QA` overlay, performs the scripted action, and
exits after five seconds.
Using `--visual-qa all` runs those scenes back-to-back for roughly one minute, changing the overlay
to identify each mini-run as it starts. Successful runs also save one post-action frame per scene under
`build/visual_qa/`; the command exits nonzero if a scripted action or screenshot capture fails.

## Test

Run the complete Catch2 and game-launched test suite with:

```sh
ctest --test-dir build --output-on-failure
```

After changing source files, rebuild first:

```sh
cmake --build build
ctest --test-dir build --output-on-failure
```

## Controls

The current keyboard and mouse layout is:

| Input | Action |
| --- | --- |
| `A` / `D` | Move left / right |
| `Space` | Jump, double jump, or thruster |
| `W` / `S` | Climb, aim, interact, or drop through platforms |
| `Left Shift` | Dash or rocket burst |
| Left mouse button | Primary attack or tool use |
| Right mouse button | Secondary attack, aim, block, or power fire |
| `Q`, `E`, `R`, `F` | Active skills |
| `1` - `8` | Hotbar slots |
| `Tab` | Inventory, crafting, and augmentations |
| `K` / `N` | Skill tree |
| `C` | Character sheet |
| `Esc` | Pause and settings |

## Repository Layout

```text
src/       Engine and gameplay implementation
tests/     Catch2 unit and integration tests
assets/    Runtime game assets and data
docs/      Architecture, content, and test-plan documentation
external/  Vendored third-party dependencies
cmake/     CMake support files
```

The design and implementation references are indexed in [PLAN.md](PLAN.md). The active execution checklist is in [TODO_EXECUTION.md](TODO_EXECUTION.md).

## Development Notes

- The project uses C++20 and treats warnings as errors to be addressed during development, with strict warning flags enabled for the project sources.
- The simulation is designed around deterministic update loops and separated input state so that future networking remains possible.
- Save files and build output are local runtime artifacts and are excluded from normal Git commits.
- Third-party code remains subject to its own licenses. See the relevant notices in each dependency directory.

## License

Runecore is proprietary software. The source code, game design, original assets, and other project materials are not open source and may not be redistributed, modified, or used commercially without written permission.

See [LICENSE](LICENSE) for the complete terms. Third-party dependencies are excluded from the proprietary license and retain their own licenses.