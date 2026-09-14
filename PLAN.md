# Untitled RPG — Complete Game Master Plan & Technical Specification

2D pixel-art ARPG sidescrolling platformer combining Terraria-style action combat, heavy survival & base-building, deep bionic and magitech body augmentations, 9 distinct classes, 20+ biomes with procedural dungeons, and an endless endgame.

Target Platform: macOS (Apple Silicon / MacBook Neo) primary; portable to Windows & Linux.  
Primary Stack: C++20, SDL3, Box2D v3, EnTT, CMake + Ninja.  
Architecture: Single-player initially, designed with client-server / headless simulation separation for future online multiplayer.  
Development Methodology: **Strict Test-Driven Development (TDD)** using Catch2 v3.

---

## 1. Project Overview & Design Pillars

### 1.1 Core Pitch
A high-mobility, gear-and-skill-driven 2D sidescrolling ARPG where ancient fantasy collides with fallen sci-fi technology. The player starts as an unaugmented survivor in a ruined world, gathering resources, farming, and building a fortified settlement in the central hub. To survive and conquer deeper threats, the player ventures into procedural dungeons in every biome, fighting with swords, bows, firearms, and spells, while gradually replacing their mortal body parts with bionic cybernetics (laser cannons, rocket boots, cybernetic hearts) or chimeric/ancient magical grafts (chimeric bear arms, ancient power crystals, runic eyes).

### 1.2 Core Pillars
1. **Terraria-Like Fluid Combat**: Responsive weapon swings, aiming with crosshair/mouse, tight platforming, bullet-spread and energy beams, knockback, hitstop, and screen shake.
2. **Dual-Track Augmentation (250+ Augmentations Across 11 Slots)**: Replace 11 body slots. Bionics consume electrical power and reduce humanity; magical augmentations consume mana and require magical stability. Includes 9 class signature augmentations that can be cross-equipped by other classes via high-cost exotic surgery.
3. **Meaningful Survival & Settlement**: Dynamic temperature, hunger, thirst, day/night cycles, night raids on wooden structures, farming crops, and recruiting NPCs by building suitable housing.
4. **Massive Progression & Infinite Scaling**:
   - **Uncapped Leveling ($1 \to \infty$)**: Campaign tuned for Level 60 to defeat the final boss ("The Architect"), but leveling continues endlessly into the Infinite Rift.
   - **500+ Skills & Universal Mastery**: Deep class trees, shared survival/traversal trees, and crafting trees. At Level 60, players unlock cross-class learning to master every skill in the game and achieve godhood.
   - **3,000+ Unique Base Items**: 10 categories, 8 tiers, individual Gaussian stat rolls with probabilistic ranges, quality bonuses (0–20%), and affix pools.
   - **Deep Crafting Tree & Stat Crafting**: Dedicated crafting mastery tree and an item modification forge allowing stat infusion, upgrading, reforging, socketing, and affix sealing with instability/fracture mechanics.
5. **Vast World (20+ Biomes with Procedural Dungeons)**: Over 20 surface, subterranean, and extra-dimensional biomes, each featuring procedurally generated dungeons, ruins, vaults, and unique boss encounters.
6. **No Permadeath**: Defeat returns the player to their hub medical pod or bed, dropping a fraction (25%) of carried raw materials into a recoverable drone, keeping all equipped gear, weapons, and augmentations intact.
7. **Multiplayer-Ready Architecture**: Built single-player first with clean deterministic simulation loops and input-state separation to allow future online multiplayer networking.

---

## 2. Technical Documentation Index

All granular game systems are documented in dedicated specification files referenced by this master plan:
- **Classes**: [docs/classes.md](docs/classes.md) — 9 class archetypes, base stats, starter kits, signature mechanics, uncapped leveling, universal skill unlocking, and Level 20 signature augments.
- **Skills**: [docs/skills.md](docs/skills.md) — 500+ active and passive skills, 4-key active hotbar (`Q`, `E`, `R`, `F`), DAG progression, mathematical scaling, and execution pipeline.
- **Augmentations**: [docs/augmentations.md](docs/augmentations.md) — 250+ augmentations across 11 body slots, dual bionic/magitech economy (Power vs Humanity, Mana vs Stability), and cross-class exotic surgery rules.
- **Items & Equipment**: [docs/items.md](docs/items.md) — 3,000+ base items across 10 categories and 8 tiers, individual Gaussian base stat roll ranges, quality modifiers, weapons, armor sets, and affixes.
- **Crafting & Modification**: [docs/crafting.md](docs/crafting.md) — 48-node Crafting Tree, stations, stat shard infusion, tier upgrading, calibration, socket drilling, affix sealing, and fracture mechanics.
- **Combat Mechanics**: [docs/combat.md](docs/combat.md) — Terraria-style 360 aim, kinematic sensor hitboxes, damage pipeline, armor mitigation, hitstop, screen shake, and status effects.
- **Survival, Building & Farming**: [docs/survival_building.md](docs/survival_building.md) — Hunger, thirst, temperature simulation, day/night cycles, weather, 16x16 grid building, crop farming, and NPC recruitment.
- **World, Biomes & Dungeons**: [docs/world_dungeons.md](docs/world_dungeons.md) — 20+ biomes, BSP procedural dungeon generation in every biome, 8 campaign tiers, boss fights, death recovery, and the Infinite Rift.

---

## 3. Technology Stack & Display Architecture

### 2.1 Dependencies & Libraries
- **Language**: C++20 (concepts, ranges, designated initializers, `std::span`).
- **Windowing, Input, & Audio**: SDL3 (`SDL_CreateWindow`, `SDL_GetRenderer`, `SDL_AudioStream`), `SDL3_image` (PNG sprite sheets), `SDL3_ttf` (pixel font rendering), `SDL3_mixer` / miniaudio.
- **Physics**: Box2D v3. Custom kinematic/raycast controller for player and humanoids; Box2D dynamic bodies for projectiles, physics debris, falling boulders, and dropped loot. Static chain shapes for tilemap collision without internal seam catches.
- **Entity Component System (ECS)**: EnTT (cache-friendly sparse set ECS).
- **Serialization & Data**: `nlohmann::json` for all items, skills, enemy tables, recipes, dialogue, and save files.
- **Diagnostics & Debug Tooling**: `spdlog` for high-throughput logging; Dear ImGui for live entity inspector, physics collider debug drawing, spawn console, and stat tweaking.
- **Testing**: Catch2 v3 for unit testing math, inventory logic, affix generation, and procgen graphs.
- **Build System**: CMake (>= 3.28) + Ninja backend. All external C++ libraries managed via `FetchContent` for zero-install, single-command workspace bootstrapping.

### 2.2 Display, Resolution & Pixel-Grid Architecture
- **Display Auto-Detection**:
  - On first boot, call `SDL_GetDisplayForWindow` and `SDL_GetDesktopDisplayMode` to detect the monitor's native display dimensions and refresh rate (e.g. 2560x1600 or 2880x1800 Retina).
  - Defaults to Fullscreen Borderless at native resolution.
- **Configurable Standard Video Options**:
  - Window Modes: Exclusive Fullscreen, Borderless Windowed, Windowed.
  - Resolutions: Native, 3840x2160 (4K), 2560x1440 (1440p), 1920x1080 (1080p), 1280x720 (720p), 16:10 MacBook native aspects (2560x1600, 1920x1200), and 21:9 Ultrawide (2560x1080, 3440x1440).
  - V-Sync: On, Off, Adaptive. Frame cap: 60, 120, 144, 240, Uncapped.
- **Pixel-Art Rendering Pipeline**:
  - Tile size: Standard **16x16** pixels.
  - Internal Virtual Canvas: Height fixed to a base target (e.g., 360 vertical pixels), with width determined by aspect ratio (e.g., 640x360 for 16:9, 576x360 for 16:10).
  - Integer Scaling: The internal canvas is rendered to an offscreen `SDL_Texture` with `SDL_SCALEMODE_NEAREST`. It is then scaled up to the window with an integer scale factor (e.g., 3x, 4x, 5x) centered with crisp black letterboxing/pillarboxing when non-integer scaling would cause pixel jitter. An optional "Smooth Integer" shader is provided for high-DPI displays.

### 2.3 Controls & Input System
- **Keyboard + Mouse First**:
  - `A` / `D`: Move Left / Right.
  - `Space`: Jump / Double Jump / Jetpack thruster hold.
  - `W` / `S`: Climb ladders, aim up/down, interact, drop through one-way platforms.
  - `Left Shift`: Dash / Rocket Burst (uses Stamina).
  - `Left Mouse Button`: Primary Attack / Tool Use (swings towards mouse cursor).
  - `Right Mouse Button`: Secondary Attack / Aim Down Sights / Shield Block / Power Fire.
  - `Q`, `E`, `R`, `F`: 4 Active Skill Hotkeys.
  - `1` through `8`: Hotbar Item Slots (weapons, tools, consumables).
  - `Tab`: Inventory, Crafting & Augmentation Menu.
  - `K` or `N`: Skill Tree & Specialization Screen.
  - `C`: Character Sheet & Stat Breakdown.
  - `Esc`: Pause Menu / Settings.
- Mouse cursor renders custom in-game crosshair indicating weapon spread and attack cooldown.

---

## 3. Core Engine Architecture & Directory Structure

