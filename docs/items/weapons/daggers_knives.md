# Daggers, Combat Knives & Concealed Blades Catalog

This document specifies the individual base stat roll ranges, critical multipliers, attack speeds, stealth bonuses, and implicit perks for fast, short-reach piercing and slashing blades across all 8 progression tiers in Untitled RPG (~150 weapon definitions).

---

## 1. Mechanics & Stat Rolling Parameters
- **Primary Scaling Attribute**: Dexterity (DEX) ($+1.8\%$ per point). Also scales with Intelligence (INT) for surgical/nano daggers.
- **Weapon Characteristics**:
  - *Ultra-Fast Attack Speed*: 3.2 to 4.5 attacks/second.
  - *Short Reach*: 1.2 to 1.6 tiles.
  - *High Critical Baseline*: $15\%$ to $35\%$ innate critical chance.
  - *Sneak / Ambush Perks*: Attacks striking enemies from stealth or from behind deal $+100\%$ to $+250\%$ bonus ambush damage.
  - *Poison & Rend Synergies*: Many daggers possess innate stacking poison or armor-shredding rend.

---

## 2. Tier 1: Scrap & Makeshift Daggers (Levels 1–10)

| ID | Name | Sub-Type | Damage Range | Speed Range | Crit Range | Reach | Special / Implicit |
|---|---|---|---|---|---|---|---|
| `wpn_dag_t1_01` | *Rusty Shiv* | Shiv | 6.0 – 9.0 | 3.2 – 3.5/s | 0.12 – 0.16 | 1.2 | Fast recovery |
| `wpn_dag_t1_02` | *Sharpened Glass Shard* | Shiv | 8.0 – 12.0 | 3.5 – 3.8/s | 0.15 – 0.20 | 1.2 | Low durability (40) |
| `wpn_dag_t1_03` | *Scrap Iron Hunting Knife*| Combat Knife | 7.0 – 10.0 | 3.0 – 3.3/s | 0.10 – 0.14 | 1.4 | Animal skinning $+25\%$ |
| `wpn_dag_t1_04` | *Bandit's Jagged Dirk* | Dirk | 8.0 – 11.0 | 3.1 – 3.4/s | 0.14 – 0.18 | 1.4 | $+10\%$ Bleed chance |
| `wpn_dag_t1_05` | *Carved Animal Bone Shank*| Shank | 6.5 – 9.5 | 3.4 – 3.7/s | 0.12 – 0.16 | 1.3 | 0 Metal weight |
| `wpn_dag_t1_06` | *Rusted Scalpel* | Scalpel | 5.5 – 8.0 | 3.8 – 4.2/s | 0.18 – 0.24 | 1.2 | Precision weakpoint $+20\%$ |
| `wpn_dag_t1_07` | *Scrap Parrying Dagger* | Main-Gauche | 7.0 – 9.5 | 2.8 – 3.1/s | 0.08 – 0.12 | 1.5 | Offhand parry window $+0.1s$ |
| `wpn_dag_t1_08` | *Goliath Excavator Rivet Knife*| Dirk | 10.0 – 14.0 | 2.8 – 3.2/s | 0.10 – 0.15 | 1.4 | Boss drop: Superheated point |

---

## 3. Tier 2: Refined Iron & Bio-Cultured Daggers (Levels 11–20)

| ID | Name | Sub-Type | Damage Range | Speed Range | Crit Range | Reach | Special / Implicit |
|---|---|---|---|---|---|---|---|
| `wpn_dag_t2_01` | *Refined Iron Stiletto* | Stiletto | 12.0 – 16.0 | 3.4 – 3.7/s | 0.18 – 0.24 | 1.4 | Punctures 10 Armor |
| `wpn_dag_t2_02` | *Bio-Lab Surgical Scalpel*| Scalpel | 10.0 – 14.0 | 4.0 – 4.4/s | 0.22 – 0.28 | 1.3 | $+30\%$ Crit Multiplier |
| `wpn_dag_t2_03` | *Mantis Claw Dagger* | Claw | 13.0 – 17.0 | 3.6 – 3.9/s | 0.16 – 0.22 | 1.4 | Stacks Deep Wound |
| `wpn_dag_t2_04` | *Venom-Coated Dirk* | Dirk | 11.0 – 15.0 | 3.2 – 3.5/s | 0.15 – 0.20 | 1.4 | Applies Neurotoxin |
| `wpn_dag_t2_05` | *Mother Chimera Tooth Dagger*| Dirk | 15.0 – 20.0 | 3.5 – 3.8/s | 0.20 – 0.26 | 1.5 | Boss drop: Acid bleed |

---

## 4. Tier 3: Industrial Steel & Combat Trench Knives (Levels 21–30)

| ID | Name | Sub-Type | Damage Range | Speed Range | Crit Range | Reach | Special / Implicit |
|---|---|---|---|---|---|---|---|
| `wpn_dag_t3_01` | *High-Tensile Trench Knife*| Combat Knife | 18.0 – 24.0 | 3.5 – 3.8/s | 0.16 – 0.22 | 1.5 | Knuckle duster impact |
| `wpn_dag_t3_02` | *High-Frequency Vibro-Blade*| Vibro-Dagger| 16.0 – 22.0 | 4.2 – 4.6/s | 0.24 – 0.32 | 1.4 | Vibrating edge ignores 20% armor |
| `wpn_dag_t3_03` | *Infiltrator Carbon Dirk* | Dirk | 19.0 – 25.0 | 3.6 – 4.0/s | 0.22 – 0.28 | 1.4 | Stealth backstab $+150\%$ |
| `wpn_dag_t3_04` | *Hydro-Turbine Fin Stiletto*| Stiletto | 17.0 – 23.0 | 3.8 – 4.2/s | 0.18 – 0.24 | 1.5 | Boss drop: Underwater speed $+30\%$ |

