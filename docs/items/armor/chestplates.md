# Chestplates, Cuirasses, Body Rigs & Robes Catalog

This document specifies the individual base stat roll ranges, defense ratings, cold/heat insulation values, carry weight impacts, and implicit set perks for torso armors across all 8 progression tiers in Untitled RPG (~180 armor definitions).

---

## 1. Mechanics & Stat Rolling Parameters
- **Primary Defensive Attributes**: Total Armor rating (mitigates incoming physical/energy damage via $\text{Damage Reduction} = \frac{\text{Armor}}{\text{Armor} + 100}$), Elemental Resistances (Fire, Cold, Shock, Toxic, Holy, Void), Cold and Heat Insulation (°C offset).
- **Armor Types**:
  - *Cloth & Robes*: Light weight (0 to 4 kg, no speed penalty), low physical armor, high magical mana pool (+20 to +100 Max Mana), high magic resistance.
  - *Leather & Chitin Light Armor*: Medium-light (4 to 10 kg, +3% to +8% move speed bonus), balanced physical defense and stealth noise reduction.
  - *Steel & Alloy Heavy Plate*: Heavy (12 to 28 kg, -5% to -15% move speed penalty unless negated by Strength or Juggernaut passives), extreme physical armor, massive knockback resistance.
  - *Titanium Exo-Rigs*: Moderate weight (12 to 16 kg), integrated battery cells (+20 to +60 Max Power), zero movement speed penalty.

---

## 2. Tier 1: Scrap, Cloth & Makeshift Chestpieces (Levels 1–10)

| ID | Name | Type | Armor Range | Cold/Heat Resist | Weight | Implicit / Special Perk |
|---|---|---|---|---|---|---|
| `arm_ch_t1_01` | *Scavenger Ragged Tunic* | Cloth | 4 – 6 | +5 Cold / +5 Heat | 0 kg | $+10\%$ Scrap find chance |
| `arm_ch_t1_02` | *Rawhide Hunter Vest* | Leather | 6 – 9 | +8 Cold / +2 Heat | 4 kg | $+5\%$ Move speed |
| `arm_ch_t1_03` | *Scrap Metal Plated Vest*| Heavy | 10 – 14 | +4 Cold / +8 Heat | 8 kg | Knockback resist $+20\%$ |
| `arm_ch_t1_04` | *Padded Winter Parka* | Cloth | 5 – 8 | +25 Cold / -10 Heat | 3 kg | Freezing immunity in Taiga |
| `arm_ch_t1_05` | *Hardened Boar-Hide Jerkin*| Leather | 8 – 11 | +6 Cold / +4 Heat | 5 kg | $+10$ Max Health |
| `arm_ch_t1_06` | *Rusted Iron Mail Hauberk*| Heavy | 12 – 16 | +2 Cold / -4 Heat | 10 kg | $-4\%$ Move speed |
| `arm_ch_t1_07` | *Apprentice Aether Tunic* | Robe | 4 – 7 | +5 Cold / +5 Heat | 2 kg | $+20$ Max Mana |
| `arm_ch_t1_08` | *Goliath Excavator Welder Vest*| Heavy | 14 – 19 | +10 Cold / +25 Heat| 11 kg | Boss drop: Blast resist $+30\%$ |

---

## 3. Tier 2: Refined Iron & Bio-Cultured Chestpieces (Levels 11–20)

| ID | Name | Type | Armor Range | Cold/Heat Resist | Weight | Implicit / Special Perk |
|---|---|---|---|---|---|---|
| `arm_ch_t2_01` | *Refined Iron Breastplate*| Heavy | 18 – 24 | +6 Cold / -5 Heat | 12 kg | $+15$ Armor when blocking |
| `arm_ch_t2_02` | *Reinforced Scout Harness*| Leather | 12 – 17 | +10 Cold / +8 Heat | 5 kg | $+8\%$ Sprint speed |
| `arm_ch_t2_03` | *Bio-Lab Hazmat Suit* | Light | 10 – 15 | +15 Cold / +15 Heat| 4 kg | Poison & acid gas immunity |
| `arm_ch_t2_04` | *Chitinous Beast Carapace*| Chitin | 16 – 22 | -5 Cold / +12 Heat | 7 kg | Reflects $15\%$ melee damage |
| `arm_ch_t2_05` | *Aether Conduit Robe* | Robe | 8 – 12 | +12 Cold / +12 Heat| 3 kg | $+45$ Max Mana, $+0.5\text{ MP/s}$ |
| `arm_ch_t2_06` | *Mother Chimera Living Chitin*| Chitin | 20 – 26 | +10 Cold / +10 Heat| 8 kg | Boss drop: Regrows 2 HP/s |

---

## 4. Tier 3: Industrial Steel & Steam-Forged Chestpieces (Levels 21–30)

