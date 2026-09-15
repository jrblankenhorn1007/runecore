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

### 4.16 Module 16: Complete Interactive Playable Game Systems
- [x] **TDD 16.1**: Dynamic Projectiles & 360-Degree Aiming
  - [x] RED: Write unit tests in `tests/test_projectiles_loot.cpp` verifying projectile spawning along 360-degree aim vectors, lifetime decay, collision with terrain and enemies, and penetration counts.
  - [x] GREEN: Implement `src/gameplay/combat/ProjectileSystem.hpp` and `ProjectileSystem.cpp`.
- [x] **TDD 16.2**: Dropped World Loot & Magnetic Vacuum Pickup
  - [x] RED: Write unit tests in `tests/test_projectiles_loot.cpp` verifying dropped item physics (gravity, bouncing on terrain), proximity magnetic attraction to player, and automatic inventory pickup.
  - [x] GREEN: Implement `src/gameplay/items/LootSystem.hpp` and `LootSystem.cpp`.
- [x] **TDD 16.3**: Mining, Tile Breaking & Block Placement
  - [x] RED: Write unit tests in `tests/test_world_interaction.cpp` verifying player reach distance, breaking foreground tiles (spawning drop items), placing blocks from inventory, and updating physics world collision.
  - [x] GREEN: Implement `src/gameplay/building/WorldInteraction.hpp` and `WorldInteraction.cpp`.
- [x] **TDD 16.4**: Overworld $\leftrightarrow$ Procedural Dungeon Level Transitions
  - [x] RED: Write unit tests in `tests/test_world_interaction.cpp` verifying world context swapping between Overworld and BSP Dungeon, maintaining player state, and positioning at dungeon entrance/exit.
  - [x] GREEN: Implement level transition management in `GameSimulation.cpp`.
- [x] **TDD 16.5**: Active 4-Skill Hotbar Execution & Visual Particles
  - [x] RED: Write unit tests verifying hotbar triggers for Q (Seismic Slam), E (Rocket Dash), R (EMP Arc Discharge), F (Nanite Heal Surge).
  - [x] GREEN: Integrate hotbar skills and active cooldown/effects in `GameSimulation.cpp`.
- [x] **TDD 16.6**: In-Game UI Overlay Modes (Inventory, Crafting, Augmentations, Skills, Minimap)
  - [x] Implement toggleable UI screens for Inventory (`Tab`), Crafting (`C`), Augmentations (`U`), and Dungeon Minimap (`M`).
  - [x] Implement visual slot cards and interactive HUD overlays in `src/render/Renderer.cpp`.
- [x] **TDD 16.7**: Dynamic Point-Light & Ambient Darkness Composite
  - [x] Implement 2D circular light attenuation around player, torches, and projectiles cutting into day/night darkness in `src/render/Renderer.cpp`.
- [x] **TDD 16.8**: Full Interactive Verification & Final Zero-Warning Build
  - [x] Verify complete interactive experience in SDL3 window with mouse aiming, shooting, mining, crafting, dungeon diving, and combat.
  - [x] Verify 100% test passage across all 16 test suites with 0 compiler warnings.

### 4.17 Module 17: Autonomous Bot Controller & Scenario Testing
- [x] **TDD 17.1**: Automated Bot Controller Architecture (`src/core/BotTester.hpp` & `.cpp`)
  - [x] Implemented multi-phase test sequence covering all 12 key gameplay systems (Movement, Jumps, Wall-Kicks, Mining, Loot Vacuum, Crafting, 360-degree Ranged Projectiles, Melee Combat, Active Skills Q/E/R/F, Procedural Dungeon Navigation, Boss Defeat, Level-Up).
  - [x] Written `tests/test_bot_tester.cpp` with Catch2 verification asserting 12/12 subsystems pass.
  - [x] Integrated `--bot` and `--bot --headless` command-line modes into main executable allowing autonomous hands-free gameplay testing in both interactive graphical window and headless CLI.

