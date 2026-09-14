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
- [x] Define skill tree architecture, DAG prerequisite rules, and mathematical scaling formulas (`docs/skills.md`).
- [x] Design 40-node Shared Skill Tree across Mobility, Survival, Weapons, and Scavenging (`docs/skills.md`).
- [x] Outline initial 15-node starter tree per class for all 9 classes (135 skills).
- [ ] **Pending**: Fully design and catalog all 500+ skills in `docs/skills.md` (~50 skills per class for all 9 classes = 450 class skills + 40 shared + 48 crafting = 538 total skills).
  - [ ] Juggernaut complete skill tree (~50 skills)
  - [ ] Berserker complete skill tree (~50 skills)
  - [ ] Gunslinger complete skill tree (~50 skills)
  - [ ] Phantom complete skill tree (~50 skills)
  - [ ] Technomancer complete skill tree (~50 skills)
  - [ ] Medic / Biomancer complete skill tree (~50 skills)
  - [ ] Symbiote complete skill tree (~50 skills)
  - [ ] Warden complete skill tree (~50 skills)
  - [ ] Reanimator complete skill tree (~50 skills)

### 1.3 Body Augmentations (Goal: 250+ Unique Augmentations)
- [x] Define 11 body modification slots and the dual-track economy (Bionic Power/Humanity vs. Magitech Stability/Rejection) in `docs/augmentations.md`.
- [x] Specify the 9 Class Signature Augmentations with native Level 20 perks, cross-class acquisition rules, and exotic surgery penalties.
- [x] Detail Cyber-Clinic and Bio-Vat installation mechanics.
- [ ] **Pending**: Fully design and catalog all 250+ augmentations across all 11 slots in `docs/augmentations.md`.
  - [ ] Head slot (24 augmentations)
  - [ ] Eyes slot (22 augmentations)
  - [ ] Nervous System slot (24 augmentations)
  - [ ] Lungs slot (20 augmentations)
  - [ ] Heart / Core slot (26 augmentations)
  - [ ] Torso slot (25 augmentations)
  - [ ] Skin / Dermis slot (22 augmentations)
  - [ ] Left Arm slot (25 augmentations)
  - [ ] Right Arm slot (26 augmentations)
  - [ ] Hands slot (22 augmentations)
  - [ ] Legs slot (24 augmentations)

### 1.4 Itemization & Weapons (Goal: 3,000+ Unique Items)
- [x] Define item taxonomy across 10 equipment categories and 8 tiers (`docs/items.md`).
- [x] Define triangular/Gaussian probability curves for individual rolled base stats.
- [x] Define item quality modifier (0% to 20%), rarity tiers (Common to Prismatic), and dynamic affix budgets.
- [x] Define weapon categories (Melee, Ballistic, Energy, Magic, Shields), armor sets, and survival consumables.
- [ ] **Pending**: Fully design and catalog the 3,000+ base items catalog across all 10 categories and 8 progression tiers in `docs/items.md`.
  - [ ] Tier 1: Scrap / Rusted / Makeshift (Levels 1–10) -> 350 base items
  - [ ] Tier 2: Refined Iron / Bio-Cultured (Levels 11–20) -> 380 base items
  - [ ] Tier 3: Industrial Steel / Steam-Forged (Levels 21–30) -> 400 base items
  - [ ] Tier 4: Volcanic Slag / Titanium-Plated (Levels 31–40) -> 420 base items
  - [ ] Tier 5: Cryo-Alloy / Liquid Nitrogen (Levels 41–50) -> 440 base items
  - [ ] Tier 6: Dimensional Void / Warped (Levels 51–58) -> 450 base items
  - [ ] Tier 7: Archon Hard-Light / Sanctified (Levels 59–60) -> 460 base items
  - [ ] Tier 8 / Prismatic: Precursor & Rift God (Endgame 60+) -> 500+ base items

### 1.5 Crafting & Item Modification System
- [x] Design 48-node Crafting Specialization Tree across Weaponsmithing, Armor-Plating, Cyber-Engineering, and Bio-Alchemy (`docs/crafting/crafting_system.md`).
- [x] Design crafting stations (Workbench, Forge & Ammo Press, Kitchen Stove, Hydroponics Lab).
- [x] Design deterministic stat-crafting system: Affix Infusion, Tier Upgrading (1–7), Instability & Fracture mechanics, Value Calibration, Socket Punching, and Stasis Sealing.
- [x] **Crafting Recipes Catalog (`docs/crafting/recipes.md`)**: Cataloged **535 crafting recipes** across all 6 stations:
  - [x] Workbench basic tools, structures, furniture, and containers (85 recipes)
  - [x] Forge & Ammo Press metal smelting, weapons, ballistic ammo, and heavy armor (125 recipes)
  - [x] Cyber-Clinic & Assembly Bench bionics, energy weapons, electronics, and battery cells (110 recipes)
  - [x] Arcane Loom & Bio-Vat chimeric grafts, spell wands, enchanted robes, and catalysts (110 recipes)
  - [x] Kitchen Stove & Fermenter meals, survival rations, buffs, and purified drinks (70 recipes)
  - [x] Hydroponics Lab seeds, fertilizers, stimulants, and medical reagents (35 recipes)

