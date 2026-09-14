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
- [x] **Detailed individual dossiers for biomes in `docs/biomes/`**:
  - [x] `the_haven.md` (Hub Valley)
  - [x] `rustwood_forest.md` (Forest Frontier)
  - [x] `ashen_foundry.md` (Industrial Slag Heaps)
  - [x] `cryo_glacier.md` (Frost Peaks)
  - [x] `bioluminescent_bog.md` (Fungal Swamplands)
  - [x] `subterranean_caverns.md` (Underground Mines & Caves)
  - [x] `sunken_necropolis.md` (Deep Mausoleums & Tombs)
  - [x] `volcanic_core.md` (Mantle Magma Trenches)
  - [x] `toxic_waste_tunnels.md` (Chemical Sewers)
  - [x] `sunken_oceanic_trenches.md` (Underwater Coral Reefs)
  - [x] `floating_astral_islands.md` (Stratosphere Archon Shrines)
  - [x] `crystal_spires.md` (Prismatic Geodes)
  - [x] `haunted_graveyards.md` (Cursed Mire)
  - [x] `cyber_wasteland.md` (Automated Assembly Megaplexes)
  - [x] `mutagenic_flesh_pits.md` (Eldritch Gestation Cavities)
  - [x] `chrono_distortion_desert.md` (Glass Sand & Time Anomalies)
  - [x] `infinite_void_rift.md` (Endgame Singularities)

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

## 3. Next Steps (In Order of Priority)

1. **Expand Architecture Folder (`docs/architecture/`)**: Create granular subsystem technical architecture markdowns (`ecs_dataflow.md`, `physics_simulation.md`, `rendering_pipeline.md`, `input_action_mapping.md`, `multiplayer_networking.md`, `ui_hierarchy.md`, `save_persistence.md`).
2. **Restructure Augmentations Folder (`docs/augmentations/`)**: Create `docs/augmentations/slots/` with 11 individual slot files and `class_signatures.md`.
3. **Split Recipes into Granular Files (`docs/crafting/recipes/`)**: Split `recipes.md` into 7 specialized category files.
4. **Expand Consumables (`docs/items/consumables/`)**: Create `potions_medicine.md`, `combat_stims_injectors.md`, `mutagens_exotics.md`, and `scrolls_transponders.md`.
5. **Expand Accessories (`docs/items/accessories/`)**: Create `necklaces_amulets.md`, `pendants_talismans.md`, `earrings_studs.md`, `toe_rings_anklets.md`, and `relics_power_cores.md`.
6. **Expand Materials (`docs/items/materials/`)**: Create `rare_exotics.md`, `monster_parts.md`, `tech_salvage.md`, and `textiles_fibers.md`.
7. **Expand Skills Catalog (`docs/skills/`)**: Create `common_trees.md` and 9 dedicated class skill markdowns with ~50 skills each.
8. **Extract Remaining Biomes (`docs/biomes/`)**: Create standalone specification files for the remaining 16 biomes.
9. **Final Review & Alignment**: Verify all modular design documents are 100% complete, code-free, cleanly linked, and aligned with `PLAN.md`.
