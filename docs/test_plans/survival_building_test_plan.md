# Survival, Building & Farming Test Plan

This test plan defines the unit tests, verification criteria, input conditions, expected outcomes, and edge cases for hunger/thirst depletion, ambient temperature calculations, 16x16 grid settlement construction, and agricultural crop growth (`src/gameplay/survival/`, `src/gameplay/building/`, `src/gameplay/farming/`).

---

## 1. `SurvivalSystem` Test Suite (`src/gameplay/survival/SurvivalSystem.hpp/.cpp`)

### Test Case 1.1: Hunger & Thirst Baseline Decay Rates
- **Objective**: Verify hunger depletes by 1 point per 18 seconds, and thirst depletes by 1 point per 12 seconds under resting conditions.
- **Input**: Character starts at 100 Hunger and 100 Thirst. Step simulation for 360 seconds (6 real minutes).
- **Assertions**:
  - Hunger decreases by exactly $\frac{360}{18} = 20$ points (remaining: 80).
  - Thirst decreases by exactly $\frac{360}{12} = 30$ points (remaining: 70).

### Test Case 1.2: Physical Exertion Acceleration
- **Objective**: Verify that sprinting, continuous weapon swings, or pickaxe mining accelerates hunger depletion by $1.5\times$.
- **Input**: Character continuously sprints for 180 seconds.
- **Assertions**:
  - Hunger decreases by $180 / 18 \times 1.5 = 15$ points (compared to 10 points at rest).

### Test Case 1.3: Starvation Health Damage (0 Hunger)
- **Objective**: Verify reaching 0 Hunger disables sprinting, caps maximum stamina at 50%, and ticks 1% Max HP damage every 3 seconds.
- **Input**: Set player Hunger to 0.0 with Max HP $= 200$. Step simulation for 15 seconds.
- **Assertions**:
  - `canSprint()` returns false.
  - Max stamina is capped at $50\%$.
  - Player takes 5 damage ticks of 2 HP each (total 10 HP lost).

### Test Case 1.4: Ambient Temperature & Heat Source Offset
- **Objective**: Verify effective body temperature equals: $\text{Ambient} + \text{TimeOfDay} + \text{NearbyHeatSources} - \text{ArmorInsulation}$.
- **Input**:
  - Biome Ambient: $-20^\circ\text{C}$ (Cryo-Glacier).
  - Armor Cold Insulation: $+15^\circ\text{C}$.
  - Adjacent Campfire: $+20^\circ\text{C}$.
- **Assertions**:
  - Effective temperature equals $-20 + 15 + 20 = +15^\circ\text{C}$ (Comfortable).
  - Player does not suffer freezing damage.

---

## 2. `GridPlacement` Test Suite (`src/gameplay/building/GridPlacement.hpp/.cpp`)

### Test Case 2.1: 16x16 Grid Snapping & Adjacency
- **Objective**: Verify world block placement snaps strictly to integer multiples of 16 pixels and requires adjacency to existing solid blocks.
- **Input**:
  - Attempt to place block at floating-point coordinate $(17.4, 33.8)$.
  - Attempt to place block floating in mid-air with 0 adjacent neighbors.
  - Place block adjacent to existing ground block.
- **Assertions**:
  - Coordinate is snapped to $(16, 32)$.
  - Floating placement fails with `NoAdjacency` error.
  - Adjacent placement succeeds and places block entity.

### Test Case 2.2: Player Collider Overlap Rejection
- **Objective**: Verify the player cannot place solid blocks directly overlapping their own character collision box.
- **Input**: Attempt to place a solid stone block at the player's exact center coordinates.
- **Assertions**:
  - Placement is rejected with `CollisionOverlap` error.
  - Material is not consumed from inventory.

---

## 3. `FarmingSystem` Test Suite (`src/gameplay/farming/FarmingSystem.hpp/.cpp`)

### Test Case 3.1: Soil Tilling & Hydration Gate
- **Objective**: Verify tilled soil advances crop growth stages only when hydrated.
- **Input**:
  - Plant Rust-Wheat on unhydrated dry soil for 3 simulated days.
  - Plant Rust-Wheat on hydrated soil for 3 simulated days.
- **Assertions**:
  - Unhydrated crop remains at Stage 0 (Sprout).
  - Hydrated crop advances through Sprout $\to$ Blooming $\to$ Mature (Stage 3).

### Test Case 3.2: Mature Crop Harvesting
- **Objective**: Verify harvesting a mature crop drops harvested produce and seeds, resetting or clearing the soil tile.
- **Input**: Interact with Stage 3 mature Rust-Wheat.
- **Assertions**:
  - Yields 2 to 4 Rust-Wheat grain items.
  - Yields 1 to 2 Rust-Wheat seeds.
  - Crop tile resets to tilled soil.