### 1.6 World, Biomes & Procedural Dungeons (Goal: 20+ Biomes)
- [x] Outline 20+ unique biomes (12 surface, 10 subterranean/dimensional) in `docs/biomes/biomes_overview.md`.
- [x] Design procedural dungeon generation concept (hybrid BSP + prefab room templates in every biome).
- [x] Design 8 campaign dungeon tiers with multi-phase bosses culminating in The Architect.
- [x] Design Infinite Rift endgame with scaling mutators and Tier 9+ Prismatic gear.
- [x] Design death mechanics (No permadeath: consciousness recall to hub with 25% raw material drop in recovery drone).
- [ ] **Pending**: Extract and detail individual documents for all 22 biomes in `docs/biomes/` (enemy spawn tables, hazard parameters, environmental conditions, and dungeon themes):
  - [x] Surface Biome: `the_haven.md`
  - [x] Surface Biome: `rustwood_forest.md`
  - [ ] Surface Biome: `whispering_taiga.md`
  - [x] Surface Biome: `ashen_foundry.md`
  - [x] Surface Biome: `cryo_glacier.md`
  - [x] Surface Biome: `bioluminescent_bog.md`
  - [ ] Surface Biome: `sunken_megalopolis.md`
  - [ ] Surface Biome: `scorched_desert.md`
  - [ ] Surface Biome: `radioactive_waste.md`
  - [ ] Surface Biome: `acidic_salt_flats.md`
  - [ ] Surface Biome: `iron_jungle.md`
  - [ ] Surface Biome: `sky_archipelago.md`
  - [ ] Subterranean Biome: `rusted_catacombs.md`
  - [ ] Subterranean Biome: `overgrown_bio_labs.md`
  - [ ] Subterranean Biome: `submerged_vaults.md`
  - [ ] Subterranean Biome: `molten_smeltery.md`
  - [ ] Subterranean Biome: `cryo_stasis_depths.md`
  - [ ] Subterranean Biome: `void_factory.md`
  - [ ] Subterranean Biome: `hard_light_citadel.md`
  - [ ] Subterranean Biome: `sunken_orbital_core.md`
  - [ ] Subterranean Biome: `crystal_caverns.md`
  - [x] Dimensional Endgame Biome: `infinite_rift.md`

### 1.7 Granular Documentation Reorganization & Item Catalogs
- [x] **Documentation Folder Restructuring**:
  - [x] `docs/architecture/`: Technical structure, file tree, system update loop, and functions reference per file.
  - [x] `docs/classes/`: All 9 classes extracted into standalone documents (`berserker_barbarian.md`, `juggernaut_warrior.md`, `gunslinger_ranger.md`, `phantom_rogue.md`, `technomancer_mage.md`, `medic_cleric.md`, `symbiote_druid.md`, `warden_paladin.md`, `reanimator_necromancer.md`, `classes_overview.md`).
  - [x] `docs/skills/`: Skills framework, DAG rules, and active hotbar mechanics.
  - [x] `docs/augmentations/`: Augmentations framework, dual economy, and class signature augments.
  - [x] `docs/items/`: Itemization math, Gaussian distribution, quality, and affix pools.
  - [x] `docs/crafting/`: Crafting trees, modification forge, and station rules.
  - [x] `docs/combat/`: Terraria-style combat, damage pipeline, and status effects.
  - [x] `docs/survival/`: Survival meters, 16x16 building, and farming.
  - [x] `docs/biomes/`: Biomes overview and world structure.
  - [x] `docs/dungeons/`: Procedural dungeon generation concept.
  - [x] `docs/test_plans/`: Modular unit test plans.
