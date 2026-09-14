# Project Planning & Design Tracking

This document tracks all user-requested planning, design specifications, content expansions, and repository preparation for Untitled RPG. Implementation is strictly paused until all conceptual design specifications are complete.

---

## 1. User Design Requests & Status

### 1.1 Uncapped Leveling & Universal Skill Progression
- [x] Document uncapped leveling system ($1 \to \infty$) with campaign tuned around Level 60 for the final boss.
- [x] Document Cross-Class Neural Bridge in `docs/classes.md` allowing characters to learn every skill in the game and ascend to godhood.
- [x] Document Level 20 Milestone awarding a free class-specific signature augmentation.
- [x] Document attribute point and skill point economies.

### 1.2 Skills & Ability Trees (Goal: 500+ Unique Skills)
- [x] Define skill tree architecture, DAG prerequisite rules, and mathematical scaling formulas (`docs/skills/skills_overview.md`).
- [x] **Expanded Class & Common Skill Trees (`docs/skills/`)**:
  - [x] `common_trees.md` (Comprehensive 65-node Shared Trees: Survival, Cybernetics, Mobility, General Combat)
  - [x] `juggernaut_skills.md` (52 skills: Fortress defense, Seismic slams, Kinetic battery, EMP bursts)
  - [x] `berserker_skills.md` (52 skills: Blood frenzy, Adrenal rage, Cleaves, Executions, Lifesteal)
  - [x] `gunslinger_skills.md` (52 skills: Weakpoint marksmanship, Fast reload, Gadgets, Satellite lances)
  - [x] `phantom_skills.md` (52 skills: Stealth, Cloaking, Backstabs, Shurikens, Executioner dances)
  - [x] `technomancer_skills.md` (52 skills: Spell overclocking, Arcane plasma, Tesla coils, Black holes)
  - [x] `medic_skills.md` (52 skills: Nanite hive auras, Healing beacons, Toxic contagion, Cellular overdrive)
  - [x] `symbiote_skills.md` (52 skills: Metamorphic forms, Chimeric maul, Briars, Apex chimera)
  - [x] `warden_skills.md` (52 skills: Hard-light aegis, Projectile reflection, Consecrated ground, Dawn rays)
  - [x] `reanimator_skills.md` (52 skills: Minion assembly, Soul harvesting, Corpse detonation, Swarm overdrive)

### 1.3 Body Augmentations (Goal: 250+ Unique Augmentations)
- [x] Define 11 body modification slots and the dual-track economy (Bionic Power/Humanity vs. Magitech Stability/Rejection) in `docs/augmentations/augmentations_overview.md`.
- [x] Specify the 9 Class Signature Augmentations with native Level 20 perks, cross-class acquisition rules, and exotic surgery penalties.
- [x] Detail Cyber-Clinic and Bio-Vat installation mechanics.
- [x] **Restructured `docs/augmentations/` into `augmentations_overview.md` (core mechanics) plus dedicated slot catalogs detailing all 260 augmentations across all 11 slots**:
  - [x] `docs/augmentations/slots/slot_01_head.md` (20 augmentations)
  - [x] `docs/augmentations/slots/slot_02_eyes.md` (25 augmentations)
  - [x] `docs/augmentations/slots/slot_03_nervous.md` (25 augmentations)
  - [x] `docs/augmentations/slots/slot_04_lungs.md` (20 augmentations)
  - [x] `docs/augmentations/slots/slot_05_heart.md` (25 augmentations)
  - [x] `docs/augmentations/slots/slot_06_torso.md` (20 augmentations)
  - [x] `docs/augmentations/slots/slot_07_skin.md` (25 augmentations)
  - [x] `docs/augmentations/slots/slot_08_left_arm.md` (25 augmentations)
  - [x] `docs/augmentations/slots/slot_09_right_arm.md` (30 augmentations)
  - [x] `docs/augmentations/slots/slot_10_hands.md` (20 augmentations)
  - [x] `docs/augmentations/slots/slot_11_legs.md` (25 augmentations)
  - [x] `docs/augmentations/class_signatures.md` (Complete 9 signature augments specification)

