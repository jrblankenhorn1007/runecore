# Helmets, Hoods, Tactical Visors & Crowns Catalog

This document specifies the individual base stat roll ranges, defense ratings, sensory perks, light emission radii, and implicit bonuses for head armors across all 8 progression tiers in Untitled RPG (~150 headpiece definitions).

---

## 1. Mechanics & Stat Rolling Parameters
- **Defensive Ratings**: Headpieces provide Armor ($+2$ to $+40$), elemental status resistances, and specialized sensory vision modes (night vision, ore detection, weakpoint scanning).
- **Sub-Types**:
  - *Cloth Hoods & Cowls*: High magic mana pool (+10 to +50 Max Mana), spell cooldown reduction, zero weight.
  - *Leather Caps & Scout Bandanas*: High critical strike chance ($+3\%$ to $+10\%$), increased field of view, night vision.
  - *Steel Enforcer Helmets & Great-Helms*: Heavy armor, headshot protection, stun reduction ($30\%$ to $50\%$).
  - *Cybernetic Visors & HUD Scanners*: Built-in flashlight illumination, shows enemy health bars, highlights weakpoints.
  - *Archon Crowns & Halo Relics*: Radiates holy light, heals nearby allies, boosts holy spell damage.

---

## 2. Complete Helmets & Headpieces Catalog

| ID | Name | Type | Armor Range | Cold/Heat Resist | Special / Implicit |
|---|---|---|---|---|---|
| `arm_hd_t1_01` | *Scavenger Cloth Hood* | Cloth | 2 – 3 | +3 Cold / +3 Heat | $+5\%$ Scrap find rate |
| `arm_hd_t1_02` | *Rawhide Hunter Cap* | Leather | 3 – 5 | +5 Cold / +2 Heat | Night vision $+20\%$ |
| `arm_hd_t1_03` | *Welder's Face Shield* | Heavy | 5 – 8 | +2 Cold / +15 Heat| Headshot protection $25\%$ |
| `arm_hd_t1_04` | *Miner's Hardhat with Torch*| Utility | 4 – 6 | +2 Cold / +2 Heat | Built-in 10-tile forward flashlight |
| `arm_hd_t1_05` | *Goliath Excavator Drill Cap*| Heavy | 7 – 10 | +5 Cold / +15 Heat| Boss drop: Mining speed $+20\%$ |
| `arm_hd_t2_01` | *Refined Iron Close-Helm* | Heavy | 10 – 14 | +4 Cold / -2 Heat | Stun duration $-25\%$ |
| `arm_hd_t2_02` | *Bio-Lab Gas Mask* | Light | 6 – 9 | +10 Cold / +10 Heat| Complete gas & poison immunity |
| `arm_hd_t2_03` | *Aether Focus Cowl* | Cloth | 5 – 8 | +8 Cold / +8 Heat | $+25$ Max Mana, $+0.5\text{ MP/s}$ |
| `arm_hd_t2_04` | *Mother Chimera Horned Crest*| Chitin | 11 – 15 | +5 Cold / +5 Heat | Boss drop: Headbutt gore attack |
| `arm_hd_t3_01` | *Steel Enforcer Great-Helm*| Heavy | 16 – 22 | +8 Cold / -4 Heat | Knockback resist $+25\%$ |
| `arm_hd_t3_02` | *Tactical Night-Vision Goggles*| Tech | 10 – 14 | +5 Cold / +5 Heat | Full night vision, reveals traps |
| `arm_hd_t3_03` | *Hydro-Turbine Diving Helm*| Heavy | 14 – 18 | +15 Cold / 0 Heat | Boss drop: Infinite underwater breath |
| `arm_hd_t4_01` | *Titanium Targeting Visor* | Tech | 20 – 26 | +15 Cold / +15 Heat| Shows enemy health bars & crits |
| `arm_hd_t4_02` | *Molten Slag Crown* | Heavy | 24 – 32 | -5 Cold / +40 Heat | $+15\%$ Fire Damage |
| `arm_hd_t4_03` | *Forge-Master Vulcan Crown*| Heavy | 28 – 36 | 0 Cold / +50 Heat | Boss drop: Emits molten sparks |
| `arm_hd_t5_01` | *Glacial Cobalt Armet* | Heavy | 30 – 38 | +50 Cold / -5 Heat | Immune to freezing blizzards |
| `arm_hd_t5_02` | *Cryomancer's Frost Crown*| Cloth | 15 – 22 | +40 Cold / 0 Heat | $+25\%$ Frost Spell Damage |
| `arm_hd_t5_03` | *Absolute Zero Visor* | Tech | 32 – 42 | +60 Cold / +15 Heat| Boss drop: Freezes enemy vision |
| `arm_hd_t6_01` | *Singularity Dark Hood* | Cloth | 22 – 30 | +25 Cold / +25 Heat| Teleport dash cooldown $-20\%$ |
| `arm_hd_t6_02` | *Void-Warped Mask* | Heavy | 40 – 52 | +30 Cold / +30 Heat| Enemies near player are slowed |
| `arm_hd_t6_03` | *Dimensional Assembler's Crown*| Heavy | 45 – 58 | +35 Cold / +35 Heat| Boss drop: Telepathic projectile defense |
| `arm_hd_t7_01` | *Archon Radiant Halo* | Holy | 35 – 46 | +40 Cold / +40 Heat| Permanent daylight aura, $+30$ holy |
| `arm_hd_t7_02` | *Solar Hard-Light Crown* | Heavy | 50 – 65 | +45 Cold / +45 Heat| Blinds attackers on hit |
| `arm_hd_t7_03` | *Archon Prime's Seraph Crest*| Holy | 55 – 72 | +50 Cold / +50 Heat| Boss drop: Orbiting light blades |
| `arm_hd_t8_01` | *The Architect's Neural Crown*| God Helm | 80 – 110 | +80 Cold / +80 Heat | All skill cooldowns $-30\%$ |
| `arm_hd_t8_02` | *God-Slayer Prismatic Helm*| God Helm | 90 – 130 | +100 Cold / +100 Heat| 5 Affixes + reveals entire dungeon map |
| `arm_hd_t8_03` | *Crown of Infinite Mind* | God Helm | 60 – 85 | +80 Cold / +80 Heat | $+200$ Max Mana, $+100$ Max Power |
