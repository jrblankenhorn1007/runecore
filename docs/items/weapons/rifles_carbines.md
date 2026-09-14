# Rifles, Carbines & Submachine Guns Catalog

This document specifies the individual base stat roll ranges, fire rates, magazine sizes, effective ranges, and recoil profiles for automatic and burst rifles across all 8 progression tiers in Untitled RPG (~160 weapon definitions).

---

## 1. Mechanics & Stat Rolling Parameters
- **Primary Scaling Attribute**: Dexterity (DEX) ($+1.5\%$ per point). Also scales with Strength (STR) for heavy battle rifles.
- **Ammunition**: Consumes Light Ballistic Rounds (Carbines, SMGs) or Heavy Rifle Rounds (Assault Rifles, Battle Rifles).
- **Weapon Sub-Types**:
  - *Tactical Submachine Guns (SMGs)*: Extreme fire rate (9.0 to 14.0 rounds/s), 25 to 40-round magazines, devastating at close-to-mid range.
  - *Semi-Automatic Carbines*: Precision semi-auto fire (3.5 to 5.0 rounds/s), high weakpoint multiplier, low recoil.
  - *Fully-Automatic Assault Rifles*: Balanced fire rate (6.5 to 9.0 rounds/s), 30-round magazine, consistent mid-to-long range DPS.
  - *Heavy Battle Rifles*: High single-shot damage, heavy recoil, 20-round magazine, penetrates 1 enemy target.

---

## 2. Tier 1: Scrap & Makeshift Rifles (Levels 1–10)

| ID | Name | Sub-Type | Damage Range | Fire Rate | Mag | Reload | Special / Implicit |
|---|---|---|---|---|---|---|---|
| `wpn_rif_t1_01` | *Scavenger's Scrap Carbine*| Carbine | 14.0 – 19.0 | 3.5 – 4.0/s | 10 | 1.8s | Semi-auto, low recoil |
| `wpn_rif_t1_02` | *Pipe-Welded SMG* | SMG | 8.0 – 11.0 | 9.0 – 11.0/s| 20 | 1.9s | High horizontal spread |
| `wpn_rif_t1_03` | *Rusted Lever-Action Rifle*| Carbine | 22.0 – 30.0 | 1.8 – 2.2/s | 8 | 0.4s/rd| Long-range iron sights |
| `wpn_rif_t1_04` | *Makeshift Assault Rifle* | Assault Rifle| 11.0 – 15.0 | 6.5 – 7.5/s | 25 | 2.1s | Moderate barrel climb |
| `wpn_rif_t1_05` | *Goliath Scrap Autocannon* | Battle Rifle | 24.0 – 32.0 | 2.2 – 2.6/s | 12 | 2.4s | Boss drop: Knocks enemies back |

---

## 3. Tier 2: Refined Iron Combat Rifles (Levels 11–20)

| ID | Name | Sub-Type | Damage Range | Fire Rate | Mag | Reload | Special / Implicit |
|---|---|---|---|---|---|---|---|
| `wpn_rif_t2_01` | *Refined Combat Carbine* | Carbine | 22.0 – 29.0 | 4.0 – 4.5/s | 15 | 1.5s | $+15\%$ Weakpoint Crit |
| `wpn_rif_t2_02` | *Enforcer Tactical SMG* | SMG | 13.0 – 17.0 | 10.0 – 12.0/s| 30 | 1.4s | Recoil dampening |
| `wpn_rif_t2_03` | *Bio-Lab Needle Carbine* | Carbine | 18.0 – 24.0 | 4.5 – 5.0/s | 20 | 1.3s | Inflicts Neurotoxin |
| `wpn_rif_t2_04` | *Heavy Iron Battle Rifle* | Battle Rifle | 32.0 – 42.0 | 3.0 – 3.5/s | 16 | 2.0s | Pierces 1 target |
| `wpn_rif_t2_05` | *Mother Chimera Quill Sprayer*| SMG | 15.0 – 20.0 | 11.0 – 13.0/s| 25 | 1.6s | Boss drop: Splinter quills |

---

## 4. Tier 3: Industrial Steel Rifles (Levels 21–30)

| ID | Name | Sub-Type | Damage Range | Fire Rate | Mag | Reload | Special / Implicit |
|---|---|---|---|---|---|---|---|
| `wpn_rif_t3_01` | *Steel Tactical Assault Rifle*| Assault Rifle| 26.0 – 34.0 | 7.5 – 8.5/s | 30 | 1.8s | Holo-sight built-in |
| `wpn_rif_t3_02` | *Steam-Piston Heavy Carbine*| Carbine | 38.0 – 50.0 | 3.8 – 4.3/s | 18 | 1.6s | Steam blast on empty reload |
| `wpn_rif_t3_03` | *Foundry Micro-SMG* | SMG | 18.0 – 24.0 | 12.0 – 14.0/s| 35 | 1.2s | Akimbo-capable |
| `wpn_rif_t3_04` | *Hydro-Turbine Torpedo Carbine*| Carbine | 40.0 – 52.0 | 3.2 – 3.7/s | 15 | 1.8s | Boss drop: Fires in water |