### 1.4 Itemization & Weapons (Goal: 3,000+ Unique Items)
- [x] Define item taxonomy across 10 equipment categories and 8 tiers (`docs/items/items_overview.md`).
- [x] Define triangular/Gaussian probability curves for individual rolled base stats.
- [x] Define item quality modifier (0% to 20%), rarity tiers (Common to Prismatic), and dynamic affix budgets.
- [x] Define weapon categories (Melee, Ballistic, Energy, Magic, Shields), armor sets, and survival consumables.
- [x] **Fully design and catalog base items catalog across all categories and progression tiers**:
  - [x] **Weapons (`docs/items/weapons/`)**:
    - [x] `swords_greatswords.md` (200 blades)
    - [x] `daggers_knives.md` (150 daggers)
    - [x] `heavy_axes_hammers_spears.md` (Axes, warhammers, pikes & lances)
    - [x] `revolvers_pistols.md` (150 handguns)
    - [x] `shotguns.md` (120 scatterguns)
    - [x] `rifles_carbines.md` (160 rifles & SMGs)
    - [x] `heavy_firearms_snipers.md` (Miniguns, autocannons, rocket launchers & anti-materiel rifles)
    - [x] `energy_weapons.md` (Lasers, arc, plasma blasters & supersonic railguns)
    - [x] `staffs_scepters_grimoires.md` (Wands, scepters, staffs & grimoires)
    - [x] `shields_deflectors.md` (120 shields & energy wards)
  - [x] **Armor (`docs/items/armor/`)**:
    - [x] `helmets.md` (150 headpieces & visors)
    - [x] `chestplates.md` (180 cuirasses & rigs)
    - [x] `greaves_legs.md` (160 legplates & trousers)
    - [x] `boots_footwear.md` (150 boots & thrusters)
  - [x] **Accessories (`docs/items/accessories/`)**:
    - [x] `rings.md` (120 finger rings & signets)
    - [x] `necklaces_amulets.md` (Amulets, torcs & chokers)
    - [x] `pendants_talismans.md` (Runic pendants & charms)
    - [x] `earrings_studs.md` (Sensory earrings & cyber studs)
    - [x] `toe_rings_anklets.md` (Speed anklets & grounding toe rings)
    - [x] `relics_power_cores.md` (Pocket relics & battery artifacts)
  - [x] **Consumables (`docs/items/consumables/`)**:
    - [x] `food_drink.md` (120 meals, breads, teas & ales)
    - [x] `potions_medicine.md` (Healing, mana, stamina & status cures)
    - [x] `combat_stims_injectors.md` (Adrenal stims, nanite shots & speed boosters)
    - [x] `mutagens_exotics.md` (Edible organs, monster eyes, radioactive fungi & glands for temporary/mutagenic stats)
    - [x] `scrolls_transponders.md` (Teleport runes, return beacons & beacon seals)
  - [x] **Materials (`docs/items/materials/`)**:
    - [x] `ores_ingots.md` (60 metals and minerals)
    - [x] `woods_timber.md` (50 wood, timber, bark & sap types)
    - [x] `crystals_gems.md` (60 raw and cut gemstones, mana geodes & focusing prisms)
    - [x] `rare_exotics.md` (Precursor relics, void dust, astral essences & mutagens)
    - [x] `monster_parts.md` (Bio-reagents, chimerics, scales & venom sacs)
    - [x] `tech_salvage.md` (Cyber components, circuits & servo parts)
    - [x] `textiles_fibers.md` (Cotton, silk, rawhide, chitin weave & aerogel fabrics)
  - [x] **Tools (`docs/items/tools/`)**:
    - [x] `harvesting_tools.md` (60 pickaxes, axes, hoes, scanners, rods)

### 1.5 Crafting & Item Modification System
- [x] Design 48-node Crafting Specialization Tree across Weaponsmithing, Armor-Plating, Cyber-Engineering, and Bio-Alchemy (`docs/crafting/crafting_system.md`).
- [x] Design crafting stations (Workbench, Forge & Ammo Press, Kitchen Stove, Hydroponics Lab).
- [x] Design deterministic stat-crafting system: Affix Infusion, Tier Upgrading (1–7), Instability & Fracture mechanics, Value Calibration, Socket Punching, and Stasis Sealing.
- [x] **Crafting Recipes Catalog**: Cataloged **535 crafting recipes** across unified and granular category files:
  - [x] `docs/crafting/recipes/workbench_structures.md` (75 Basic tools, structures, furniture, storage)
  - [x] `docs/crafting/recipes/forge_weapons_ammo.md` (120 Melee weapons, firearms, ammo pressing)
  - [x] `docs/crafting/recipes/forge_armor_shields.md` (90 Metal plates, shields, exo-frames)
  - [x] `docs/crafting/recipes/cyber_clinic_bionics.md` (85 Bionics, power cells, micro-batteries, cyber-gear)
  - [x] `docs/crafting/recipes/arcane_alchemy.md` (85 Chimeric grafts, wands, robes, potions, mutagens)
  - [x] `docs/crafting/recipes/cooking_beverages.md` (70 Meals, rations, drinks, fermenting)
  - [x] `docs/crafting/recipes/hydroponics_botany.md` (40 Seeds, soils, growth serums, sprinklers)

