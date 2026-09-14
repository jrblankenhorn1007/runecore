# Code Architecture & File Structure Specification

This document provides the authoritative software architecture, directory organization, module boundaries, dataflow pipelines, and client-server simulation separation for Untitled RPG.

---

## 1. High-Level Architectural Principles

1. **Data-Oriented Entity Component System (ECS)**:
   - Built on **EnTT**. All gameplay entities (Player, Enemies, NPCs, Projectiles, Dropped Items, Placed Furniture, Sensor Hitboxes) are lightweight integer IDs (`entt::entity`).
   - Components are pure data objects (plain structs) with zero business logic and zero virtual methods.
   - Systems are stateless free functions that query views of components and execute transformations over contiguous cache lines.
2. **Deterministic Fixed Simulation & Interpolated Rendering**:
   - The simulation loop ticks at an exact 60 Hz ($dt = 1/60\text{ s}$).
   - The rendering pipeline runs at the display's variable refresh rate, computing a fractional alpha interpolation factor between previous and current physics states to achieve sub-pixel smoothness without tunneling.
3. **Strict Decoupling via Event Bus**:
   - Cross-module communication (e.g. an enemy dying triggering an XP reward, a quest progress update, a loot spawn, and an audio sound effect) occurs through a centralized, type-safe `EventBus`.
4. **Multiplayer-Ready Headless Simulation Boundary**:
   - The game logic is partitioned into a pure simulation core (`src/gameplay/`, `src/physics/`, `src/procgen/`, `src/ecs/`) and an output/presentation layer (`src/render/`, `src/ui/`, `src/audio/`).
   - The simulation core accepts an abstracted `InputState` and produces deterministic state updates without referencing windowing, rendering, or audio contexts. This ensures future online multiplayer client-server synchronization (client-side prediction and server reconciliation) can be added seamlessly.

---

## 2. Complete Planned File Tree & Module Breakdown

