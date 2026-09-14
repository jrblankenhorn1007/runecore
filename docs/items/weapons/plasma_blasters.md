# Energy & Plasma Firearms Catalog

This document specifies the individual base stat roll ranges, energy consumption rates, projectile speeds, splash radii, and heat accumulation limits for high-tech energy and plasma firearms across all 8 progression tiers in Untitled RPG (~140 weapon definitions).

---

## 1. Mechanics & Stat Rolling Parameters
- **Primary Scaling Attribute**: Cyber-Affinity (CYB) ($+1.5\%$ per point) and Intelligence (INT) ($+1.0\%$ per point).
- **Power Resource System**: Energy weapons do not consume physical ballistic ammunition; they draw **Power Units** directly from the player's installed Heart / Core augmentation.
- **Weapon Sub-Types**:
  - *Plasma Pulse Blasters*: Rapid glowing plasma spheres (3.0 to 5.0 shots/s), moderate velocity, melts physical armor.
  - *Plasma Scatter-Guns*: Conical spreads of superheated plasma projectiles, devastating at close range.
  - *Continuous Beam Cutters*: Emits sustained surgical energy beams that tick damage 10 times per second.
  - *Gauss Railguns*: High single-shot piercing slugs accelerated by electromagnetic rails.

---

## 2. Tier 1: Makeshift Battery Blasters (Levels 1–10)

| ID | Name | Sub-Type | Damage Range | Fire Rate | Power Cost | Special / Implicit |
|---|---|---|---|---|---|---|
| `wpn_plz_t1_01` | *Scrap Spark Blaster* | Pulse Blaster | 15.0 – 20.0 | 2.5 – 3.0/s | 2 Power/shot | Ignores 10% physical armor |
| `wpn_plz_t1_02` | *Overheated Battery Pistol*| Pulse Blaster | 18.0 – 24.0 | 1.8 – 2.2/s | 3 Power/shot | High heat buildup |
| `wpn_plz_t1_03` | *Makeshift Beam Pointer* | Laser Beam | 40.0 – 55.0/s | Continuous | 4 Power/sec | Continuous low-power beam |
| `wpn_plz_t1_04` | *Goliath Excavator Welder* | Pulse Blaster | 22.0 – 30.0 | 2.0 – 2.4/s | 3 Power/shot | Boss drop: Melts terrain blocks |

---

## 3. Tier 2: Refined Plasma Carbines (Levels 11–20)

| ID | Name | Sub-Type | Damage Range | Fire Rate | Power Cost | Special / Implicit |
|---|---|---|---|---|---|---|
| `wpn_plz_t2_01` | *Refined Plasma Pistol* | Pulse Blaster | 28.0 – 36.0 | 3.0 – 3.5/s | 3 Power/shot | Armor pierce 25% |
| `wpn_plz_t2_02` | *Bio-Plasma Dart Gun* | Pulse Blaster | 24.0 – 32.0 | 3.5 – 4.0/s | 3 Power/shot | Plasma burns with toxin |
| `wpn_plz_t2_03` | *Continuous Surgical Cutter*| Laser Beam | 75.0 – 95.0/s | Continuous | 5 Power/sec | High single-target focus |
| `wpn_plz_t2_04` | *Mother Chimera Acid Plasma*| Scatter-Gun | 6x 10.0 – 14.0| 1.5 – 1.8/s | 6 Power/shot | Boss drop: Acid plasma splash |

---

## 4. Tier 3: Industrial Arc & Plasma Blasters (Levels 21–30)

| ID | Name | Sub-Type | Damage Range | Fire Rate | Power Cost | Special / Implicit |
|---|---|---|---|---|---|---|
| `wpn_plz_t3_01` | *Industrial Pulse Rifle* | Pulse Blaster | 40.0 – 52.0 | 4.0 – 4.6/s | 4 Power/shot | Pierces 1 target |
| `wpn_plz_t3_02` | *Tesla Arc Cannon* | Arc Discharger | 48.0 – 62.0 | 1.8 – 2.2/s | 8 Power/shot | Chains to 4 targets |
| `wpn_plz_t3_03` | *Heavy Industrial Railgun*| Railgun | 120.0 – 160.0| 0.8 – 1.0/s | 18 Power/shot| Penetrates 3 enemies |
| `wpn_plz_t3_04` | *Hydro-Turbine Arc Projector*| Arc Discharger| 55.0 – 72.0 | 2.0 – 2.4/s | 10 Power/shot| Boss drop: Conducts in water |

---

## 5. Tier 4: Volcanic Plasma & Thermal Blasters (Levels 31–40)

