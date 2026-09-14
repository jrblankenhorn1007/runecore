# Swords, Greatswords & Bladed Melee Weapons Catalog

This document specifies the individual base stat roll ranges, scaling attributes, attack animations, reach distances, and implicit perks for bladed melee weapons (One-Handed Swords, Two-Handed Greatswords, Katanas, Cleavers, Scythes, and Energy Sabers) across all 8 progression tiers in Untitled RPG (~200 weapon definitions).

---

## 1. Mechanics & Stat Rolling Parameters
- **Primary Scaling Attribute**: Strength (STR) ($+1.5\%$ per point). Katanas also scale with Dexterity (DEX).
- **Stat Ranges & Distributions**: Every discovered or crafted blade rolls its stats using a triangular distribution $\text{RollFactor} \in [0.0, 1.0]$. Quality ($0\%$ to $20\%$) skews the roll upward.
- **Weapon Classes**:
  - *Arming Swords*: Balanced swing speed (1.6 to 2.0/s), moderate stagger, medium reach (2.0 tiles).
  - *Greatswords & Cleavers*: Heavy slow swings (0.8 to 1.1/s), wide arc (2.8 to 3.2 tiles), high knockdown.
  - *High-Frequency Katanas*: Rapid swings (2.2 to 2.8/s), narrow reach (2.2 tiles), high critical strike chance ($+15\%$ to $+30\%$).
  - *Energy Sabers*: Fast swings (1.8 to 2.2/s), ignores target physical armor, consumes 1 Power per swing.
  - *Reaping Scythes*: Wide sweeping cleaves (1.2 to 1.5/s), harvests Soul Fragments from kills.

---

## 2. Tier 1: Scrap, Rusted & Makeshift Blades (Levels 1–10)
*Found in Rustwood Forest, surface junk piles, and Tier 1 Rusted Catacombs.*

| ID | Name | Sub-Type | Damage Range | Speed Range | Crit Range | Reach | Special / Implicit |
|---|---|---|---|---|---|---|---|
| `wpn_sw_t1_01` | *Scrap Machete* | Arming Sword | 10.0 – 14.0 | 1.7 – 1.9/s | 0.05 – 0.08 | 2.0 | $+5\%$ vs Beasts |
| `wpn_sw_t1_02` | *Rusted Iron Falchion* | Arming Sword | 12.0 – 16.0 | 1.5 – 1.7/s | 0.04 – 0.07 | 2.0 | Heavy tip stagger |
| `wpn_sw_t1_03` | *Makeshift Cleaver* | Cleaver | 14.0 – 19.0 | 1.2 – 1.4/s | 0.05 – 0.08 | 2.2 | $+10\%$ Bleed on hit |
| `wpn_sw_t1_04` | *Notched Longsword* | Arming Sword | 11.0 – 15.0 | 1.6 – 1.8/s | 0.05 – 0.07 | 2.2 | Basic balance |
| `wpn_sw_t1_05` | *Scrap Metal Broadsword*| Arming Sword | 13.0 – 17.0 | 1.4 – 1.6/s | 0.04 – 0.06 | 2.1 | $+10$ Knockback |
| `wpn_sw_t1_06` | *Pipe-Welded Spatha* | Arming Sword | 12.0 – 16.0 | 1.6 – 1.8/s | 0.06 – 0.09 | 2.0 | Fast thrust recovery |
| `wpn_sw_t1_07` | *Rusted Scrapslicer* | Katana | 9.0 – 13.0 | 2.1 – 2.4/s | 0.12 – 0.18 | 2.0 | $+15\%$ Critical Multiplier |
| `wpn_sw_t1_08` | *Bent Iron Claymore* | Greatsword | 18.0 – 25.0 | 0.9 – 1.1/s | 0.03 – 0.06 | 2.8 | Wide 180° swing |
| `wpn_sw_t1_09` | *Scavenger Zweihander* | Greatsword | 20.0 – 28.0 | 0.8 – 1.0/s | 0.04 – 0.06 | 3.0 | Knockdown on hit |
| `wpn_sw_t1_10` | *Sharpened Leaf Blade* | Arming Sword | 10.0 – 14.0 | 1.8 – 2.0/s | 0.07 – 0.10 | 1.9 | Low stamina cost |
| `wpn_sw_t1_11` | *Rusted Cutlass* | Arming Sword | 11.0 – 15.0 | 1.7 – 1.9/s | 0.06 – 0.09 | 2.0 | $+5\%$ Dodge recovery |
| `wpn_sw_t1_12` | *Spiked Meat Cleaver* | Cleaver | 15.0 – 21.0 | 1.1 – 1.3/s | 0.05 – 0.08 | 2.2 | Stacks minor Rend |
| `wpn_sw_t1_13` | *Salvaged Rail Spike Blade*| Arming Sword | 14.0 – 18.0 | 1.3 – 1.5/s | 0.04 – 0.06 | 2.0 | Heavy blunt impact |
| `wpn_sw_t1_14` | *Crude Iron Scythe* | Scythe | 16.0 – 22.0 | 1.1 – 1.3/s | 0.06 – 0.09 | 2.6 | Sweeping arc cleave |
| `wpn_sw_t1_15` | *Rusted Boiler Plate Blade*| Greatsword | 22.0 – 30.0 | 0.7 – 0.9/s | 0.02 – 0.05 | 2.7 | Destroys wooden blocks |
| `wpn_sw_t1_16` | *Worn Cavalry Saber* | Arming Sword | 12.0 – 16.0 | 1.8 – 2.0/s | 0.08 – 0.11 | 2.2 | Running attack bonus |
| `wpn_sw_t1_17` | *Bandit's Jagged Edge* | Arming Sword | 13.0 – 17.0 | 1.6 – 1.8/s | 0.06 – 0.09 | 2.1 | $+15\%$ Bleed damage |
| `wpn_sw_t1_18` | *Serrated Scrap Katana* | Katana | 10.0 – 14.0 | 2.2 – 2.5/s | 0.14 – 0.20 | 2.1 | Quickdraw speed $+40\%$ |
| `wpn_sw_t1_19` | *Cracked Basalt Sword* | Arming Sword | 14.0 – 18.0 | 1.4 – 1.6/s | 0.03 – 0.06 | 2.0 | High durability decay |
| `wpn_sw_t1_20` | *Goliath Excavator Tooth*| Greatsword | 24.0 – 34.0 | 0.7 – 0.9/s | 0.05 – 0.08 | 3.0 | Boss drop: $+20$ knockback |

