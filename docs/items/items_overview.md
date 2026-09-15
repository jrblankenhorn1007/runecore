# Items, Equipment, Weapons & Loot Specification

This document provides the exhaustive specification for the itemization, 3,000+ unique item taxonomy, individual base stat roll ranges, probability distributions, weapon arsenal, armor sets, survival consumables, crafting resources, and dynamic affix generation systems in Untitled RPG.

---

## 1. Item Architecture, Rarity Tiers & The 3,000+ Item Taxonomy

Every item in the game is an individually instantiated data object. When an item is generated (via enemy drop, chest loot, dungeon vault, or crafting), its base stats and affixes roll probabilistically from defined ranges.

### 1.1 The 3,000+ Unique Item Taxonomy & Matrix
The game features over **3,000 distinct base items**, organized across 10 equipment categories and 8 world progression tiers:

```
[10 Categories]
 ├── 1. Melee Weapons         (Swords, Greatswords, Katanas, Claws, Hammers, Spears, Daggers, Scythes)
 ├── 2. Ballistic Firearms    (Revolvers, Pistols, Shotguns, Carbines, Rifles, Snipers, Miniguns, Flak)
 ├── 3. Energy & Beam Weapons (Pulse Blasters, Laser Cutters, Arc Dischargers, Gauss Railguns, Wave Cannons)
 ├── 4. Magic Implements      (Sparks Wands, Elemental Staffs, Grimoires, Void Scepters, Chimes)
 ├── 5. Shields & Off-Hands   (Kite Shields, Aegis Emitters, Parrying Daggers, Alchemical Flasks)
 ├── 6. Armor Pieces          (Helmets, Chestplates, Greaves, Sabatons across Light, Medium, Heavy)
 ├── 7. Body Augmentations    (Bionic, Magitech, and Chimeric implants across 11 body slots)
 ├── 8. Accessories           (Rings, Amulets, Relics, Power Cores, Nanite Belts)
 ├── 9. Survival Tools        (Pickaxes, Wood Axes, Farming Hoes, Canteens, Geological Scanners)
 └── 10. Consumables & Mats   (Cooked Meals, Potions, Injections, Ores, Ingots, Nanite Salvage, Gems)

[8 Progression Tiers]
 ├── Tier 1: Scrap / Rusted / Makeshift       (Levels 1–10)   -> 350 Unique Base Items
 ├── Tier 2: Refined Iron / Bio-Cultured      (Levels 11–20)  -> 380 Unique Base Items
 ├── Tier 3: Industrial Steel / Steam-Forged  (Levels 21–30)  -> 400 Unique Base Items
 ├── Tier 4: Volcanic Slag / Titanium-Plated  (Levels 31–40)  -> 420 Unique Base Items
 ├── Tier 5: Cryo-Alloy / Liquid Nitrogen     (Levels 41–50)  -> 440 Unique Base Items
 ├── Tier 6: Dimensional Void / Warped        (Levels 51–58)  -> 450 Unique Base Items
 ├── Tier 7: Archon Hard-Light / Sanctified   (Levels 59–60)  -> 460 Unique Base Items
 └── Tier 8 / Prismatic: Precursor & Rift God (Endgame 60+)   -> 500+ Unique Base Items
 Total Catalog: > 3,400 Unique Base Item Definitions
```

---

### 1.2 Individual Base Stat Roll Ranges & Probability Distributions

No two dropped weapons or armor pieces are identical. Each base item definition specifies a **min-max range** for each base stat. When an item drops or is crafted, the engine rolls its individual stats.

#### 1. The Gaussian / Triangular Roll Formula
To create the rewarding feeling of hunting for "god rolls", stat generation uses a triangular distribution (averaging three uniform random variables) rather than flat uniform RNG. This clusters rolls near the median while making minimum and maximum rolls distinctively rare:

$$\text{RollFactor} = \frac{R_1 + R_2 + R_3}{3}, \quad R_1, R_2, R_3 \sim \mathcal{U}(0, 1)$$
$$\text{RolledStat} = \text{Stat}_{\min} + (\text{Stat}_{\max} - \text{Stat}_{\min}) \times \text{RollFactor}$$

#### 2. Item Quality Influence (0% to 20%)
Crafted items or items found in secret dungeon vaults can roll an innate **Quality** ($0\%$ to $20\%$). Quality provides a linear bonus skew to the roll factor:
$$\text{EffectiveRollFactor} = \min\left(1.0, \; \text{RollFactor} + \frac{\text{Quality}}{100.0} \times 0.25\right)$$