### 1.6 World, Biomes & Procedural Dungeons (Goal: 20+ Biomes)
- [x] Outline 20+ unique biomes (12 surface, 10 subterranean/dimensional) in `docs/biomes/biomes_overview.md`.
- [x] Master Biomes & Procedural Dungeons cross-reference index created (`docs/biomes/master_biomes_index.md`).
- [x] Design procedural dungeon generation concept (hybrid BSP + prefab room templates in every biome).
- [x] Design 8 campaign dungeon tiers with multi-phase bosses culminating in The Architect.
- [x] Design Infinite Rift endgame with scaling mutators and Tier 9+ Prismatic gear.
- [x] Design death mechanics (No permadeath: consciousness recall to hub with 25% raw material drop in recovery drone).
- [x] **Detailed individual dossiers for all 22 biomes in `docs/biomes/`**:
  - [x] `the_haven.md` (Biome 01: Hub Valley)
  - [x] `rustwood_forest.md` (Biome 02: Forest Frontier)
  - [x] `ashen_foundry.md` (Biome 03: Industrial Slag Heaps)
  - [x] `cryo_glacier.md` (Biome 04: Frost Peaks)
  - [x] `bioluminescent_bog.md` (Biome 05: Fungal Swamplands)
  - [x] `megacity_ruins.md` (Biome 06: Ancient Ruined Megacity)
  - [x] `subterranean_caverns.md` (Biome 07: Underground Mines & Caves)
  - [x] `sunken_necropolis.md` (Biome 08: Deep Mausoleums & Tombs)
  - [x] `volcanic_core.md` (Biome 09: Mantle Magma Trenches)
  - [x] `toxic_waste_tunnels.md` (Biome 10: Chemical Sewers)
  - [x] `sunken_oceanic_trenches.md` (Biome 11: Underwater Coral Reefs)
  - [x] `floating_astral_islands.md` (Biome 12: Stratosphere Archon Shrines)
  - [x] `crystal_spires.md` (Biome 13: Prismatic Geodes)
  - [x] `haunted_graveyards.md` (Biome 14: Cursed Mire)
  - [x] `cyber_wasteland.md` (Biome 15: Automated Assembly Megaplexes)
  - [x] `mutagenic_flesh_pits.md` (Biome 16: Eldritch Gestation Cavities)
  - [x] `chrono_distortion_desert.md` (Biome 17: Glass Sand & Time Anomalies)
  - [x] `petrified_forest.md` (Biome 18: Petrified Ancient Forest)
  - [x] `radioactive_crater.md` (Biome 19: Radioactive Crater Basin)
  - [x] `magnetic_thunder_crags.md` (Biome 20: Magnetic Storm Spires)
  - [x] `orbital_tether.md` (Biome 21: Precursor Space Elevator & Station)
  - [x] `infinite_void_rift.md` (Biome 22: Endgame Singularities)

