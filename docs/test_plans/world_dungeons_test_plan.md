# World, Procedural Dungeons & Bosses Test Plan

This test plan defines the unit tests, verification criteria, input conditions, expected outcomes, and edge cases for procedural dungeon generation, BSP leaf partitioning, room connectivity, multi-phase boss state machines, and death recovery drone drops (`src/procgen/`, `src/gameplay/ai/`).

---

## 1. `DungeonGenerator` Test Suite (`src/procgen/DungeonGenerator.hpp/.cpp`)

### Test Case 1.1: Guaranteed BFS Path Solvability
- **Objective**: Verify that 100% of generated dungeons have a valid, unblocked navigable path from Entrance to the Boss Arena.
- **Input**: Generate 100 distinct procedural dungeon layouts across different random seeds ($1$ to $100$) and all 20+ biomes.
- **Assertions**:
  - Breadth-First Search (BFS) pathfinder successfully discovers an unblocked path from the Entrance coordinate to the Boss Chamber door in all 100 iterations ($100\%$ pass rate).
  - No generation results in disjoint, unreachable room islands.

### Test Case 1.2: Minimum Room Dimension Enforcement
- **Objective**: Verify that BSP tree leaf partitioning never subdivides rooms smaller than the minimum navigable threshold ($16 \times 12$ tiles).
- **Input**: Run BSP subdivision to maximum recursion depth.
- **Assertions**:
  - Every generated room bounding box has $\text{width} \ge 16$ tiles and $\text{height} \ge 12$ tiles.

### Test Case 1.3: Autotile Edge Alignment
- **Objective**: Verify that solid block boundaries between rooms and corridors execute autotiling rules without missing collision tiles.
- **Input**: Generate dungeon layout and inspect boundary coordinates.
- **Assertions**:
  - All exterior walls have corresponding Box2D static chain shapes.
  - Zero hollow gaps or missing wall textures exist on map perimeter.

---

## 2. `BossStateMachine` Test Suite (`src/gameplay/ai/BossStateMachine.hpp/.cpp`)

### Test Case 2.1: Multi-Phase Health Threshold Transitions
- **Objective**: Verify that bosses transition to subsequent phases precisely when health reaches defined percentage thresholds.
- **Input**:
  - Spawn MK-1 Goliath Excavator (1,000 Max HP, Phase 2 threshold $= 500\text{ HP}$).
  - Deal 501 damage (remaining HP $= 499$).
- **Assertions**:
  - Boss current phase immediately updates from Phase 1 to Phase 2.
  - Boss clears ground tread movement and activates ceiling pipe grip behavior.
  - Attack pattern updates to oil drops and slam strikes.

### Test Case 2.2: The Architect 3-Phase Climax Transition
- **Objective**: Verify that The Architect advances through all 3 distinct phases before triggering victory.
- **Input**:
  - Step 1: Reduce Phase 1 (Orbital Matrix Relay) HP to 0 $\to$ Core detaches into Phase 2 (Transcendent Chimera Core).
  - Step 2: Reduce Phase 2 HP to 0 $\to$ Core collapses into Phase 3 (Singularity Avatar).
  - Step 3: Reduce Phase 3 HP to 0.
- **Assertions**:
  - Each phase transition triggers appropriate invulnerability frames, arena reconfiguration, and ability swaps.
  - Upon 0 HP in Phase 3, boss entity dies, campaign victory flag is set to true, and Infinite Rift portal entity spawns.

---

## 3. Death & Recovery Test Suite (`src/gameplay/items/LootSystem.hpp/.cpp`)

### Test Case 3.1: Retention of Equipped Gear & Augmentations
- **Objective**: Verify that character death in a dungeon preserves all equipped weapons, armor, accessories, and body augmentations.
- **Input**: Character with full equipment and 6 augmentations dies in a Tier 4 dungeon.
- **Assertions**:
  - Character consciousness respawns at Haven bed.
  - All 9 equipment slots remain intact and equipped.
  - All 11 augmentation slots remain intact and active.

### Test Case 3.2: 25% Raw Material Recovery Drone Drop
- **Objective**: Verify exactly 25% of carried raw salvage/materials are placed into a recovery drone at death coordinates, while remaining 75% stays in inventory.
- **Input**: Character carries 100x Scrap Metal, 40x Titanium Ore, and 1,000 Credits. Trigger death at dungeon coordinates $(450, 120)$.
- **Assertions**:
  - Character retains 75x Scrap Metal, 30x Titanium Ore, and 750 Credits upon respawn.
  - A Recovery Drone entity is spawned in the dungeon at $(450, 120)$ holding 25x Scrap Metal, 10x Titanium Ore, and 250 Credits.
  - Returning to $(450, 120)$ and interacting with the drone returns the exact dropped amounts to player inventory.