### 4.18 Module 18: Overworld Biome Engine & Environmental Hazards
- [x] **TDD 18.1**: Multi-Biome Overworld Mapping & Ambient Climates
  - [x] RED: Write unit tests in `tests/test_biomes_system.cpp` testing horizontal biome coordinates (Haven -> Rustwood -> Ashen Foundry -> Cryo Glacier -> Bioluminescent Bog), ambient temperature transitions (-20°C to +85°C), and biome metadata.
  - [x] GREEN: Implement `src/procgen/BiomeSystem.hpp` and `BiomeSystem.cpp`.
- [x] **TDD 18.2**: Hazard Tiles (Spikes, Lava, Acid Sludge)
  - [x] RED: Write unit tests verifying tile contact damage, status ailment infliction (Lava -> Burn, Acid -> Armor Corrode, Spikes -> Impale Bleed), and hazard bitmask checks.
  - [x] GREEN: Implement hazard tile interaction in `BiomeSystem.cpp` and `CollisionWorld.cpp`.

### 4.19 Module 19: Expanded Weapon Mechanics, Shotguns, Ammo & Shield Parry
- [x] **TDD 19.1**: Firearm Ammunition Magazines & Active Reloads
  - [x] RED: Write unit tests in `tests/test_weapon_arsenal.cpp` verifying magazine capacities, ammo depletion, reload delays, and out-of-ammo dry-fire checks.
  - [x] GREEN: Implement `src/gameplay/combat/WeaponArsenal.hpp` and `WeaponArsenal.cpp`.
- [x] **TDD 19.2**: Multi-Pellet Shotgun Spread & Supersonic Railguns
  - [x] RED: Write unit tests verifying cone spread with 8 pellets per shell and wall-piercing supersonic slugs.
  - [x] GREEN: Implement specialized firing modes in `WeaponArsenal.cpp`.
- [x] **TDD 19.3**: Shield Blocking, Stamina Guard & Timed Parries
  - [x] RED: Write unit tests verifying 100% frontal damage block, stamina block drain, and timed parry window (0.2s) reflecting projectiles and staggering attackers.
  - [x] GREEN: Implement shield mechanics in `WeaponArsenal.cpp`.

### 4.20 Module 20: NPC Housing, Settlement Recruitment & Quests
- [x] **TDD 20.1**: Settlement Housing Suitability Checks
  - [x] RED: Write unit tests in `tests/test_settlement_quests.cpp` evaluating room enclosure (walls, roof, floor, door, light source, chair/bed) to validate NPC move-in conditions.
  - [x] GREEN: Implement `src/gameplay/survival/SettlementSystem.hpp` and `SettlementSystem.cpp`.
- [x] **TDD 20.2**: Quest Engine & Objective Progression
  - [x] RED: Write unit tests tracking quest states (Unstarted, Active, Completed), objective progress counters (Mine 5 Iron, Slay Dungeon Boss, Craft Weapon), and reward delivery.
  - [x] GREEN: Implement `src/gameplay/survival/QuestSystem.hpp` and `QuestSystem.cpp`.

### 4.21 Module 21: High-Performance 2D Particle Engine
- [x] **TDD 21.1**: Particle Pool Emitter & Dynamics
  - [x] RED: Write unit tests in `tests/test_particle_system.cpp` verifying particle spawning, lifetime decay, velocity damping, gravity, and color blending.
  - [x] GREEN: Implement `src/render/ParticleSystem.hpp` and `ParticleSystem.cpp`.
- [x] **TDD 21.2**: Combat FX Emitters (Sparks, Blood, Muzzle Flash, Dust)
  - [x] RED: Write unit tests verifying emission on sword hit, projectile explosion, and jump dust.
  - [x] GREEN: Integrated particle pool and lifecycle in `src/render/ParticleSystem.cpp`.