#### 3. Base Item Definition Format & Properties
Each base item definition declares:
- **Base Identification**: Unique identifier, display name, tier level (1 to 8), and equipment category.
- **Roll Ranges**: Min-max damage range, attack speed range, critical chance range, and max durability range.
- **Implicit Modifiers**: Innate archetype bonuses (e.g., weakpoint critical multiplier, innate armor penetration, or elemental affinity) with distinct roll bounds.

---

### 1.3 Rarity Hierarchy & Affix Budgets

| Rarity | UI Border Color | Base Stat Multiplier | Affix Slots | Description |
|---|---|---|---|---|
| **Common** | White (`#CCCCCC`) | $1.0\times$ | 0 | Standard mass-produced scrap, basic tools, starter gear. |
| **Uncommon** | Green (`#4CAF50`) | $1.15\times$ | 1 | Refined materials, improved alloys, minor enchantments. |
| **Rare** | Blue (`#2196F3`) | $1.35\times$ | 2 | Superior craftsmanship, military-grade components, ancient runes. |
| **Epic** | Purple (`#9C27B0`) | $1.65\times$ | 3 | Prototype high-tech weaponry, high-potency arcane relics. |
| **Legendary** | Gold (`#FFC107`) | $2.0\times$ | 4 + 1 Unique Perk | Named boss drops, masterwork technological breakthroughs. |
| **Prismatic** | Iridescent (`#E040FB`) | $2.5\times$ | 5 + 2 Unique Perks | Ultra-rare endgame drops exclusive to the Infinite Rift (Tier 9+). |

---

## 2. Complete Weapons Catalog

The reorganized weapon documentation is indexed at [docs/items/weapons/weapons_index.md](weapons/weapons_index.md). Weapons are grouped into Melee, Ballistic Firearms, Energy and Beam, Magic Implements, and Shields and Off-Hands; every weapon has its own name-based dossier with detailed stats and usage notes.

Weapons operate with real-time Terraria-style aiming towards the mouse crosshair, imparting physical recoil, screen shake, and hitstop.

```
[Weapons Catalog]
 ├── Melee Weapons          (Swords, Greatswords, Daggers, Spears, Hammers, Energy Sabers)
 ├── Ballistic Firearms     (Pistols, Shotguns, Assault Rifles, Snipers, Flak Cannons) -> Uses Physical Ammo
 ├── Energy & Beam Weapons  (Plasma Blasters, Laser Cutters, Arc Dischargers, Railguns) -> Uses Power Units
 ├── Magic Implements       (Wands, Staffs, Grimoires, Void Relics)                     -> Uses Mana
 └── Shields & Off-Hands    (Kite Shields, Forcefield Emitters, Parrying Daggers, Flasks)
```

---

### 2.1 Melee Weapons

| Weapon ID | Name | Damage | Attack Speed | Reach | Resource Cost | Special Properties |
|---|---|---|---|---|---|---|
| `wpn_mel_machete` | *Scrap Machete* | 12 Phys | 1.8/s | 2.0 tiles | 5 Stamina | Fast starter arc swing. |
| `wpn_mel_katana` | *High-Frequency Katana*| 26 Phys | 2.5/s | 2.2 tiles | 8 Stamina | $+20\%$ Critical Strike Chance; swings inflict Bleed. |
| `wpn_mel_greatsword`| *Industrial Cleaver* | 55 Phys | 0.9/s | 3.0 tiles | 16 Stamina | Two-handed; heavy sweep knocks enemies backward 4 tiles. |
| `wpn_mel_hammer` | *Rocket-Powered Sledge* | 75 Phys | 0.6/s | 2.5 tiles | 22 Stamina | Ground strike triggers shockwave dealing $50\%$ AoE damage. |
| `wpn_mel_spear` | *Chimeric Bone Pike* | 32 Phys | 1.5/s | 3.5 tiles | 10 Stamina | Straight thrust; pierces through up to 3 targets in a line. |
| `wpn_mel_dagger` | *Carbon Nano-Dagger* | 14 Phys | 3.8/s | 1.4 tiles | 4 Stamina | $+35\%$ Critical Strike Chance; strikes from behind deal $+100\%$ dmg. |
| `wpn_mel_saber` | *Plasma Saber* | 48 Energy | 2.0/s | 2.2 tiles | 1 Power/swing | Pure energy blade; completely ignores physical armor. |
| `wpn_mel_scythe` | *Reaper's Nanite Scythe*| 42 Dark | 1.2/s | 2.8 tiles | 12 Stamina | Slaying enemies generates 1 guaranteed Soul Fragment. |