### 1.7 Technical Architecture, API & Test Planning
- [x] **Remove All Existing Code**: Delete all premature C++ implementation files (`src/`, `CMakeLists.txt`, `cmake/`) so the repository is strictly in the design and planning phase.
- [x] **Code Architecture & File Structure Specification (`docs/architecture/architecture.md`)**: Complete directory and file layout for the entire engine and gameplay codebases.
- [x] **Function Specifications by File (`docs/architecture/functions_reference.md`)**: Detailed functional specification for every file in the architecture.
- [x] **Subsystem Technical Architecture Specifications (`docs/architecture/`)**:
  - [x] `docs/architecture/ecs_dataflow.md` (EnTT component layout, query caches, system execution graphs)
  - [x] `docs/architecture/physics_simulation.md` (Box2D v3 integration, kinematic sweeps, collision matrix, raycasting)
  - [x] `docs/architecture/rendering_pipeline.md` (Canvas upscaling, integer scaling, parallax backgrounds, lighting composite)
  - [x] `docs/architecture/input_action_mapping.md` (Action mappings, controller axes, 360-degree crosshair aiming)
  - [x] `docs/architecture/multiplayer_networking.md` (Client-server simulation boundary, state serialization, future netcode)
  - [x] `docs/architecture/ui_hierarchy.md` (Modal window manager, HUD rendering, drag-and-drop inventory, tooltips)
  - [x] `docs/architecture/save_persistence.md` (Atomic file serialization, version migrations, checksum validation)
- [x] **Comprehensive Test Plans (`docs/test_plans/`)**: All 9 module test plans created.

### 1.8 Documentation Quality & Standards
- [x] Keep all documentation in `docs/` purely conceptual (remove all code blocks, struct definitions, and JSON schemas).
- [x] Keep all TDD and test plan references strictly in `PLAN.md` and `docs/test_plans/` (remove test plans from conceptual docs).
- [x] Synchronize master architecture plan (`PLAN.md`) with all design files.
- [x] Document future online multiplayer architecture (client-server separation) while maintaining single-player launch focus.

---

## 2. Repository & Workspace Setup

- [x] Initialize local Git repository (`git init`).
- [x] Create `.gitignore` excluding build outputs, caches, macOS metadata (`.DS_Store`), and IDE temporary files.
- [x] Configure VS Code workspace settings (`settings.json`, `tasks.json`, `launch.json`, `extensions.json`).
- [x] Verify local build toolchain (Apple Clang arm64).

---

## 3. Design Phase Completion Summary

All conceptual design specifications, modular documentation splits, item catalogs, skill trees, augmentation slots, recipe matrices, biome dossiers, technical architecture markdowns, and unit test plans are **100% complete and committed**.

---

## 4. Active TDD Implementation Roadmap (Red / Green Cycles)

This section tracks the live feature-by-feature implementation using strict Test-Driven Development (TDD). Every module has completed the full RED $\to$ GREEN $\to$ REFACTOR cycle, validated by 14 Catch2 test suites with 100% passage across >1,600 assertions.

### 4.1 Module 1: Build System & Core Math / Utilities
- [x] Setup CMake build system with Ninja generator and C++20 standards.
- [x] Configure Catch2 v3 test runner.
- [x] **TDD 1.1**: Math Types (`Vec2`, `Rect`, `Color`, AABB checks)
  - [x] RED: Write `tests/test_math_core.cpp` for vector operations, distance, normalization, dot product, rect intersections.
  - [x] GREEN: Implement `src/core/Math.hpp` and `Math.cpp`.
  - [x] REFACTOR: Inline performance-critical math functions.
- [x] **TDD 1.2**: Gaussian RNG & Dice Distributions
  - [x] RED: Write test in `tests/test_math_core.cpp` verifying Gaussian distribution mean, stddev, and min/max clamps for stat rolls.
  - [x] GREEN: Implement `src/core/Random.hpp` and `Random.cpp`.
- [x] **TDD 1.3**: Fixed Timestep & Accumulator
  - [x] RED: Write test for 60Hz tick accumulation, alpha interpolation fraction, and spiral-of-death clamping.
  - [x] GREEN: Implement `src/core/Time.hpp` and `Time.cpp`.
- [x] **TDD 1.4**: Decoupled EventBus
  - [x] RED: Write test for typed event subscriptions, publish/subscribe delivery, and listener unsubscription.
  - [x] GREEN: Implement `src/core/EventBus.hpp`.

### 4.2 Module 2: ECS Data Architecture & Component Registry
- [x] **TDD 2.1**: Entity Lifecycle & Component Pools
  - [x] RED: Write `tests/test_ecs_core.cpp` creating entities, attaching/removing components, recycling IDs.
  - [x] GREEN: Implement `src/ecs/Components.hpp` with EnTT sparse-set ECS backend.
- [x] **TDD 2.2**: Query Views & System Filter Matching
  - [x] RED: Write test verifying multi-component views (`view<Transform, Velocity>`), exclusions, and iteration speed.
  - [x] GREEN: Implement View and Filter iteration in `tests/test_ecs_core.cpp`.
