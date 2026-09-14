# Potions, Tonics, Draughts & Medicinal Remedies Catalog

This document specifies the individual healing values, mana restoration, stamina acceleration, elemental protection, and status cleansing properties for potions and medicinal brews across Untitled RPG (~100 potion definitions).

---

## 1. Potion Mechanics & Brewing Parameters
- **Brewing Station**: Brewed at the Arcane Loom, Bio-Vat, or Alchemical Crucible using glass vials, water, and harvested flora.
- **Consumption Speed**: Instant drinking animation (0.4s). Can be consumed during combat movement.
- **Stack Size**: Maximum 20 potions per inventory slot.
- **Tiers of Potency**: Minor (Tier 1), Standard (Tier 2-3), Greater (Tier 4-5), Superior (Tier 6-7), and Elixir of the Gods (Tier 8 / Prismatic).

---

## 2. Complete Potions & Medicine Catalog

| ID | Name | Category | Tier | Health / Mana Restored | Buff / Effect Granted | Duration |
|---|---|---|---|---|---|---|
| `con_pot_01` | *Minor Healing Potion* | Healing | 1 | 50 HP instant | None | Instant |
| `con_pot_02` | *Standard Healing Potion* | Healing | 2 | 120 HP instant | None | Instant |
| `con_pot_03` | *Greater Healing Potion* | Healing | 4 | 250 HP instant | $+5\text{ HP/s}$ regen | 5 secs |
| `con_pot_04` | *Superior Healing Potion*| Healing | 6 | 500 HP instant | $+15\text{ HP/s}$ regen | 8 secs |
| `con_pot_05` | *Elixir of Full Restoration*| Healing | 8 | 100% HP & Mana | Cleanses all debuffs | Instant |
| `con_pot_06` | *Minor Mana Draught* | Mana | 1 | 40 Mana instant | None | Instant |
| `con_pot_07` | *Standard Mana Draught* | Mana | 2 | 100 Mana instant | None | Instant |
| `con_pot_08` | *Greater Mana Draught* | Mana | 4 | 220 Mana instant | $+1.5\text{ MP/s}$ regen | 10 secs |
| `con_pot_09` | *Superior Mana Draught* | Mana | 6 | 450 Mana instant | Spell cost $-20\%$ | 15 secs |
| `con_pot_10` | *Stamina Stimulant Tonic*| Stamina | 1 | Restores 50 Stamina | $+50\%$ Stamina regen | 5 mins |
| `con_pot_11` | *Greater Stamina Tonic* | Stamina | 4 | Restores 100 Stamina | $+100\%$ Stamina regen | 8 mins |
| `con_pot_12` | *Universal Antidote* | Cleansing | 2 | None | Cleanses Poison, Venoms & Acid | Instant |
| `con_pot_13` | *Burn Soothing Salve* | Cleansing | 2 | Restores 40 HP | Extinguishes Burn, $+20$ Heat Resist| 5 mins |
| `con_pot_14` | *Thawing Pepper Elixir* | Cleansing | 2 | None | Cleanses Freeze, $+25$ Cold Resist| 5 mins |
| `con_pot_15` | *Iron-Skin Potion* | Defensive | 3 | None | $+25$ Armor rating | 8 mins |
| `con_pot_16` | *Diamond-Skin Elixir* | Defensive | 5 | None | $+60$ Armor, knockback resist | 10 mins |
| `con_pot_17` | *Swiftfoot Agility Potion*| Utility | 2 | None | $+15\%$ Movement Speed | 6 mins |
| `con_pot_18` | *Cheetah Velocity Draught*| Utility | 5 | None | $+30\%$ Move & Sprint Speed | 8 mins |
| `con_pot_19` | *Night-Owl Vision Tincture*| Utility | 2 | None | Full night vision, reveals traps | 10 mins |
| `con_pot_20` | *Feather-Fall Draught* | Utility | 3 | None | Zero environmental fall damage | 5 mins |
| `con_pot_21` | *Gilled Diver Potion* | Utility | 3 | None | Infinite underwater breath hold | 10 mins |
| `con_pot_22` | *Invisibility Phial* | Stealth | 4 | None | Complete invisibility | 30 secs |
| `con_pot_23` | *Deadeye Precision Potion*| Combat | 3 | None | $+15\%$ Critical Strike Chance | 5 mins |
| `con_pot_24` | *Executioner's Elixir* | Combat | 6 | None | $+0.50\times$ Crit Multiplier | 6 mins |
| `con_pot_25` | *Arcane Power Potion* | Combat | 3 | None | $+20\%$ Spell Damage | 6 mins |
| `con_pot_26` | *Archmage Solar Phial* | Combat | 6 | None | $+40\%$ Holy & Arcane Damage | 8 mins |
| `con_pot_27` | *Pyromancer's Flame Draft*| Combat | 4 | None | $+35\%$ Fire Damage, attacks ignite| 6 mins |
| `con_pot_28` | *Cryomancer's Frost Draft*| Combat | 4 | None | $+35\%$ Frost Damage, attacks chill| 6 mins |
| `con_pot_29` | *Electromancer's Spark Vial*| Combat| 4 | None | $+35\%$ Shock Damage, chains arcs | 6 mins |
| `con_pot_30` | *Titan's Brawn Elixir* | Utility | 3 | None | $+35\text{ kg}$ Carry Weight Capacity | 15 mins |
| `con_pot_31` | *Sterile Field Bandage* | Medical | 1 | 40 HP over 6s | Stops Bleeding instantly | 6 secs |
| `con_pot_32` | *Nanite Trauma Kit* | Medical | 3 | 150 HP over 4s | Heals broken limb status | 4 secs |
| `con_pot_33` | *Automated Medical Syringe*| Medical | 5 | 300 HP over 3s | Grants 3s invulnerability frames | 3 secs |
| `con_pot_34` | *Rad-X Anti-Radiation Phial*| Medical| 3 | None | Cleanses radiation sickness | Instant |
| `con_pot_35` | *Sanity Restoring Draught*| Medical | 4 | None | Restores 20 Humanity points | Instant |
