# Wands, Scepters & Magic Implements Catalog

This document specifies the individual base stat roll ranges, mana costs, projectile trajectories, elemental schools, and spell affinities for wands and scepters across all 8 progression tiers in Untitled RPG (~160 weapon definitions).

---

## 1. Mechanics & Stat Rolling Parameters
- **Primary Scaling Attribute**: Intelligence (INT) ($+2.0\%$ per point) and Wisdom (WIS) ($+1.0\%$ per point).
- **Mana Resource System**: Wands and scepters consume player **Mana** directly with each cast.
- **Weapon Sub-Types**:
  - *Spark Wands*: Ultra-fast casting speed (3.0 to 4.5 casts/s), low mana cost (3 to 6 MP), light homing tracking.
  - *Elemental Scepters*: Mid-range channeled or single-bolt spells (1.8 to 2.5 casts/s), moderate mana cost (12 to 20 MP), inflicts elemental status effects (Burn, Freeze, Shock, Toxin).
  - *Focus Rods*: Empowers active skill hotkeys, granting cooldown reduction and mana cost discounts.
  - *Chimes & Relic Bells*: Radiates supportive healing and cleansing pulses to self and allies.

---

## 2. Tier 1: Makeshift Wooden Wands (Levels 1–10)

| ID | Name | Element | Damage Range | Cast Speed | Mana Cost | Special / Implicit |
|---|---|---|---|---|---|---|
| `wpn_wnd_t1_01` | *Carved Oak Spark Wand* | Arcane | 12.0 – 16.0 | 3.2 – 3.6/s | 4 MP | Light homing dart |
| `wpn_wnd_t1_02` | *Copper-Etched Focus Rod* | Lightning | 14.0 – 18.0 | 2.5 – 2.8/s | 5 MP | Small shock arc |
| `wpn_wnd_t1_03` | *Charred Branch Fire Scepter*| Fire | 18.0 – 24.0 | 1.8 – 2.1/s | 8 MP | 20% Burn chance |
| `wpn_wnd_t1_04` | *Glacial Icicle Wand* | Frost | 15.0 – 20.0 | 2.2 – 2.5/s | 6 MP | Chills targets 20% |
| `wpn_wnd_t1_05` | *Goliath Excavator Core Wand*| Magma | 22.0 – 30.0 | 1.6 – 1.9/s | 10 MP| Boss drop: Fires lava globules |

---

## 3. Tier 2: Refined Silver & Crystal Wands (Levels 11–20)

| ID | Name | Element | Damage Range | Cast Speed | Mana Cost | Special / Implicit |
|---|---|---|---|---|---|---|
| `wpn_wnd_t2_01` | *Silver Conduit Wand* | Arcane | 24.0 – 32.0 | 3.5 – 4.0/s | 6 MP | Mana cost $-15\%$ |
| `wpn_wnd_t2_02` | *Bio-Lab Spore Scepter* | Toxin | 26.0 – 35.0 | 2.2 – 2.6/s | 9 MP | Spores linger on ground |
| `wpn_wnd_t2_03` | *Sapphire Frost Scepter* | Frost | 28.0 – 38.0 | 2.0 – 2.4/s | 10 MP| Freezes on 4 hits |
| `wpn_wnd_t2_04` | *Ruby Fireball Wand* | Fire | 32.0 – 44.0 | 1.8 – 2.2/s | 12 MP| Explosive splash 1.5 tiles |
| `wpn_wnd_t2_05` | *Mother Chimera Venom Rod* | Nature | 30.0 – 40.0 | 2.5 – 3.0/s | 8 MP | Boss drop: Spawns acid vines |

---

## 4. Tier 3: Industrial Arc & Steam Scepters (Levels 21–30)

| ID | Name | Element | Damage Range | Cast Speed | Mana Cost | Special / Implicit |
|---|---|---|---|---|---|---|
| `wpn_wnd_t3_01` | *Tesla Coil Arc Wand* | Lightning | 38.0 – 50.0 | 2.8 – 3.3/s | 10 MP| Chains to 3 enemies |
| `wpn_wnd_t3_02` | *High-Pressure Steam Scepter*| Fire/Water| 42.0 – 56.0 | 2.0 – 2.4/s | 14 MP| Blinds and pushes enemies |
| `wpn_wnd_t3_03` | *Hydro-Turbine Water Wand* | Cold | 45.0 – 60.0 | 2.2 – 2.6/s | 12 MP| Boss drop: Creates water surge |

