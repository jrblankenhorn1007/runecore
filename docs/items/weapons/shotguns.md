# Shotguns & Scatterguns Catalog

This document specifies the individual base stat roll ranges, pellet counts, spreads, knockback forces, and reload behaviors for shotguns and scatterguns across all 8 progression tiers in Untitled RPG (~130 weapon definitions).

---

## 1. Mechanics & Stat Rolling Parameters
- **Primary Scaling Attribute**: Strength (STR) ($+1.0\%$ per point) and Dexterity (DEX) ($+0.8\%$ per point).
- **Ammunition**: Consumes 12-Gauge Shotgun Shells or specialized incendiary/slug shells.
- **Weapon Sub-Types**:
  - *Pump-Action Trench Shotguns*: 8 to 10 pellets, heavy stagger and knockback, reload shell-by-shell.
  - *Double-Barrel Break-Actions*: 2-round capacity, extreme burst damage, rapid 2-shot discharge, wide spread.
  - *Semi-Automatic Combat Shotguns*: 6 to 12-round box magazines, fast fire rate (2.0 to 3.0/s), moderate recoil.
  - *Automatic Rotary Shotguns*: 20-round drums, devastating sustained room-clearing fire.

---

## 2. Tier 1: Scrap & Makeshift Shotguns (Levels 1–10)

| ID | Name | Pellets | Damage / Pellet | Fire Rate | Mag | Reload | Special / Implicit |
|---|---|---|---|---|---|---|---|
| `wpn_shg_t1_01` | *Scavenger's Pipe Shotgun*| 6 | 5.0 – 7.0 | 0.8 – 1.0/s | 1 | 1.8s | Break-action single shot |
| `wpn_shg_t1_02` | *Sawed-Off Double-Barrel* | 8 | 6.0 – 8.0 | 2.5 – 3.0/s | 2 | 2.0s | $+40\%$ Spread, massive point-blank |
| `wpn_shg_t1_03` | *Rusted Pump Trenchgun* | 8 | 5.5 – 7.5 | 1.0 – 1.2/s | 4 | 0.5s/sh | Slam-fire: hold to pump |
| `wpn_shg_t1_04` | *Lead-Bettie Scattergun* | 10 | 4.0 – 6.0 | 0.9 – 1.1/s | 3 | 0.6s/sh | High knockback (5 tiles) |
| `wpn_shg_t1_05` | *Goliath Excavator Rivetgun*| 8 | 7.0 – 9.0 | 1.1 – 1.3/s | 5 | 2.2s | Boss drop: Superheated rivets |

---

## 3. Tier 2: Refined Iron Combat Shotguns (Levels 11–20)

| ID | Name | Pellets | Damage / Pellet | Fire Rate | Mag | Reload | Special / Implicit |
|---|---|---|---|---|---|---|---|
| `wpn_shg_t2_01` | *Machined Police Trenchgun*| 8 | 8.0 – 11.0 | 1.2 – 1.4/s | 6 | 0.4s/sh | Tight choke: -25% spread |
| `wpn_shg_t2_02` | *Double-Barreled Elephant Gun*| 10 | 10.0 – 14.0 | 2.8 – 3.2/s | 2 | 1.8s | Staggers boss monsters |
| `wpn_shg_t2_03` | *Bio-Lab Spore Sweeper* | 8 | 8.5 – 11.5 | 1.5 – 1.8/s | 5 | 2.0s | Pellets inflict Toxin |
| `wpn_shg_t2_04` | *Semi-Auto Riot Shotgun* | 8 | 7.5 – 10.0 | 2.2 – 2.6/s | 8 | 2.4s | Box mag reload |
| `wpn_shg_t2_05` | *Mother Chimera Quill Scatterer*| 12 | 7.0 – 9.5 | 1.3 – 1.6/s | 6 | 2.1s | Boss drop: Homing quills |

---

## 4. Tier 3: Industrial Steel & Steam Shotguns (Levels 21–30)

| ID | Name | Pellets | Damage / Pellet | Fire Rate | Mag | Reload | Special / Implicit |
|---|---|---|---|---|---|---|---|
| `wpn_shg_t3_01` | *Steam-Piston Heavy Shotgun*| 8 | 12.0 – 16.0 | 1.3 – 1.5/s | 6 | 0.4s/sh | Steam blast cone behind target |
| `wpn_shg_t3_02` | *Enforcer Tactical Mag-12* | 8 | 13.0 – 17.0 | 2.0 – 2.4/s | 10 | 2.2s | Armor pierce 15% |
| `wpn_shg_t3_03` | *High-Pressure Water Cannon*| 10 | 11.0 – 15.0 | 1.0 – 1.3/s | 4 | 1.9s | Boss drop: Drenches & conducts shock |