| ID | Name | Type | Armor Range | Cold/Heat Resist | Weight | Implicit / Special Perk |
|---|---|---|---|---|---|---|
| `arm_ch_t3_01` | *Steel Enforcer Cuirass* | Heavy | 28 – 36 | +10 Cold / -5 Heat | 16 kg | Knockback resist $+40\%$ |
| `arm_ch_t3_02` | *Steam-Powered Exo-Brace* | Heavy | 30 – 40 | +15 Cold / +15 Heat| 14 kg | $+25\text{ kg}$ Carry weight |
| `arm_ch_t3_03` | *Infiltrator Nano-Vest* | Light | 18 – 24 | +10 Cold / +10 Heat| 5 kg | Silent footsteps |
| `arm_ch_t3_04` | *Turbine diver Wet-Suit* | Light | 16 – 22 | +20 Cold / 0 Heat | 6 kg | Boss drop: Swimming speed $+50\%$ |

---

## 5. Tier 4: Volcanic Slag & Titanium Rigs (Levels 31–40)

| ID | Name | Type | Armor Range | Cold/Heat Resist | Weight | Implicit / Special Perk |
|---|---|---|---|---|---|---|
| `arm_ch_t4_01` | *Titanium Combat Exo-Rig* | Heavy | 42 – 54 | +25 Cold / +25 Heat| 12 kg | $+40$ Max Power, 0% speed penalty |
| `arm_ch_t4_02` | *Molten Slag Foundry Plate*| Heavy | 48 – 62 | -10 Cold / +60 Heat| 18 kg | Immune to lava floor burning |
| `arm_ch_t4_03` | *Pyromancer's Ashen Robes*| Robe | 20 – 28 | -5 Cold / +45 Heat | 4 kg | $+25\%$ Fire spell damage |
| `arm_ch_t4_04` | *Forge-Master Vulcan Crucible Plate*| Heavy | 55 – 72 | 0 Cold / +75 Heat | 20 kg | Boss drop: Magma shield barrier |

---

## 6. Tier 5: Cryo-Alloy Chestpieces (Levels 41–50)

| ID | Name | Type | Armor Range | Cold/Heat Resist | Weight | Implicit / Special Perk |
|---|---|---|---|---|---|---|
| `arm_ch_t5_01` | *Glacial Cobalt Cuirass* | Heavy | 58 – 74 | +70 Cold / -10 Heat| 18 kg | Immune to freezing blizzard |
| `arm_ch_t5_02` | *Cryomancer's Frost-Weave*| Robe | 26 – 35 | +60 Cold / 0 Heat | 4 kg | $+30\%$ Frost spell damage |
| `arm_ch_t5_03` | *Absolute Zero Commander's Exo-Suit*| Heavy | 68 – 88 | +85 Cold / +30 Heat| 14 kg | Boss drop: Emits freezing pulse |

---

## 7. Tier 6: Dimensional Void Chestpieces (Levels 51–58)

| ID | Name | Type | Armor Range | Cold/Heat Resist | Weight | Implicit / Special Perk |
|---|---|---|---|---|---|---|
| `arm_ch_t6_01` | *Gravity-Dense Dark Plate*| Heavy | 78 – 98 | +40 Cold / +40 Heat| 22 kg | Absorbs $15\%$ of all damage |
| `arm_ch_t6_02` | *Void-Weaver's Shroud* | Robe | 35 – 48 | +35 Cold / +35 Heat| 3 kg | Teleport dash on damage taken |
| `arm_ch_t6_03` | *Dimensional Assembler's Core Frame*| Heavy | 88 – 115| +50 Cold / +50 Heat| 16 kg | Boss drop: Inverts gravity pulses |

---

## 8. Tier 7: Archon Hard-Light Chestpieces (Levels 59–60)

| ID | Name | Type | Armor Range | Cold/Heat Resist | Weight | Implicit / Special Perk |
|---|---|---|---|---|---|---|
| `arm_ch_t7_01` | *Archon Hard-Light Breastplate*| Heavy | 95 – 125 | +50 Cold / +50 Heat| 16 kg | Emits daylight aura, $+35$ holy |
| `arm_ch_t7_02` | *Seraph Radiant Vestments*| Robe | 45 – 60 | +40 Cold / +40 Heat| 4 kg | $+40\%$ Holy damage, heals allies |
| `arm_ch_t7_03` | *Archon Prime's Aegis Plate*| Heavy | 115 – 150| +60 Cold / +60 Heat| 18 kg | Boss drop: Fatal hit triggers dome |

---

## 9. Tier 8 & Prismatic: Precursor & Rift God Chestpieces (Endgame 60+)

| ID | Name | Type | Armor Range | Cold/Heat Resist | Weight | Implicit / Special Perk |
|---|---|---|---|---|---|---|
| `arm_ch_t8_01` | *The Architect's Living Matrix*| Heavy | 160 – 220| +100 Cold / +100 Heat| 12 kg | Immune to all status debuffs |
| `arm_ch_t8_02` | *God-Slayer Prismatic Cuirass*| Heavy | 180 – 260| +120 Cold / +120 Heat| 14 kg | 5 Affix slots + Prismatic barrier |
| `arm_ch_t8_03` | *Rift-Born Singularity Robes* | Robe | 80 – 120 | +100 Cold / +100 Heat| 2 kg | $+80\%$ Spell damage, black hole aura |