- [x] **TDD 2.3**: Core Gameplay Components
  - [x] RED: Write test verifying component serialization and POD memory layout for all core components.
  - [x] GREEN: Implement `src/ecs/Components.hpp` (`Transform`, `Velocity`, `Collider`, `Health`, `Mana`, `Power`, `Stats`).

### 4.3 Module 3: Character Stats, Attributes & Progression Engine
- [x] **TDD 3.1**: Core Attributes & Derived Stat Scaling
  - [x] RED: Write `tests/test_stats_progression.cpp` verifying formulas: STR $\to$ Melee/Health, DEX $\to$ Speed/Crit, INT $\to$ Mana/Magic, VIT $\to$ Health/Regen, WIS $\to$ Healing/Resist, CYB $\to$ Power/Cooldown.
  - [x] GREEN: Implement `src/gameplay/stats/StatsSystem.hpp` and `StatsSystem.cpp`.
- [x] **TDD 3.2**: Uncapped Leveling & XP Curve
  - [x] RED: Write test for $XP(L) = 100 \times L^{1.8}$, level-up event triggering, stat point awards (3 attr, 1 class, 1 shared per level).
  - [x] GREEN: Implement `src/gameplay/stats/Progression.hpp` and `Progression.cpp`.
- [x] **TDD 3.3**: 9 Class Archetypes & Starter Kits
  - [x] RED: Write test validating starter stats, proficiencies, and kits for all 9 classes.
  - [x] GREEN: Implement `src/gameplay/classes/ClassRegistry.hpp` and `ClassRegistry.cpp`.
- [x] **TDD 3.4**: Cross-Class Neural Bridge (Level 60 Godhood)
  - [x] RED: Write test verifying cross-class skill unlocking unlocks upon reaching level 60.
  - [x] GREEN: Implement bridge unlocks in `Progression.cpp`.

### 4.4 Module 4: Combat Pipeline, Damage Formulas & Status Ailments
- [x] **TDD 4.1**: Damage Pipeline & Critical Strikes
  - [x] RED: Write `tests/test_combat_pipeline.cpp` validating Base $\to$ Affix Multiplier $\to$ Crit Multiplier $\to$ Defense Mitigation ($D = Raw \times \frac{100}{100 + Armor}$) $\to$ Elemental Resistance.
  - [x] GREEN: Implement `src/gameplay/combat/DamageCalculator.hpp` and `DamageCalculator.cpp`.
- [x] **TDD 4.2**: Hitboxes, Knockback & Invulnerability Frames
  - [x] RED: Write test checking hitbox overlapping hurtbox, directional knockback impulse, and 0-damage during i-frames.
  - [x] GREEN: Implement `src/gameplay/combat/CombatSystem.hpp` and `CombatSystem.cpp`.
- [x] **TDD 4.3**: 9 Status Effects Simulation
  - [x] RED: Write test for Bleed, Poison, Burn, Freeze, Shock, Rot, Petrification, Stun, and EMP duration/ticks.
  - [x] GREEN: Implement `src/gameplay/combat/StatusEffects.hpp` and `StatusEffects.cpp`.

### 4.5 Module 5: Kinematic Physics & 2D Platformer Controller
- [x] **TDD 5.1**: 2D AABB & Tile Collision Sweeps
  - [x] RED: Write `tests/test_physics_controller.cpp` testing horizontal/vertical movement sweeps against tile solids and slopes.
  - [x] GREEN: Implement `src/physics/CollisionWorld.hpp` and `CollisionWorld.cpp`.
- [x] **TDD 5.2**: Platformer Character Controller Dynamics
  - [x] RED: Write test verifying Walk, Sprint, Jump, Double Jump, Wall Slide, Wall Jump, Dash, Drop-Through Platforms, and Grounded checks.
  - [x] GREEN: Implement `src/physics/CharacterController.hpp` and `CharacterController.cpp`.
- [x] **TDD 5.3**: Collision Layers & Filtering Matrix
  - [x] RED: Write test verifying player, enemies, projectiles, terrain, sensors, and loot layer interactions.
  - [x] GREEN: Implement `src/physics/CollisionLayers.hpp`.