### 3.1 Project File Layout
```
untitled_rpg/
├── CMakeLists.txt
├── cmake/
│   └── Dependencies.cmake      # FetchContent for SDL3, Box2D, EnTT, ImGui, JSON, spdlog
├── assets/
│   ├── sprites/                # Atlases, character sheets, monster sheets
│   ├── tilesets/               # 16x16 environment tilesets
│   ├── maps/                   # Tiled .tmj files for Hub and Overworld zones
│   ├── fonts/                  # Pixel fonts (TTF)
│   ├── audio/                  # SFX and OGG music tracks
│   └── data/                   # JSON balancing data
│       ├── classes.json
│       ├── skills.json
│       ├── augmentations.json
│       ├── items.json
│       ├── recipes.json
│       ├── enemies.json
│       ├── loot_tables.json
│       ├── biomes.json
│       └── dungeons.json
├── src/
│   ├── main.cpp
│   ├── core/
│   │   ├── Application.hpp/.cpp
│   │   ├── Config.hpp/.cpp      # Display, video, audio, keybinding settings
│   │   ├── Time.hpp/.cpp        # Fixed 60Hz delta time, interpolation factor
│   │   ├── EventBus.hpp
│   │   └── AssetManager.hpp/.cpp
│   ├── render/
│   │   ├── Renderer.hpp/.cpp
│   │   ├── Camera.hpp/.cpp      # Pixel-snapped 2D camera with deadzone and shake
│   │   ├── SpriteBatch.hpp/.cpp
│   │   ├── TilemapRenderer.hpp/.cpp
│   │   ├── Animation.hpp/.cpp
│   │   └── Lighting.hpp/.cpp    # 2D ambient darkness + dynamic point lights
│   ├── input/
│   │   ├── InputManager.hpp/.cpp
│   │   └── Actions.hpp
│   ├── physics/
│   │   ├── PhysicsWorld.hpp/.cpp
│   │   ├── CharacterController.hpp/.cpp
│   │   └── CollisionLayers.hpp
│   ├── ecs/
│   │   ├── Components.hpp
│   │   └── Systems.hpp
│   ├── gameplay/
│   │   ├── stats/
│   │   ├── combat/
│   │   ├── skills/
│   │   ├── augmentations/
│   │   ├── items/
│   │   ├── crafting/
│   │   ├── survival/
│   │   ├── building/
│   │   └── ai/
│   ├── procgen/
│   │   ├── DungeonGenerator.hpp/.cpp
│   │   ├── RoomTemplates.hpp/.cpp
│   │   └── BSPTree.hpp/.cpp
│   ├── ui/
│   │   ├── HUD.hpp/.cpp
│   │   ├── InventoryUI.hpp/.cpp
│   │   ├── AugmentationUI.hpp/.cpp
│   │   ├── SkillTreeUI.hpp/.cpp
│   │   └── DebugMenu.hpp/.cpp   # ImGui debug tools
│   └── save/
│       └── SaveManager.hpp/.cpp
└── tests/
    ├── test_stats.cpp
    ├── test_inventory.cpp
    └── test_dungeon_gen.cpp
```

### 3.2 Fixed-Timestep Execution Loop
- Simulation runs at an exact 60.0 Hz (`dt = 1.0 / 60.0f`).
- Input is polled continuously. Physics and game state advance in deterministic ticks.
- Frame rendering calculates an alpha interpolation fraction `alpha = accumulator / dt` to render smooth sub-pixel sprite positions while preventing physics tunneling.
- Execution pipeline per tick:
  1. Input Processing & Action State Update
  2. Player State Machine & Controller Processing
  3. AI Perception & Behavior Trees
  4. Movement & Kinematic Sweeps
  5. Box2D World Step (Dynamic bodies, sensor triggers)
  6. Combat Collision & Hitbox Overlap Resolution
  7. Status Effects, Survival Decay & Augmentation Power Drains
  8. Day/Night Cycle & Weather Timers
  9. Animation Tick & Particle Simulation
  10. Render Pass: Parallax Background -> Tile Layers -> Entities -> Light Map Blend -> Screen Shake -> UI -> ImGui Debug Overlay.

---

## 4. Character Progression, Stats & The Dual Energy Economy

### 4.1 Primary Attributes
Every character possesses 6 primary attributes:
1. **Strength (STR)**: Increases physical melee damage (+1.5% per point), max carry weight (+2kg), and heavy armor move speed penalty reduction.
2. **Dexterity (DEX)**: Increases ranged/ballistic weapon damage (+1.5%), critical strike chance (+0.1%), movement speed (+0.2%), and weapon attack speed.
3. **Intelligence (INT)**: Increases spell damage (+2.0%), max mana pool (+5), and crafting speed.
4. **Vitality (VIT)**: Increases maximum Health (+10 HP per point), health regen (+0.05 HP/sec), and status resistance against bleed/toxin.
5. **Wisdom (WIS)**: Increases mana regeneration (+0.1 MP/sec), magic stability (+1), and healing received (+1%).
6. **Cyber-Affinity (CYB)**: Increases maximum Power Capacity (+10 Power Units), reduces bionic humanity penalty by 1.5% per point, and amplifies energy weapon damage.

### 4.2 Leveling Curve & Allocations (Levels 1 to 60)
- **Level Cap**: 60.
- **Experience Equation**:
  $$\text{XP Required}(L) = 150 \times L^{1.85} + 50 \times L$$
- **Points per Level-up**:
  - Attribute Points: 3 points per level to distribute freely among STR, DEX, INT, VIT, WIS, CYB.
  - Shared Skill Tree: 1 point per level (60 points total).
  - Class Specialization Tree: 1 point every 2 levels starting at level 2 (30 points total).
- **Level 20 Milestone**: Every class unlocks their **Free Signature Augmentation** that automatically installs into its designated slot without consuming slot installation fees or humanity penalties.

### 4.3 The Dual Energy & Body Balance System
A character's body is balanced between two distinct technological and esoteric forces:

```
[Full Tech / Bionic] <============== [Pure Mortal] ==============> [Full Magitech / Chimeric]
 High Power Capacity                                                   High Mana Regeneration
 Heavy Armor & Forcefields                                             High Spell Resonance
 Low Humanity (Weak Healing)                                           Instability / Corruption Risk
```

1. **Power Budget (For Bionics & Energy Weapons)**:
   - Provided by the **Heart / Power Core** slot (e.g. Micro-Fission Cell, Cold-Fusion Arc, Plasma Reactor, or Power Crystals).
   - Each bionic augmentation reserves or drains Power:
     - Passive Drain: Constantly reserves a portion of Max Power (e.g., Subdermal Plating reserves 15 Power).
     - Active Drain: Consumes power upon activation (e.g., Arm Laser Cannon fires at 10 Power per shot).
   - If Power hits 0, bionic abilities power down and movement speed is reduced by 30%.
2. **Humanity & Sanity**:
   - Mortal base: 100 Humanity.
   - Bionic implants subtract Humanity (e.g. Hydraulic Arms -15, Targeting Optics -10).
   - Below 50 Humanity: Magical healing received drops by 50%.
   - Below 20 Humanity: Magical spell damage drops by 75%; character gains "Cyber-Overclock" (+15% attack speed, immune to Fear and Mental debuffs).
3. **Magic Stability (For Magitech & Chimeric Grafts)**:
   - Mortal base: 100 Stability.
   - Chimeric grafts (e.g. Chimeric Bear Arm, Void Tentacle) and ancient spell crystals require continuous mana resonance.
   - Each graft exerts a passive Mana Upkeep (e.g., Bear Arm drains 0.8 Mana/sec to keep stable).
   - If Mana drops to 0, chimeric grafts suffer "Cellular Rejection": the player suffers damage over time and loses the limb's bonus until mana regenerates.

---

## 5. The 11 Body Augmentation Slots & Complete Augmentation Catalog

Augmentations are acquired through dungeon loot, crafting at the Cyber-Clinic/Bio-Vat, or defeating tier bosses. Each slot can house either a Bionic, Magitech, or Chimeric modification.

### 5.1 Slot Definitions & System Matrix
1. **Head**: Neural processors, targeting HUDs, telepathic crowns.
2. **Eyes**: Optical sensors, night vision, thermal scanners, laser sights, runic eyes.
3. **Nervous System**: Superconducting wire reflex boosters, mana meridians.
4. **Lungs**: Rebreathers, hazard filtration units, cryo/pyro breath glands.
5. **Heart / Core**: Power generators for bionics or ancient elemental mana crystals.
6. **Torso**: Internal armor plates, nanite dispensaries, runic ribcages.
7. **Skin / Dermis**: Subdermal alloy weave, thermoregulation skin, camouflaging scales.
8. **Left Arm**: Heavy utility tools, shields, chimeric beast limbs (bear arms), arm cannons.
9. **Right Arm**: Weapon actuators, hydraulic smashers, arcane casting channels, laser cannons.
10. **Hands**: Micro-thruster palms, grip clamps, alchemical touch fingertips.
11. **Legs**: Rocket jump boots, mantis spring tendons, pneumatic shock absorbers.

### 5.2 Complete Augmentation Catalog

