# Combat & Damage Pipeline Test Plan

This test plan defines the unit tests, verification criteria, input conditions, expected outcomes, and edge cases for the combat engine, damage calculation pipeline, status effect systems, and projectile physics (`src/gameplay/combat/`).

---

## 1. `CombatSystem` Test Suite (`src/gameplay/combat/CombatSystem.hpp/.cpp`)

### Test Case 1.1: Base Damage & Primary Attribute Scaling
- **Objective**: Verify that weapon base damage scales accurately with primary attributes.
- **Input**:
  - Weapon Base Damage: $50.0$.
  - Scaling Attribute: STR $= 20$.
  - Scaling Formula: $\text{Scaled} = \text{Base} \times (1.0 + \text{STR} \times 0.015)$.
- **Assertions**:
  - Computed scaled damage equals $50.0 \times (1.0 + 20 \times 0.015) = 50.0 \times 1.30 = 65.0$.

### Test Case 1.2: Armor Mitigation Curve
- **Objective**: Verify that armor mitigates damage according to the formula: $\text{Reduction} = \frac{\text{Armor}}{\text{Armor} + 100}$.
- **Input**:
  - Scenario A: Incoming Damage $= 100$, Target Armor $= 0$.
  - Scenario B: Incoming Damage $= 100$, Target Armor $= 100$ ($50\%$ reduction).
  - Scenario C: Incoming Damage $= 100$, Target Armor $= 300$ ($75\%$ reduction).
- **Assertions**:
  - Scenario A final damage $= 100.0$.
  - Scenario B final damage $= 50.0$.
  - Scenario C final damage $= 25.0$.

### Test Case 1.3: Minimum Damage Clamping
- **Objective**: Verify that regardless of how high target armor is, attacks always deal at least 1 point of damage.
- **Input**: Incoming Damage $= 10$, Target Armor $= 10,000$.
- **Assertions**:
  - Final damage taken is strictly clamped to $\ge 1$.

### Test Case 1.4: Critical Strike Multiplier
- **Objective**: Verify critical hits multiply damage by the character's crit multiplier.
- **Input**: Base damage $= 100$, Crit Multiplier $= 1.50\times$, forced critical hit roll.
- **Assertions**:
  - Final damage equals $150.0$.
  - Critical strike flag in damage result is true.

### Test Case 1.5: Hit-Deduplication per Swing Lifecycle
- **Objective**: Verify that a multi-frame lingering swing hitbox only damages an overlapping hurtbox once during its attack duration.
- **Input**: Spawn sensor hitbox overlapping a target dummy entity for 10 consecutive simulation ticks.
- **Assertions**:
  - Target dummy takes damage exactly once on Tick 1.
  - Ticks 2 through 10 register zero additional damage to that target ID.

### Test Case 1.6: Hitstop Simulation Pause
- **Objective**: Verify that landing a heavy or critical hit pauses physics simulation ticks for the specified frame count while keeping renderer clock advancing.
- **Input**: Trigger critical strike with 3-frame hitstop setting.
- **Assertions**:
  - Simulation core skips physics integration for exactly 3 ticks.
  - On the 4th tick, normal simulation resumes seamlessly.

---

## 2. `StatusEffectSystem` Test Suite (`src/gameplay/combat/StatusEffectSystem.hpp/.cpp`)

### Test Case 2.1: Burn Periodic Damage Ticking
- **Objective**: Verify Burn ticks damage every 0.5 seconds for 5.0 seconds (total 10 ticks) and expires cleanly.
- **Input**: Apply Burn (10 damage per tick) to target entity. Step simulation for $5.5\text{ s}$.
- **Assertions**:
  - Target takes 10 damage at each 0.5s interval.
  - Total health lost over duration is exactly 100.
  - At $t = 5.0\text{ s}$, Burn component is removed from entity.

### Test Case 2.2: Freeze Movement Lock & Shatter Bonus
- **Objective**: Verify Freeze prevents all movement and taking a heavy blunt hit triggers shatter bonus damage.
- **Input**: Apply Freeze (2.5s duration) to target. Attempt movement input. Strike with heavy hammer.
- **Assertions**:
  - Target velocity remains $(0, 0)$ despite movement input.
  - Heavy hammer attack deals $+50\%$ bonus shatter damage.
  - Freeze condition clears upon shatter.

### Test Case 2.3: Shock Chain Propagation Count
- **Objective**: Verify Shock chains electrical arcs to up to 2 adjacent targets within 4 tiles, but no further.
- **Input**: 4 enemy dummies positioned in a row 3 tiles apart. Apply Shock to Dummy 1.
- **Assertions**:
  - Dummy 1 takes initial electric damage.
  - Dummy 2 and Dummy 3 take chain shock damage.
  - Dummy 4 takes 0 damage (chain limit of 2 reached).

---

## 3. `ProjectileSystem` Test Suite (`src/gameplay/combat/ProjectileSystem.hpp/.cpp`)

### Test Case 3.1: Ballistic Trajectory & Gravity Arching
- **Objective**: Verify ballistic projectiles experience downward gravitational acceleration over long distances.
- **Input**: Fire arrow with horizontal velocity $20.0\text{ m/s}$, vertical velocity $0.0\text{ m/s}$. Step simulation by $0.5\text{ s}$.
- **Assertions**:
  - Projectile Y coordinate drops below origin height.
  - Downward velocity equals $-9.8 \times 0.5 = -4.9\text{ m/s}$.

### Test Case 3.2: Piercing Projectile Penetration Limit
- **Objective**: Verify sniper rifle slug penetrates up to 4 targets and despawns on the 5th target contact.
- **Input**: Fire piercing slug through 6 aligned enemy hurtboxes.
- **Assertions**:
  - Enemies 1 through 4 take damage.
  - Projectile entity is destroyed upon striking Enemy 5.
  - Enemy 6 takes 0 damage.