### 4.22 Module 22: Code Coverage Enhancement & 1:1 Mirrored Test Architecture
- [x] **Restructure Test Suite into Standard 1:1 Mirrored Directory Tree**:
  - [x] `tests/core/`: `test_Math.cpp`, `test_Random.cpp`, `test_Time.cpp`, `test_EventBus.cpp`, `test_EngineContext.cpp`, `test_GameSimulation.cpp`, `test_BotTester.cpp`
  - [x] `tests/ecs/`: `test_Components.cpp`
  - [x] `tests/gameplay/ai/`: `test_EnemyAI.cpp`, `test_BossAI.cpp`
  - [x] `tests/gameplay/augmentations/`: `test_AugmentationMatrix.cpp`
  - [x] `tests/gameplay/building/`: `test_BuildingSystem.cpp`, `test_FarmingSystem.cpp`, `test_WorldInteraction.cpp`
  - [x] `tests/gameplay/classes/`: `test_ClassRegistry.cpp`
  - [x] `tests/gameplay/combat/`: `test_DamageCalculator.cpp`, `test_CombatSystem.cpp`, `test_StatusEffects.cpp`, `test_ProjectileSystem.cpp`, `test_WeaponArsenal.cpp`
  - [x] `tests/gameplay/crafting/`: `test_CraftingEngine.cpp`, `test_ModificationForge.cpp`
  - [x] `tests/gameplay/items/`: `test_Item.cpp`, `test_ItemGenerator.cpp`, `test_Inventory.cpp`, `test_LootSystem.cpp`
  - [x] `tests/gameplay/skills/`: `test_SkillTree.cpp`, `test_SkillRegistry.cpp`, `test_SkillExecutor.cpp`
  - [x] `tests/gameplay/stats/`: `test_StatsSystem.cpp`, `test_Progression.cpp`
  - [x] `tests/gameplay/survival/`: `test_Metabolism.cpp`, `test_Environment.cpp`, `test_SettlementSystem.cpp`, `test_QuestSystem.cpp`
  - [x] `tests/physics/`: `test_CollisionLayers.cpp`, `test_CollisionWorld.cpp`, `test_CharacterController.cpp`
  - [x] `tests/procgen/`: `test_Tilemap.cpp`, `test_DungeonGenerator.cpp`, `test_BiomeSystem.cpp`
  - [x] `tests/render/`: `test_Camera.cpp`, `test_ParticleSystem.cpp`, `test_Renderer.cpp`
  - [x] `tests/input/`: `test_InputManager.cpp`
  - [x] `tests/save/`: `test_SaveManager.cpp`
- [x] **Fix All Warnings in Build**:
  - [x] Audit all 46 test executables and library files under `-Wall -Wextra -Wpedantic`.
  - [x] Eliminate missing field initializers in `src/core/BotTester.cpp`.
  - [x] Remove unused private fields in `src/core/BotTester.hpp`.
  - [x] Eliminate unused local variables in `tests/ecs/test_Components.cpp` and `tests/gameplay/combat/test_StatusEffects.cpp`.
  - [x] Verify clean, warning-free build across all targets (`ninja -C build` with 0 warnings).
- [x] **Achieve Near-100% Code Coverage**:
  - [x] Comprehensive edge condition, failure case, and method tests implemented across all 47 test suites.
  - [x] Measured **98.0% line coverage** and **97.6% function coverage** across all engine, gameplay, physics, procgen, rendering, and persistence modules via `gcov` and `gcovr`.
  - [x] 100% line coverage achieved across `GameSimulation`, `Math`, `Random`, `Time`, `EnemyAI`, `BossAI`, `BuildingSystem`, `FarmingSystem`, `WorldInteraction`, `CombatSystem`, `DamageCalculator`, `StatusEffects`, `WeaponArsenal`, `CraftingEngine`, `ModificationForge`, `ItemGenerator`, `LootSystem`, `SkillExecutor`, `SkillRegistry`, `SkillTree`, `Progression`, `StatsSystem`, `Environment`, `Metabolism`, `QuestSystem`, `SettlementSystem`, `InputManager`, `CharacterController`, `CollisionWorld`, `BiomeSystem`, `DungeonGenerator`, `Tilemap`, `Camera`, `ParticleSystem`, and `SaveManager`.

### 4.23 Module 23: Autonomous Gameplay Auto-Pilot & Non-Blocking Execution
- [x] **Default Auto-Pilot Mode**: Running `./build/untitled_rpg` actively plays the game on screen automatically without waiting for user action.
- [x] **Seamless Human Takeover**: If a user presses movement or action keys, manual mode engages immediately with indefinite playtime until Escape.
- [x] **Autonomous Full Playthrough & Auto-Exit**: The autonomous bot executes the complete 12-system scenario (Movement, Jumps, Wall-Kicks, Mining, Loot Vacuum, Crafting, 360-degree Ranged Projectiles, Melee Combat, Active Skills, Dungeon Diving, Boss Fight), outputs the verification report, saves the game, and exits cleanly.

