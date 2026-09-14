# Crafting & Stat Modification Test Plan

This test plan defines the unit tests, verification criteria, input conditions, expected outcomes, and edge cases for recipe crafting, station validation, stat shard infusion, tier upgrading, instability tracking, fracture mechanics, and affix sealing (`src/gameplay/crafting/`).

---

## 1. `CraftingBench` Test Suite (`src/gameplay/crafting/CraftingBench.hpp/.cpp`)

### Test Case 1.1: Recipe Ingredient Deduction & Output
- **Objective**: Verify that crafting an item consumes the exact required quantities of raw materials and outputs the crafted item.
- **Input**: Player inventory contains 6x Scrap Wood and 2x Iron Scrap. Craft `Scrap Wooden Door` (requires 6x Wood, 1x Iron).
- **Assertions**:
  - `craftRecipe()` returns true.
  - Exactly 6x Scrap Wood and 1x Iron Scrap are removed from inventory.
  - Remaining 1x Iron Scrap is preserved.
  - 1x `Scrap Wooden Door` is placed in player inventory.

### Test Case 1.2: Insufficient Material Rejection
- **Objective**: Verify that crafting fails if even 1 required reagent is missing or below required count.
- **Input**: Recipe requires 10x Titanium Ingot. Player possesses 9x Titanium Ingot.
- **Assertions**:
  - `craftRecipe()` returns false.
  - Zero materials are deducted.
  - No item is produced.

### Test Case 1.3: Station Proximity Requirement Gate
- **Objective**: Verify that advanced metal and electronic recipes cannot be crafted unless the player is within 4 tiles of the required crafting station.
- **Input**: Player has all materials for `Steel Ingot` (requires Blast Forge) but is standing 15 tiles away from the station.
- **Assertions**:
  - Crafting request is rejected with `StationOutOfRange` error.

---

## 2. `ModificationForge` Test Suite (`src/gameplay/crafting/ModificationForge.hpp/.cpp`)

### Test Case 2.1: Affix Infusion into Empty Slot
- **Objective**: Verify infusing a stat shard into an item with an empty slot attaches that stat at Tier 1 and raises Instability.
- **Input**: Rare weapon with 1 populated affix and 1 empty affix slot (Instability $= 0$). Infuse *Shard of Striking* (+Physical Dmg).
- **Assertions**:
  - Affix slot is populated with `Tier 1 Physical Damage`.
  - Item Instability increases from 0 to between 5 and 15.
  - Second empty slot count becomes 0.

### Test Case 2.2: Tier Upgrading Success
- **Objective**: Verify that upgrading an existing affix on an item with low instability advances it to the next tier cleanly.
- **Input**: Weapon with Tier 2 Volcanic (+12 Fire Dmg, Instability $= 10$). Trigger tier upgrade.
- **Assertions**:
  - Affix advances to `Tier 3 Volcanic` (+18 Fire Dmg).
  - Instability increases appropriately.
  - Item is not fractured.

### Test Case 2.3: Instability & Fracture Lockout
- **Objective**: Verify that when item Instability is high, an upgrade attempt can result in a Fracture, permanently prohibiting further modifications.
- **Input**: Weapon with Instability $= 90$. Trigger tier upgrade that rolls a fracture failure.
- **Assertions**:
  - Item flag `isFractured` is set to true.
  - Current stats and affixes are fully retained and usable in combat.
  - Subsequent calls to `infuseStatShard()`, `upgradeStatTier()`, or `calibrateValues()` are rejected immediately with `ItemFracturedException`.

### Test Case 2.4: Numerical Calibration within Tier Bounds
- **Objective**: Verify that using a Nanite Calibration Core re-rolls existing affix values strictly within their current tier min/max bounds without altering the tier itself.
- **Input**: Weapon with Tier 3 Physical Dmg ($[16.0, 22.0]$, current value $= 16.0$). Apply calibration core.
- **Assertions**:
  - New value falls strictly within $[16.0, 22.0]$.
  - Affix tier remains Tier 3.

### Test Case 2.5: Stasis Sealing Independence
- **Objective**: Verify that applying a Stasis Seal permanently locks the chosen affix, preventing it from being rerolled, and frees up its slot against the normal maximum affix cap.
- **Input**: Legendary item with 4 affixes. Apply Stasis Seal to Affix 1.
- **Assertions**:
  - Affix 1 is flagged as `isSealed = true`.
  - Item gains 1 additional usable empty affix slot (allowing a total of 5 affixes).
  - Calling `scrambleAffixes()` re-rolls Affixes 2, 3, and 4 while leaving Affix 1 completely untouched.