| Slot | Name | Type | Cost / Stats | Special Ability / Effect |
|---|---|---|---|---|
| **Head** | *MK-IV Target Matrix* | Bionic | -10 Humanity, +5 CYB | Crosshair shows enemy HP, weak points (+15% crit). |
| **Head** | *Crown of the Archmage* | Magitech | +20 Max Mana, +10 INT | Reduces mana cost of all active skills by 15%. |
| **Head** | *Primal Hive-Node* | Chimeric | -10 Stability, +15 VIT | Spawns mini-hornets when damaged that attack enemies. |
| **Eyes** | *Thermal Spectrum Optics* | Bionic | -5 Humanity, +3 DEX | Highlights enemies, ores, and hidden dungeon passages in dark. |
| **Eyes** | *Ocular Laser Emitter* | Bionic | -8 Humanity, 5 Power/s | Fires continuous eye laser beam with Right Mouse Button. |
| **Eyes** | *Eyes of the Void Gazer* | Magitech | -15 Stability, +8 WIS | Dodge chance +10%; see invisible and phasing spirits. |
| **Nervous** | *Synaptic Accelerator* | Bionic | -12 Humanity, +10% Speed | When dropping below 30% HP, enters 4s bullet time. |
| **Nervous** | *Aether Conduit Weave* | Magitech | +1.5 Mana Regen/s | Active spells have a 10% chance to refund their full mana cost. |
| **Lungs** | *Toxin Scrubber V2* | Bionic | -5 Humanity | Complete immunity to poison, spore clouds, and gas traps. |
| **Lungs** | *Dragon-Drake Pyro Gland* | Chimeric | 15 Mana upkeep | Exhale a cone of flame while dashing, burning foes for 5s. |
| **Heart** | *Micro-Fission Arc Core* | Bionic | +120 Max Power, -20 Humanity | Generates 15 Power/sec; powers heavy bionic weaponry. |
| **Heart** | *Ancient Astral Crystal* | Magitech | +80 Max Mana, +20 WIS | Overheals mana into a temporary shield absorbing 150 damage. |
| **Heart** | *Behemoth Chimera Heart* | Chimeric | +150 Max HP, -20 Stability | Triples health regeneration while standing in sunlight or water. |
| **Torso** | *Titanium-Carbide Plate* | Bionic | -10 Humanity, +25 Armor | Reduces all physical damage taken by 20%; cannot be knocked down. |
| **Torso** | *Runic Spell-Plate* | Magitech | +20 Magic Resist | Absorbs 15% of incoming spell damage as restored Mana. |
| **Skin** | *Subdermal Mesh* | Bionic | -5 Humanity, +10 Armor | Negates environmental fall damage and spikes. |
| **Skin** | *Thermal Insulator Dermis*| Bionic | -5 Humanity | Complete resistance to cold/heat environmental freezing & heatstroke. |
| **Skin** | *Chameleonic Scales* | Chimeric | 5 Mana upkeep | Standing still for 1.5s makes player invisible to non-bosses. |
| **Left Arm**| *Pneumatic Aegis Shield*| Bionic | -10 Humanity, 10 Power/block | Blocks 100% frontal damage; parrying stuns attacker for 2s. |
| **Left Arm**| *Chimeric Ursine Arm* | Chimeric | -15 Stability, +20 STR | Replaces arm with beast bear arm; melee attacks gain +40% AoE swipe. |
| **Right Arm**| *Arm-Mounted Laser Cannon*| Bionic | -15 Humanity, 25 Power/shot | Alt-fire fires a hyper-velocity piercing laser beam through enemies. |
| **Right Arm**| *Arcane Resonator Arm* | Magitech | +15 INT, +15% Spell Dmg | Basic wand attacks split into 3 homing arcane bolts. |
| **Hands** | *Micro-Thruster Palms* | Bionic | 2 Power/sec during thrust | Allows 3s hovering in mid-air and reduces weapon recoil to 0. |
| **Hands** | *Alchemical Touch* | Magitech | +10% Drop Rate | Harvesting plants or mining ore produces double yield. |
| **Legs** | *Hydraulic Piston Greaves*| Bionic | -8 Humanity, +20% Jump | Triples jump height and causes shockwave ground slam on fall. |
| **Legs** | *Plasma Jet Boots* | Bionic | 5 Power/sec while active | Enables continuous rocket flight for up to 4 seconds. |
| **Legs** | *Mantis Leap Tendons* | Chimeric | -5 Stability | Enables infinite wall-jumping and double-wall clinging. |

---

## 6. The 9 Classes: Roles, Starting Kits, Signature Mechanics & Level 20 Augmentations

Every class represents a specialized biological/technological archetype. At character creation, the player picks one class.

### 6.1 Class Summary Matrix

| Class | Archetype | Starting Primary Stats | Signature Mechanic | Free Level 20 Signature Augmentation |
|---|---|---|---|---|
| **1. Juggernaut** | Heavy Armor Tank / Cyber-Vanguard | 15 STR, 12 VIT, 6 DEX, 5 INT, 5 WIS, 7 CYB | **Overcharge Kinetic Plating**: Blocking & taking hits builds Kinetic Energy, unleashed as an EMP burst. | **Integrated Hydraulic Piston Core (Torso)**: Doubles armor value and grants permanent knockback immunity. |
| **2. Berserker** | Adrenal Bio-Bruiser / Chimeric Savage | 16 STR, 14 VIT, 8 DEX, 4 INT, 4 WIS, 4 CYB | **Blood Frenzy**: Attack speed and life-leech scale inversely with current HP percentage. | **Chimeric Beast Claws & Tendons (Right Arm)**: Melee hits inflict Rend, stacking bleed and granting 8% lifesteal. |
| **3. Gunslinger** | Ballistic Marksman / Cyber-Sharpshooter | 8 STR, 16 DEX, 6 VIT, 6 INT, 6 WIS, 8 CYB | **Tactical Reload & Weakpoint Aim**: Precision shots on glowing enemy markers deal 250% critical damage. | **Sub-Orbital Target Link (Eyes)**: Pierces all terrain with crosshair; ballistic bullets ricochet toward targets. |
| **4. Phantom** | Nano-Infiltrator / Energy Assassin | 6 STR, 16 DEX, 8 VIT, 8 INT, 5 WIS, 7 CYB | **Holo-Decoy & Cloaking**: Dashing leaves an explosive hologram decoy and turns player invisible for 2.5s. | **Nano-Wire Monomolecular Daggers (Hands)**: Attacks from stealth deal 400% damage and ignore enemy armor. |
| **5. Technomancer** | Arcane-Circuit Caster / Magitech Blaster | 5 STR, 6 DEX, 7 VIT, 16 INT, 10 WIS, 6 CYB | **Spell Overclock**: Spells can consume stored Power to double projectile speed and cause electrical detonation. | **Runic Micro-Reactor (Heart)**: Power generated is automatically converted to continuous Mana regen at 1:1 ratio. |
| **6. Medic** | Biomancer / Nanite Restorer | 7 STR, 8 DEX, 12 VIT, 10 INT, 14 WIS, 6 CYB | **Nanite Swarm Aura**: Emits an aura that continuously repairs player HP, cleanses poisons, and melts nearby foes. | **Subdermal Cellular Replicator (Skin)**: Fatal damage is prevented once every 5 minutes, reviving player to 50% HP. |
| **7. Symbiote** | Chimeric Shifter / Nature-Grafted Primal | 12 STR, 10 DEX, 14 VIT, 6 INT, 10 WIS, 4 CYB | **Metamorphic Forms**: Can shift into armoured Ursine form (tank) or winged Raptor form (aerial speed). | **Symbiotic Chimeric Carapace (Torso)**: Transforms skin into living chitin, restoring 2% max HP and Stamina every 3s. |
| **8. Warden** | Forcefield Crusader / Magitech Templar | 12 STR, 7 DEX, 12 VIT, 10 INT, 8 WIS, 8 CYB | **Aegis Barrier**: Generates an overshield that deflects hostile projectiles back at attackers. | **Hard-Light Aegis Projector (Left Arm)**: Creates a stationary 6-second dome shield blocking all hostile fire. |
| **9. Reanimator** | Drone-Swarm & Cyber-Necromancer | 6 STR, 7 DEX, 8 VIT, 15 INT, 8 WIS, 12 CYB | **Drone Fabricator & Soul Harvester**: Harvests fallen enemies to assemble combat cyber-drones and bone-servants. | **Automated Assembler Spine (Nervous)**: Automatically reconstructs destroyed minions instantly without material cost. |

---

## 7. Complete Skill Trees: Class Trees & The Shared Tree

Active skills occupy 4 hotkeys (`Q`, `E`, `R`, `F`). Each class has a dedicated 15-node tree containing 4 active skills and 11 passive nodes.

### 7.1 Class Specialization Trees (All 9 Classes)

#### Class 1: Juggernaut
- **Q — Seismic Shockwave** (Cost: 20 Stamina, 8s CD): Slam the ground with fists/weapon, creating a fissure that knocks enemies into the air and deals 180% physical damage.
- **E — Fortress Stance** (Cost: 15 Power, 12s CD): Encase body in heavy plating for 5 seconds. Movement speed -20%, Armor +150%, reflects 40% of incoming damage back to attackers.
- **R — Kinetic Charge** (Cost: 25 Stamina, 10s CD): Rocket forward horizontally, knocking enemies back and smashing through breakable environment blocks.
- **F — Overload Discharge** (Cost: 50 Power, 30s CD): Detonates stored kinetic energy in a massive 360-degree EMP burst dealing 350% electric damage and disabling enemy shields/lasers for 6s.
- **Passives (11 Nodes)**:
  1. *Plated Sinew*: +10% Max Health.
  2. *Reinforced Bulk*: +15 Armor when wearing heavy chest armor.
  3. *Unyielding Stride*: Knockback resistance +50%.
  4. *Spiteful Armor*: Attackers take 5 flat physical damage per hit.
  5. *Heavy Impact*: Jump-landing from height deals AoE crushing damage.
  6. *Kinetic Conversion*: 5% of damage taken is converted into Power.
  7. *Colossus Grip*: Two-handed weapons can be wielded with one hand at -15% attack speed.
  8. *Internal Dampeners*: Blast/explosion damage taken reduced by 30%.
  9. *Crushing Momentum*: Dashing into enemies staggers them for 1s.
  10. *Ironclad Recovery*: Health regen increases by +2.0 HP/s while below 30% HP.
  11. *Indomitable Will*: Stun and freeze durations reduced by 50%.