---

## 3. Tier 2: Refined Iron & Bio-Cultured Blades (Levels 11–20)
*Found in Overgrown Bio-Labs, Whispering Taiga, and forged at Tier 2 anvil.*

| ID | Name | Sub-Type | Damage Range | Speed Range | Crit Range | Reach | Special / Implicit |
|---|---|---|---|---|---|---|---|
| `wpn_sw_t2_01` | *Refined Iron Arming Sword*| Arming Sword | 18.0 – 24.0 | 1.7 – 1.9/s | 0.06 – 0.09 | 2.1 | Balanced swing |
| `wpn_sw_t2_02` | *Tempered Iron Claymore* | Greatsword | 28.0 – 38.0 | 0.9 – 1.1/s | 0.04 – 0.07 | 2.9 | Cleaves 3 enemies |
| `wpn_sw_t2_03` | *Bio-Vine Briar Blade* | Arming Sword | 19.0 – 25.0 | 1.6 – 1.8/s | 0.07 – 0.10 | 2.2 | Roots target on crit |
| `wpn_sw_t2_04` | *Mantis Claw Scythe* | Scythe | 25.0 – 34.0 | 1.3 – 1.5/s | 0.08 – 0.12 | 2.7 | $+20\%$ Rend damage |
| `wpn_sw_t2_05` | *Honed Iron Katana* | Katana | 16.0 – 21.0 | 2.3 – 2.6/s | 0.15 – 0.22 | 2.2 | $+25\%$ Crit Multiplier |
| `wpn_sw_t2_06` | *Bio-Lab Surgical Machete*| Cleaver | 22.0 – 29.0 | 1.4 – 1.6/s | 0.08 – 0.12 | 2.2 | $+20\%$ vs Mutants |
| `wpn_sw_t2_07` | *Spore-Etched Falchion* | Arming Sword | 19.0 – 26.0 | 1.5 – 1.7/s | 0.05 – 0.08 | 2.1 | Inflicts Toxin cloud |
| `wpn_sw_t2_08` | *Heavy Iron Executioner* | Greatsword | 32.0 – 42.0 | 0.8 – 1.0/s | 0.06 – 0.10 | 3.0 | Execute below 20% HP |
| `wpn_sw_t2_09` | *Chlorophyll Infused Blade*| Arming Sword | 18.0 – 23.0 | 1.8 – 2.0/s | 0.06 – 0.09 | 2.1 | Restores 2 HP on hit |
| `wpn_sw_t2_10` | *Venom-Tipped Gladius* | Arming Sword | 17.0 – 22.0 | 1.9 – 2.1/s | 0.09 – 0.13 | 1.9 | Fast poison stacks |
| `wpn_sw_t2_11` | *Chitinous Great-Cleaver*| Cleaver | 30.0 – 40.0 | 0.9 – 1.1/s | 0.05 – 0.08 | 2.8 | Reflects 10% melee |
| `wpn_sw_t2_12` | *Feral Wolf-Fang Blade* | Arming Sword | 20.0 – 26.0 | 1.7 – 1.9/s | 0.10 – 0.14 | 2.1 | Lifesteal $+3\%$ |
| `wpn_sw_t2_13` | *Alloy Trench Saber* | Arming Sword | 19.0 – 25.0 | 1.8 – 2.0/s | 0.07 – 0.10 | 2.2 | Dash strike $+25\%$ dmg |
| `wpn_sw_t2_14` | *Greenhouse Pruning Scythe*| Scythe | 24.0 – 32.0 | 1.2 – 1.4/s | 0.06 – 0.09 | 2.6 | Plant gathering $+40\%$ |
| `wpn_sw_t2_15` | *Mother Chimera Talon Sword*| Katana | 22.0 – 30.0 | 2.4 – 2.7/s | 0.18 – 0.25 | 2.3 | Boss drop: Toxic Frenzy |

