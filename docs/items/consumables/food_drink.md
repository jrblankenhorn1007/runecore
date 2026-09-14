# Food, Meals, Drinks & Hydration Consumables Catalog

This document specifies the individual nutritional values (Hunger and Thirst restoration), temperature offsets, buff durations, and health regeneration effects for food items and beverages across Untitled RPG (~130 consumable definitions).

---

## 1. Mechanics & Digestion Parameters
- **Hunger Pool**: 0 to 100 points. Food restores Hunger. At 0 Hunger, the player suffers starving health damage.
- **Thirst Pool**: 0 to 100 points. Beverages restore Thirst. At 0 Thirst, stamina regeneration drops to zero.
- **Temperature Interaction**: Hot foods (Soups, Chilis, Mulled Cider) raise body temperature by $+10^\circ\text{C}$ to $+25^\circ\text{C}$ to prevent freezing. Chilled drinks (Iced Tea, Hydro-Melon) lower body temperature by $-10^\circ\text{C}$ to $-20^\circ\text{C}$ to prevent heatstroke.
- **Buff Exclusivity**: Players can maintain 1 active Food buff and 1 active Beverage buff simultaneously. Consuming a higher-tier meal refreshes or overrides the active buff.

---

## 2. Complete Food & Meals Catalog

| ID | Name | Hunger Restored | Thirst Restored | Temp Effect | Buff Granted | Duration |
|---|---|---|---|---|---|---|
| `con_fd_01` | *Raw Berries* | 10 | 5 | 0 | None | Instant |
| `con_fd_02` | *Raw Game Venison* | 25 | 0 | 0 | 25% Food Poisoning risk | Instant |
| `con_fd_03` | *Baked Rust-Bread* | 35 | -5 | 0 | $+5$ Max Stamina | 10 mins |
| `con_fd_04` | *Hardtack Cracker* | 15 | -5 | 0 | None (never spoils) | Instant |
| `con_fd_05` | *Roasted Game Steak* | 50 | 0 | +5°C | $+5\text{ HP/s}$ regen | 10 secs |
| `con_fd_06` | *Charbroiled River Trout*| 40 | 10 | +5°C | $+5\%$ Swimming speed | 15 mins |
| `con_fd_07` | *Hearty Vegetable Stew* | 60 | 30 | +15°C | $+10\%$ Max Health | 15 mins |
| `con_fd_08` | *Spicy Glazed Ribs* | 80 | -10 | +25°C | $+15\%$ Melee Damage, Cold Resist | 15 mins |
| `con_fd_09` | *Hydro-Melon Slice* | 20 | 45 | -15°C | Heatstroke Immunity | 10 mins |
| `con_fd_10` | *Mushroom Skewer* | 35 | 0 | +5°C | $+15$ Max Mana | 12 mins |
| `con_fd_11` | *Smoked Jerky Strips* | 25 | -5 | 0 | None (lasts indefinitely) | Instant |
| `con_fd_12` | *Trench Ration Hash* | 65 | 5 | +10°C | $+12$ Armor rating | 15 mins |
| `con_fd_13` | *Roasted Cave Bat Wings*| 30 | 0 | +5°C | $+5\%$ Dodge Evasion | 10 mins |
| `con_fd_14` | *Seared Raptor Cutlet* | 70 | 0 | +10°C | $+10\%$ Movement Speed | 15 mins |
| `con_fd_15` | *Crispy Fried Beetle Legs*| 15 | 0 | 0 | None | Instant |
| `con_fd_16` | *Boiled Rust-Corn Cob* | 30 | 5 | +5°C | $+10$ Max Stamina | 10 mins |
| `con_fd_17` | *Stuffed Bell Peppers* | 75 | 10 | +10°C | $+50$ Max Stamina | 15 mins |
| `con_fd_18` | *Fisherman's Chowder* | 65 | 40 | +20°C | $+25$ Cold Resistance | 20 mins |
| `con_fd_19` | *Garlic Roasted Potatoes*| 55 | 0 | +10°C | $+1.5\text{ HP/s}$ regen | 15 mins |
| `con_fd_20` | *Glazed Honey Ham* | 95 | 0 | +10°C | $+100$ Max Health | 20 mins |
| `con_fd_21` | *Carrot Ginger Puree* | 40 | 15 | +10°C | Cures Nausea and Weakness | Instant |
| `con_fd_22` | *Trail Nut Mix* | 40 | -5 | 0 | Fast Eating (0.2s consume) | Instant |
| `con_fd_23` | *Savory Meat Pie* | 85 | 0 | +15°C | $+10\%$ Physical Melee Dmg | 15 mins |
| `con_fd_24` | *Spicy Monster Curry* | 80 | 15 | +30°C | $+40$ Cold Resist, $+10\%$ Fire Dmg| 20 mins |
| `con_fd_25` | *Chilled Melon Gazpacho*| 35 | 50 | -20°C | Extreme Heat Immunity | 15 mins |
| `con_fd_26` | *Sweet Berry Tart* | 45 | 0 | +5°C | $+25$ Max Mana | 15 mins |
| `con_fd_27` | *Golden Apple Compote* | 50 | 20 | 0 | $+15\%$ to All Primary Stats | 15 mins |
| `con_fd_28` | *Boiled River Crab* | 50 | 10 | +10°C | $+10$ Armor rating | 12 mins |
| `con_fd_29` | *Grilled Swamp Eel* | 55 | 5 | +10°C | $+20$ Shock Resistance | 15 mins |
| `con_fd_30` | *Wild Herb Omelette* | 45 | 0 | +5°C | $+8\%$ Critical Strike Chance | 12 mins |
| `con_fd_31` | *Scorched Lizard Tail* | 40 | 0 | +15°C | $+25$ Heat Resistance | 15 mins |
| `con_fd_32` | *Rich Bone Marrow Broth*| 40 | 25 | +20°C | $+10\text{ HP/s}$ rapid heal | 30 secs |
| `con_fd_33` | *Aged Cheese Wheel* | 60 | -10 | 0 | $+15$ Armor rating | 15 mins |
| `con_fd_34` | *Kimchi Ferment Pot* | 45 | 5 | +15°C | $+15\%$ Stamina recovery rate | 15 mins |
| `con_fd_35` | *The Haven Grand Banquet*| 100 | 50 | +15°C | $+20\%$ Damage, $+100$ Max HP | 24 mins |