---

### 2.2 Ballistic Firearms (Consumes Physical Ammo)

| Weapon ID | Name | Damage per Shot | Fire Rate | Mag Size | Reload | Ammo Type | Special Properties |
|---|---|---|---|---|---|---|---|
| `wpn_gun_revolver` | *Scavenger's Revolver* | 24 Phys | 2.2/s | 6 rounds | 1.4s | Light Ammo | High single-target stagger; precision weakpoint bonus. |
| `wpn_gun_shotgun` | *Trench Sweeper* | $8 \times 8$ Phys | 1.0/s | 5 shells | 2.2s | Shotgun Shell | 8-pellet spread; massive close-range knockback. |
| `wpn_gun_rifle` | *Assault Carbine* | 18 Phys | 8.0/s | 30 rounds | 1.8s | Light Ammo | Fully automatic; moderate bullet spread after 5 shots. |
| `wpn_gun_sniper` | *Anti-Materiel Cannon* | 145 Phys | 0.7/s | 4 rounds | 2.8s | Heavy Ammo | Extreme bullet velocity; pierces through 4 enemies. |
| `wpn_gun_flak` | *Flak Hand-Cannon* | 55 Blast | 1.2/s | 4 shells | 2.0s | Explosive Shell| Projectile explodes on contact in a 2.5-tile radius. |
| `wpn_gun_minigun` | *Rotary Autocannon* | 22 Phys | 12.0/s | 100 rounds | 4.0s | Heavy Ammo | Spools up over 1.0s; slows movement speed by $30\%$ while firing. |

---

### 2.3 Energy & Beam Weapons (Consumes Power from Core)

| Weapon ID | Name | Damage | Fire Rate / Upkeep | Power Cost | Range | Special Properties |
|---|---|---|---|---|---|---|
| `wpn_nrg_blaster` | *Plasma Pulse Blaster* | 34 Energy | 3.0/s | 4 Power/shot | 16 tiles | Fires glowing plasma orbs; melts physical armor. |
| `wpn_nrg_laser` | *Continuous Beam Cutter*| 95 Energy/s | Continuous (10 ticks/s)| 6 Power/sec | 12 tiles | Continuous surgical beam; focuses damage on a single point. |
| `wpn_nrg_arc` | *Tesla Arc Projector* | 42 Electric | 1.8/s | 10 Power/shot | 10 tiles | Lightning chains between up to 4 targets in proximity. |
| `wpn_nrg_railgun` | *Magnetic Gauss Railgun* | 210 Energy | 0.5/s (1s charge) | 25 Power/shot | Screen-wide | Supersonic slug pierces all terrain and enemies in line. |
| `wpn_nrg_wave` | *Disruption Wave Cannon*| 60 Sonic | 1.2/s | 12 Power/shot | 8-tile cone | Fires expanding sonic wave that disarms mechanical enemies. |

---

### 2.4 Magic Implements (Consumes Mana)

| Weapon ID | Name | Damage | Cast Speed | Mana Cost | Element | Special Properties |
|---|---|---|---|---|---|---|
| `wpn_mag_spark` | *Apprentice Spark Wand*| 18 Magic | 3.5/s | 4 Mana | Arcane | Fast, low-cost magic darts with light homing tracking. |
| `wpn_mag_flame` | *Pyromancer's Flame Staff*| 65 Fire | 1.1/s | 18 Mana | Fire | Hurls arced fire meteor that creates burning ground patch. |
| `wpn_mag_frost` | *Cryo-Shard Grimoire* | $5 \times 12$ Frost| 1.6/s | 22 Mana | Frost | Conical volley of 5 ice shards; freezes targets for 2s. |
| `wpn_mag_void` | *Void Tendril Staff* | 40 Void/strike | 0.8/s | 30 Mana | Void | Summons stationary tentacle on ground that slashes nearby foes. |
| `wpn_mag_radiant`| *Solar Prism Scepter* | 52 Holy | 2.0/s | 16 Mana | Holy | Concentrated ray of daylight; $+50\%$ damage against undead. |