---

## 4. Tier 3: Industrial Steel & Steam-Forged Blades (Levels 21–30)
*Found in Submerged Cooling Vaults, Ashen Foundry, and Steam Workshops.*

| ID | Name | Sub-Type | Damage Range | Speed Range | Crit Range | Reach | Special / Implicit |
|---|---|---|---|---|---|---|---|
| `wpn_sw_t3_01` | *Industrial High-Tensile Blade*| Arming Sword | 28.0 – 36.0 | 1.8 – 2.0/s | 0.08 – 0.12 | 2.2 | High durability (300) |
| `wpn_sw_t3_02` | *Steam-Vented Greatsword*| Greatsword | 42.0 – 56.0 | 0.9 – 1.1/s | 0.05 – 0.08 | 3.0 | Releases steam burst |
| `wpn_sw_t3_03` | *High-Frequency Vibro-Katana*| Katana | 25.0 – 33.0 | 2.5 – 2.9/s | 0.20 – 0.28 | 2.2 | Armor pierce $15\%$ |
| `wpn_sw_t3_04` | *Electric Arc Saber* | Energy Saber | 32.0 – 42.0 | 1.9 – 2.2/s | 0.10 – 0.14 | 2.2 | Chains electric arc |
| `wpn_sw_t3_05` | *Turbine Rotor Cleaver* | Cleaver | 38.0 – 48.0 | 1.2 – 1.4/s | 0.07 – 0.10 | 2.6 | Pulls water / air |
| `wpn_sw_t3_06` | *Tempered Steel Longsword*| Arming Sword | 29.0 – 38.0 | 1.7 – 1.9/s | 0.07 – 0.11 | 2.3 | Balanced defensive parry |
| `wpn_sw_t3_07` | *Shock-Discharge Scythe*| Scythe | 36.0 – 47.0 | 1.3 – 1.5/s | 0.09 – 0.13 | 2.8 | Shocks grounded enemies |
| `wpn_sw_t3_08` | *Heavy Foundry Slicer* | Greatsword | 45.0 – 58.0 | 0.8 – 1.0/s | 0.04 – 0.07 | 3.1 | Slag impact splash |
| `wpn_sw_t3_09` | *Pneumatic Thrusting Sword*| Arming Sword | 30.0 – 39.0 | 2.0 – 2.2/s | 0.12 – 0.16 | 2.5 | Extra long thrust reach |
| `wpn_sw_t3_10` | *Hydro-Turbine Fin Blade*| Arming Sword | 31.0 – 40.0 | 1.8 – 2.0/s | 0.08 – 0.12 | 2.2 | Boss drop: Whirlpool pull |

---

## 5. Tier 4: Volcanic Slag & Titanium-Plated Blades (Levels 31–40)
*Found in Molten Core Smeltery and Scorched Glass Desert.*

