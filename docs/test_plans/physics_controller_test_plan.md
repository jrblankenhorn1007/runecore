# Physics & Kinematic Controller Test Plan

This test plan defines the unit tests, verification criteria, input conditions, expected outcomes, and edge cases for the physics wrapper and character movement controller files (`src/physics/`).

---

## 1. `PhysicsWorld` Test Suite (`src/physics/PhysicsWorld.hpp/.cpp`)

### Test Case 1.1: World Gravitational Step
- **Objective**: Verify that dynamic bodies accelerate downward under standard gravity.
- **Input**: Spawn dynamic body at $(0, 10)$ with velocity $(0, 0)$. Step world by $0.1\text{ s}$.
- **Assertions**:
  - Y position is less than $10.0$ (falling downward).
  - Y velocity is negative and equals $-9.8 \times 0.1 \pm 0.05$.

### Test Case 1.2: Static Chain Edge Collision without Seam Snags
- **Objective**: Verify that a kinematic capsule sliding horizontally across adjacent static chain segments experiences no vertical velocity catches.
- **Input**: Create two collinear static edge shapes joining at $(10, 0)$. Move body horizontally at $5.0\text{ m/s}$ across coordinate $x = 10$.
- **Assertions**:
  - Body passes seamlessly across the seam without vertical pop or stoppage.
  - Horizontal velocity remains constant.

---

## 2. `KinematicController` Test Suite (`src/physics/KinematicController.hpp/.cpp`)

### Test Case 2.1: Horizontal Acceleration and Ground Friction
- **Objective**: Verify horizontal movement accelerates smoothly to maximum run speed and halts cleanly when input ceases.
- **Input**: Hold MoveRight input for $0.5\text{ s}$, then release input on grounded character.
- **Assertions**:
  - Velocity increases up to base run speed ($6.0\text{ m/s}$).
  - Upon release, ground friction decelerates velocity to exactly $0.0\text{ m/s}$ within $0.15\text{ s}$.

### Test Case 2.2: Variable Jump Height via Button Release Cutoff
- **Objective**: Verify that tapping the jump button produces a short hop while holding the jump button achieves maximum jump height.
- **Input**:
  - Scenario A: Press jump for 1 frame ($0.016\text{ s}$), then release.
  - Scenario B: Hold jump for full duration ($0.30\text{ s}$).
- **Assertions**:
  - Maximum apex reached in Scenario A is at least $40\%$ lower than apex reached in Scenario B.
  - Upward velocity is truncated immediately upon jump release in Scenario A.

### Test Case 2.3: Coyote Time Jump Leniency
- **Objective**: Verify that the character can successfully jump within a 0.08s window after running off a ledge.
- **Input**: Walk character off a cliff edge into air. Issue Jump command at $t = 0.05\text{ s}$ after leaving the ground.
- **Assertions**:
  - Jump executes successfully with full upward impulse.
  - Grounded flag is cleared immediately.

### Test Case 2.4: Jump Input Buffering
- **Objective**: Verify that pressing the jump button up to 0.1s before touching the ground triggers an immediate jump upon landing.
- **Input**: Character is falling through the air $0.5$ tiles above ground. Press Jump $0.06\text{ s}$ before ground contact.
- **Assertions**:
  - Jump input is buffered.
  - The exact frame ground contact occurs, the buffered jump consumes and launches character upward.

### Test Case 2.5: One-Way Platform Drop-Through
- **Objective**: Verify pressing Down + Jump while standing on a wooden one-way platform disables collision and drops character downward.
- **Input**: Character standing on wooden platform entity. Send `Action::MoveDown` and `Action::Jump`.
- **Assertions**:
  - Collision mask between character and platform is temporarily disabled for $0.25\text{ s}$.
  - Character falls through the platform.

### Test Case 2.6: Wall-Cling & Wall-Jump Impulse
- **Objective**: Verify pushing against a vertical wall slows descent speed and allows kicking off in the opposite direction.
- **Input**: Character contacts vertical wall while in air holding MoveLeft into wall. Press Jump.
- **Assertions**:
  - Descent fall speed is capped at $25\%$ of normal terminal velocity.
  - Jumping imparts an impulse angled up and away from the wall (positive X, positive Y).

---

## 3. `Raycaster` Test Suite (`src/physics/Raycaster.hpp/.cpp`)

### Test Case 3.1: Ground Detection Distance
- **Objective**: Verify raycast detects solid terrain within specified skin width distance.
- **Input**: Cast ray downward from character feet ($1.0$ tile above solid block).
- **Assertions**:
  - Returns hit true.
  - Hit distance matches exactly $1.0$ tile.
  - Hit surface normal vector is $(0, 1)$ pointing upward.