---

## 5. Tier 4: Volcanic Slag Shotguns (Levels 31–40)

| ID | Name | Pellets | Damage / Pellet | Fire Rate | Mag | Reload | Special / Implicit |
|---|---|---|---|---|---|---|---|
| `wpn_shg_t4_01` | *Molten Slag Dragon-Breath*| 8 | 18.0 – 24.0 | 1.4 – 1.7/s | 6 | 0.4s/sh | 50% Fire dmg, ignites ground |
| `wpn_shg_t4_02` | *Titanium Combat Sweeper* | 8 | 19.0 – 25.0 | 2.2 – 2.7/s | 12 | 2.0s | Recoil reduced by 40% |
| `wpn_shg_t4_03` | *Forge-Master Vulcan Blaster*| 12 | 16.0 – 22.0 | 1.1 – 1.4/s | 8 | 2.4s | Boss drop: Exploding pellets |

---

## 6. Tier 5: Cryo-Alloy Shotguns (Levels 41–50)

| ID | Name | Pellets | Damage / Pellet | Fire Rate | Mag | Reload | Special / Implicit |
|---|---|---|---|---|---|---|---|
| `wpn_shg_t5_01` | *Glacial Cobalt Trenchgun* | 8 | 25.0 – 34.0 | 1.3 – 1.6/s | 7 | 0.4s/sh | Chills targets by 40% |
| `wpn_shg_t5_02` | *Sub-Zero Frost Scatterer* | 10 | 22.0 – 30.0 | 2.0 – 2.5/s | 8 | 2.1s | Freezes on full point-blank hit |
| `wpn_shg_t5_03` | *Absolute Zero Cryo-Flak* | 12 | 24.0 – 32.0 | 1.2 – 1.5/s | 6 | 2.3s | Boss drop: Creates ice wall shields |

---

## 7. Tier 6: Dimensional Void Shotguns (Levels 51–58)

| ID | Name | Pellets | Damage / Pellet | Fire Rate | Mag | Reload | Special / Implicit |
|---|---|---|---|---|---|---|---|
| `wpn_shg_t6_01` | *Singularity Vortex Shotgun*| 8 | 34.0 – 46.0 | 1.4 – 1.8/s | 8 | 2.0s | Pellets pull enemies together |
| `wpn_shg_t6_02` | *Phase-Shifted Scattergun* | 10 | 30.0 – 42.0 | 2.2 – 2.6/s | 10 | 2.1s | Pellets ignore physical shields |
| `wpn_shg_t6_03` | *Dimensional Assembler's Press*| 14 | 28.0 – 38.0 | 1.1 – 1.4/s | 8 | 2.4s | Boss drop: Gravitational crush |

---

## 8. Tier 7: Archon Hard-Light Shotguns (Levels 59–60)

| ID | Name | Pellets | Damage / Pellet | Fire Rate | Mag | Reload | Special / Implicit |
|---|---|---|---|---|---|---|---|
| `wpn_shg_t7_01` | *Hard-Light Judgment Sweeper*| 10 | 42.0 – 56.0 | 1.8 – 2.2/s | 10 | 1.8s | Holy energy pellets, blinds |
| `wpn_shg_t7_02` | *Solar Flare Rotary Auto-Shotgun*| 8 | 38.0 – 50.0 | 3.5 – 4.2/s | 20 | 2.5s | Incinerates unarmored targets |
| `wpn_shg_t7_03` | *Archon Prime's Seraph Scatter*| 12 | 45.0 – 60.0 | 1.5 – 1.9/s | 8 | 2.0s | Boss drop: Laser funnel scatter |

---

## 9. Tier 8 & Prismatic: Precursor & Rift God Shotguns (Endgame 60+)

| ID | Name | Pellets | Damage / Pellet | Fire Rate | Mag | Reload | Special / Implicit |
|---|---|---|---|---|---|---|---|
| `wpn_shg_t8_01` | *The Architect's Core Breacher*| 12 | 70.0 – 95.0 | 2.0 – 2.5/s | 12 | 1.6s | Spatial tear per pellet |
| `wpn_shg_t8_02` | *God-Slayer Prismatic Scattergun*| 14 | 75.0 – 105.0| 2.2 – 2.7/s | 14 | 1.8s | 5 Affixes + screen-wide shock |
| `wpn_shg_t8_03` | *Infinite Apocalyptic Rotary* | 10 | 60.0 – 82.0 | 4.5 – 5.5/s | 30 | 2.2s | Continuous devastating wall of lead |
