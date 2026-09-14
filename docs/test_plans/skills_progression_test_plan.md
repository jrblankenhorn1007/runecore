# Skills & Progression Test Plan

This test plan defines the unit tests, verification criteria, input conditions, expected outcomes, and edge cases for skill trees, uncapped leveling, hotbar execution, and universal mastery (`src/gameplay/skills/` & `src/gameplay/stats/`).

---

## 1. `SkillTreeManager` Test Suite (`src/gameplay/skills/SkillTreeManager.hpp/.cpp`)

### Test Case 1.1: DAG Prerequisite Enforcement
- **Objective**: Verify that a skill node cannot be unlocked if its prerequisite parent nodes have not been allocated.
- **Input**: Attempt to allocate `skill_air_dash` (requires `skill_double_jump`) while `skill_double_jump` rank is 0.
- **Assertions**:
  - `canAllocateNode()` returns false.
  - `allocateNode()` fails and returns false.
  - Player skill points remain unchanged.

### Test Case 1.2: Point Spending and Rank Incrementing
- **Objective**: Verify that allocating a valid node spends exactly 1 skill point and increments rank.
- **Input**: Player has 3 available skill points. Allocate valid Tier 1 skill `skill_swiftfoot` (Rank 0/3).
- **Assertions**:
  - `allocateNode()` returns true.
  - `skill_swiftfoot` rank becomes 1.
  - Available skill points decrement to 2.

### Test Case 1.3: Max Rank Clamping
- **Objective**: Verify that a node cannot be allocated beyond its defined maximum rank.
- **Input**: Node `skill_double_jump` has `maxRanks = 1`. Allocate it twice with 5 available skill points.
- **Assertions**:
  - First allocation succeeds (Rank becomes 1, points decrement to 4).
  - Second allocation returns false.
  - Rank remains 1, points remain 4.

### Test Case 1.4: Respec Point Refund Equality
- **Objective**: Verify that resetting a skill tree refunds the exact number of spent points and unapplies all passive stat bonuses.
- **Input**: Allocate 12 points into Warrior tree (+20 Armor passive granted). Call `respecTree()`.
- **Assertions**:
  - Available class skill points increase by exactly 12.
  - All Warrior tree node ranks reset to 0.
  - Granted +20 Armor bonus is removed from player stats.

---

## 2. `ActiveSkillSystem` Test Suite (`src/gameplay/skills/ActiveSkillSystem.hpp/.cpp`)

### Test Case 2.1: Hotbar Assignment Validation
- **Objective**: Verify active skills can be assigned to slots 0 through 3 (`Q`, `E`, `R`, `F`), but passive skills cannot.
- **Input**: Assign passive skill `skill_plated_sinew` to Slot Q; assign active skill `skill_seismic_shockwave` to Slot Q.
- **Assertions**:
  - Passive assignment fails and returns false.
  - Active assignment succeeds and returns true.

### Test Case 2.2: Resource Gating (Stamina, Mana, Power)
- **Objective**: Verify that triggering an active skill without sufficient resource fails and does not initiate cooldown.
- **Input**: Skill requires 30 Mana. Player currently has 15 Mana. Press skill hotkey.
- **Assertions**:
  - `triggerHotbarSkill()` returns false.
  - Player Mana remains at 15.
  - Skill cooldown timer remains at 0.0s.

### Test Case 2.3: Cooldown Gating & Countdown
- **Objective**: Verify that an active skill cannot be triggered while its cooldown timer is active, and the timer decrements correctly.
- **Input**: Trigger skill with 8.0s cooldown with sufficient resources. Immediately attempt to trigger again. Step simulation by 4.0s.
- **Assertions**:
  - First trigger succeeds, resource is deducted, cooldown becomes 8.0s.
  - Immediate second trigger fails.
  - After 4.0s, remaining cooldown is exactly 4.0s.
  - After 8.0s, cooldown becomes 0.0s and skill can be cast again.

---

## 3. `LevelingSystem` Test Suite (`src/gameplay/stats/LevelingSystem.hpp/.cpp`)

### Test Case 3.1: Uncapped XP Requirement Equation
- **Objective**: Verify XP requirement formula matches: $\text{XP Required}(L) = 150 \times L^{1.85} + 50 \times L$.
- **Input**: Calculate required XP for Level 1, Level 10, Level 60, and Level 100.
- **Assertions**:
  - Level 1: $150 \times 1^{1.85} + 50 = 200\text{ XP}$.
  - Level 60 and Level 100 return finite, monotonically increasing positive integers.
  - Leveling never caps at Level 60; Level 61, 62, etc., remain achievable.

### Test Case 3.2: Level-up Reward Allocation
- **Objective**: Verify each level-up grants exactly 3 attribute points, 1 class skill point, and 1 shared skill point.
- **Input**: Award sufficient XP to level up from Level 4 to Level 5.
- **Assertions**:
  - Available attribute points increase by 3.
  - Available class points increase by 1.
  - Available shared points increase by 1.
  - `PlayerLeveledUpEvent` is published.

---

## 4. `UniversalMastery` Test Suite (`src/gameplay/skills/UniversalMastery.hpp/.cpp`)

### Test Case 4.1: Level 60 Neural Bridge Requirement Gate
- **Objective**: Verify that characters below Level 60 cannot invest points into non-native class trees, while characters Level 60+ can.
- **Input**:
  - Character A: Level 59 Warrior attempting to allocate a Mage skill.
  - Character B: Level 60 Warrior attempting to allocate a Mage skill.
- **Assertions**:
  - Character A allocation is rejected.
  - Character B allocation succeeds and unlocks the cross-class node.