### 4.24 Module 24: Focused Game-Launched QA Harness
- [x] Add isolated fresh-simulation scenarios for movement, jumping, mining, loot pickup, crafting, projectiles, melee, skills, dungeon entry, feedback systems, and UI mode toggles.
- [x] Add `--qa <scenario>` CLI execution with nonzero exit status on failure and measurable result details.
- [x] Add `--qa-list` discovery output and `--qa all` aggregate execution that prints every scenario result.
- [x] Cover each focused scenario in `test_BotTester.cpp` and verify each scenario can boot and pass independently.
- [x] Expand focused scenarios to cover persistence, NPC settlement, hazards, boss phases, and keyboard/mouse workflows.
- [x] Register each workflow as an individually runnable `test_<scenario>` CTest process that boots a fresh `GameSimulation` through `untitled_rpg --qa <scenario>`.
- [x] Provide isolated processes for movement, jumping, mining, loot, crafting, projectile, melee, skills, dungeon, feedback, UI, persistence, hazards, settlement, boss, and input.
- [x] Add isolated processes for inventory movement/use, settings, character creation, and respawn.
- [x] Expand `test_inventory_drag` into full mouse drag/drop, equipment paperdoll, tooltip, and right-click item-use coverage.

---

## 5. Commercial Pre-Launch Production Roadmap (The Road to 1.0 Release)

This roadmap details all player-facing features, audiovisual juice, interactive GUI systems, and gameplay loops required to transition Untitled RPG from an architectural simulation into a complete, commercial-grade 2D sidescrolling ARPG.

### 5.1 Combat Feel, Game-Juice & Visual Feedback
- [x] **Floating Combat Text (FCT) System**:
  - [x] Render dynamic bouncing damage numbers on hit: White for standard physical hits, Orange for fire/burn, Cyan for cold/frost, Yellow for critical strikes ("CRIT! 150"), Green for health restoration ("+45 HP"), Violet for XP ("+100 XP").
  - [x] Text gravity and drift: numbers pop upwards with initial velocity and fade out over 0.75 seconds.
- [x] **Enemy Hit-Flash & Health Bar Display**:
  - [x] Flash enemy sprite pure white for 2 frames ($33\text{ ms}$) on taking damage.
  - [x] Overhead health bar that stays visible for 3 seconds after receiving damage, with phase/armor-style pip indicators.
- [x] **Enemy Death Effects & Dissolution**:
  - [x] Enemies emit family-specific colored debris bursts and distinct death audio before removal.
  - [x] 3-frame death stretch/squash animation with deferred removal state.
- [x] **Hitstop & Freeze-Frame Impact**:
  - [x] Implemented a 40 ms simulation pause on successful melee impacts.
- [x] **Camera Screen Shake & Trauma Decay**:
  - [x] Camera trauma changes the snapped view and decays over time for heavy attacks and level-up impacts.
- [x] **Weapon-in-Hand Visualization & 360-Degree Aiming**:
  - [x] Render equipped weapon sprite in the player's hands rotating 360 degrees to point toward the mouse cursor.
  - [x] Weapon swing animations (overhead arc chop, horizontal thrust, gun recoil kickback) synchronized with hitbox active frames.

### 5.2 Enemy Archetypes, AI Behaviors & Boss Mechanics
- [x] **Enemy Roster Implementation (Minimum 15 Distinct Overworld & Dungeon Mobs)**:
  - [ ] *Jumping Slimes / Acid Blobs*: Hop towards player, squash on landing, split into mini-slimes on death.
  - [ ] *Cave Bats & Flying Harpies*: Perch on ceilings, screech to alert swarms, swoop in dive-bombs and retreat to ceiling.
  - [ ] *Saurian Raptors & Dire Beasts*: Rapid sprint, leap pounces with pin mechanics, bleeding bites.
  - [ ] *Rogue Snipers & Raider Gunners*: Maintain 8-tile distance, take cover behind terrain, fire laser-sighted bullet volleys.
  - [ ] *Armored Carapace Beetles*: Impenetrable frontal shield; player must jump behind them or use armor-piercing weapons.
