# Revolvers, Pistols & Hand Firearms Catalog

This document specifies the individual base stat roll ranges, scaling attributes, magazine capacities, reload speeds, projectile velocities, and implicit perks for ballistic and sidearm hand firearms across all 8 progression tiers in Untitled RPG (~160 weapon definitions).

---

## 1. Mechanics & Stat Rolling Parameters
- **Primary Scaling Attribute**: Dexterity (DEX) ($+1.5\%$ per point). Certain magnum variants also scale with Strength (STR).
- **Ammunition**: Consumes Light Ballistic Rounds or specialized Flak Shells pressed at the Forge.
- **Weapon Sub-Types**:
  - *Six-Shot Revolvers*: High single-target stagger, elevated critical weakpoint multipliers ($2.2\times$ to $2.8\times$), fast recovery.
  - *Automatic Pistols*: High fire rate (3.5 to 5.0/s), 12 to 20-round magazines, fast tactical reloads (0.8s to 1.2s).
  - *Flak Hand-Cannons*: Low fire rate (1.0 to 1.4/s), 3 to 5-round capacity, explosive shell detonations on impact.
  - *Silenced Assassin Pistols*: Inaudible to distant enemies, $+100\%$ sneak attack critical multiplier.

---

## 2. Tier 1: Scrap, Rusted & Makeshift Handguns (Levels 1–10)

| ID | Name | Sub-Type | Damage Range | Fire Rate | Mag | Reload | Special / Implicit |
|---|---|---|---|---|---|---|---|
| `wpn_pst_t1_01` | *Scavenger's Rusty Revolver*| 6-Shot | 18.0 – 24.0 | 2.0 – 2.3/s | 6 | 1.6s | $+10\%$ Weakpoint Crit |
| `wpn_pst_t1_02` | *Zip-Gun Single-Shot* | Pistol | 24.0 – 32.0 | 0.8 – 1.0/s | 1 | 1.8s | High close-range stagger |
| `wpn_pst_t1_03` | *Crude 9mm Autopistol* | Auto-Pistol | 12.0 – 16.0 | 3.5 – 4.0/s | 10 | 1.3s | Moderate spread |
| `wpn_pst_t1_04` | *Lead-Pipe Flak Pistol* | Flak Pistol | 38.0 – 50.0 | 0.9 – 1.1/s | 2 | 2.2s | AoE splash radius 1.5 tiles |
| `wpn_pst_t1_05` | *Notched Iron Peacemaker*| 6-Shot | 20.0 – 26.0 | 1.8 – 2.1/s | 6 | 1.5s | $+15\%$ Stagger duration |
| `wpn_pst_t1_06` | *Makeshift Flare Gun* | Pistol | 15.0 – 20.0 | 1.0 – 1.2/s | 1 | 1.4s | Ignites targets, lights area |
| `wpn_pst_t1_07` | *Scrap Snub-Nose 38* | 6-Shot | 16.0 – 22.0 | 2.4 – 2.7/s | 5 | 1.2s | Quickdraw speed $+30\%$ |
| `wpn_pst_t1_08` | *Rusted Service Pistol* | Auto-Pistol | 13.0 – 17.0 | 3.2 – 3.7/s | 8 | 1.4s | Balanced recoil |
| `wpn_pst_t1_09` | *Double-Barrel Derringer* | Pistol | 22.0 – 30.0 | 2.0 – 2.5/s | 2 | 1.0s | Pocket gun: 0 weight |
| `wpn_pst_t1_10` | *Goliath Scrap Bolter* | 6-Shot | 26.0 – 35.0 | 1.4 – 1.7/s | 6 | 1.8s | Boss drop: Fires hot rivets |

---

## 3. Tier 2: Refined Iron & Machined Handguns (Levels 11–20)