---

## 3. Complete Beverages & Hydration Catalog

| ID | Name | Thirst Restored | Hunger Restored | Temp Effect | Special Effect |
|---|---|---|---|---|---|
| `con_bv_01` | *Contaminated Water Bottle* | 40 | 0 | 0 | 50% Parasite infection risk |
| `con_bv_02` | *Boiled Clean Water* | 50 | 0 | 0 | Pure hydration, safe |
| `con_bv_03` | *Purified Mineral Spring Water*| 75 | 0 | 0 | $+10\%$ Stamina regen 10 mins |
| `con_bv_04` | *Electrolyte Stim-Flask* | 50 | 0 | 0 | Restores 50 Stamina, $+30$ Power |
| `con_bv_05` | *Mountain Peppermint Tea* | 45 | 0 | -10°C | Cures fatigue, cools body |
| `con_bv_06` | *Hot Spiced Apple Cider* | 45 | 5 | +20°C | $+15$ Cold Resistance |
| `con_bv_07` | *Black Roast Coffee* | 40 | 0 | +10°C | $+20\%$ Sprint speed 8 mins |
| `con_bv_08` | *Chamomile Sleep Infusion*| 40 | 0 | +5°C | Restores 100% HP during bed rest |
| `con_bv_09` | *Fermented Honey Mead* | 35 | 5 | +10°C | $+10\%$ Melee Damage, $-5\%$ accuracy |
| `con_bv_10` | *Dark Malt Foundry Ale* | 35 | 10 | +10°C | $+15\%$ Damage, knockback resist |
| `con_bv_11` | *Corn Mash Whiskey* | 25 | 0 | +25°C | Stops hypothermia shivering |
| `con_bv_12` | *Wild Sweet Berry Wine* | 35 | 5 | +5°C | $+25$ Max Mana 12 mins |
| `con_bv_13` | *Energy Stim-Cola* | 45 | 5 | 0 | $+12\%$ Movement speed 6 mins |
| `con_bv_14` | *Pasteurized Goat Milk* | 50 | 10 | 0 | Cleanses 1 negative status effect |
| `con_bv_15` | *Iced Herbal Pitcher* | 70 | 0 | -25°C | Cures heatstroke, $+20$ Heat Resist |
| `con_bv_16` | *Mulled Winter Wine* | 40 | 5 | +25°C | $+30$ Cold Resistance |
| `con_bv_17` | *Symbiotic Bio-Kombucha*| 45 | 0 | 0 | $+20\%$ Poison/Acid Resistance |
| `con_bv_18` | *Dandelion Detox Tonic* | 40 | 0 | 0 | Cleanses all liver poisons |
| `con_bv_19` | *Roasted Barley Tea* | 50 | 0 | 0 | Zero caffeine, steady hydration |
| `con_bv_20` | *Pure Aether Drop Nectar*| 60 | 20 | 0 | Restores 100 Mana, $+2.0\text{ MP/s}$ |