---

### 2.5 Shields & Off-Hands

| Weapon ID | Name | Block % | Parry Window | Durability / Cost | Special Properties |
|---|---|---|---|---|---|
| `wpn_shd_kite` | *Reinforced Iron Shield* | $75\%$ Frontal | 0.15s | 15 Stamina/hit | Standard blocking shield; parrying stuns attacker for 1.5s. |
| `wpn_shd_force` | *Hard-Light Aegis Emitter*| $100\%$ Frontal | 0.20s | 8 Power/hit | Parrying reflects hostile projectiles back to attacker. |
| `wpn_shd_dagger`| *Duelist's Main-Gauche* | $40\%$ Frontal | 0.30s | 8 Stamina/hit | Offhand parrying dagger; successful parry empowers next main-hand crit. |
| `wpn_shd_flask` | *Caustic Alchemical Vial*| N/A | N/A | Consumable | Thrown with RMB to shatter corrosive pool shredding armor. |

---

## 3. Complete Armor Sets & Clothing

Armor is equipped in 4 slots: **Head**, **Chest**, **Legs**, **Boots**. Full sets provide a powerful **Set Bonus**.

### 3.1 Armor Sets Table

| Set Name | Slot Breakdown | Total Armor | Temperature Insulation | Weight / Speed Penalty | Full Set Bonus |
|---|---|---|---|---|---|
| **Scavenger Ragged** | Cloth Hood, Tunic, Pants, Wraps | 12 Armor | Cold $+5$, Heat $+5$ | 0 kg (0% penalty) | $+10\%$ Gathering and Scrap finding yield. |
| **Reinforced Welder** | Welder Mask, Plated Vest, Overalls, Boots | 35 Armor | Cold $+15$, Heat $+30$ | 12 kg (-6% speed) | Blast/fire damage reduced by $40\%$. |
| **Iron-Alloy Combat** | Iron Helm, Breastplate, Greaves, Sabatons | 58 Armor | Cold $+10$, Heat $-5$ | 24 kg (-12% speed) | Knockback resistance $+60\%$; $+10\%$ Melee Damage. |
| **Titanium Exo-Suit** | Cyber-Helmet, Rig Chest, Servo-Legs, Boots | 85 Armor | Cold $+25$, Heat $+25$ | 16 kg (0% penalty) | Maximum Power $+40$; sprint speed $+25\%$. |
| **Chitin Carapace** | Horned Chitin Helm, Chest, Greaves, Claws | 70 Armor | Cold $-10$, Heat $+15$ | 10 kg (+5% speed) | Reflects $25\%$ of physical melee damage taken back to attacker. |
| **Arcane Aether Robes** | Hood of Focus, Robe, Trousers, Slippers | 28 Armor | Cold $+20$, Heat $+20$ | 4 kg (+5% speed) | Maximum Mana $+80$; Spell Mana costs reduced by $20\%$. |
| **Hard-Light Templar** | Archon Crown, Plate, Leggings, War-Boots | 110 Armor | Cold $+35$, Heat $+35$ | 28 kg (-5% speed) | Taking fatal damage creates a 5-second invulnerable light dome. |

---

## 4. Survival Consumables & Reagents

### 4.1 Food Items
- **Baked Rust-Bread**: Restores 35 Hunger. (Crafted at Stove: 3x Rust-Wheat).
- **Roasted Game Meat**: Restores 50 Hunger, $+5\text{ HP/s}$ for 10s. (Cooked at Campfire: 1x Raw Meat).
- **Hydro-Melon Slice**: Restores 20 Hunger, 40 Thirst. (Harvested from Hydro-Melon crop).
- **Spicy Glazed Ribs**: Restores 80 Hunger, grants $+15\%$ physical damage and $+25$ Cold Resistance for 10 minutes.
- **Hearty Mushroom Stew**: Restores 60 Hunger, 30 Thirst, grants $+10\%$ Max Health for 15 minutes.

### 4.2 Water & Hydration
- **Contaminated Water Canteen**: Restores 40 Thirst; $50\%$ chance to inflict Parasites (drains 2 HP/s unless player has *Iron Stomach*).
- **Boiled Clean Water**: Restores 50 Thirst, zero infection risk. (Crafted at Campfire: Contaminated Water + Fuel).
- **Purified Hydro-Flask**: Restores 80 Thirst, grants $+20\%$ Stamina Regeneration for 5 minutes.
- **Electrolyte Stim-Drink**: Restores 50 Thirst, 30 Power, restores 50 Stamina instantly.