#### Class 2: Berserker
- **Q — Primal Cleave** (Cost: 15 Stamina, 4s CD): A sweeping 180-degree cleave with melee weapons dealing 220% physical damage and inflicting Bleed.
- **E — Adrenaline Surge** (Cost: 10% Current HP, 15s CD): Enter an enraged state for 8 seconds: +35% attack speed, +20% movement speed, and +15% lifesteal.
- **R — Death-Defying Roar** (Cost: 20 Stamina, 20s CD): Roars, fearing all non-boss enemies within 8 tiles for 3s and granting immunity to stuns for 5s.
- **F — Guillotine Leap** (Cost: 30 Stamina, 25s CD): Leaps high into the air and crashes down upon target location dealing up to 500% damage to enemies below 25% HP.
- **Passives (11 Nodes)**:
  1. *Rage Conduit*: Gain +1% damage for every 2% of missing Health.
  2. *Taste of Blood*: Killing a bleeding target restores 5% max Health.
  3. *Unstoppable Force*: Cannot be slowed below base running speed.
  4. *Frenzy Stacks*: Consecutive melee hits grant +3% attack speed (stacks up to 5 times).
  5. *Gore Feast*: Critical hits cause targets to explode in bone fragments dealing AoE damage.
  6. *Savage Vitality*: +150 Max Health, but armor effectiveness is reduced by 10%.
  7. *Thick Hide*: Physical damage taken reduced by 1% per 100 current HP.
  8. *Brawn Over Brain*: Melee weapons deal +10% bonus damage based on total STR.
  9. *Rampage*: Defeating an enemy extends active Adrenaline Surge duration by 1.5s.
  10. *Blood-Soaked Blade*: Increases melee range by +25%.
  11. *Last Stand*: Taking lethal damage keeps the player alive at 1 HP for 3 seconds (60s internal cooldown).

#### Class 3: Gunslinger
- **Q — Fan the Hammer / Rapid Burst** (Cost: 12 Ammo/Energy, 6s CD): Fires a lightning-fast 6-shot volley in a tight cone dealing 6 x 60% weapon damage.
- **E — High-Explosive Grenade** (Cost: 1 Crafted Grenade or 20 Power, 10s CD): Throws a frag/plasma grenade that bounces once and detonates for 280% fire/blast damage in a 4-tile radius.
- **R — Grappling Hook Launcher** (Cost: 10 Stamina, 5s CD): Fires a high-tension cable up to 15 tiles, rapidly pulling the player to the point of impact.
- **F — Orbital Satellite Strike** (Cost: 40 Power, 45s CD): Marks target coordinate on screen; after 1.5s, an orbital particle beam incinerates the column dealing 600% energy damage.
- **Passives (11 Nodes)**:
  1. *Lead Storm*: +15% bullet velocity and +10% maximum range.
  2. *Quickdraw*: Weapon swap speed +80%; first shot after swapping has +25% crit chance.
  3. *Recoil Stabilizers*: Weapon kickback reduced by 50%.
  4. *Hollow-Point Rounds*: Ballistic weapons inflict Bleed on critical hit.
  5. *Overcharged Cells*: Energy weapons chain electricity to 1 adjacent target.
  6. *Bandolier Stitching*: Max ammo carry capacity doubled.
  7. *Deadeye Focus*: Standing still for 1s increases critical strike multiplier to 3.0x.
  8. *Shrapnel Ricochet*: Bullets have a 20% chance to ricochet off walls into nearby targets.
  9. *Thermal Vents*: Energy weapon overheat rate reduced by 30%.
  10. *Trick Shot*: Shooting active thrown grenades triggers an immediate double-damage blast.
  11. *Point Blank*: Firearms deal +30% damage to targets within 3 tiles.

#### Class 4: Phantom
- **Q — Shadow Blink** (Cost: 15 Stamina, 6s CD): Instantly teleports 6 tiles in the direction of the mouse cursor, leaving behind smoke that blinds enemies for 2s.
- **E — Nano-Cloak** (Cost: 20 Power or 25 Mana, 14s CD): Enter complete invisibility for 6s. Next attack from cloak deals +150% damage.
- **R — Shuriken Flurry / Drone Darts** (Cost: 15 Stamina, 8s CD): Throws 5 piercing shurikens that seek nearby enemy weakpoints.
- **F — Executioner's Dance** (Cost: 35 Stamina, 30s CD): Teleports rapidly between up to 5 targets within 10 tiles, slashing each for 200% damage with full invulnerability frames.
- **Passives (11 Nodes)**:
  1. *Silent Footsteps*: Enemy detection radius reduced by 40%.
  2. *Lethal Precision*: Base critical strike chance +5%.
  3. *Backstab Protocol*: Attacks striking enemies from behind deal +40% bonus damage.
  4. *Venomous Coat*: Thrown weapons and daggers apply stacking Neurotoxin (slows and damages).
  5. *Acrobatic Momentum*: Dashing costs 30% less Stamina.
  6. *Phase Shift*: Successfully dodging through an attack restores 10 Stamina.
  7. *Coup de Grace*: Deal +50% damage to targets stunned, frozen, or blinded.
  8. *Mirror Step*: Teleporting leaves behind a holographic decoy for 3s.
  9. *Shadow Dagger Mastery*: Dual-wielding daggers increases attack speed by +20%.
  10. *Smoke Screen*: Taking more than 30% max HP in one hit automatically deploys smoke.
  11. *Lethality Overflow*: Critical strikes refund 5 Stamina.

#### Class 5: Technomancer
- **Q — Arcane Plasma Bolt** (Cost: 15 Mana, 2s CD): Fires an undulating orb of plasma-charged arcane energy that pierces through up to 3 enemies.
- **E — Tesla Shock Pylon** (Cost: 25 Power or 30 Mana, 12s CD): Deploys a stationary coil that zaps up to 3 nearby enemies every 1.0s with chain lightning.
- **R — Quantum Rift Barrier** (Cost: 35 Mana, 18s CD): Creates a localized distortion field for 6s that slows incoming enemy projectiles by 80% and boosts allied projectile damage by +30%.
- **F — Singularity Collapse** (Cost: 60 Mana, 40s CD): Casts a micro-black hole at target location, pulling all nearby enemies inward before violently exploding for 450% spatial damage.
- **Passives (11 Nodes)**:
  1. *Arcane Flux*: +15% maximum Mana.
  2. *Overclocked Wands*: Wands fire +20% faster.
  3. *Static Field*: Casting a spell charges next melee attack with 20 electrical bonus damage.
  4. *Superconductor*: Lightning spells chain to +2 additional targets.
  5. *Mana Shielding*: 20% of damage taken is subtracted from Mana instead of Health.
  6. *Thermodynamic Transfer*: Fire spells burn targets; hitting burned targets with Frost deals +35% shatter damage.
  7. *Runic Amplification*: Magic damage scaled additionally by +0.5% per point of CYB.
  8. *Essence Tap*: Defeating an enemy with a spell restores 4% maximum Mana.
  9. *Plasma Core Infusion*: Energy weapon kills grant +10% spell damage for 8s (stacks 3x).
  10. *Channeled Velocity*: Channeled spells grant +20% movement speed while casting.
  11. *Archmage Circuitry*: Spell cooldowns reduced by 15%.

#### Class 6: Medic (Biomancer)
- **Q — Nanite Injection Dart** (Cost: 20 Mana, 4s CD): Fires a smart dart. If striking an ally/self: heals 80 HP over 4s. If striking an enemy: deals 100 toxic damage and weakens defense by 20%.
- **E — Healing Field Generator** (Cost: 30 Power, 16s CD): Deploys a medical beacon on the ground creating a 6-tile cleansing zone that restores 15 HP/sec for 10s.
- **R — Bio-Contagion Cloud** (Cost: 35 Mana, 14s CD): Releases a cloud of necro-spores that damages all enemies inside; victims who die in the cloud burst, spreading it to nearby foes.
- **F — Cellular Overdrive** (Cost: 50 Mana, 45s CD): Floods the body with regeneration nanites: restores 50% max HP instantly and boosts move and attack speed by +30% for 8s.
- **Passives (11 Nodes)**:
  1. *Hippocratic Oath*: All healing performed and received +15%.
  2. *Antidote Synthesis*: Immune to natural poisons and venoms.
  3. *Combat Syringe*: Dart and needle weapons gain +25% velocity and armor pierce.
  4. *Sympathetic Link*: Healing an NPC or summon restores 25% of that amount to player.
  5. *Nanite Armor*: When at 100% HP, excess healing converts into an absorption shield up to 20% max HP.
  6. *Transfusion*: Melee attacks leech 3% of damage dealt as healing.
  7. *Sterile Scalpels*: Daggers and surgical blades have +15% critical strike chance.
  8. *Defibrillation*: Shock damage inflicted on enemies has a 20% chance to stun them for 2s.
  9. *Adrenaline Mist*: Healing Field also boosts stamina regen by +50%.
  10. *Biomass Recycler*: Gathering plants yields double medical herbs.
  11. *Vitality Resonator*: +1.0 HP/sec passive health regeneration.

#### Class 7: Symbiote (Primal)
- **Q — Chimeric Swipe / Maul** (Cost: 15 Stamina, 3s CD): Slashes with transformed claws dealing 160% damage; restores 5 Stamina on hit.
- **E — Primal Metamorphosis** (Cost: 25 Mana, 10s CD): Toggle between Ursine Form (+50% Armor, +20% HP, slow) and Lupine Form (+30% Move speed, high jump, double claw attack).
- **R — Thorn Bramble Trap** (Cost: 20 Mana, 8s CD): Summons a patch of toxic briars that roots enemies for 3s and deals continuous nature damage.
- **F — Apex Predator Unleashed** (Cost: 40 Mana, 35s CD): Releases inner beast form: grows massive chimeric wings and jaws for 10s, granting flight and causing attacks to unleash shockwaves.
- **Passives (11 Nodes)**:
  1. *Feral Senses*: Detect all enemy locations on minimap within 30 tiles.
  2. *Grafted Durability*: +100 Max Health.
  3. *Predator's Stalk*: Movement speed in tall grass, forest, and underground caves +20%.
  4. *Chitinous Spikes*: Reflects 15% of incoming melee damage back to attackers.
  5. *Photosynthetic Recovery*: Restores 1 HP/sec and 1 Mana/sec when outdoors in daylight.
  6. *Savage Rend*: Claws and fangs apply stacks of Deep Wound (armor reduced by 5% per stack).
  7. *Beast's Stamina*: Stamina recovery delay reduced by 50%.
  8. *Rooted Strength*: Standing still for 1s grants +25% physical resistance.
  9. *Pack Leader*: Tamed animals and summons gain +30% damage and health.
  10. *Primal Ferocity*: Critical strike hits grant +10% move speed for 4s.
  11. *Adaptive Biology*: Elemental damage taken (fire/frost/lightning) reduces future damage of that type by 15% for 10s.