| ID | Name | Sub-Type | Damage Range | Fire Rate | Power Cost | Special / Implicit |
|---|---|---|---|---|---|---|
| `wpn_plz_t4_01` | *Titanium Plasma Blaster*| Pulse Blaster | 58.0 – 75.0 | 4.2 – 4.8/s | 4 Power/shot | Heat dissipation $+40\%$ |
| `wpn_plz_t4_02` | *Thermal Plasma Lance* | Laser Beam | 130.0 – 170.0/s| Continuous | 7 Power/sec | Melts armor completely |
| `wpn_plz_t4_03` | *Magma Scatter-Blaster* | Scatter-Gun | 8x 16.0 – 22.0| 1.8 – 2.2/s | 8 Power/shot | Leaves magma puddles |
| `wpn_plz_t4_04` | *Forge-Master Vulcan Plasma Mortar*| Plasma Cannon| 140.0 – 185.0| 0.9 – 1.1/s | 20 Power/shot| Boss drop: Massive AoE blast |

---

## 6. Tier 5: Cryo-Plasma & Frozen Beams (Levels 41–50)

| ID | Name | Sub-Type | Damage Range | Fire Rate | Power Cost | Special / Implicit |
|---|---|---|---|---|---|---|
| `wpn_plz_t5_01` | *Glacial Cobalt Blaster* | Pulse Blaster | 78.0 – 102.0 | 3.8 – 4.4/s | 5 Power/shot | Chills targets by $40\%$ |
| `wpn_plz_t5_02` | *Liquid Nitrogen Freeze Beam*| Laser Beam | 180.0 – 240.0/s| Continuous | 8 Power/sec | Freezes target after 1.5s |
| `wpn_plz_t5_03` | *Absolute Zero Cryo-Railgun*| Railgun | 230.0 – 305.0| 0.7 – 0.9/s | 25 Power/shot| Boss drop: Freezes in a line |

---

## 7. Tier 6: Dimensional Void Blasters (Levels 51–58)

| ID | Name | Sub-Type | Damage Range | Fire Rate | Power Cost | Special / Implicit |
|---|---|---|---|---|---|---|
| `wpn_plz_t6_01` | *Singularity Pulse Cannon* | Pulse Blaster | 110.0 – 145.0| 3.2 – 3.8/s | 8 Power/shot | Micro-black hole on hit |
| `wpn_plz_t6_02` | *Phase-Shifted Void Railgun*| Railgun | 320.0 – 420.0| 0.6 – 0.8/s | 30 Power/shot| Ignores all obstacles & walls |
| `wpn_plz_t6_03` | *Dimensional Assembler's Beam*| Laser Beam | 260.0 – 350.0/s| Continuous | 12 Power/sec| Boss drop: Spatial distortion |

---

## 8. Tier 7: Archon Hard-Light Blasters (Levels 59–60)

| ID | Name | Sub-Type | Damage Range | Fire Rate | Power Cost | Special / Implicit |
|---|---|---|---|---|---|---|
| `wpn_plz_t7_01` | *Hard-Light Solar Blaster* | Pulse Blaster | 145.0 – 190.0| 4.5 – 5.2/s | 6 Power/shot | Blinds target, $+50\%$ vs Undead |
| `wpn_plz_t7_02` | *Archon Grand Rail-Cannon* | Railgun | 450.0 – 600.0| 0.5 – 0.7/s | 35 Power/shot| Pierces entire map |
| `wpn_plz_t7_03` | *Archon Prime's Seraph Beam*| Laser Beam | 350.0 – 480.0/s| Continuous | 14 Power/sec| Boss drop: Triple laser funnels |

---

## 9. Tier 8 & Prismatic: Precursor & Rift God Blasters (Endgame 60+)

| ID | Name | Sub-Type | Damage Range | Fire Rate | Power Cost | Special / Implicit |
|---|---|---|---|---|---|---|
| `wpn_plz_t8_01` | *The Architect's Core Annihilator*| Heavy Beam | 600.0 – 850.0/s| Continuous | 15 Power/sec| Reality disintegrator beam |
| `wpn_plz_t8_02` | *God-Slayer Prismatic Railgun*| Railgun | 800.0 – 1100.0| 0.6 – 0.8/s | 40 Power/shot| 5 Affixes + instant vaporization |
| `wpn_plz_t8_03` | *Infinity Singularity Blaster*| Pulse Blaster | 250.0 – 340.0| 5.0 – 6.0/s | 5 Power/shot | Bottomless power on crit kill |