### 4.3 Medicine & Injections
- **Sterile Bandage**: Stops Bleeding instantly; restores 40 HP over 6 seconds.
- **Nanite Med-Kit**: Restores 150 HP over 4 seconds; repairs broken limb status effects.
- **Universal Antitoxin**: Cleanses all poison, acid, and neurotoxin debuffs immediately.
- **Adrenaline Combat Injector**: Grants $+30\%$ movement speed, $+20\%$ attack speed, and immunity to slow/stun for 12 seconds.

---

## 5. Dynamic Affix Generation System

When an item of **Uncommon** or higher rarity is generated (via enemy drop, chest loot, or crafting), it draws from a pool of prefix and suffix modifiers based on item category and level tier.

### 5.1 Affix Tables

#### Prefixes (Affects Offense, Attributes, and Power)
- `Jagged`: $+5\%$ to $+15\%$ Physical Weapon Damage.
- `Overclocked`: $+10\%$ to $+25\%$ Attack Speed; $+5$ Power Drain.
- `Glacial`: Adds $+8$ to $+20$ Frost Damage; attacks chill targets by $20\%$.
- `Volcanic`: Adds $+10$ to $+25$ Fire Damage; attacks ignite targets.
- `Galvanized`: Adds $+12$ to $+30$ Shock Damage; attacks chain to 1 enemy.
- `Titanic`: $+4$ to $+12$ Strength; $+50$ Max Health.
- `Nimble`: $+4$ to $+12$ Dexterity; $+5\%$ Critical Strike Chance.
- `Enlightened`: $+4$ to $+12$ Intelligence; $+30$ Max Mana.
- `Cybernetic`: $+5$ to $+15$ Cyber-Affinity; $+20$ Max Power.

#### Suffixes (Affects Defense, Utility, and Procs)
- `of Haste`: $+5\%$ to $+12\%$ Movement Speed.
- `of the Leech`: $+2\%$ to $+6\%$ Lifesteal on hit.
- `of Deflection`: $+5$ to $+15$ Armor; $+10\%$ Projectile Deflection Chance.
- `of the Salamander`: $+20$ to $+40$ Heat and Fire Resistance.
- `of the Yeti`: $+20$ to $+40$ Cold and Frost Resistance.
- `of the Juggernaut`: $+50$ to $+150$ Max Health; knockback resistance $+30\%$.
- `of Annihilation`: Critical strike multiplier increased by $+0.3\times$ to $+0.8\times$.

---

## 6. Inventory & Equipment Conceptual Model

### 6.1 Individual Item Instance Model
Each item instance maintains:
- **Base Item Reference**: Pointer or identifier to the base catalog definition.
- **Quantity & Stack Count**: 1 for weapons/armor/augmentations; up to category stack size for consumables/materials.
- **Durability**: Current vs. maximum durability points (tools and non-indestructible weapons).
- **Quality Percentage**: $0.0\%$ to $20.0\%$, influencing stat potency and vendor value.
- **Crafting Instability & Fracture State**: Instability rating (0–100) and fracture flag indicating whether further bench modification is prohibited.
- **Rolled Base Stats**: Realized values for primary attributes, damage bounds, and attack speeds within base ranges, including percentile grade.
- **Rolled Affixes**: Dynamic list of prefix and suffix modifiers granted by rarity or crafting.
- **Socketed Sockets**: Sockets holding inlaid power crystals, elemental chips, or runic components.

### 6.2 Player Inventory & Equipment Layout
- **Hotbar**: 8 immediately accessible slots selectable via number keys (`1`–`8`) or mouse wheel.
- **Backpack Storage**: 32 grid inventory slots supporting drag-and-drop organization and stack splitting.
- **Weight & Encumbrance**: Total carried mass tracked against carry capacity ($60\text{ kg}$ base + Strength bonuses).
- **Equipment Slots**: 9 dedicated character slots: Head, Chest, Legs, Boots, Main Hand, Off Hand, Ring 1, Ring 2, and Amulet. (Augmentations are managed separately in the 11-slot Cyber-Clinic body grid).