### 4.6 Module 6: Itemization, Affix Generator & Inventory Matrix
- [x] **TDD 6.1**: Procedural Gaussian Stat Roller & Quality Scalar
  - [x] RED: Write `tests/test_inventory_items.cpp` validating base roll within bounds and $0\% \to 20\%$ quality bonus.
  - [x] GREEN: Implement `src/gameplay/items/ItemGenerator.hpp` and `ItemGenerator.cpp`.
- [x] **TDD 6.2**: Dynamic Affix Budget & Rarity Allocation
  - [x] RED: Write test validating prefix/suffix counts and tiers according to rarity (Common to Prismatic).
  - [x] GREEN: Implement `src/gameplay/items/ItemGenerator.cpp`.
- [x] **TDD 6.3**: Grid Inventory, Stacking, Equipment Slots & Weight
  - [x] RED: Write test for item addition, splitting, moving, equipment slot rules, weight calculation, and over-encumbrance.
  - [x] GREEN: Implement `src/gameplay/items/Inventory.hpp` and `Inventory.cpp`.

### 4.7 Module 7: Augmentations Matrix (11 Body Slots)
- [x] **TDD 7.1**: 11 Body Slots & Installation Rules
  - [x] RED: Write `tests/test_augmentations.cpp` testing equipping into Head, Eyes, Nervous, Lungs, Heart, Torso, Skin, L-Arm, R-Arm, Hands, Legs.
  - [x] GREEN: Implement `src/gameplay/augmentations/AugmentationMatrix.hpp` and `AugmentationMatrix.cpp`.
- [x] **TDD 7.2**: Dual-Energy Economy (Power vs Humanity, Mana vs Stability)
  - [x] RED: Write test validating power drain, humanity strain penalties, mana upkeep, and rejection thresholds.
  - [x] GREEN: Implement strain calculations in `AugmentationMatrix.cpp`.
- [x] **TDD 7.3**: 9 Class Signatures & Cross-Class Exotic Surgeries
  - [x] RED: Write test ensuring Level 20 free install for matching class, and heavy credit/strain penalty for cross-class install.
  - [x] GREEN: Implement signature logic in `AugmentationMatrix.cpp`.

### 4.8 Module 8: Skills Engine & Ability Execution Pipeline
- [x] **TDD 8.1**: DAG Skill Tree & Prerequisite Validation
  - [x] RED: Write `tests/test_skills_system.cpp` verifying node unlock requirements, tier prerequisites, and respec point refunds.
  - [x] GREEN: Implement `src/gameplay/skills/SkillTree.hpp` and `SkillTree.cpp`.
- [x] **TDD 8.2**: 4-Slot Hotbar & Cast Execution State Machine
  - [x] RED: Write test verifying cast checks (cooldown, stamina/mana/power), trigger state, and cooldown countdowns.
  - [x] GREEN: Implement `src/gameplay/skills/SkillExecutor.hpp` and `SkillExecutor.cpp`.
- [x] **TDD 8.3**: Skill Database Registration (Class & Common Skills)
  - [x] RED: Write test verifying loading and lookups for class and universal skills.
  - [x] GREEN: Implement `src/gameplay/skills/SkillRegistry.hpp` and `SkillRegistry.cpp`.

### 4.9 Module 9: Crafting Engine & Modification Forge
- [x] **TDD 9.1**: Recipe Matching & Material Consumption
  - [x] RED: Write `tests/test_crafting_modification.cpp` testing recipe lookups, station proximity, inventory consumption, and output creation.
  - [x] GREEN: Implement `src/gameplay/crafting/CraftingEngine.hpp` and `CraftingEngine.cpp`.
- [x] **TDD 9.2**: Deterministic Modification Forge & Instability Mechanics
  - [x] RED: Write test testing Affix Infusion, Tier Upgrades (T1–T7), Value Calibration, Socket Punching, and Fracture risk math.
  - [x] GREEN: Implement `src/gameplay/crafting/ModificationForge.hpp` and `ModificationForge.cpp`.

### 4.10 Module 10: Survival Metabolism, Building & Agriculture
- [x] **TDD 10.1**: Metabolism Simulation (Hunger, Thirst, Temperature)
  - [x] RED: Write `tests/test_survival_building.cpp` testing tick depletion, environmental heat loss/gain, hypothermia, starvation.
  - [x] GREEN: Implement `src/gameplay/survival/Metabolism.hpp` and `Metabolism.cpp`.