```
untitled_rpg/
├── assets/
│   ├── data/                   # Balancing and definition files (JSON)
│   │   ├── augmentations.json  # 250+ augmentations across 11 slots
│   │   ├── biomes.json         # 20+ biomes parameters, hazards, and themes
│   │   ├── classes.json        # 9 classes baseline, starter gear, stat weights
│   │   ├── crafting.json       # 48-node crafting tree and station blueprints
│   │   ├── enemies.json        # Enemy archetypes, base stats, attack behaviors
│   │   ├── items.json          # 3,000+ base items catalog and roll ranges
│   │   ├── loot_tables.json    # Tiered drop rates, affixes, and quality curves
│   │   ├── recipes.json        # Workbench, forge, stove, and alchemy recipes
│   │   └── skills.json         # 500+ skills DAG definitions and formulas
│   ├── fonts/                  # TrueType pixel typography
│   ├── maps/                   # Handcrafted Tiled (.tmj) overworld zones and hub
│   ├── audio/                  # Positional SFX and atmospheric ambient loops
│   └── sprites/                # 16x16 sprite sheets, tilesets, and atlas metadata
├── docs/                       # Conceptual design specifications & reference
│   ├── architecture.md         # This software architecture specification
│   ├── augmentations.md        # 11-slot augmentation matrix & dual economy
│   ├── classes.md              # 9 classes, uncapped leveling & universal mastery
│   ├── combat.md               # 360-degree aiming, damage pipeline & status effects
│   ├── crafting.md             # 48-node crafting tree & stat modification forge
│   ├── functions_reference.md  # Detailed API & function specification per file
│   ├── items.md                # 3,000+ items, stat ranges & dynamic affix pools
│   ├── skills.md               # 500+ skills, 4-key hotbar & execution pipeline
│   ├── survival_building.md    # Survival meters, 16x16 grid building & farming
│   ├── world_dungeons.md       # 20+ biomes, procedural vaults & boss mechanics
│   └── test_plans/             # Detailed test plan per file/module
│       ├── augmentations_test_plan.md
│       ├── combat_stats_test_plan.md
│       ├── core_platform_test_plan.md
│       ├── crafting_modification_test_plan.md
│       ├── items_inventory_test_plan.md
│       ├── physics_controller_test_plan.md
│       ├── skills_progression_test_plan.md
│       ├── survival_building_test_plan.md
│       └── world_dungeons_test_plan.md
├── src/                        # C++ source code (organized into distinct modules)
│   ├── main.cpp                # Entry point: bootstrap, argument parsing, run loop
│   ├── core/                   # Platform abstractions, timing, configuration, events
│   │   ├── Application.hpp/.cpp      # Master application lifecycle manager
│   │   ├── AssetManager.hpp/.cpp     # Texture, font, audio, and JSON cache
│   │   ├── Config.hpp/.cpp           # Video, display, audio, and gameplay settings
│   │   ├── DisplayManager.hpp/.cpp   # Monitor auto-detection and mode resolution
│   │   ├── EventBus.hpp              # Type-safe publish/subscribe event dispatcher
│   │   └── Time.hpp/.cpp             # Fixed-timestep accumulator and delta clock
│   ├── render/                 # Visual rendering pipeline
│   │   ├── AnimationSystem.hpp/.cpp  # Frame-based sprite animation state machine
│   │   ├── Camera.hpp/.cpp           # Pixel-snapped 2D camera with deadzone and shake
│   │   ├── LightingSystem.hpp/.cpp   # 2D ambient darkness, torches, and point lights
│   │   ├── Renderer.hpp/.cpp         # Canvas rendering, integer scaling, letterbox
│   │   ├── SpriteBatch.hpp/.cpp      # Batched textured quad renderer
│   │   └── TilemapRenderer.hpp/.cpp  # Multi-layer Tiled grid chunk renderer
│   ├── input/                  # Input capture and action mapping
│   │   ├── ActionMapping.hpp         # Abstract game action identifiers
│   │   ├── ControllerSupport.hpp/.cpp# Gamepad analog axes and button mapping
│   │   └── InputManager.hpp/.cpp     # Keyboard, mouse, and cursor position polling
│   ├── physics/                # Box2D wrapper and humanoid movement controller
│   │   ├── CollisionLayers.hpp       # Bitmask collision filters and categories
│   │   ├── KinematicController.hpp/.cpp # Platformer controller (jump, coyote, wall)
│   │   ├── PhysicsWorld.hpp/.cpp     # Box2D v3 world step wrapper and debug draw
│   │   └── Raycaster.hpp/.cpp        # Sensor line casts for ground, wall, ceiling
│   ├── ecs/                    # Entity Component System definitions
│   │   ├── Components.hpp            # POD component declarations (Transform, Stats, etc.)
│   │   └── EntityFactory.hpp/.cpp    # Prefab entity spawning helpers
│   ├── gameplay/               # Core gameplay rules, mechanics, and simulations
│   │   ├── ai/
│   │   │   ├── AISystem.hpp/.cpp           # Perception, patrol, chase, attack trees
│   │   │   └── BossStateMachine.hpp/.cpp   # Multi-phase boss battle controllers
│   │   ├── augmentations/
│   │   │   ├── AugmentationManager.hpp/.cpp# 11-slot equip checks, power, stability
│   │   │   └── CyberClinic.hpp/.cpp        # Surgical installation and fee verification
│   │   ├── building/
│   │   │   ├── ElectricalGrid.hpp/.cpp     # Generator power distribution and wiring
│   │   │   ├── GridPlacement.hpp/.cpp      # 16x16 tile placement, breaking, repairs
│   │   │   └── StructuralIntegrity.hpp/.cpp# Material durability and raid damage
│   │   ├── combat/
│   │   │   ├── CombatSystem.hpp/.cpp       # Attack hitboxes, damage calculation, crits
│   │   │   ├── ProjectileSystem.hpp/.cpp   # Ballistic and energy projectile physics
│   │   │   └── StatusEffectSystem.hpp/.cpp # Burn, Freeze, Shock, Toxin, Bleed ticks
│   │   ├── crafting/
│   │   │   ├── CraftingBench.hpp/.cpp      # Recipe validation and station fabrication
│   │   │   ├── CraftingTree.hpp/.cpp       # 48-node crafting mastery progression
│   │   │   └── ModificationForge.hpp/.cpp  # Stat infusion, upgrading, fracture risk
│   │   ├── farming/
│   │   │   └── FarmingSystem.hpp/.cpp      # Soil hydration, crop growth stages, harvest
│   │   ├── items/
│   │   │   ├── AffixRoller.hpp/.cpp        # Dynamic prefix/suffix generation
│   │   │   ├── InventorySystem.hpp/.cpp    # 32-slot inventory, hotbar, stacking
│   │   │   ├── ItemFactory.hpp/.cpp        # Gaussian base stat roll instantiation
│   │   │   └── LootSystem.hpp/.cpp         # Drop tables, rarity borders, recovery drone
│   │   ├── skills/
│   │   │   ├── ActiveSkillSystem.hpp/.cpp  # 4-key hotbar execution and cooldowns
│   │   │   ├── SkillTreeManager.hpp/.cpp   # DAG prerequisite checks and point spend
│   │   │   └── UniversalMastery.hpp/.cpp   # Level 60+ Cross-Class Neural Bridge
│   │   ├── stats/
│   │   │   ├── LevelingSystem.hpp/.cpp     # Uncapped XP curve and attribute awards
│   │   │   └── StatsCalculator.hpp/.cpp    # Derived stats aggregation from attributes
│   │   └── survival/
│   │       ├── DayNightSystem.hpp/.cpp     # 24-minute diurnal cycle and night spawns
│   │       ├── SurvivalSystem.hpp/.cpp     # Hunger, thirst, and thermal exposure
│   │       └── WeatherSystem.hpp/.cpp      # Dynamic rain, blizzard, sandstorm timers
│   ├── procgen/                # Subterranean procedural dungeon generator
│   │   ├── BSPTree.hpp/.cpp          # Binary Space Partitioning leaf subdivider
│   │   ├── DungeonGenerator.hpp/.cpp # Master dungeon assembler for 20+ biomes
│   │   ├── GraphSolver.hpp/.cpp      # BFS path connectivity and exit validator
│   │   ├── RoomPlacer.hpp/.cpp       # Prefab Tiled template socketing
│   │   └── TileStitcher.hpp/.cpp     # 16x16 autotile edge welding rules
│   ├── ui/                     # User interface rendering and interactions
│   │   ├── AugmentationUI.hpp/.cpp   # Holographic 11-slot body schematic screen
│   │   ├── CraftingUI.hpp/.cpp       # Recipe browser and modification bench UI
│   │   ├── DebugOverlay.hpp/.cpp     # Dear ImGui developer console and profiler
│   │   ├── HUD.hpp/.cpp              # Health, Stamina, Mana, Power, survival bars
│   │   ├── InventoryUI.hpp/.cpp      # Grid slot management, equipment, tooltips
│   │   ├── MenuManager.hpp/.cpp      # Main menu, settings, pause, death screen
│   │   └── SkillTreeUI.hpp/.cpp      # Interactive node tree and hotkey assigner
│   └── save/                   # Persistence and serialization
│       ├── SaveManager.hpp/.cpp      # Save/load file coordinator and checksums
│       └── StateSerializer.hpp/.cpp  # High-speed JSON serialization of entity state
└── tests/                      # Catch2 v3 unit test suites (organized by module)
    ├── test_main.cpp                 # Catch2 test runner entry point
    ├── test_augmentations.cpp
    ├── test_combat_stats.cpp
    ├── test_core_platform.cpp
    ├── test_crafting_modification.cpp
    ├── test_items_inventory.cpp
    ├── test_physics_controller.cpp
    ├── test_skills_progression.cpp
    ├── test_survival_building.cpp
    └── test_world_dungeons.cpp
```