---

## 5. Tier 4: Volcanic & Titanium Scepters (Levels 31–40)

| ID | Name | Element | Damage Range | Cast Speed | Mana Cost | Special / Implicit |
|---|---|---|---|---|---|---|
| `wpn_wnd_t4_01` | *Titanium Focus Rod* | Arcane | 55.0 – 72.0 | 3.8 – 4.4/s | 8 MP | Skill cooldowns $-20\%$ |
| `wpn_wnd_t4_02` | *Molten Slag Meteor Scepter*| Fire | 68.0 – 90.0 | 1.8 – 2.2/s | 18 MP| Calls down falling meteors |
| `wpn_wnd_t4_03` | *Forge-Master Vulcan Crucible Wand*| Magma | 75.0 – 100.0 | 1.7 – 2.0/s | 20 MP| Boss drop: Slag magma wave |

---

## 6. Tier 5: Glacial Cobalt Wands (Levels 41–50)

| ID | Name | Element | Damage Range | Cast Speed | Mana Cost | Special / Implicit |
|---|---|---|---|---|---|---|
| `wpn_wnd_t5_01` | *Glacial Cobalt Frost Wand* | Frost | 75.0 – 98.0 | 3.4 – 3.9/s | 12 MP| Chills targets by $40\%$ |
| `wpn_wnd_t5_02` | *Sub-Zero Blizzard Scepter* | Frost | 95.0 – 125.0 | 1.9 – 2.3/s | 22 MP| Creates freezing hail storm |
| `wpn_wnd_t5_03` | *Absolute Zero Cryo-Scepter*| Frost | 110.0 – 145.0| 1.8 – 2.1/s | 25 MP| Boss drop: Freezes in 4-tile cone |

---

## 7. Tier 6: Dimensional Void Wands (Levels 51–58)

| ID | Name | Element | Damage Range | Cast Speed | Mana Cost | Special / Implicit |
|---|---|---|---|---|---|---|
| `wpn_wnd_t6_01` | *Phase-Shifted Void Wand* | Void | 105.0 – 140.0| 3.6 – 4.2/s | 14 MP| Bolts phase through terrain |
| `wpn_wnd_t6_02` | *Singularity Rift Scepter* | Void | 135.0 – 180.0| 1.8 – 2.2/s | 28 MP| Pulls enemies into vortex |
| `wpn_wnd_t6_03` | *Dimensional Assembler's Focus*| Spatial | 150.0 – 200.0| 2.0 – 2.5/s | 25 MP| Boss drop: Teleports on crit |

---

## 8. Tier 7: Archon Hard-Light Scepters (Levels 59–60)

| ID | Name | Element | Damage Range | Cast Speed | Mana Cost | Special / Implicit |
|---|---|---|---|---|---|---|
| `wpn_wnd_t7_01` | *Hard-Light Solar Wand* | Holy | 140.0 – 185.0| 3.8 – 4.5/s | 15 MP| Blinds targets, $+50\%$ vs Undead |
| `wpn_wnd_t7_02` | *Judgment Grand Scepter* | Holy | 180.0 – 240.0| 1.8 – 2.2/s | 32 MP| Vertical dawn pillar beam |
| `wpn_wnd_t7_03` | *Archon Prime's Seraph Wand*| Holy/Laser| 210.0 – 280.0| 2.2 – 2.7/s | 30 MP| Boss drop: Orbiting laser funnels |

---

## 9. Tier 8 & Prismatic: Precursor & Rift God Wands (Endgame 60+)

| ID | Name | Element | Damage Range | Cast Speed | Mana Cost | Special / Implicit |
|---|---|---|---|---|---|---|
| `wpn_wnd_t8_01` | *The Architect's Neural Scepter*| Spatial | 280.0 – 380.0| 2.5 – 3.2/s | 20 MP| Bolts detonate in reality tears |
| `wpn_wnd_t8_02` | *God-Slayer Prismatic Wand* | All | 320.0 – 440.0| 4.0 – 4.8/s | 18 MP| 5 Affixes + casts all 4 elements |
| `wpn_wnd_t8_03` | *Infinity Chrono-Scepter* | Time | 250.0 – 340.0| 3.0 – 3.8/s | 15 MP| Stops target time for 1.5s on crit |