---

## 5. Tier 4: Volcanic Slag & Titanium Rifles (Levels 31–40)

| ID | Name | Sub-Type | Damage Range | Fire Rate | Mag | Reload | Special / Implicit |
|---|---|---|---|---|---|---|---|
| `wpn_rif_t4_01` | *Titanium Tactical Carbine* | Carbine | 44.0 – 58.0 | 4.5 – 5.2/s | 24 | 1.2s | Laser sight, zero sway |
| `wpn_rif_t4_02` | *Volcanic Ash Assault Rifle* | Assault Rifle| 36.0 – 48.0 | 8.0 – 9.0/s | 30 | 1.7s | 50% Fire dmg, ignites |
| `wpn_rif_t4_03` | *Thermite Spool SMG* | SMG | 25.0 – 34.0 | 13.0 – 15.0/s| 40 | 1.3s | Shreds physical armor |
| `wpn_rif_t4_04` | *Forge-Master Vulcan Autocannon*| Battle Rifle| 55.0 – 72.0 | 3.5 – 4.0/s | 20 | 2.2s | Boss drop: Explosive slugs |

---

## 6. Tier 5: Glacial Cobalt Rifles (Levels 41–50)

| ID | Name | Sub-Type | Damage Range | Fire Rate | Mag | Reload | Special / Implicit |
|---|---|---|---|---|---|---|---|
| `wpn_rif_t5_01` | *Glacial Cobalt Assault Rifle*| Assault Rifle| 52.0 – 68.0 | 7.8 – 8.8/s | 30 | 1.6s | Chills targets by $35\%$ |
| `wpn_rif_t5_02` | *Sub-Zero Frost SMG* | SMG | 35.0 – 46.0 | 13.0 – 15.5/s| 45 | 1.2s | Freezes on 8 hits |
| `wpn_rif_t5_03` | *Absolute Zero Storm Rifle* | Battle Rifle | 75.0 – 98.0 | 3.2 – 3.8/s | 20 | 1.9s | Boss drop: Creates ice trail |

---

## 7. Tier 6: Dimensional Void Rifles (Levels 51–58)

| ID | Name | Sub-Type | Damage Range | Fire Rate | Mag | Reload | Special / Implicit |
|---|---|---|---|---|---|---|---|
| `wpn_rif_t6_01` | *Phase-Shifted Void Carbine* | Carbine | 75.0 – 98.0 | 4.8 – 5.5/s | 25 | 1.3s | Bullets pierce walls |
| `wpn_rif_t6_02` | *Singularity Spool SMG* | SMG | 50.0 – 66.0 | 14.0 – 16.5/s| 50 | 1.1s | Graviton vortex on mag dump |
| `wpn_rif_t6_03` | *Dimensional Assembler's Rifle*| Assault Rifle| 70.0 – 92.0 | 8.5 – 9.5/s | 35 | 1.5s | Boss drop: Reality tears |

---

## 8. Tier 7: Archon Hard-Light Rifles (Levels 59–60)

| ID | Name | Sub-Type | Damage Range | Fire Rate | Mag | Reload | Special / Implicit |
|---|---|---|---|---|---|---|---|
| `wpn_rif_t7_01` | *Hard-Light Solar Carbine* | Carbine | 95.0 – 125.0 | 5.0 – 5.8/s | 28 | 1.2s | Blinds target, $+50\%$ vs Undead |
| `wpn_rif_t7_02` | *Photon-Burst Assault Rifle* | Assault Rifle| 85.0 – 112.0 | 8.5 – 9.8/s | 35 | 1.4s | Lasers reflect off walls |
| `wpn_rif_t7_03` | *Archon Prime's Seraph Rifle* | Battle Rifle | 120.0 – 160.0| 3.8 – 4.5/s | 24 | 1.7s | Boss drop: Light pillar on crit |

---

## 9. Tier 8 & Prismatic: Precursor & Rift God Rifles (Endgame 60+)

| ID | Name | Sub-Type | Damage Range | Fire Rate | Mag | Reload | Special / Implicit |
|---|---|---|---|---|---|---|---|
| `wpn_rif_t8_01` | *The Architect's Singularity Carbine*| Carbine| 160.0 – 215.0| 5.5 – 6.5/s | 30 | 1.0s | Instant kill non-boss on crit |
| `wpn_rif_t8_02` | *God-Slayer Prismatic SMG* | SMG | 95.0 – 135.0 | 16.0 – 20.0/s| 60 | 0.9s | 5 Affixes + lightning storms |
| `wpn_rif_t8_03` | *Infinity Vector Battle Rifle* | Battle Rifle | 210.0 – 285.0| 4.0 – 4.8/s | 25 | 1.4s | Penetrates all targets on screen |
