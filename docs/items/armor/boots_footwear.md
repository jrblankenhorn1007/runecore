# Boots, Sabatons, Thruster Footwear & Slippers Catalog

This document specifies the individual base stat roll ranges, defense ratings, movement speed multipliers, fall damage reduction percentages, jump enhancers, and implicit perks for footwear across all 8 progression tiers in Untitled RPG (~150 footwear definitions).

---

## 1. Mechanics & Stat Rolling Parameters
- **Defensive & Mobility Ratings**: Footwear provides Armor ($+1$ to $+25$), base movement speed bonuses ($+3\%$ to $+35\%$), sprinting acceleration, wall-slide grip friction, and fall damage negation.
- **Sub-Types**:
  - *Light Wraps & Slippers*: Lightweight, silent steps, enhanced jump heights, mana regeneration bonuses.
  - *Leather & Scout Boots*: Sprint speed multipliers, reduced dash cooldowns, mud/swamp friction compensation.
  - *Steel Sabatons & Armored Stompers*: High armor rating, immunity to ground spikes, crushing jump-slam damage.
  - *Rocket & Jet Boots*: Powered bionic thrusters, double jump capabilities, hovering, and continuous rocket flight.

---

## 2. Complete Footwear Catalog

| ID | Name | Type | Armor Range | Speed Bonus | Special / Implicit Perk |
|---|---|---|---|---|---|
| `arm_bt_t1_01` | *Scavenger Footwraps* | Cloth | 1 – 2 | +3% Speed | Silent footsteps |
| `arm_bt_t1_02` | *Rawhide Hunter Boots* | Leather | 2 – 4 | +5% Speed | Mud walking penalty removed |
| `arm_bt_t1_03` | *Scrap Metal Sabatons* | Heavy | 4 – 6 | 0% Speed | Ground spike damage $-50\%$ |
| `arm_bt_t1_04` | *Padded Snow Mukluks* | Cloth | 2 – 4 | +2% Speed | Ice slipping reduced by $50\%$ |
| `arm_bt_t1_05` | *Goliath Excavator Treads*| Heavy | 5 – 8 | -3% Speed | Boss drop: Crushing ground impact |
| `arm_bt_t2_01` | *Refined Iron Sabatons* | Heavy | 8 – 11 | 0% Speed | Fall damage $-30\%$ |
| `arm_bt_t2_02` | *Reinforced Scout Boots*| Leather | 5 – 8 | +8% Speed | Dash distance $+1$ tile |
| `arm_bt_t2_03` | *Bio-Lab Rubber Boots* | Light | 4 – 7 | +4% Speed | Acid puddle immunity |
| `arm_bt_t2_04` | *Mantis Spring Boots* | Chitin | 6 – 9 | +6% Speed | Jump height $+25\%$ |
| `arm_bt_t2_05` | *Mother Chimera Talon Boots*| Chitin | 8 – 12 | +8% Speed | Boss drop: Wall cling & climb |
| `arm_bt_t3_01` | *Steel Enforcer Stompers*| Heavy | 12 – 16 | 0% Speed | Knockback resistance $+20\%$ |
| `arm_bt_t3_02` | *Steam Rocket Boots* | Tech | 10 – 14 | +10% Speed | Built-in double jump (uses steam) |
| `arm_bt_t3_03` | *Hydro-Turbine Flippers* | Light | 8 – 12 | +5% Speed | Boss drop: Swimming speed $+75\%$ |
| `arm_bt_t4_01` | *Titanium Thruster Boots*| Tech | 16 – 22 | +15% Speed | Mid-air hover for 2.0s |
| `arm_bt_t4_02` | *Molten Slag Sabatons* | Heavy | 18 – 25 | 0% Speed | Walk across lava without damage |
| `arm_bt_t4_03` | *Forge-Master Vulcan Stompers*| Heavy| 20 – 28| +2% Speed | Boss drop: Jump-land triggers fire wave |
| `arm_bt_t5_01` | *Glacial Cobalt Sabatons*| Heavy | 22 – 30 | +5% Speed | Frictionless ice skating mode |
| `arm_bt_t5_02` | *Cryo-Jet Jump Boots* | Tech | 18 – 24 | +18% Speed | Triple jump built-in |
| `arm_bt_t5_03` | *Absolute Zero Frost Stompers*| Heavy| 24 – 34| +5% Speed | Boss drop: Freezes water underfoot |
| `arm_bt_t6_01` | *Singularity Dark Boots* | Heavy | 28 – 38 | +12% Speed | Teleport dash through walls |
| `arm_bt_t6_02` | *Void-Warped Striders* | Cloth | 15 – 22 | +22% Speed | Phase walk (ignore enemy hitboxes) |
| `arm_bt_t6_03` | *Dimensional Assembler's Treads*| Heavy| 32 – 44| +10% Speed| Boss drop: Gravity flip on double jump |
| `arm_bt_t7_01` | *Archon Hard-Light Sabatons*| Heavy| 35 – 48 | +15% Speed | Leaves glowing light trail, $+25$ holy |
| `arm_bt_t7_02` | *Seraph Feather Slippers*| Cloth | 20 – 28 | +25% Speed | Permanent zero fall damage |
| `arm_bt_t7_03` | *Archon Prime's Winged Boots*| Holy | 40 – 55 | +20% Speed | Boss drop: 3 seconds flight on jump |
| `arm_bt_t8_01` | *The Architect's Flight Skids*| God Boots| 60 – 85 | +30% Speed | Continuous infinite rocket flight |
| `arm_bt_t8_02` | *God-Slayer Prismatic Boots*| God Boots| 70 – 100| +35% Speed | 5 Affixes + permanent bullet-time on dash |
| `arm_bt_t8_03` | *Boots of the Void God* | God Boots| 50 – 75 | +25% Speed | Walk on air; immune to all ground hazards |