| ID | Name | Sub-Type | Damage Range | Speed Range | Crit Range | Reach | Special / Implicit |
|---|---|---|---|---|---|---|---|
| `wpn_sw_t4_01` | *Titanium-Carbide Longsword*| Arming Sword | 40.0 – 52.0 | 1.9 – 2.1/s | 0.10 – 0.14 | 2.3 | Weightless: zero move penalty |
| `wpn_sw_t4_02` | *Molten Slag Greatsword* | Greatsword | 62.0 – 80.0 | 0.9 – 1.1/s | 0.06 – 0.09 | 3.1 | 50% Fire dmg, leaves fire |
| `wpn_sw_t4_03` | *Thermal Plasma Saber* | Energy Saber | 48.0 – 62.0 | 2.1 – 2.4/s | 0.14 – 0.18 | 2.3 | Melts physical armor 100% |
| `wpn_sw_t4_04` | *Volcanic Ash Cleaver* | Cleaver | 52.0 – 68.0 | 1.2 – 1.4/s | 0.08 – 0.12 | 2.7 | Blinds on hit with soot |
| `wpn_sw_t4_05` | *Titanium Razor Katana* | Katana | 36.0 – 48.0 | 2.6 – 3.0/s | 0.22 – 0.30 | 2.3 | Bleed damage $+35\%$ |
| `wpn_sw_t4_06` | *Crucible Forge Greatblade*| Greatsword | 65.0 – 85.0 | 0.8 – 1.0/s | 0.05 – 0.08 | 3.2 | Ground slam lava fissures |
| `wpn_sw_t4_07` | *Obsidian Shard Scythe* | Scythe | 50.0 – 65.0 | 1.3 – 1.5/s | 0.12 – 0.16 | 2.9 | Explodes on critical kill |
| `wpn_sw_t4_08` | *Forge-Master Vulcan Hammer-Sword*| Greatsword | 70.0 – 92.0 | 0.7 – 0.9/s | 0.08 – 0.12 | 3.2 | Boss drop: Slag explosion |

---

## 6. Tier 5: Cryo-Alloy & Liquid Nitrogen Blades (Levels 41–50)
*Found in Cryo-Stasis Depths and Cryo-Glacier Neon Peaks.*

| ID | Name | Sub-Type | Damage Range | Speed Range | Crit Range | Reach | Special / Implicit |
|---|---|---|---|---|---|---|---|
| `wpn_sw_t5_01` | *Glacial Cobalt Broadsword*| Arming Sword | 54.0 – 70.0 | 1.8 – 2.0/s | 0.11 – 0.15 | 2.3 | Chills targets by $30\%$ |
| `wpn_sw_t5_02` | *Absolute Zero Greatsword*| Greatsword | 82.0 – 108.0 | 0.9 – 1.1/s | 0.07 – 0.10 | 3.2 | Freezes on 3rd hit |
| `wpn_sw_t5_03` | *Liquid Nitrogen Saber* | Energy Saber | 65.0 – 84.0 | 2.0 – 2.3/s | 0.15 – 0.20 | 2.3 | Shatter bonus $+50\%$ |
| `wpn_sw_t5_04` | *Frostbite Razor Katana* | Katana | 48.0 – 64.0 | 2.7 – 3.1/s | 0.24 – 0.32 | 2.4 | Crit slows target attack |
| `wpn_sw_t5_05` | *Cryo-Stasis Reaping Scythe*| Scythe | 68.0 – 90.0 | 1.3 – 1.5/s | 0.12 – 0.16 | 3.0 | Leaves zero-friction frost |
| `wpn_sw_t5_06` | *Sub-Zero Executioner* | Cleaver | 72.0 – 96.0 | 1.1 – 1.3/s | 0.09 – 0.13 | 2.8 | Shatters frozen targets |
| `wpn_sw_t5_07` | *Absolute Zero Commander's Frostbrand*| Greatsword | 90.0 – 120.0 | 0.8 – 1.0/s | 0.10 – 0.15 | 3.3 | Boss drop: Blizzard aura |

---

## 7. Tier 6: Dimensional Void & Warped Blades (Levels 51–58)
*Found in Void-Warped Factory and Radioactive Wastelands.*

| ID | Name | Sub-Type | Damage Range | Speed Range | Crit Range | Reach | Special / Implicit |
|---|---|---|---|---|---|---|---|
| `wpn_sw_t6_01` | *Gravity-Dense Dark Sword*| Arming Sword | 72.0 – 94.0 | 1.9 – 2.1/s | 0.12 – 0.16 | 2.4 | Pulls target on hit |
| `wpn_sw_t6_02` | *Singularity Cleaver* | Cleaver | 95.0 – 125.0 | 1.1 – 1.3/s | 0.10 – 0.14 | 2.9 | Black hole impact micro-blast |
| `wpn_sw_t6_03` | *Phase-Shifted Void Katana*| Katana | 64.0 – 85.0 | 2.8 – 3.2/s | 0.26 – 0.35 | 2.4 | Hits through walls |
| `wpn_sw_t6_04` | *Dimensional Rift Greatblade*| Greatsword | 110.0 – 145.0 | 0.9 – 1.1/s | 0.08 – 0.12 | 3.3 | Tears spatial rifts |
| `wpn_sw_t6_05` | *Void Harvester Scythe* | Scythe | 90.0 – 118.0 | 1.3 – 1.5/s | 0.15 – 0.20 | 3.0 | Triples Soul Fragment yield |
| `wpn_sw_t6_06` | *Warped Precursor Saber* | Energy Saber | 85.0 – 112.0 | 2.1 – 2.4/s | 0.18 – 0.24 | 2.4 | Teleports behind target |
| `wpn_sw_t6_07` | *Dimensional Assembler's Reality Cleaver*| Greatsword | 125.0 – 165.0 | 0.8 – 1.0/s | 0.12 – 0.18 | 3.4 | Boss drop: Inverts gravity |