| ID | Name | Sub-Type | Damage Range | Fire Rate | Mag | Reload | Special / Implicit |
|---|---|---|---|---|---|---|---|
| `wpn_pst_t2_01` | *Refined Alloy Revolver*| 6-Shot | 30.0 – 39.0 | 2.2 – 2.5/s | 6 | 1.4s | $+20\%$ Weakpoint Crit |
| `wpn_pst_t2_02` | *Machined Police Special*| Auto-Pistol | 20.0 – 26.0 | 4.0 – 4.5/s | 15 | 1.2s | Low recoil climb |
| `wpn_pst_t2_03` | *Bio-Lab Needle Injector*| Dart Gun | 18.0 – 24.0 | 3.0 – 3.5/s | 8 | 1.1s | Fires neurotoxin needles |
| `wpn_pst_t2_04` | *Trench Hand-Mortar* | Flak Pistol | 55.0 – 72.0 | 1.0 – 1.2/s | 3 | 2.0s | AoE splash radius 2.0 tiles |
| `wpn_pst_t2_05` | *Heavy Iron Hand-Cannon* | 6-Shot | 38.0 – 50.0 | 1.6 – 1.9/s | 5 | 1.6s | Knocks enemies backward |
| `wpn_pst_t2_06` | *Suppressed Infiltrator* | Auto-Pistol | 22.0 – 28.0 | 3.8 – 4.3/s | 12 | 1.0s | Silent: does not break cloak |
| `wpn_pst_t2_07` | *Mother Chimera Venom Gun*| Dart Gun | 26.0 – 35.0 | 2.8 – 3.2/s | 6 | 1.3s | Boss drop: Acid puddles |

---

## 4. Tier 3: Industrial Steel & Steam-Assisted Handguns (Levels 21–30)

| ID | Name | Sub-Type | Damage Range | Fire Rate | Mag | Reload | Special / Implicit |
|---|---|---|---|---|---|---|---|
| `wpn_pst_t3_01` | *High-Pressure Steam Revolver*| 6-Shot | 45.0 – 58.0 | 2.2 – 2.6/s | 6 | 1.3s | Knocks targets airborne |
| `wpn_pst_t3_02` | *Steel Enforcer Magnum* | 6-Shot | 52.0 – 68.0 | 1.7 – 2.0/s | 6 | 1.5s | Armor pierce $20\%$ |
| `wpn_pst_t3_03` | *Rapid Burst Machine Pistol*| Auto-Pistol | 28.0 – 36.0 | 5.5 – 6.5/s | 20 | 1.1s | 3-round burst mode |
| `wpn_pst_t3_04` | *Industrial Shrapnel Pistol*| Flak Pistol | 75.0 – 98.0 | 1.1 – 1.3/s | 4 | 1.9s | Releases 6 bouncing pellets |
| `wpn_pst_t3_05` | *Hydro-Turbine Torpedo Gun*| Pistol | 60.0 – 78.0 | 1.3 – 1.6/s | 4 | 1.7s | Boss drop: Fires underwater |

---

## 5. Tier 4: Volcanic Slag & Titanium Handguns (Levels 31–40)

| ID | Name | Sub-Type | Damage Range | Fire Rate | Mag | Reload | Special / Implicit |
|---|---|---|---|---|---|---|---|
| `wpn_pst_t4_01` | *Titanium Tactical Sidearm*| Auto-Pistol | 42.0 – 55.0 | 4.2 – 4.8/s | 18 | 1.0s | Laser sight built-in |
| `wpn_pst_t4_02` | *Volcanic Flare Magnum* | 6-Shot | 72.0 – 94.0 | 1.8 – 2.1/s | 6 | 1.4s | 50% Fire dmg, ignites foes |
| `wpn_pst_t4_03` | *Thermite Shell Flak Pistol*| Flak Pistol | 105.0 – 138.0| 1.0 – 1.2/s | 4 | 1.8s | Leaves burning magma pool |
| `wpn_pst_t4_04` | *Titanium Dual Derringers* | Auto-Pistol | 36.0 – 48.0 | 6.0 – 7.2/s | 24 | 1.2s | Akimbo dual firing |
| `wpn_pst_t4_05` | *Forge-Master Molten Riveter*| 6-Shot | 80.0 – 105.0 | 1.6 – 1.9/s | 6 | 1.5s | Boss drop: Superheated slugs |

---

## 6. Tier 5: Cryo-Alloy Handguns (Levels 41–50)

