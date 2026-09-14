# Items & Inventory Test Plan

This test plan defines the unit tests, verification criteria, input conditions, expected outcomes, and edge cases for item instantiation, Gaussian stat rolling, inventory storage, hotbar swapping, and equipment stat aggregation (`src/gameplay/items/`).

---

## 1. `ItemFactory` Test Suite (`src/gameplay/items/ItemFactory.hpp/.cpp`)

### Test Case 1.1: Triangular / Gaussian Stat Distribution Bounds
- **Objective**: Verify that rolled base stats are strictly bounded between defined minimum and maximum ranges, with higher frequency around the median.
- **Input**: Generate 1,000 instances of `wpn_gun_revolver_t3` with damage range $[32.0, 44.0]$ and Quality $= 0\%$.
- **Assertions**:
  - All 1,000 rolled damages fall strictly within $[32.0, 44.0]$.
  - The mean rolled damage is within $38.0 \pm 0.5$ (median convergence).
  - Outlier rolls (minimum $32.0$ to $33.0$ and maximum $43.0$ to $44.0$) occur in less than $5\%$ of instances.

### Test Case 1.2: Quality Modifier Influence
- **Objective**: Verify that an item's innate Quality ($0\%$ to $20\%$) skews base stat rolls upward proportionally.
- **Input**:
  - Sample A: Generate 500 instances with Quality $= 0\%$.
  - Sample B: Generate 500 instances with Quality $= 20\%$.
- **Assertions**:
  - Mean stat roll of Sample B is strictly higher than Sample A by at least $10\%$.
  - Maximum possible stat roll is clamped to $1.0\times$ maximum range without arithmetic overflow.

### Test Case 1.3: Dynamic Affix Budget per Rarity
- **Objective**: Verify that generated items contain exactly the number of affixes permitted by their rarity tier.
- **Input**: Generate 100 items of each rarity: Common, Uncommon, Rare, Epic, Legendary, Prismatic.
- **Assertions**:
  - Common: Exactly 0 affixes.
  - Uncommon: Exactly 1 affix.
  - Rare: Exactly 2 affixes.
  - Epic: Exactly 3 affixes.
  - Legendary: Exactly 4 affixes + 1 unique perk.
  - Prismatic: Exactly 5 affixes + 2 unique perks.

---

## 2. `InventorySystem` Test Suite (`src/gameplay/items/InventorySystem.hpp/.cpp`)

### Test Case 2.1: Stackable Item Consolidation
- **Input**: Inventory contains 1 slot with 80 Light Ammo (max stack 99). Add 30 Light Ammo.
- **Assertions**:
  - First slot quantity increases to 99.
  - A second slot is populated with the remaining 11 Light Ammo.
  - Total ammo recorded across inventory equals 110.

### Test Case 2.2: Full Inventory Rejection
- **Input**: All 8 hotbar slots and all 32 backpack slots are filled to capacity. Attempt to pick up a new unique item.
- **Assertions**:
  - `addItem()` returns false.
  - World dropped item entity remains untouched on the ground.
  - Player inventory contents remain unchanged.

### Test Case 2.3: Equipment Stat Aggregation
- **Input**: Equip Iron Breastplate (+20 Armor), Iron Helm (+12 Armor), and Titanium Ring (+15 Armor).
- **Assertions**:
  - Character total Armor increases by exactly $+47$.
  - Unequipping Iron Helm reduces total Armor to $+35$.

### Test Case 2.4: Weight & Encumbrance Penalties
- **Input**: Character has Max Carry Weight $= 60.0\text{ kg}$. Add heavy tungsten metal plates totaling $75.0\text{ kg}$ into backpack.
- **Assertions**:
  - `isEncumbered()` returns true.
  - Sprinting is disabled.
  - Movement speed drops by $40\%$.