#### Class 8: Warden (Aegis)
- **Q — Radiant Smite / Laser Brand** (Cost: 18 Mana, 4s CD): Infuses weapon with holy energy or hard-light plasma, striking for 200% damage and blinding target for 2s.
- **E — Bastion Shield Bash** (Cost: 15 Stamina, 6s CD): Dashes forward with shield raised, deflecting projectiles and knocking enemies back 5 tiles with a 1.5s stun.
- **R — Consecrated Ground** (Cost: 30 Mana, 15s CD): Sanctifies an 8-tile zone for 8s: allies gain +20 Armor and 10 HP/sec; undead and machine enemies take 25 holy damage/sec.
- **F — Judgment Cannon / Dawn Ray** (Cost: 50 Mana, 35s CD): Channels a brilliant vertical beam of energy from above for 3 seconds dealing continuous ticks of 120% holy/energy damage.
- **Passives (11 Nodes)**:
  1. *Vanguard Resolve*: Armor increased by +10% while holding any shield.
  2. *Righteous Retribution*: Parrying an attack releases a burst of light dealing 50 damage to nearby foes.
  3. *Unwavering Faith*: Status effect durations against player reduced by 30%.
  4. *Shield Wall*: Projectiles hitting the player's shield have a 40% chance to be reflected.
  5. *Bulwark Aura*: Standing near friendly NPCs grants them +20% damage resistance.
  6. *Hard-Light Infusion*: Weapons deal an additional +15% holy/energy damage.
  7. *Beacon of Hope*: Potions heal an additional +25% health.
  8. *Zealot's Stride*: Heavy armor movement penalty reduced by 100%.
  9. *Holy Vengeance*: When health drops below 25%, an explosion of light blinds all nearby enemies for 4s (90s CD).
  10. *Sanctified Steel*: Melee hits against corrupted/undead enemies deal +35% bonus damage.
  11. *Divine Bastion*: Max Health +80 and Max Mana +50.

#### Class 9: Reanimator (Cyber-Necromancer)
- **Q — Nanite Soul Harvester** (Cost: 15 Mana, 3s CD): Siphons the life energy of a target dealing 80 dark damage and generating a "Soul Fragment".
- **E — Fabricate Combat Drone / Thrall** (Cost: 1 Soul Fragment, 5s CD): Consumes a soul fragment to assemble either a flying laser drone or a skeletal bio-cyborg minion (max 4 minions).
- **R — Corpse Detonation** (Cost: 20 Mana, 6s CD): Targets a fallen enemy or active minion, causing it to explode in an acidic shrapnel burst dealing 260% damage.
- **F — Swarm Overdrive / Army of the Dead** (Cost: 50 Mana, 40s CD): Supercharges all active minions for 10s: they gain +100% attack speed, +50% size, and emit an aura of radiation.
- **Passives (11 Nodes)**:
  1. *Harvest Protocol*: Defeating any enemy has a 30% chance to drop a Soul Fragment.
  2. *Reinforced Chassis*: Minions gain +40% max Health and +15 Armor.
  3. *Drone Overclock*: Flying drones fire bursts of 2 lasers instead of 1.
  4. *Necrotic Siphon*: Whenever a minion hits an enemy, the player restores 2 HP.
  5. *Dark Metallurgy*: Crafting weapons and armor costs 15% less metal.
  6. *Soul Capacity*: Maximum active minions increased by +2 (total 6).
  7. *Acidic Residue*: Corpse explosions leave a lingering acid puddle for 5s.
  8. *Unholy Resonator*: Minion damage increased by +1.5% per point of INT.
  9. *Self-Destruct Matrix*: Minions explode automatically upon death for 150% damage.
  10. *Shadow Ward*: While at least 2 minions are alive, player takes 15% less damage.
  11. *Master of the Grave*: Minions inherit 50% of the player's critical strike chance.

---

### 7.2 The Shared Skill Tree (40 Nodes Open to All Characters)
The Shared Tree is organized into 4 branches of 10 nodes each. Any character can invest points earned on each level-up.

```
       [Central Root: Survival Instincts]
       /           |            |           \
  [Mobility]   [Survival]   [Combat/Guns]   [Craft/Tech]
   (10 Nodes)   (10 Nodes)   (10 Nodes)      (10 Nodes)
```

#### Branch 1: Mobility & Traversal (10 Nodes)
1. *Swiftfoot*: Movement speed +5%.
2. *Agile Leap*: Jump height +10%.
3. *Double Jump*: Enables a second jump in mid-air.
4. *Wall Grip*: Allows clinging to vertical walls and slow sliding.
5. *Air Dash*: Enables a horizontal dash in mid-air (`Shift`).
6. *Feather Fall*: Fall damage reduced by 50%.
7. *Pneumatic Sprint*: Sprinting speed bonus increased from +30% to +50%.
8. *Ledge Clamber*: Automatically mantles onto ledges when jumping near edges.
9. *Rocket Recovery*: Pressing jump after being knocked down immediately recovers to feet.
10. *Terminal Velocity Control*: Hold `S` while falling to slam down; deals damage based on fall height.

#### Branch 2: Survival & Constitution (10 Nodes)
1. *Hearty Appetite*: Max Hunger bar increased by +25%.
2. *Camel's Endurance*: Water/Thirst depletion rate reduced by 30%.
3. *Insulated Flesh*: Resistance to environmental freezing and heatstroke +20%.
4. *Iron Stomach*: Consuming raw food or contaminated water has zero chance of disease.
5. *Deep Metabolism*: Resting at a bed or campfire restores HP and Stamina 50% faster.
6. *Brawny Spine*: Carry weight capacity +15 kg.
7. *Herbology Lore*: Consuming cooked food items grants double the duration of buffs.
8. *Survivalist Grit*: When Hunger and Thirst are above 80%, gain +10 Armor and +5% move speed.
9. *Second Breath*: When Stamina reaches 0, it instantly refills to 50% (120s cooldown).
10. *Natural Immunity*: Poison, burn, and bleed durations against player reduced by 40%.

#### Branch 3: Weapons & Combat Mastery (10 Nodes)
1. *Sharpened Edges*: All physical melee damage +6%.
2. *Steady Stance*: Ranged weapon projectile spread reduced by 25%.
3. *Executioner*: Critical strike damage multiplier +0.25x.
4. *Quick Loader*: Reload speed of ballistic firearms increased by +25%.
5. *Power Flow*: Energy weapon power consumption reduced by 15%.
6. *Impact Force*: Knockback dealt to enemies +30%.
7. *Armor Cracker*: Attacks ignore 5 points of enemy Armor.
8. *Adrenaline Leech*: Slaying an elite or boss enemy restores 15% max Health and 25 Power.
9. *Point-Blank Brawler*: Firearms deal +15% damage at close range.
10. *Master of Arms*: Weapon swapping speed +50%; stamina cost of weapon swings reduced by 20%.

#### Branch 4: Crafting, Engineering & Scavenging (10 Nodes)
1. *Scrap Hound*: Slaying enemies and breaking dungeon crates drops +25% more scrap metal.
2. *Efficient Smelting*: Ores smelt into ingots using 20% less fuel/coal.
3. *Tinker's Gift*: Placed structures (turrets, traps, campfires) gain +50% durability.
4. *Precision Machinist*: Weapons crafted at the workbench roll with at least 1 guaranteed rare affix.
5. *Alchemical Yield*: Brewing potions produces an extra bonus potion 25% of the time.
6. *Battery Optimizer*: Power capacity of all installed bionic augmentations increased by +15%.
7. *Botanist's Touch*: Farm crops grow 25% faster.
8. *Deconstruction Specialist*: Dismantling weapons and armor refunds 80% of crafting materials (up from 50%).
9. *Structural Engineer*: Placed walls and doors take 50% less damage from enemy night raids.
10. *Master Artificer*: Reduces the material and credit cost of Cyber-Clinic surgeries by 30%.

---

## 8. Combat Mechanics & Weapon Arsenal

### 8.1 Combat Feel & Game Feel Architecture
- **Terraria-Style Crosshair Aim**: Character torso and weapon rotate to aim dynamically at mouse position; sprite flips horizontally when crossing the vertical midline.
- **Hitboxes & Hurtboxes**: Attacks spawn brief kinematic sensor shapes in Box2D. Each hitbox tracks hit entity IDs to prevent double-hitting on consecutive frames.
- **Hitstop (Screen Freeze)**: Critical hits and heavy weapon collisions pause game simulation for 2 to 4 frames (33ms to 66ms) while rendering remains active, creating physical punch.
- **Dynamic Knockback & Velocity Decay**: Hits impart velocity to Box2D bodies, resisted by enemy mass and armor.
- **Damage Numbers & Popups**: Pixel-styled floating combat text: White (normal physical), Yellow (critical), Blue (energy/electric), Purple (arcane), Green (poison/acid), Orange (fire/burn).
- **Screen Shake**: Decaying sinusoidal trauma shake on player damage, boss slams, and explosions.

### 8.2 Weapons Catalog (5 Distinct Categories)

```
[Weapon Types]
 ├── Melee (Swords, Greatswords, Energy Blades, Chimeric Claws, Spears)
 ├── Ballistic Firearms (Pistols, Shotguns, Assault Rifles, Sniper Rifles) -> Uses Physical Ammo
 ├── Energy & Beam Weapons (Plasma Blasters, Laser Carbines, Railguns)   -> Uses Power Units
 ├── Magic Implements (Wands, Staffs, Spell Grimoires)                   -> Uses Mana
 └── Shields & Off-Hands (Kite Shields, Forcefield Projectors, Parrying Daggers)
```