| ID | Name | Sub-Type | Damage Range | Fire Rate | Mag | Reload | Special / Implicit |
|---|---|---|---|---|---|---|---|
| `wpn_pst_t5_01` | *Glacial Cobalt Revolver* | 6-Shot | 90.0 – 118.0 | 2.0 – 2.4/s | 6 | 1.3s | Chills targets by $35\%$ |
| `wpn_pst_t5_02` | *Sub-Zero Cryo-Pistol* | Auto-Pistol | 58.0 – 76.0 | 4.5 – 5.2/s | 16 | 1.1s | Freezes on 4 consecutive hits |
| `wpn_pst_t5_03` | *Liquid Nitrogen Flak Cannon*| Flak Pistol | 135.0 – 175.0| 1.1 – 1.3/s | 4 | 1.7s | Frost nova blast on impact |
| `wpn_pst_t5_04` | *Absolute Zero Commander's Sidearm*| Auto-Pistol | 70.0 – 92.0 | 4.8 – 5.5/s | 20 | 1.0s | Boss drop: Ricochets off ice |

---

## 7. Tier 6: Dimensional Void Handguns (Levels 51–58)

| ID | Name | Sub-Type | Damage Range | Fire Rate | Mag | Reload | Special / Implicit |
|---|---|---|---|---|---|---|---|
| `wpn_pst_t6_01` | *Phase-Shifted Void Magnum*| 6-Shot | 120.0 – 158.0| 2.1 – 2.5/s | 6 | 1.2s | Bullets phase through thin walls |
| `wpn_pst_t6_02` | *Singularity Flak Pistol* | Flak Pistol | 170.0 – 225.0| 1.0 – 1.2/s | 4 | 1.6s | Micro-black hole pulls enemies |
| `wpn_pst_t6_03` | *Warped Precursor Autopistol*| Auto-Pistol | 82.0 – 108.0 | 5.2 – 6.0/s | 22 | 0.9s | Instant reload on crit kill |
| `wpn_pst_t6_04` | *Dimensional Assembler's Hand-Cannon*| 6-Shot | 145.0 – 190.0| 1.8 – 2.2/s | 6 | 1.4s | Boss drop: Gravity distortion |

---

## 8. Tier 7: Archon Hard-Light Handguns (Levels 59–60)

| ID | Name | Sub-Type | Damage Range | Fire Rate | Mag | Reload | Special / Implicit |
|---|---|---|---|---|---|---|---|
| `wpn_pst_t7_01` | *Hard-Light Judgment Revolver*| 6-Shot | 155.0 – 205.0| 2.2 – 2.6/s | 6 | 1.1s | Blinds target, $+50\%$ vs Undead |
| `wpn_pst_t7_02` | *Photon-Burst Machine Pistol*| Auto-Pistol | 105.0 – 138.0| 6.0 – 7.0/s | 25 | 0.9s | Fires hard-light lasers |
| `wpn_pst_t7_03` | *Archon Prime's Seraph Hand-Cannon*| 6-Shot | 180.0 – 240.0| 2.0 – 2.4/s | 6 | 1.2s | Boss drop: Laser funnel volley |

---

## 9. Tier 8 & Prismatic: Precursor & Rift God Handguns (Endgame 60+)

| ID | Name | Sub-Type | Damage Range | Fire Rate | Mag | Reload | Special / Implicit |
|---|---|---|---|---|---|---|---|
| `wpn_pst_t8_01` | *The Architect's Final Decree*| 6-Shot | 260.0 – 350.0| 2.4 – 2.8/s | 6 | 1.0s | Weakpoint crit $= 4.0\times$ |
| `wpn_pst_t8_02` | *God-Slayer Prismatic Magnum*| 6-Shot | 280.0 – 380.0| 2.2 – 2.6/s | 6 | 1.1s | 5 Affixes + smart ricochet |
| `wpn_pst_t8_03` | *Infinity Burst Machine Pistol*| Auto-Pistol | 170.0 – 230.0| 7.5 – 9.0/s | 40 | 0.8s | Bottomless mag for 2s on kill |
| `wpn_pst_t8_04` | *Rift-Void Cataclysm Cannon* | Flak Pistol | 380.0 – 520.0| 1.2 – 1.5/s | 5 | 1.4s | Screen-wide reality blast |