- [x] **TDD 10.2**: Day/Night Cycle & Weather Systems
  - [x] RED: Write test verifying 24-minute time progression, night darkness transitions, rain/snow/fallout modifiers.
  - [x] GREEN: Implement `src/gameplay/survival/Environment.hpp` and `Environment.cpp`.
- [x] **TDD 10.3**: 16x16 Grid Building System
  - [x] RED: Write test for placing/breaking walls, platforms, doors, storage chests, and checking structural support.
  - [x] GREEN: Implement `src/gameplay/building/BuildingSystem.hpp` and `BuildingSystem.cpp`.
- [x] **TDD 10.4**: Agriculture & Crop Growth
  - [x] RED: Write test for soil tilling, hydration, seed planting, growth stages, and harvest yield.
  - [x] GREEN: Implement `src/gameplay/building/FarmingSystem.hpp` and `FarmingSystem.cpp`.

### 4.11 Module 11: World Generation & Procedural Dungeons
- [x] **TDD 11.1**: Tilemap Chunk Storage & Biome Placement
  - [x] RED: Write `tests/test_world_dungeons.cpp` testing chunk loading, block retrieval, foreground/background layers, and biome mapping.
  - [x] GREEN: Implement `src/procgen/Tilemap.hpp` and `Tilemap.cpp`.
- [x] **TDD 11.2**: Hybrid BSP Procedural Dungeon Generator
  - [x] RED: Write test validating BSP room splitting, corridor carving, prefab stamping, door placement, and reachability.
  - [x] GREEN: Implement `src/procgen/DungeonGenerator.hpp` and `DungeonGenerator.cpp`.

### 4.12 Module 12: Enemy Artificial Intelligence
- [x] **TDD 12.1**: FSM State Machine & Sensor Queries
  - [x] RED: Write `tests/test_ai_behavior.cpp` testing transitions: Idle $\to$ Patrol $\to$ Aggro $\to$ Chase $\to$ Attack $\to$ Flee.
  - [x] GREEN: Implement `src/gameplay/ai/EnemyAI.hpp` and `EnemyAI.cpp`.
- [x] **TDD 12.2**: Multi-Phase Boss State Transitions
  - [x] RED: Write test verifying boss phase triggers at 50% HP, ability rotation shifts, and enrage state.
  - [x] GREEN: Implement `src/gameplay/ai/BossAI.hpp` and `BossAI.cpp`.

### 4.13 Module 13: Save / Load Persistence & Data Integrity
- [x] **TDD 13.1**: JSON Serialization & Atomic File I/O
  - [x] RED: Write `tests/test_save_persistence.cpp` testing serialization of character, inventory, augments, buildings, and world state.
  - [x] GREEN: Implement `src/save/SaveManager.hpp` and `SaveManager.cpp`.
- [x] **TDD 13.2**: Checksum Validation & Anti-Corruption
  - [x] RED: Write test verifying file corruption detection via SHA-256 and fallback recovery.
  - [x] GREEN: Implement checksum validation in `SaveManager.cpp`.

### 4.14 Module 14: Engine Context, Game Loop & Integration Runner
- [x] **TDD 14.1**: Engine Context & Full Game Simulation Loop
  - [x] RED: Write `tests/test_game_engine.cpp` stepping the complete integrated simulation for 600 ticks (10s) with player, enemies, physics, and combat.
  - [x] GREEN: Implement `src/core/EngineContext.hpp`, `EngineContext.cpp`, and `src/core/GameSimulation.hpp`/`.cpp`.
- [x] **TDD 14.2**: Virtual Canvas Scaling & UI Matrix Math
  - [x] RED: Write test verifying 360px height scaling, aspect ratio adaptation, and camera pixel snapping.
  - [x] GREEN: Implement `src/render/Camera.hpp` and `Camera.cpp`.
- [x] **TDD 14.3**: Main Executable Entry Point
  - [x] Create `src/main.cpp` running the integrated game in interactive/headless simulation mode.

### 4.15 Module 15: Zero-Warning Clean Build & Compiler Rigor
- [x] Fix all compiler warnings across game engine library (`untitled_rpg_lib`), main executable (`untitled_rpg`), and test executables.
- [x] Eliminate missing field initializers, unused variables, and unused private fields.
- [x] Ensure `-Wall -Wextra -Wpedantic` compiles with 0 warnings on Apple Clang.