#### 1. Melee Arsenal
- **Scrap Machete**: Fast horizontal arc swipe; basic starter weapon (12 dmg).
- **Vibro-Katana**: High-frequency blade; +20% attack speed, high critical chance (28 dmg).
- **Rocket-Powered Great-Hammer**: Slow, heavy 2-handed swing; triggers explosive ground shockwave (75 dmg).
- **Chimeric Bone Spear**: Long thrust range, pierces through 2 enemies, inflicts bleed (35 dmg).
- **Plasma Saber**: Energy blade; draws 1 Power per swing, completely ignores enemy physical armor (52 energy dmg).

#### 2. Ballistic Firearms (Consumes Physical Crafted Ammo)
- **Scavenger's Revolver**: 6-shot capacity, high single-target stagger, moderate reload (22 dmg per shot).
- **Combat Trench Shotgun**: 8-pellet spread, massive knockback, devastating at 1-3 tile distance (8 x 8 dmg).
- **Autocannon Carbine**: 30-round magazine, high fire rate, moderate bullet spray (16 dmg per shot).
- **Anti-Materiel Sniper Rifle**: 4-round magazine, extreme velocity, penetrates through up to 4 targets (140 dmg).
- **Hand Cannon / Flak Pistol**: Fires explosive shells detonating on impact (60 AoE dmg).

#### 3. Energy & Beam Firearms (Consumes Power Units from Core)
- **Plasma Pulse Blaster**: Fires glowing balls of plasma traveling at moderate speed, dealing fire/energy damage (4 Power/shot, 34 dmg).
- **Continuous Laser Cutter**: Emits a constant beam damaging targets every 0.1s; heats up over time (6 Power/sec, 90 dmg/sec).
- **Heavy Arc Discharger**: Fires an electric bolt that chains between up to 4 enemies (12 Power/shot, 45 electric dmg).
- **Gauss Railgun**: Charges for 1.0s before firing a supersonic magnetic slug that pierces the entire screen (30 Power/shot, 220 dmg).

#### 4. Magic Implements (Consumes Mana)
- **Apprentice Spark Wand**: Rapid-fire magic dart with low mana cost (4 Mana/cast, 18 magic dmg).
- **Pyromancer's Flame Staff**: Hurls a fiery meteor in an arc that leaves a burning patch on the ground (18 Mana/cast, 65 fire dmg).
- **Cryo-Shard Grimoire**: Fires a cone of 5 ice shards that freeze enemies in place for 2s (22 Mana/cast, 5 x 12 frost dmg).
- **Void Tendril Staff**: Summons a flailing tentacle from the floor that strikes nearby enemies for 6s (30 Mana/cast, 40 void dmg/strike).

#### 5. Shields & Off-Hands
- **Riot Shield**: Hold RMB to raise shield, blocking 70% damage from the front and preventing knockback.
- **Holographic Force-Emitter**: Reserves 10 Power; tap RMB right as an attack lands to parry and deflect projectiles.
- **Alchemical Poison Flask**: Throw with RMB to shatter a vial of corrosive gas damaging and melting armor.

---

## 9. Survival, Settlement, Building & Crafting Systems

### 9.1 Survival Meters & Dynamics
1. **Hunger (0 to 100)**:
   - Drains at 1 point per 18 seconds (approx. 30 real minutes from full to zero).
   - Higher exertion (sprinting, jumping, swinging heavy weapons) accelerates decay by up to 1.5x.
   - At 0 Hunger: Player cannot sprint; max stamina capped at 50%; takes 1% max HP damage every 3 seconds.
2. **Thirst (0 to 100)**:
   - Drains at 1 point per 12 seconds. Accelerated in hot biomes.
   - At 0 Thirst: Stamina regeneration drops to zero; vision blurs.
3. **Body Temperature (-50°C to +50°C)**:
   - Determined by: Ambient Biome Temp + Time of Day + Weather (Rain/Snow) + Nearby Heat (Campfires/Torches) - Armor Cold Insulation.
   - **Freezing (< -10°C)**: Movement speed slows by 30%; player shivers (weapon spread +50%); takes hypothermia damage.
   - **Comfortable (-10°C to +35°C)**: Normal operation.
   - **Overheating (> +35°C)**: Thirst drains 3x faster; stamina cost of all actions doubled; heatstroke ticks.
4. **Day / Night Cycle**:
   - 1 Full Day = 24 real minutes (14 minutes day, 2 minutes dusk, 6 minutes night, 2 minutes dawn).
   - Nightfall brings deep darkness requiring torches, flashlights, or night-vision optics.
   - Night enemies are significantly more aggressive, have glowing eyes, and drop rare night-shards and cyber-salvage.

### 9.2 Building & Settlement Construction
- **Grid Placement**: 16x16 pixel grid snapping.
- **Blocks & Tiles**:
  - *Dirt & Stone*: Basic terrain; mineable with pickaxe.
  - *Wood Planks & Beams*: Basic structural walls and floors.
  - *Reinforced Concrete & Steel Plates*: High-durability blast-resistant walls.
  - *Glass & Windows*: Lets daylight pass through while blocking wind/cold.
  - *Doors & Hatches*: Open/close on interact or proximity (configurable).
  - *Platforms*: Solid to stand on; pressing `S + Space` drops through.
- **Structural Integrity & Raids**:
  - Wooden walls can be damaged and broken by tier 1-2 night beast enemies.
  - Upgrading to Stone, Concrete, or Powered Hard-Light Walls prevents enemy breaches.
- **Power Wiring & Illumination**:
  - Place Generators (Steam, Solar, Plasma Core). Run wires along walls to connect automated ceiling lights, defense turrets, and automated hydroponic sprayers.

### 9.3 Farming & Botany
- **Tilling**: Using a Hoe on dirt creates tilled soil.
- **Crops**:
  - *Rust-Wheat*: Used to bake bread (restores 35 Hunger).
  - *Hydro-Melon*: High water content (restores 20 Hunger, 40 Thirst).
  - *Bioluminescent Moss*: Used for alchemy and glow potions.
  - *Cyber-Weed*: High-yield fiber used in high-tech synthetic armor.
  - *Soma Berry*: Restores health and cures poison.
- **Growth Stages**: Seed -> Sprout -> Blooming -> Mature Harvest. Requires moisture (rain or watering can) and sunlight or grow-lights.

### 9.4 Crafting Stations & NPCs
Building a valid room (8x5 tiles enclosed with walls, door, light source, chair, and table) invites specialized NPCs to reside in the Hub.

1. **Workbench**: Basic tools, wood/stone building tiles, chests, torches.
2. **Forge & Ammo Press**: Smelts ores into ingots (Iron, Copper, Titanium, Adamantite); presses ballistic ammo and shells.
3. **Cyber-Clinic (Dr. Raymond, Cyber-Surgeon)**: Installs, swaps, and overclocks bionic body augmentations.
4. **Arcane Sanctum (Weaver Selene)**: Infuses ancient crystals, crafts magic wands, robes, and binds chimeric limbs.
5. **Kitchen Stove & Fermenter**: Cook complex meals with stat buffs (e.g. *Spicy Glazed Ribs*: +15% damage, cold resistance for 10 mins).
6. **Hydroponics Lab (Botanist Ivy)**: Sells exotic seeds, automated sprinklers, and rare plant extracts.

---

## 10. World Design, Biomes, Procedural Dungeons & Bosses

### 10.1 Overworld Zones & Hub Layout
The surface world is a seamless, hand-crafted Tiled map sequence flanking the central settlement:

```
[West]                                                                     [East]
Sunken Megalopolis <== Bioluminescent Bog <== THE HAVEN (Hub) ==> Rustwood Forest ==> Ashen Foundry ==> Cryo-Glacier
```

1. **The Haven (Central Hub)**: Safe zone with pre-existing ruins, NPC homes, clean water spring, farmland, and the entrance to the Dungeon Vaults.
2. **Rustwood Forest (West & East transition)**: Temperate ruined forest littered with rusted war machines, wildlife, deer, bandits, and scrap piles.
3. **Ashen Foundry (East Lowlands)**: Volcanic, smoke-choked industrial sector; flowing slag, magma slimes, rogue mining automations, extreme heat.
4. **Cryo-Glacier & Neon Peaks (Far East Mountains)**: Frozen peaks containing derelict military satellites and ice beasts; extreme sub-zero freezing.
5. **Bioluminescent Bog (West Swamp)**: Toxic, mushroom-covered wetlands; mutant amphibians, spore traps, acid puddles, high humidity.
6. **Sunken Megalopolis (Far West Coastal City)**: Half-submerged skyscrapers, cyber-cultists, flooded subways, advanced scrap technology.

---

### 10.2 The 8 Procedural Dungeon Tiers & Boss Encounters
Beneath the overworld lie the Vaults—procedural dungeons using a hybrid Binary Space Partitioning (BSP) and prefab-room graph generation algorithm. Each run generates a unique layout populated with traps, elite enemies, secret vaults, and a boss chamber.

#### Tier 1: The Rusted Catacombs
- **Biome Aesthetic**: Crumbling stone crypts entangled with rusty industrial pipes and flickering Edison bulbs.
- **Enemies**: Scrap Scavengers, Rabid Hounds, Steam Golems, Reanimated Servitors.
- **Boss**: **MK-1 Goliath Excavator**
  - Massive dual-tread mining robot armed with a drill arm and molten rivet gun.
  - Phase 1: Drills forward, bouncing off walls; fires arced rivet bursts.
  - Phase 2 (50% HP): Loses treads, mounts ceiling pipes, dropping burning hydraulic oil and slamming down on player.