- [ ] **Granular Items Folder Structure & 3,000+ Items Catalog**:
  - [x] Create granular item subdirectories: `docs/items/weapons/`, `docs/items/armor/`, `docs/items/accessories/`, `docs/items/consumables/`, `docs/items/materials/`, `docs/items/tools/`
  - [ ] Detail each granular item grouping file with individual stat roll ranges, tiers, and drop rules across all 3,000 items:
    - [x] `docs/items/weapons/swords_greatswords.md` (200 weapons)
    - [x] `docs/items/weapons/daggers_knives.md` (150 weapons)
    - [ ] `docs/items/weapons/axes_hammers.md` (150 weapons)
    - [ ] `docs/items/weapons/spears_polearms.md` (120 weapons)
    - [x] `docs/items/weapons/revolvers_pistols.md` (150 weapons)
    - [x] `docs/items/weapons/shotguns.md` (120 weapons)
    - [x] `docs/items/weapons/rifles_carbines.md` (160 weapons)
    - [ ] `docs/items/weapons/sniper_rifles.md` (100 weapons)
    - [ ] `docs/items/weapons/heavy_firearms.md` (100 weapons)
    - [x] `docs/items/weapons/plasma_blasters.md` (120 weapons)
    - [ ] `docs/items/weapons/lasers_beams.md` (100 weapons)
    - [ ] `docs/items/weapons/arc_lightning.md` (80 weapons)
    - [ ] `docs/items/weapons/railguns.md` (60 weapons)
    - [x] `docs/items/weapons/wands_scepters.md` (160 weapons)
    - [ ] `docs/items/weapons/staffs.md` (140 weapons)
    - [ ] `docs/items/weapons/grimoires_tomes.md` (100 weapons)
    - [x] `docs/items/weapons/shields_deflectors.md` (120 shields/off-hands)
    - [x] `docs/items/armor/helmets.md` (150 headpieces)
    - [x] `docs/items/armor/chestplates.md` (180 chest armors)
    - [x] `docs/items/armor/greaves_legs.md` (160 leg armors)
    - [x] `docs/items/armor/boots_footwear.md` (150 boots)
    - [x] `docs/items/accessories/rings.md` (120 rings)
    - [ ] `docs/items/accessories/amulets.md` (100 amulets)
    - [ ] `docs/items/accessories/relics_cores.md` (80 relics)
    - [x] `docs/items/consumables/food_drink.md` (120 meals and drinks)
    - [ ] `docs/items/consumables/potions_medicine.md` (100 potions and remedies)
    - [x] `docs/items/materials/ores_ingots.md` (60 metals and minerals)
    - [ ] `docs/items/materials/monster_parts.md` (80 bio-reagents)
    - [ ] `docs/items/materials/tech_salvage.md` (80 cyber components)
    - [x] `docs/items/tools/harvesting_tools.md` (60 pickaxes, axes, hoes, scanners)

### 1.8 Technical Architecture, API & Test Planning
- [x] **Remove All Existing Code**: Delete all premature C++ implementation files (`src/`, `CMakeLists.txt`, `cmake/`) so the repository is strictly in the design and planning phase.
- [x] **Code Architecture & File Structure Specification (`docs/architecture/architecture.md`)**:
  - [x] Complete directory and file layout for the entire engine and gameplay codebases.
  - [x] System architecture diagrams, ECS dataflow, memory management, and update loops.
  - [x] Client/server simulation boundary for future online multiplayer.
- [x] **Function Specifications by File (`docs/architecture/functions_reference.md`)**:
  - [x] Detailed functional specification for every file in the architecture.
  - [x] Specific functions, methods, parameters, return types, error handling, and state mutations.
- [x] **Comprehensive Test Plans (`docs/test_plans/`)**:
  - [x] Core platform test plan (`docs/test_plans/core_platform_test_plan.md`)
  - [x] Physics & controller test plan (`docs/test_plans/physics_controller_test_plan.md`)
  - [x] Combat & damage test plan (`docs/test_plans/combat_stats_test_plan.md`)
  - [x] Skills & progression test plan (`docs/test_plans/skills_progression_test_plan.md`)
  - [x] Augmentations & dual economy test plan (`docs/test_plans/augmentations_test_plan.md`)
  - [x] Items & inventory test plan (`docs/test_plans/items_inventory_test_plan.md`)
  - [x] Crafting & modification test plan (`docs/test_plans/crafting_modification_test_plan.md`)
  - [x] Survival, building & farming test plan (`docs/test_plans/survival_building_test_plan.md`)
  - [x] World, biomes & procgen test plan (`docs/test_plans/world_dungeons_test_plan.md`)

### 1.9 Documentation Quality & Standards
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

## 3. Next Steps (In Order of Priority)

1. **Granular Items Folder Structure & Catalog (`docs/items/`)**: Populate granular item files covering all 3,000+ base items across `weapons/`, `armor/`, `accessories/`, `consumables/`, `materials/`, `tools/`.
2. **Extract Biomes into Dedicated Documents (`docs/biomes/`)**: Create standalone specification files for each of the 22 biomes with hazards, visual aesthetics, enemy spawns, resource tables, and dungeon themes.
3. **Extract Augmentations by Slot (`docs/augmentations/`)**: Create slot-by-slot specification files across all 11 body slots to catalog all 250+ augmentations.
4. **Expand Skills Catalog (`docs/skills/`)**: Expand class trees from 15 to ~50 skills each across all 9 classes.
5. **Final Review & Alignment**: Verify all modular design documents are 100% complete, code-free, cleanly linked, and aligned with `PLAN.md`.