- [x] **Telegraphed Boss Fights with Dedicated Boss HUD**:
  - [x] Boss health bar anchored at top-center of screen with phase markers and shield-layer indicators.
  - [ ] Visual ground telegraphs: Red danger lanes and expanding circles 1 second before colossal slams or laser sweeps.
  - [x] Multi-phase arena shifts: Boss entering enrage at 50% HP triggers arena-wide hazards, minion summons, and new attack patterns.
  - [x] Boss defeat slow-motion explosion with guaranteed epic loot fountain.

### 5.3 Player Progression, Level-Up Celebration & Character Sheet
- [x] **Level-Up Fanfare & Visual Feedback**:
  - [x] Golden particle pillar/burst, level-up fanfare, camera impact, and floating level banner on level-up.
  - [ ] Screen-center banner still needs full attribute/skill-point text presentation.
- [x] **Interactive Character Sheet (`I` Key)**:
  - [x] Display RPG attributes breakdown: STR, DEX, INT, VIT, WIS, CYB.
  - [x] Clickable `[+]` buttons allocate unspent attribute points through the simulation.
  - [ ] Detailed stats panel: Physical/Energy Armor, resistances (Fire, Cold, Shock, Nature, Dark, Holy), movement speed, attack speed, and carry weight.
- [x] **Interactive Skill Tree UI (`K` Key)**:
  - [x] Visual starter node graph for mobility, combat, and survival skills.
  - [x] Click-to-allocate respects prerequisites and skill-point availability.
  - [ ] Connecting paths, hover tooltips, confirmation, and respec UI remain to be added.

### 5.4 Full Mouse-Driven GUI & Inventory Paperdoll
- [ ] **Interactive 40-Slot Grid Inventory (`Tab` Key)**:
  - [ ] Drag-and-drop or shift-click item movement between inventory slots and equipment slots.
  - [ ] Right-click to consume potions, stims, or food directly from inventory.
  - [ ] Full Equipment Paperdoll: 10 visual slots (Main Hand, Off Hand, Helmet, Chestplate, Greaves, Boots, Ring 1, Ring 2, Amulet, Relic).
  - [ ] Dynamic Item Tooltips: Render item name in rarity color, tier badge, rolled base stats, quality percentage ($+0\%$ to $+20\%$), prefix/suffix affixes, and socket display.
- [ ] **Interactive Crafting Forge GUI (`C` Key)**:
  - [ ] Categorized tabs: Weapons, Armor, Bionics, Alchemy, Cooking, Structures.
  - [ ] Search bar and filter by "Craftable Only".
  - [ ] Clickable recipe cards showing required ingredients vs held amounts with a prominent `[Craft]` button.
- [ ] **Interactive Cyber-Clinic / Augmentations Screen (`U` Key)**:
  - [ ] Visual 11-slot cyborg body doll with glowing slot sockets.
  - [ ] Live humanity strain bar vs rejection threshold, and net bionic power generation/upkeep meter.
  - [ ] Drag-and-drop bionic and chimeric implants with surgical confirmation prompts.

### 5.5 World Aesthetics, Procedural Biomes & Parallax
- [x] **Multi-Layer Parallax Backgrounds**:
  - [x] 4 background parallax layers scrolling at varying speeds (distant mountains, ruined city towers, clouds, foreground hills).
  - [x] Biome-specific background themes shifting dynamically as player walks horizontally across the world.
- [x] **Tile Palette Richness & Autotiling**:
  - [ ] Organic terrain transitions: Grass tufts on top of dirt blocks, dripping stalactites beneath stone blocks, snow caps on ice blocks.
  - [ ] Sloped tiles ($45^\circ$ ramps) for smooth hill ascents and descents without blocky stepping.
- [x] **Day/Night & Weather Visual Composite**:
  - [ ] Dynamic sky color transitions: Golden sunrise, bright midday, crimson sunset, deep midnight starlight.
  - [x] Weather particle effects: Falling rain droplets, blizzard snow flurries, falling volcanic embers, radioactive dust haze.
  - [ ] Light sources (torches, campfires, laser blasts, bioluminescent moss) illuminating the darkness with soft circular attenuation.