#### Tier 2: The Overgrown Bio-Labs
- **Biome Aesthetic**: Glass greenhouses shattered by mutated roots, fluorescent grow-lights, ruptured cryo-stasis tanks.
- **Enemies**: Spore Spitters, Chimeric Vine Thralls, Acid Sprayers, Genetic Horrors.
- **Boss**: **Grafted Mother Chimera**
  - Multi-limbed monstrosity blending plant vines, mantis blades, and a bear torso.
  - Phase 1: Sweeping horizontal claw attacks; shoots toxic spore clusters that bloom into hazard zones.
  - Phase 2 (40% HP): Enters frenzy; latches to walls, launching homing quill barrages; summons vine tendrils from floor.

#### Tier 3: The Submerged Cooling Vaults
- **Biome Aesthetic**: Dripping industrial catwalks over deep electrified water, steam vents, rusted turbine generators.
- **Enemies**: Shock Drones, Waterlogged Reanimates, Arc Eels, Heavy Maintenance Bipeds.
- **Boss**: **Hydro-Turbine Overlord**
  - Armored diving mech with high-pressure water cannons and Tesla coils.
  - Phase 1: Floods floor sections, firing electricity that conducts through the water; requires platform navigation.
  - Phase 2 (50% HP): Charges a screen-wide whirlpool; fires tracking torpedoes while projecting an electric barrier.

#### Tier 4: The Molten Core Smeltery
- **Biome Aesthetic**: Heavy steel gantries suspended over boiling lakes of slag, automated crane claws, blast furnaces.
- **Enemies**: Magma Walkers, Flame-Troopers, Molten Slimes, Thermite Drones.
- **Boss**: **Forge-Master Vulcan**
  - Gigantic molten cyborg wielding a thermal warhammer and crucible shield.
  - Phase 1: Hammers anvil, sending lava waves horizontally; hurls canisters of molten metal.
  - Phase 2 (30% HP): Discards armor, igniting in full plasma flames; dashes across room leaving magma trails; triggers ceiling slag drop.

#### Tier 5: The Cryo-Stasis Depths
- **Biome Aesthetic**: Blue neon corridors encased in sheer ice, frozen humanoid specimens, leaking liquid nitrogen pipes.
- **Enemies**: Cryo-Snipers, Frozen Husks, Ice Golems, Frostbite Drones.
- **Boss**: **Absolute Zero Commander**
  - Cryogenic commander in an anti-matter exo-suit with dual ice-beam blasters.
  - Phase 1: Fires sweeping laser beams that freeze ground tiles into slick zero-friction ice; creates ice wall shields.
  - Phase 2 (50% HP): Summons a swirling blizzard reducing visibility; blinks around the arena leaving freezing time-bombs.

#### Tier 6: The Void-Warped Factory
- **Biome Aesthetic**: Corrupted industrial production line warped by purple arcane portals and reality tears.
- **Enemies**: Warp Phantoms, Automated Assembly Arms, Corrupted Turrets, Void Walkers.
- **Boss**: **The Dimensional Assembler**
  - Eldritch computer core fused with automated manufacturing presses.
  - Phase 1: Spawns conveyor belts moving the player into crushers; fabricates waves of cyber-minions while firing void lasers.
  - Phase 2 (40% HP): Warps the arena, inverting gravity periodically; fires dimensional rifts that pull player inward.

#### Tier 7: The Holy Citadel of Hard-Light
- **Biome Aesthetic**: Gleaming white marble combined with gold circuits and floating geometric hard-light platforms.
- **Enemies**: Light Sentinels, Solar Knights, Archon Turrets, Radiant Disciples.
- **Boss**: **Archon Prime, Seraph of Logic**
  - Four-winged biomechanical angel with a halo of plasma laser funnels.
  - Phase 1: Sweeping orbital cross-lasers; charges across the sky slashing with hard-light dual swords.
  - Phase 2 (30% HP): Summons glowing golden pillars that limit the arena; unleashes full-screen bullet-hell laser spirals.

#### Tier 8: The Sunken Orbital Core & The Final Boss
- **Biome Aesthetic**: The crashed bridge of a planet-harvesting ancient starship embedded deep in the earth; starfield visible through hull breaches.
- **Enemies**: Elite Cyber-Commandos, Nanite Swarms, Precursor Guardians.
- **The Final Boss**: **THE ARCHITECT**
  - The ancient planetary machine consciousness that triggered the cataclysm to reshape humanity into the ultimate biomechanical entity.
  - **Phase 1: Orbital Matrix Relay**: The Architect controls the central mainframe, deploying automated laser rings, shifting wall crushers, and rotating beam grids.
  - **Phase 2: The Transcendent Chimera Core**: The central core detaches, growing massive biomechanical limbs, energy wings, and arcane eyes. Combines all elemental attacks (fire, ice, lightning, void) while actively chasing the player.
  - **Phase 3: Singularity Avatar**: Down to the shattered central brain. Gravity distorts; time slows intermittently. The Architect unleashes devastating reality-rending slash waves and summoning shadow copies of the player’s own class.
  - **Victory**: The Architect is destroyed, stabilizing the planetary energy grid. The world is saved from the immediate cataclysm, unlocking the Infinite Rift.

---

### 10.3 The Endgame: The Infinite Rift
- Located in the deepest chamber of the Haven once The Architect is defeated.
- **Infinite Scaling Levels**: Rift Depth 1, 2, 3... infinite.
- **Affixes & Modifiers**: Each rift floor applies randomized mutators (e.g., *Solar Flare*: ambient heat + enemies explode on death; *Null-Magic*: mana costs doubled, energy weapon damage +50%; *Vampiric Swarm*: enemies heal on hit).
- **Prismatic & Ancient Gear**: Drops Tier 9+ Prismatic weapons with randomized unique affixes, allowing infinite min-maxing and build experimentation.

---

## 11. Complete Data Schemas (JSON)

All game content is data-driven. The C++ engine deserializes these definitions at startup into EnTT component templates.

### 11.1 Item Definition Schema (`items.json`)
```json
{
  "$schema": "http://json-schema.org/draft-07/schema#",
  "title": "ItemDefinition",
  "type": "object",
  "required": ["id", "name", "category", "rarity", "stackSize", "value"],
  "properties": {
    "id": { "type": "string" },
    "name": { "type": "string" },
    "description": { "type": "string" },
    "category": { 
      "type": "string", 
      "enum": ["weapon", "armor", "augmentation", "consumable", "material", "tool", "ammo"] 
    },
    "rarity": { 
      "type": "string", 
      "enum": ["common", "uncommon", "rare", "epic", "legendary", "prismatic"] 
    },
    "stackSize": { "type": "integer", "default": 1 },
    "value": { "type": "integer" },
    "sprite": {
      "type": "object",
      "required": ["atlas", "x", "y", "w", "h"],
      "properties": {
        "atlas": { "type": "string" },
        "x": { "type": "integer" },
        "y": { "type": "integer" },
        "w": { "type": "integer" },
        "h": { "type": "integer" }
      }
    },
    "weapon": {
      "type": "object",
      "properties": {
        "weaponType": { "type": "string", "enum": ["melee", "ballistic", "energy", "magic", "shield"] },
        "baseDamage": { "type": "number" },
        "damageType": { "type": "string", "enum": ["physical", "energy", "fire", "frost", "electric", "toxic", "holy", "void"] },
        "attackSpeed": { "type": "number" },
        "critChance": { "type": "number" },
        "knockback": { "type": "number" },
        "powerCost": { "type": "number", "default": 0 },
        "manaCost": { "type": "number", "default": 0 },
        "ammoType": { "type": "string" }
      }
    },
    "armor": {
      "type": "object",
      "properties": {
        "slot": { "type": "string", "enum": ["head", "chest", "legs", "feet"] },
        "defense": { "type": "integer" },
        "coldResist": { "type": "number" },
        "heatResist": { "type": "number" },
        "weight": { "type": "number" }
      }
    },
    "statModifiers": {
      "type": "object",
      "properties": {
        "str": { "type": "integer" },
        "dex": { "type": "integer" },
        "int": { "type": "integer" },
        "vit": { "type": "integer" },
        "wis": { "type": "integer" },
        "cyb": { "type": "integer" }
      }
    }
  }
}
```

### 11.2 Augmentation Definition Schema (`augmentations.json`)
```json
{
  "id": "aug_arm_laser_cannon",
  "name": "Arm-Mounted Laser Cannon",
  "slot": "right_arm",
  "type": "bionic",
  "humanityCost": 15,
  "stabilityCost": 0,
  "powerReserve": 10,
  "powerActiveCost": 15,
  "statModifiers": { "cyb": 8, "dex": 4 },
  "grantedSkill": "skill_arm_laser_fire",
  "passiveDescription": "Replaces right arm with high-energy focusing lens. RMB fires a high-velocity piercing beam.",
  "requiredLevel": 12,
  "craftCost": [
    { "item": "mat_titanium_ingot", "count": 8 },
    { "item": "mat_plasma_diode", "count": 2 },
    { "item": "mat_cyber_salvage", "count": 15 }
  ]
}
```

### 11.3 Skill Tree Schema (`skills.json`)
```json
{
  "id": "skill_seismic_shockwave",
  "name": "Seismic Shockwave",
  "tree": "juggernaut",
  "slot": "Q",
  "type": "active",
  "maxRanks": 5,
  "cooldown": 8.0,
  "staminaCost": 20.0,
  "manaCost": 0.0,
  "powerCost": 0.0,
  "description": "Slam the ground with immense force, sending forth a shockwave dealing physical damage and launching foes.",
  "damageFormula": "baseDamage * (1.5 + rank * 0.3) * (1 + STR * 0.015)",
  "prerequisites": [],
  "icon": { "atlas": "skills_ui", "x": 0, "y": 0, "w": 32, "h": 32 }
}
```

---

## 12. Phased Implementation Roadmap (TDD Driven: Step 0 through M10)

