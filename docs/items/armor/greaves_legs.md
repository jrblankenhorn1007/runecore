# Greaves, Legplates, Trousers & Exo-Legs Catalog

This document specifies the individual base stat roll ranges, defense ratings, sprint stamina efficiencies, movement modifiers, and implicit bonuses for leg armors across all 8 progression tiers in Untitled RPG (~160 leg armor definitions).

---

## 1. Mechanics & Stat Rolling Parameters
- **Defensive Ratings**: Leg armor provides Armor ($+1$ to $+35$), cold/heat insulation, fall damage mitigation, and sprint stamina cost reductions.
- **Sub-Types**:
  - *Cloth Trousers & Skirts*: Lightweight (0 to 3 kg), zero movement penalty, increased stamina recovery rate ($+5\%$ to $+15\%$).
  - *Leather Chaps & Scout Pants*: Medium-light (3 to 6 kg), slide speed bonuses, reduced dash cooldowns.
  - *Steel & Alloy Heavy Greaves*: Heavy (8 to 18 kg), extreme armor protection, resistance to leg crippling and ground spikes.
  - *Servo-Assisted Exo-Legs*: Powered legs providing jump height bonuses ($+15\%$ to $+35\%$) and sprint velocity boosts.

---

## 2. Complete Leg Armor Catalog

| ID | Name | Type | Armor Range | Cold/Heat Resist | Special / Implicit |
|---|---|---|---|---|---|
| `arm_lg_t1_01` | *Scavenger Cloth Pants* | Cloth | 2 – 3 | +2 Cold / +2 Heat | Stamina regen $+5\%$ |
| `arm_lg_t1_02` | *Rawhide Hunter Chaps* | Leather | 4 – 6 | +4 Cold / +2 Heat | Slide distance $+1$ tile |
| `arm_lg_t1_03` | *Scrap Metal Shinplates*| Heavy | 6 – 9 | +2 Cold / +5 Heat | Spike trap damage $-25\%$ |
| `arm_lg_t1_04` | *Padded Snow Trousers* | Cloth | 4 – 7 | +20 Cold / -5 Heat | Snow walking penalty removed |
| `arm_lg_t1_05` | *Goliath Excavator Piston Legs*| Heavy | 8 – 12 | +4 Cold / +15 Heat| Boss drop: Ground slam shockwave |
| `arm_lg_t2_01` | *Refined Iron Greaves* | Heavy | 12 – 16 | +4 Cold / -3 Heat | Fall damage $-20\%$ |
| `arm_lg_t2_02` | *Reinforced Scout Chaps*| Leather | 8 – 11 | +8 Cold / +6 Heat | Sprint stamina cost $-15\%$ |
| `arm_lg_t2_03` | *Bio-Lab Hazmat Trousers*| Light | 7 – 10 | +12 Cold / +12 Heat| Acid puddle immunity |
| `arm_lg_t2_04` | *Chitinous Beast Leggings*| Chitin | 10 – 14 | -4 Cold / +8 Heat | Move speed $+5\%$ |
| `arm_lg_t2_05` | *Mother Chimera Mantis Greaves*| Chitin | 14 – 18 | +6 Cold / +6 Heat | Boss drop: Wall slide speed $-50\%$ |
| `arm_lg_t3_01` | *Steel Enforcer Legplates*| Heavy | 18 – 24 | +6 Cold / -3 Heat | Knockback resist $+20\%$ |
| `arm_lg_t3_02` | *Steam-Powered Exo-Legs*| Tech | 20 – 26 | +10 Cold / +10 Heat| Jump height $+20\%$ |
| `arm_lg_t3_03` | *Hydro-Turbine Fin Greaves*| Heavy | 15 – 20 | +15 Cold / 0 Heat | Boss drop: Underwater move speed $+40\%$ |
| `arm_lg_t4_01` | *Titanium Exo-Greaves* | Tech | 26 – 34 | +15 Cold / +15 Heat| Dash distance $+1.5$ tiles |
| `arm_lg_t4_02` | *Molten Slag Legguards* | Heavy | 30 – 40 | -5 Cold / +45 Heat | Immune to burning terrain |
| `arm_lg_t4_03` | *Forge-Master Vulcan Greaves*| Heavy | 35 – 46 | 0 Cold / +55 Heat | Boss drop: Dashing leaves fire trail |
| `arm_lg_t5_01` | *Glacial Cobalt Greaves* | Heavy | 38 – 48 | +55 Cold / -5 Heat | Ice walking friction $+100\%$ |
| `arm_lg_t5_02` | *Cryomancer's Frost Skirt*| Cloth | 18 – 25 | +45 Cold / 0 Heat | Spell mana cost $-10\%$ |
| `arm_lg_t5_03` | *Absolute Zero Legplates*| Tech | 42 – 54 | +65 Cold / +15 Heat| Boss drop: Chills ground walked on |
| `arm_lg_t6_01` | *Singularity Dark Greaves*| Heavy | 48 – 62 | +30 Cold / +30 Heat| Teleport blink distance $+2$ tiles |
| `arm_lg_t6_02` | *Void-Warped Leggings* | Cloth | 24 – 32 | +25 Cold / +25 Heat| Phase through enemy bodies |
| `arm_lg_t6_03` | *Dimensional Assembler's Treads*| Heavy | 55 – 70| +35 Cold / +35 Heat| Boss drop: Gravitational stomp |
| `arm_lg_t7_01` | *Archon Hard-Light Greaves*| Heavy | 60 – 78 | +45 Cold / +45 Heat| Daylight aura, $+25$ holy resist |
| `arm_lg_t7_02` | *Seraph Radiant Skirt* | Cloth | 30 – 40 | +35 Cold / +35 Heat| Sprint heals nearby allies |
| `arm_lg_t7_03` | *Archon Prime's Legplates*| Heavy | 70 – 90 | +50 Cold / +50 Heat| Boss drop: Double jump built-in |
| `arm_lg_t8_01` | *The Architect's Core Greaves*| God Legs | 100 – 135| +80 Cold / +80 Heat | Immune to all slow & root debuffs |
| `arm_lg_t8_02` | *God-Slayer Prismatic Greaves*| God Legs | 115 – 155| +90 Cold / +90 Heat | 5 Affixes + permanent sprint mode |
| `arm_lg_t8_03` | *Greaves of Infinite Stride*| God Legs | 80 – 110 | +80 Cold / +80 Heat | Infinite jump height, zero fall damage |