### 5.6 Dungeons, Exploration & World Discovery
- [ ] **Procedural Dungeon Overworld Entrances**:
  - [ ] Physical ruin structures, temple gates, and bunker blast doors placed across biomes with interactive entry triggers (`W` key).
  - [ ] Dungeon interior generation: Multi-room BSP layouts with varied elevations, locked security doors, and hidden secret rooms behind destructible walls.
- [x] **Interactive Dungeon Props**:
  - [ ] *Treasure Chests*: Golden, wooden, and precursor chests; opening them plays a creak sound and pops out Gaussian-rolled loot items.
  - [ ] *Keycards & Levers*: Coloured doors (Red, Blue, Gold) requiring matching keys dropped by dungeon elites.
  - [ ] *Dungeon Traps*: Pressure plate dart traps, swinging blade pendulums, and collapsing crumbling floors over spike pits.
- [x] **Mini-Map & Full Map Screen (`M` Key)**:
  - [ ] Fog of war: Unexplored dungeon rooms hidden until entered.
  - [ ] Icons indicating player position, dungeon entrance, key locations, chests, and boss chambers.

### 5.7 Audio Engine & Soundscapes
- [x] Fix normal windowed startup forcing the audio engine into headless mode; QA and benchmark runs remain silent/headless.
- [x] **Sound Effects Engine (SDL3 Audio Stream / Miniaudio)**:
  - [ ] *Combat SFX*: Weapon swings (heavy blade whoosh, dagger snick), firearm reports (revolver crack, shotgun boom, minigun whir), laser beam hums, and flesh/armor impact sounds.
  - [ ] *Player Movement SFX*: Footsteps on dirt/stone/wood/snow, jump grunt, double jump whoosh, land thud, wall slide scrape.
  - [ ] *World & Mining SFX*: Pickaxe clinking on stone/ore, wood chopping thud, block break pop, water splash.
  - [ ] *UI & Feedback SFX*: Inventory slot click, item equip thud, potion drinking gulp, XP pickup chime, level-up trumpet fanfare.
- [x] **Dynamic Soundtrack**:
  - [ ] Peaceful acoustic/synth soundtrack in The Haven Hub.
  - [ ] Ambient atmospheric tracks for forests, caves, and ruins.
  - [ ] Driving, high-tempo battle themes during elite and boss encounters.

### 5.8 Terraria-Style Settlement Building & Town NPCs
- [x] **Base Building Tools**:
  - [ ] Differentiate tool powers: Pickaxes mine solid blocks; Axes chop trees and wooden furniture; Hammers break background walls.
  - [ ] Placement preview: Ghost translucent block rendered at cursor position showing valid placement.
- [x] **NPC Town Recruitment**:
  - [x] Town NPCs move in when an enclosed house (walls, door, light source, chair/bed) is constructed in the Haven valley.
  - [ ] *Blacksmith*: Sells metal ingots, repairs equipment, forges weapons.
  - [ ] *Cyber-Surgeon*: Performs bionic installations, cleanses rejection strain, sells batteries.
  - [ ] *Alchemist*: Sells herbs, glass vials, and brewing recipes.
  - [ ] *Guide / Quest-Giver*: Offers introductory quests, tutorials, and tracks boss progression.

### 5.9 Pre-Launch Polish, Settings & Save Management
- [x] **Options & Settings Menu (`Esc` Key)**:
  - [ ] Video settings: Fullscreen Borderless, Exclusive Fullscreen, Windowed, Resolution picker, V-Sync, Integer Scaling toggle.
  - [x] Live Master Volume and SFX Volume sliders.
  - [ ] Music/Ambience sliders and rebindable controls remain to be added.
- [x] **Multiple Save Slots & Character Creation**:
  - [ ] Title Screen with Save Slot selection (Slots 1–3), showing Character Name, Class, Level, and Playtime.
  - [ ] New Game character creation screen: Pick name, class archetype, and visual visor color.
- [x] **Death & Respawn Sequence**:
  - [ ] Death screen: Screen fades to red/black, displaying "CONSCIOUSNESS RECALL INITIATED".
  - [ ] Respawn at the Hub clinic medical bed or player-placed bed roll with full health, leaving a recovery drone with dropped materials at death site.
