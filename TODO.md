# Project Planning & Design Tracking

This document tracks all planning, conceptual specifications, content catalogs, and development roadmap for Untitled RPG.

---

## Phase 1: Conceptual Design & System Specifications

- [x] **Class System Architecture** (`docs/classes.md`)
  - [x] All 9 class archetypes detailed (Juggernaut, Berserker, Gunslinger, Phantom, Technomancer, Medic, Symbiote, Warden, Reanimator).
  - [x] Uncapped leveling progression ($1 \to \infty$) with campaign tuned for Level 60 final boss.
  - [x] Universal skill acquisition unlocked post-60 via Cross-Class Neural Bridge.
  - [x] Free Signature Augmentation awarded at Level 20.
  - [x] 15-node starter tree per class (135 skills total).
  - [ ] Full expansion of each class tree to ~50 skills (to reach 450+ class skills).

- [ ] **Skills & Ability Framework** (`docs/skills.md`)
  - [x] Skill tree DAG architecture, prerequisite rules, and mathematical scaling formulas.
  - [x] 40-node Shared Skill Tree (Mobility, Survival, Weapons, Scavenging).
  - [x] 4 active hotkey slot system (`Q`, `E`, `R`, `F`) and casting pipeline.
  - [ ] Complete catalog of 500+ unique skills across all trees (currently ~175 outlined; ~325 class specializations to be fully cataloged).

- [ ] **Body Augmentation Matrix** (`docs/augmentations.md`)
  - [x] 11 distinct modification slots defined.
  - [x] Dual-track economy: Bionic Power & Humanity vs. Magitech Stability & Cellular Rejection.
  - [x] 9 Class Signature Augmentations with cross-class installation rules and penalty trade-offs.
  - [x] Cyber-Clinic and Bio-Vat surgical installation rules.
  - [ ] Complete catalog of 250+ augmentations across all 11 slots (currently ~40 representative blueprints detailed; ~210 to be fully cataloged).

- [ ] **Itemization & Loot Generation** (`docs/items.md`)
  - [x] 10 categories and 8 tiers taxonomy defined.
  - [x] Triangular/Gaussian probability curves for individual rolled base stats.
  - [x] Quality modifier ($0\% \to 20\%$) and dynamic affix budget (Common to Prismatic).
  - [x] Complete weapon categories (Melee, Ballistic, Energy, Magic, Shields).
  - [x] Armor sets with set bonuses and environmental insulation values.
  - [ ] Complete catalog of 3,000+ base items with stat roll ranges (taxonomy established; individual item data to be fully cataloged).

- [x] **Crafting Tree & Item Modification** (`docs/crafting.md`)
  - [x] 48-node Crafting Specialization Tree (Weaponsmithing, Armor-Plating, Cyber-Engineering, Bio-Alchemy).
  - [x] Deterministic stat-crafting system (Affix Infusion, Tier Upgrading 1–7, Instability & Fracture risk).
  - [x] Value calibration, affix scrambling, socket drilling, and affix stasis sealing.

- [x] **Combat & Physics Concept** (`docs/combat.md`)
  - [x] 360-degree mouse aiming, Box2D kinematic sensor hitboxes, and hit-deduplication.
  - [x] Damage pipeline: base $\to$ scaling $\to$ crits $\to$ armor mitigation $\to$ shields.
  - [x] Hitstop, screen shake trauma math, and floating popups.
  - [x] Status effect state machine (Burn, Freeze, Shock, Toxin, Bleed, Stun).

- [x] **Survival, Building & Farming** (`docs/survival_building.md`)
  - [x] Hunger, Thirst, and ambient Body Temperature equations.
  - [x] 24-minute Day/Night cycle, nocturnal enemy raids, and dynamic weather patterns.
  - [x] 16x16 grid settlement construction with 4 structural integrity tiers and electrical wiring.
  - [x] Botany and crop hydration mechanics.
  - [x] NPC housing criteria and recruitment roster.