---

## 8. Tier 7: Archon Hard-Light & Sanctified Blades (Levels 59–60)
*Found in Holy Citadel of Hard-Light and Sunken Orbital Core.*

| ID | Name | Sub-Type | Damage Range | Speed Range | Crit Range | Reach | Special / Implicit |
|---|---|---|---|---|---|---|---|
| `wpn_sw_t7_01` | *Hard-Light Solar Broadsword*| Arming Sword | 92.0 – 120.0 | 2.0 – 2.2/s | 0.14 – 0.18 | 2.4 | Blinds target, $+50\%$ vs Undead |
| `wpn_sw_t7_02` | *Archon Radiant Greatsword*| Greatsword | 140.0 – 185.0 | 0.9 – 1.1/s | 0.09 – 0.14 | 3.4 | Beams of daylight on swing |
| `wpn_sw_t7_03` | *Photon-Weave Katana* | Katana | 80.0 – 105.0 | 2.9 – 3.4/s | 0.28 – 0.38 | 2.5 | Critical strike heals 15 HP |
| `wpn_sw_t7_04` | *Judgment Grand Scythe* | Scythe | 115.0 – 150.0 | 1.4 – 1.6/s | 0.16 – 0.22 | 3.2 | Consecrates ground on hit |
| `wpn_sw_t7_05` | *Seraph Hard-Light Dual Blades*| Arming Sword | 85.0 – 110.0 | 2.4 – 2.7/s | 0.18 – 0.25 | 2.3 | Swings launch photon arcs |
| `wpn_sw_t7_06` | *Sunken Flagship Monomolecular Cutter*| Greatsword | 155.0 – 205.0 | 0.8 – 1.0/s | 0.12 – 0.16 | 3.5 | 100% Armor pierce |
| `wpn_sw_t7_07` | *Archon Prime's Seraphic Twinblades*| Katana | 100.0 – 135.0 | 3.0 – 3.5/s | 0.30 – 0.40 | 2.6 | Boss drop: Flying light swords |

---

## 9. Tier 8 & Prismatic: Precursor & Infinite Rift God Blades (Endgame 60+)
*Exclusive drops from The Architect and scaling floors of the Infinite Rift.*

| ID | Name | Sub-Type | Damage Range | Speed Range | Crit Range | Reach | Special / Implicit |
|---|---|---|---|---|---|---|---|
| `wpn_sw_t8_01` | *The Architect's Singularity Edge*| Greatsword | 200.0 – 280.0 | 1.0 – 1.2/s | 0.15 – 0.22 | 3.6 | Reality-rending shockwaves |
| `wpn_sw_t8_02` | *God-Slayer Prismatic Claymore*| Greatsword | 220.0 – 310.0 | 0.9 – 1.1/s | 0.18 – 0.26 | 3.8 | 5 Affix slots + Prismatic Glow |
| `wpn_sw_t8_03` | *Infinite Chrono-Katana* | Katana | 140.0 – 195.0 | 3.2 – 3.8/s | 0.35 – 0.48 | 2.6 | Time slows for 1s on crit |
| `wpn_sw_t8_04` | *Omni-Elemental Beam Saber*| Energy Saber | 160.0 – 220.0 | 2.2 – 2.6/s | 0.22 – 0.30 | 2.6 | Cycles Fire, Cold, Shock, Void |
| `wpn_sw_t8_05` | *Rift-Born World Ender* | Greatsword | 250.0 – 360.0 | 0.8 – 1.0/s | 0.20 – 0.30 | 4.0 | Screenshake destruction radius |
| `wpn_sw_t8_06` | *Reaper of Dimensions* | Scythe | 180.0 – 250.0 | 1.5 – 1.8/s | 0.25 – 0.35 | 3.5 | Instant kill non-boss below 15% |
