# Crystals, Gemstones, Mana Geodes & Focusing Prisms Catalog

This document specifies the geological origins, optical refractive indexes, elemental mana affinities, socket bonuses, and crafting applications for all gemstones, crystals, and prisms in Untitled RPG (~60 mineral crystal definitions).

---

## 1. Crystal Mechanics & Socket System
- **Extraction**: Raw crystals are mined from geode nodes in subterranean vaults using a Mineral Chisel tool. Extracting without a chisel has a $50\%$ chance to produce cracked fragments rather than intact gems.
- **Cutting & Refining**: Uncut rough gems are polished at the Lapidary Wheel or Alchemical Crucible into **Faceted Sockets**.
- **Equipment Sockets**: Sockets punched into weapons, armor, or bionic limbs via the Modification Forge accept cut gems to grant permanent passive bonuses:
  - *Weapons*: Adds flat elemental damage (Fire, Cold, Shock, Toxic, Holy, Void) or critical multipliers.
  - *Armor*: Grants flat elemental damage resistance or maximum resource pool bonuses (+Health, +Mana, +Power).
  - *Augmentations*: Overclocks primary attributes or accelerates energy generation.

---

## 2. Complete Crystals, Gemstones & Prisms Catalog

| ID | Name | Cut Type | Tier | Stack Size | Base Value | Socket Bonus (Weapon / Armor) |
|---|---|---|---|---|---|---|
| `mat_gem_01` | *Rough Quartz Shard* | Raw Mineral | 1 | 99 | 4 | Weapon: $+3$ Physical Dmg. Armor: $+10$ Max Stamina. |
| `mat_gem_02` | *Polished Clear Quartz* | Faceted Gem | 1 | 99 | 10 | Weapon: $+6$ Physical Dmg. Armor: $+20$ Max Stamina. |
| `mat_gem_03` | *Rough Amethyst Geode* | Raw Mineral | 1 | 99 | 6 | Weapon: $+4$ Arcane Dmg. Armor: $+15$ Max Mana. |
| `mat_gem_04` | *Faceted Deep Amethyst* | Faceted Gem | 2 | 99 | 16 | Weapon: $+8$ Arcane Dmg. Armor: $+35$ Max Mana. |
| `mat_gem_05` | *Rough Topaz Crystal* | Raw Mineral | 2 | 99 | 8 | Weapon: $+5$ Shock Dmg. Armor: $+10$ Shock Resist. |
| `mat_gem_06` | *Faceted Lightning Topaz*| Faceted Gem | 2 | 99 | 20 | Weapon: $+12$ Shock Dmg. Armor: $+25$ Shock Resist. |
| `mat_gem_07` | *Rough Fire Ruby* | Raw Mineral | 3 | 99 | 15 | Weapon: $+8$ Fire Dmg. Armor: $+15$ Fire Resist. |
| `mat_gem_08` | *Faceted Volcanic Ruby* | Faceted Gem | 3 | 99 | 35 | Weapon: $+18$ Fire Dmg, ignites. Armor: $+35$ Fire Resist. |
| `mat_gem_09` | *Rough Glacial Sapphire* | Raw Mineral | 3 | 99 | 15 | Weapon: $+7$ Frost Dmg. Armor: $+15$ Cold Resist. |
| `mat_gem_10` | *Faceted Sub-Zero Sapphire*| Faceted Gem | 4 | 99 | 40 | Weapon: $+16$ Frost Dmg, chills. Armor: $+40$ Cold Resist. |
| `mat_gem_11` | *Rough Emerald Geode* | Raw Mineral | 3 | 99 | 12 | Weapon: $+6$ Toxin Dmg. Armor: $+20$ Max Health. |
| `mat_gem_12` | *Faceted Bio-Emerald* | Faceted Gem | 4 | 99 | 32 | Weapon: $+15$ Toxin Dmg, poisons. Armor: $+50$ Max Health. |
| `mat_gem_13` | *Flawless Diamond Crystal*| Rare Gem | 5 | 99 | 80 | Weapon: $+0.35\times$ Crit Multiplier. Armor: $+15$ Armor. |
| `mat_gem_14` | *Radiant Sunstone* | Radiant Gem | 5 | 99 | 75 | Weapon: $+25$ Holy Dmg. Armor: Radiates light aura. |
| `mat_gem_15` | *Corrupted Void Onyx* | Dark Gem | 6 | 99 | 90 | Weapon: $+30$ Void Dmg. Armor: $+5\%$ Dodge Evasion. |
| `mat_gem_16` | *Singularity Black Diamond*| Dark Gem | 6 | 99 | 130 | Weapon: Attacks pull targets. Armor: Absorbs $10\%$ damage. |
| `mat_gem_17` | *Pure Aether Mana Crystal*| Arcane Geode | 5 | 99 | 65 | Weapon: Refund 10% mana cost. Armor: $+1.5\text{ MP/s}$ regen. |
| `mat_gem_18` | *Hard-Light Resonator Prism*| Optical Prism| 7 | 99 | 150 | Weapon: Wand attacks split into 2. Armor: Reflects lasers. |
| `mat_gem_19` | *Ancient Astral Geode* | Precursor Gem| 7 | 99 | 200 | Heart Socket: Generates 15 Power/s and 1.5 MP/s. |
| `mat_gem_20` | *The Architect's Singularity Core*| God Gem | 8 | 99 | 500 | Any Socket: $+25$ to All Primary Attributes. |
| `mat_gem_21` | *Prismatic Chrono-Crystal*| God Gem | 8 | 99 | 450 | Weapon: Time slows on crit. Armor: $+100$ HP, $+100$ MP. |
| `mat_gem_22` | *Fluorite Optical Lens* | Optical Glass| 3 | 99 | 18 | Laser sights, sniper scopes, night-vision goggles. |
| `mat_gem_23` | *Garnet Impact Cluster* | Raw Cluster | 2 | 99 | 12 | Weapon: Knockback $+30\%$. Armor: Stun duration $-25\%$. |
| `mat_gem_24` | *Peridot Vitality Shard* | Raw Mineral | 2 | 99 | 10 | Armor: Health regeneration $+0.5\text{ HP/s}$. |
| `mat_gem_25` | *Neodymium Magnetite Geode*| Magnetic Core| 4 | 99 | 25 | Pulls dropped items and ammo from 8 tiles away. |
| `mat_gem_26` | *Sulfur Calcite Crystal*| Chemical Gem | 3 | 99 | 14 | Brewing high-yield blast flasks and thermite. |
| `mat_gem_27` | *Tourmaline Conduit Gem*| Electrical | 4 | 99 | 30 | Energy weapons consume $20\%$ less Power. |
| `mat_gem_28` | *Bloodstone Carnelian* | Bio-Crystal | 4 | 99 | 35 | Weapon: $+4\%$ Lifesteal on hit. Armor: $+5\%$ Rend resist. |
| `mat_gem_29` | *Cryo-Quartz Needle* | Sharp Crystal | 5 | 99 | 28 | Crafting piercing frost arrows and cryo-syringes. |
| `mat_gem_30` | *Radioactive Uranium Geode*| Nuclear Core | 5 | 99 | 60 | Powers Micro-Fission Cores and atomic grenades. |
| `mat_gem_31` | *Opal Rainbow Flakes* | Prismatic Dust| 6 | 99 | 45 | Ingredient in multi-elemental weapon enchantments. |
| `mat_gem_32` | *Lapis Lazuli Focus Stone*| Magic Stone | 3 | 99 | 20 | Enchanting bench catalyst; increases affix roll quality. |
| `mat_gem_33` | *Malachite Toxin Shard* | Toxic Mineral| 3 | 99 | 16 | Weapon: Inflicts Acid Bleed. Armor: $+25$ Acid resist. |
| `mat_gem_34` | *Adamantine Crystal Matrix*| Structural Gem| 6 | 99 | 110 | Hardens equipment; adds $+500$ Max Durability. |
| `mat_gem_35` | *Solar Flare Topaz* | Radiant Gem | 7 | 99 | 140 | Weapon: Attacks emit blinding flares of daylight. |