- [ ] **World, Biomes & Procedural Dungeons** (`docs/world_dungeons.md`)
  - [x] Over 20 unique biomes conceptual design (12 surface, 10 subterranean/dimensional).
  - [x] Procedural dungeon generation concept (hybrid BSP + prefab room templates in every biome).
  - [x] 8 campaign dungeon tiers with multi-phase bosses culminating in The Architect.
  - [x] Infinite Rift endgame with scaling mutators and Tier 9+ Prismatic gear.
  - [x] No permadeath: consciousness recall to hub with $25\%$ raw material drop in recovery drone.
  - [ ] Detailed enemy spawn tables, hazard parameters, and prefab room templates for all 20+ biomes.

- [x] **Master Implementation Plan Alignment** (`PLAN.md`)
  - [x] Sync master plan with uncapped leveling ($1 \to \infty$), 500+ skills, and universal mastery.
  - [x] Document online multiplayer architecture roadmap (client-server separation for future multiplayer while launching single-player first).
  - [x] Sync 3,000+ item catalog, individual stat roll ranges, and crafting systems into master plan.
  - [x] Sync 250+ augmentations and 20+ biomes into master plan.
  - [x] Link and reference all granular specifications in `docs/*.md`.

---

## Phase 2: Repository Setup & Build Environment Preparation

- [ ] **Git Repository Setup**
  - [ ] Initialize local Git repository (`git init`).
  - [ ] Create comprehensive `.gitignore` for CMake build artifacts, Ninja caches, macOS metadata (`.DS_Store`), and IDE configs.
  - [ ] Create initial git commit locking in the master plan, todo list, and system design specifications.

- [ ] **Build Environment Verification**
  - [ ] Verify macOS build toolchain (Apple Clang, CMake $\ge 3.28$, Ninja).
  - [ ] Configure VS Code settings (`launch.json`, `tasks.json`, CMake Tools).

---

## Phase 3: Planned Implementation Milestones

### Milestone 0: Engine Skeleton & Display System
- [ ] Root `CMakeLists.txt` with `FetchContent` dependencies (SDL3, Box2D v3, EnTT, nlohmann_json, spdlog, Dear ImGui, Catch2).
- [ ] Platform & display initialization: Monitor detection, selectable resolution list, letterboxed 16x16 integer pixel canvas.
- [ ] Fixed-timestep loop (60Hz) with render interpolation.
- [ ] Input action mapper (WASD, mouse, hotkeys).
- [ ] Render a movable placeholder pixel sprite with WASD.
- [ ] Dear ImGui debug overlay showing FPS, frame time, resolution, and memory.

### Milestone 1: Platformer Physics & Kinematic Character Controller
- [ ] Tiled `.tmj` map loader and Box2D static chain shape collider builder.
- [ ] Kinematic character controller (run, variable jump, wall-slide, one-way platform drop).
- [ ] Pixel-snapped 2D camera with deadzone and level clamping.
- [ ] Sprite animation state machine (Idle, Run, Jump, Fall, WallSlide).

### Milestone 2: Combat Engine & Hitbox Pipeline
- [ ] Damage calculation pipeline (Base weapon dmg, attribute scaling, crit roll, armor mitigation).
- [ ] Short-lived Box2D sensor hitboxes attached to weapon swing arcs and mouse direction with hit-deduplication.
- [ ] Hitstop, directional knockback, camera shake, and floating damage numbers.
- [ ] Basic enemy AI (patrol, chase, attack) and health/death lifecycle.
- [ ] Player HUD (Health, Stamina, Mana, Power bars).

### Milestone 3: Inventory, Equipment, 3,000+ Items & Firearms
- [ ] Data-driven item loader supporting 3,000+ base items from JSON.
- [ ] Grid inventory UI (slots, drag-and-drop, stacking, item tooltips).
- [ ] Equipment slots (Head, Chest, Legs, Boots, Main Hand, Off Hand, Ring x2, Amulet).
- [ ] Ballistic firearms with projectile physics, ammo consumption, reloading, and spread.
- [ ] Energy weapons consuming power; magic wands consuming mana.
- [ ] Procedural loot drop system with rarity borders (Common to Prismatic) and dynamic affix rolling.