---

## 3. System Execution Order & Frame Lifecycle

Every simulation tick (60 Hz) and render frame follows a deterministic pipeline:

```
[Start Frame]
      │
      ▼
[1. Input Polling & Action State Update] (Keyboard, Mouse, Gamepad)
      │
      ▼
[2. Fixed Timestep Loop (Accumulator >= 1/60s)]
      │
      ├── 2.1 Character Controller & AI Decision Trees
      ├── 2.2 Movement Velocities & Kinematic Sweeps
      ├── 2.3 Box2D World Step (Dynamic bodies, sensors, raycasts)
      ├── 2.4 Sensor Hitbox Overlaps & Combat Damage Pipeline
      ├── 2.5 Status Effect Ticks & Survival Meter Decay
      ├── 2.6 Active Skill Cooldowns & Augmentation Power Reservations
      ├── 2.7 Day/Night Timers, Weather Shifts & Crop Growth
      └── 2.8 Entity Lifecycle Cleanup (Dead entities, despawns)
      │
      ▼
[3. Render Interpolation (Alpha = Accumulator / dt)]
      │
      ├── 3.1 Camera Position Smoothing & Screen Shake Computation
      ├── 3.2 Parallax Background Layers Render
      ├── 3.3 Tilemap Visible Chunks Render
      ├── 3.4 Entity Sprites Interpolated Render (Batching)
      ├── 3.5 Dynamic Lighting Mask Multiplication Pass
      ├── 3.6 Floating Combat Numbers & Particle FX Render
      ├── 3.7 UI Layer Render (HUD, Open Windows, Inventory, Tooltips)
      └── 3.8 Dear ImGui Debug Overlay (if active)
      │
      ▼
[4. Present Frame (V-Sync / Backbuffer Swap)]
```

---

## 4. Client-Server Simulation Separation (Multiplayer Roadmap)

To guarantee that the game can transition from single-player to online cooperative multiplayer in future phases, all gameplay code adheres to the **Headless Simulation Separation Pattern**:

1. **Separation of Concerns**:
   - `SimulationState`: Maintains the `entt::registry`, Box2D world, and active game world data. It has zero dependencies on SDL windowing, OpenGL/Metal rendering, or audio streams.
   - `ClientView`: Observes the `SimulationState`, feeds user inputs via structured `InputMessage` packets, interpolates entity transforms, and renders visual/audio effects.
2. **Determinism**:
   - All gameplay random number generation uses a seeded pseudo-random generator (`std::mt19937_64`) synchronized per world tick.
   - Frame rates, display resolution changes, and window resizing do not alter the outcome of physics, combat, or survival updates.