Development strictly follows **Test-Driven Development (TDD)**:
1. **Red**: Write a failing unit test in `tests/test_*.cpp` specifying the required behavior or mathematical outcome.
2. **Green**: Implement the minimal, clean C++ code in `src/` to make the test pass.
3. **Refactor**: Clean up and optimize the implementation while maintaining full test passage.
4. **Integration**: Wire the tested component into the EnTT ECS and Box2D simulation loop.

### Step 0: Git Repository Setup & Project Genesis
- [ ] Initialize local Git version control repository (`git init`).
- [ ] Create comprehensive `.gitignore` for CMake build folders (`build/`), Ninja caches, macOS metadata (`.DS_Store`), and IDE configs.
- [ ] Create initial git commit locking in master architecture plan and granular design specifications.

### Milestone 0: Engine Skeleton & Display System
- [ ] Write Catch2 tests for core timing, fixed delta math, and JSON configuration parsing.
- [ ] CMakeLists.txt with `FetchContent` for SDL3, Box2D v3, EnTT, nlohmann_json, spdlog, Dear ImGui, Catch2.
- [ ] Platform & display initialization: Monitor detection, selectable resolution list, letterboxed 16x16 integer pixel canvas.
- [ ] Fixed-timestep loop (60Hz) with frame interpolation.
- [ ] Input action mapper (WASD, mouse, hotkeys).
- [ ] Render a movable placeholder pixel sprite with WASD.
- [ ] ImGui debug overlay showing FPS, frame time, resolution, and memory.

### Milestone 1: Platformer Physics & Kinematic Character Controller
- [ ] Write Catch2 tests for kinematic movement math, jump curves, coyote time, and input buffer windows.
- [ ] Tilemap parser for Tiled JSON (`.tmj`) format; static Box2D edge/chain collision generation.
- [ ] Character controller: Variable jump height, jump buffering (0.1s), coyote time (0.08s), wall-sliding, one-way platform drop-through (`S + Space`).
- [ ] Pixel-snapped 2D camera with deadzone and level bounds clamping.
- [ ] Sprite animation state machine (Idle, Run, Jump, Fall, WallSlide).

### Milestone 2: Combat Engine & Hitbox Pipeline
- [ ] Write Catch2 tests for damage calculations, armor mitigation, critical hits, and status effect ticks.
- [ ] Short-lived Box2D sensor hitboxes attached to weapon swing arcs and mouse direction with hit-deduplication.
- [ ] Hitstop (2-4 frame screen pause), directional knockback, camera shake, floating damage numbers.
- [ ] Basic enemy AI: Walker (patrols, detects, leaps) and Flyer (swoops, shoots).
- [ ] Player health, death screen, and respawn at hub spawn point.

### Milestone 3: Inventory, Equipment, 3,000+ Items & Firearms
- [ ] Write Catch2 tests for inventory stacking, weight encumbrance, Gaussian base stat rolls, and affix generation.
- [ ] Data-driven item loader supporting 3,000+ base items (`items.json`).
- [ ] Grid inventory UI (slots, drag-and-drop, stacking, item tooltips).
- [ ] Equipment slots (Head, Chest, Legs, Boots, Main Hand, Off Hand, Ring x2, Amulet).
- [ ] Ballistic firearms with projectile physics, ammo consumption, reloading, and spread.
- [ ] Energy weapons consuming power; magic wands consuming mana.
- [ ] Procedural loot drop system with rarity borders (Common to Prismatic) and dynamic affix rolling.

### Milestone 4: Classes, Uncapped Leveling & 500+ Skill System
- [ ] Write Catch2 tests for uncapped XP curves, skill DAG prerequisite validation, and respec point refunds.
- [ ] Leveling curve implementation ($1 \to \infty$) with XP awards from kills and gathering.
- [ ] Class selection UI at new game with all 9 classes, base stats, and starter gear.
- [ ] Interactive Skill Tree UI: The 40-node Shared Tree + 50-node Class Trees (over 500 skills total).
- [ ] Hotkey assignment for 4 active skill slots (`Q`, `E`, `R`, `F`).
- [ ] Level 20 Milestone trigger: Automatically awards the class-specific Free Signature Augmentation.
- [ ] Cross-Class Neural Bridge system unlocking universal skill learning post-Level 60.

### Milestone 5: The 11-Slot Augmentation System (250+ Augments) & Cyber-Clinic
- [ ] Write Catch2 tests for 11 body slot constraints, power capacity reserves, and Cellular Rejection triggers.
- [ ] Augmentation data structures for all 11 body slots (Head, Eyes, Nervous, Lungs, Heart, Torso, Skin, L-Arm, R-Arm, Hands, Legs).
- [ ] The Dual Energy calculation: Power budget reserve vs Humanity penalty, and Mana upkeep vs Stability.
- [ ] Cyber-Clinic UI: Install, uninstall, and view holographic wireframe of player's augmented body.
- [ ] Implementation of signature augments: Arm laser cannons, jet boots, chimeric bear arms, and deflector shields.
- [ ] Cross-class exotic surgery rules with neural rejection and incompatibility penalties.

### Milestone 6: Crafting Tree & Deterministic Item Modification Forge
- [ ] Write Catch2 tests for recipe discovery, affix shard infusion, stat tier upgrading, and fracture probability.
- [ ] Implement the 48-node Crafting Specialization Tree (Weaponsmithing, Armor-Plating, Cyber-Engineering, Bio-Alchemy).
- [ ] Implement crafting station UIs (Workbench, Forge & Ammo Press, Kitchen Stove, Hydroponics Lab).
- [ ] Implement Modification Forge: Stat shard infusion, Tier 1–7 upgrading, instability tracking, fracture locks, value calibration, socket punching, and affix sealing.

### Milestone 7: Survival Systems, Day/Night & Settlement Building
- [ ] Write Catch2 tests for hunger/thirst depletion rates, effective temperature calculations, and crop hydration checks.
- [ ] Hunger and Thirst decay mechanics; edible food items and clean water sources.
- [ ] Ambient temperature simulation with weather effects (Rain, Snow, Heatwave) and hypothermia/heatstroke.
- [ ] Day/Night lighting shader (24-minute cycle) with torch and campfire dynamic lights.
- [ ] 16x16 grid building system: Place and break walls, floors, doors, platforms, and storage chests.
- [ ] Farming system: Till soil, plant seeds, water crops, growth stages, harvesting.
- [ ] NPC housing verification: Spawns the Cyber-Surgeon, Blacksmith, Botanist, and Merchant NPCs into built rooms.

### Milestone 8: Procedural Dungeons in Every Biome (20+ Biomes) & Tiers 1–3
- [ ] Write Catch2 tests for BSP dungeon room partitioning, hallway graph connectivity (BFS solvability), and recovery drone drops.
- [ ] BSP and prefab room graph dungeon generator producing sprawling 2D levels in all 20+ biomes.
- [ ] Tier 1 (Rusted Catacombs), Tier 2 (Overgrown Bio-Labs), Tier 3 (Submerged Vaults).
- [ ] Traps, locked doors, keycards, and chest rooms.
- [ ] Boss fight state machines for Tier 1 (Goliath Excavator), Tier 2 (Mother Chimera), and Tier 3 (Hydro-Turbine Overlord).
- [ ] Dungeon death rule: Retain equipped gear and augmentations; drop 25% of carried raw materials in recovery drone at death site.

### Milestone 9: Campaign Tiers 4–8, The Architect & Infinite Rift Endgame
- [ ] Write Catch2 tests for multi-phase boss state machines and Infinite Rift floor scaling algorithms.
- [ ] Tier 4 (Molten Smeltery), Tier 5 (Cryo-Stasis Depths), Tier 6 (Void Factory), Tier 7 (Citadel of Hard-Light).
- [ ] Tier 8 crashed starship dungeon: The Sunken Orbital Core.
- [ ] 3-phase epic confrontation against **The Architect** (Orbital Relay, Chimera Core, Singularity Avatar).
- [ ] Post-game transition: Unlocks The Infinite Rift in the Haven hub.
- [ ] Infinite scaling dungeon generator with randomized mutators and Tier 9+ Prismatic gear with affix combinations.

### Milestone 10: Multiplayer-Ready State Separation, Audio, Polish & Packaging
- [ ] Client-server / headless simulation separation for future online multiplayer.
- [ ] Audio system integration: Positional SFX, ambient soundscapes, dynamic combat music transitions.
- [ ] Visual polish: Hit particles, dust puffs, liquid splashes, shell casing ejections, and screen shake tuning.
- [ ] Input settings: Rebindable keyboard keys and full Gamepad controller support with aim assist.
- [ ] Save/Load persistence: High-speed JSON serialization of player stats, inventory, augmentations, world changes, and placed tiles.
- [ ] Performance profiling: Sprite batching optimization, chunked tilemap culling, steady 60+ FPS on Apple Silicon.
- [ ] macOS `.app` bundle build target and deployment packaging.

---

## 13. Dev Environment Setup & Conventions

### 13.1 macOS Build Instructions
```sh
xcode-select --install                  # Apple Clang, lldb, git
brew install cmake ninja                # Build system and fast generator
```

Configure and build:
```sh
cmake -B build -G Ninja -DCMAKE_BUILD_TYPE=Debug
cmake --build build
./build/untitled_rpg
```

### 13.2 Code Standards & Conventions
- **C++20**: `-Wall -Wextra -Werror` in debug.
- **Naming**: `snake_case` for files and components; `PascalCase` for classes, structs, and systems; `camelCase` for functions and variables.
- **ECS**: Components are pure POD data structs without logic. Systems are free functions `void UpdateX(entt::registry& registry, float dt)`.
- **Data-Driven**: All stats, costs, damage values, and drop rates live in `assets/data/*.json`. Hardcoded constants in C++ gameplay logic are prohibited.
- **Testing**: Every core system (Stats pipeline, Inventory/Augmentation equipping, Dungeon generation) has accompanying Catch2 tests in `tests/`.

