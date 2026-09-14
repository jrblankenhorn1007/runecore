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
- [x] Design 48-node Crafting Specialization Tree across Weaponsmithing, Armor-Plating, Cyber-Engineering, and Bio-Alchemy (`docs/crafting.md`).
- [x] Design crafting stations (Workbench, Forge & Ammo Press, Kitchen Stove, Hydroponics Lab).
- [x] Design deterministic stat-crafting system: Affix Infusion, Tier Upgrading (1–7), Instability & Fracture mechanics, Value Calibration, Socket Punching, and Stasis Sealing (`docs/crafting.md`).

### 1.6 World, Biomes & Procedural Dungeons (Goal: 20+ Biomes)
- [x] Outline 20+ unique biomes (12 surface, 10 subterranean/dimensional) in `docs/world_dungeons.md`.
- [x] Design procedural dungeon generation concept (hybrid BSP + prefab room templates in every biome).
- [x] Design 8 campaign dungeon tiers with multi-phase bosses culminating in The Architect.
- [x] Design Infinite Rift endgame with scaling mutators and Tier 9+ Prismatic gear.
- [x] Design death mechanics (No permadeath: consciousness recall to hub with 25% raw material drop in recovery drone).
- [ ] **Pending**: Detail enemy spawn tables, environmental hazard parameters, and prefab room template rules for all 20+ biomes in `docs/world_dungeons.md`.

### 1.7 Documentation Quality & Standards
- [x] Keep all documentation in `docs/` purely conceptual (remove all code blocks, struct definitions, and JSON schemas).
- [x] Keep all TDD and test plan references strictly in `PLAN.md` (remove test plans from `docs/` files).
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

1. **Expand Skills Catalog (`docs/skills.md`)**: Detail all 500+ skills across all 9 class trees to complete the skill design ask.
2. **Expand Augmentation Catalog (`docs/augmentations.md`)**: Detail all 250+ augmentations across all 11 slots to complete the augmentation design ask.
3. **Expand Items Catalog (`docs/items.md`)**: Catalog the 3,000+ unique base items with stat roll ranges across all 10 categories and 8 tiers.
4. **Detail Biomes & Dungeons (`docs/world_dungeons.md`)**: Detail enemy spawn tables and dungeon parameters for each of the 20+ biomes.
5. **Final Review & Alignment**: Verify all design documents are 100% complete, code-free, and aligned with `PLAN.md` before any implementation commences.