---

## 5. Tier 4: Volcanic Slag & Titanium Daggers (Levels 31–40)

| ID | Name | Sub-Type | Damage Range | Speed Range | Crit Range | Reach | Special / Implicit |
|---|---|---|---|---|---|---|---|
| `wpn_dag_t4_01` | *Titanium Razor Dagger* | Dagger | 25.0 – 33.0 | 3.8 – 4.2/s | 0.22 – 0.28 | 1.5 | Zero weight penalty |
| `wpn_dag_t4_02` | *Volcanic Obsidian Shard* | Shiv | 28.0 – 37.0 | 3.5 – 3.9/s | 0.25 – 0.32 | 1.4 | Ignites target for 5s |
| `wpn_dag_t4_03` | *Thermite Needle Blade* | Scalpel | 24.0 – 32.0 | 4.4 – 4.8/s | 0.28 – 0.35 | 1.3 | Melts physical armor on hit |
| `wpn_dag_t4_04` | *Forge-Master Vulcan Spike* | Dirk | 30.0 – 40.0 | 3.4 – 3.7/s | 0.20 – 0.26 | 1.5 | Boss drop: Explodes on kill |

---

## 6. Tier 5: Glacial Cobalt & Cryo Daggers (Levels 41–50)

| ID | Name | Sub-Type | Damage Range | Speed Range | Crit Range | Reach | Special / Implicit |
|---|---|---|---|---|---|---|---|
| `wpn_dag_t5_01` | *Glacial Cobalt Icicle* | Stiletto | 34.0 – 45.0 | 3.7 – 4.1/s | 0.24 – 0.30 | 1.5 | Chills targets by $40\%$ |
| `wpn_dag_t5_02` | *Sub-Zero Cryo-Scalpel* | Scalpel | 30.0 – 40.0 | 4.5 – 5.0/s | 0.30 – 0.38 | 1.3 | Freezes on 4th consecutive hit |
| `wpn_dag_t5_03` | *Absolute Zero Frost Dirk*| Dirk | 36.0 – 48.0 | 3.6 – 4.0/s | 0.26 – 0.34 | 1.5 | Boss drop: Shatter bonus $+60\%$ |

---

## 7. Tier 6: Dimensional Void Daggers (Levels 51–58)

| ID | Name | Sub-Type | Damage Range | Speed Range | Crit Range | Reach | Special / Implicit |
|---|---|---|---|---|---|---|---|
| `wpn_dag_t6_01` | *Phase-Shifted Void Dagger*| Dagger | 45.0 – 58.0 | 4.0 – 4.5/s | 0.28 – 0.36 | 1.5 | Strikes ignore physical shields |
| `wpn_dag_t6_02` | *Singularity Rift Blade* | Dirk | 48.0 – 64.0 | 3.8 – 4.2/s | 0.32 – 0.40 | 1.5 | Pulls enemy towards blade |
| `wpn_dag_t6_03` | *Dimensional Assembler's Scalpel*| Scalpel | 42.0 – 56.0 | 4.8 – 5.4/s | 0.35 – 0.45 | 1.4 | Boss drop: Teleport behind target |

---

## 8. Tier 7: Archon Hard-Light Daggers (Levels 59–60)

| ID | Name | Sub-Type | Damage Range | Speed Range | Crit Range | Reach | Special / Implicit |
|---|---|---|---|---|---|---|---|
| `wpn_dag_t7_01` | *Hard-Light Solar Dirk* | Dagger | 56.0 – 72.0 | 4.2 – 4.7/s | 0.30 – 0.38 | 1.5 | Blinds target, $+50\%$ vs Undead |
| `wpn_dag_t7_02` | *Monomolecular Light-Fang* | Scalpel | 52.0 – 68.0 | 5.0 – 5.6/s | 0.38 – 0.48 | 1.4 | 100% Armor pierce |
| `wpn_dag_t7_03` | *Archon Prime's Seraph Talon*| Dirk | 62.0 – 80.0 | 4.0 – 4.5/s | 0.35 – 0.45 | 1.6 | Boss drop: Flying photon blades |

---

## 9. Tier 8 & Prismatic: Precursor & Rift God Daggers (Endgame 60+)

| ID | Name | Sub-Type | Damage Range | Speed Range | Crit Range | Reach | Special / Implicit |
|---|---|---|---|---|---|---|---|
| `wpn_dag_t8_01` | *The Architect's Micro-Blade*| Dagger | 90.0 – 125.0 | 4.5 – 5.2/s | 0.35 – 0.45 | 1.6 | Stealth ambush deals $500\%$ dmg |
| `wpn_dag_t8_02` | *God-Slayer Prismatic Stiletto*| Stiletto | 100.0 – 140.0| 4.4 – 5.0/s | 0.40 – 0.52 | 1.6 | 5 Affixes + instant kill below 10% |
| `wpn_dag_t8_03` | *Infinite Chrono-Dagger* | Scalpel | 85.0 – 115.0 | 5.5 – 6.5/s | 0.45 – 0.60 | 1.5 | Attacks stop enemy time for 0.5s |