### Milestone 4: Classes, Uncapped Leveling & 500+ Skill System
- [ ] Leveling curve implementation ($1 \to \infty$) with XP awards from kills and gathering.
- [ ] Class selection UI at new game with all 9 classes, base stats, and starter gear.
- [ ] Interactive Skill Tree UI: The 40-node Shared Tree + Class Trees (over 500 skills total).
- [ ] Hotkey assignment for 4 active skill slots (`Q`, `E`, `R`, `F`).
- [ ] Level 20 Milestone trigger: Automatically awards the class-specific Free Signature Augmentation.
- [ ] Cross-Class Neural Bridge system unlocking universal skill learning post-Level 60.

### Milestone 5: The 11-Slot Augmentation System (250+ Augments) & Cyber-Clinic
- [ ] Implement 11 body slot data structures and component tracking.
- [ ] Implement Cyber-Clinic UI for installation, removal, and humanity/power stat displays.
- [ ] Implement signature augmentations: Arm laser cannons, jet boots, chimeric bear arms, and deflector shields.
- [ ] Implement cross-class exotic surgery rules and penalty modifiers.

### Milestone 6: Crafting Tree & Deterministic Item Modification Forge
- [ ] Implement the 48-node Crafting Specialization Tree (Weaponsmithing, Armor-Plating, Cyber-Engineering, Bio-Alchemy).
- [ ] Implement crafting station UIs (Workbench, Forge & Ammo Press, Kitchen Stove, Hydroponics Lab).
- [ ] Implement Modification Forge: Stat shard infusion, Tier 1–7 upgrading, instability tracking, fracture locks, value calibration, socket punching, and affix sealing.

### Milestone 7: Survival Systems, Day/Night & Settlement Building
- [ ] Implement Hunger and Thirst meters, edible food buffs, and clean water purification.
- [ ] Implement ambient temperature system with weather events and hypothermia/heatstroke.
- [ ] Implement 24-minute day/night cycle with dynamic 2D lighting and nocturnal enemy raids.
- [ ] Implement 16x16 grid building system: Place and break walls, floors, doors, platforms, and storage chests.
- [ ] Implement farming botany (tilling, planting, hydration, harvesting).
- [ ] Implement NPC room verification and recruit survivor NPCs into Haven.

### Milestone 8: Procedural Dungeons in Every Biome (20+ Biomes) & Tiers 1–3
- [ ] Implement BSP + prefab room dungeon generator producing sprawling 2D levels in all 20+ biomes.
- [ ] Implement Vault generation across surface and subterranean biomes.
- [ ] Implement Tier 1 (Rusted Catacombs), Tier 2 (Overgrown Bio-Labs), and Tier 3 (Submerged Cooling Vaults).
- [ ] Implement Boss fights: MK-1 Goliath Excavator, Grafted Mother Chimera, and Hydro-Turbine Overlord.
- [ ] Implement dungeon defeat recall and $25\%$ material drop in recovery drone.

### Milestone 9: Campaign Tiers 4–8, The Architect & Infinite Rift Endgame
- [ ] Implement Tier 4 (Molten Smeltery), Tier 5 (Cryo-Stasis Depths), Tier 6 (Void Factory), Tier 7 (Citadel of Hard-Light).
- [ ] Implement Tier 8 (Sunken Orbital Core) and 3-phase final boss battle against **The Architect**.
- [ ] Implement victory transition unlocking the Infinite Rift portal.
- [ ] Implement infinite scaling rift floor generator with randomized mutators and Tier 9+ Prismatic gear.

### Milestone 10: Audio, Polish, Multiplayer-Ready Architecture & Packaging
- [ ] Separate networking boundary / game state serialization for future online multiplayer.
- [ ] Implement audio engine (positional SFX, ambient soundscapes, dynamic combat music).
- [ ] Visual polish: Hit particles, shell casings, liquid splashes, dust puffs.
- [ ] Input settings: Rebindable keys and gamepad controller support with aim assist.
- [ ] Save/Load persistence: High-speed JSON serialization of character, inventory, world, and base structures.
- [ ] Performance profiling: Sprite batching optimization, chunk culling, 60+ FPS on Apple Silicon.
- [ ] Build macOS `.app` bundle with code signing.
