# Physics Simulation & Collision Matrix Specification

This document specifies the physics integration, collision category filtering, character kinematic sweeps, and raycasting systems in Untitled RPG using **Box2D v3**.

---

## 1. Hybrid Physics Architecture

Untitled RPG utilizes a **hybrid physics model**:
1. **Humanoids & Creatures (Kinematic/Custom Controller)**:
   - Platformer characters (the player, humanoid NPCs, and ground enemies) are driven by custom kinematic logic rather than direct rigid-body dynamics.
   - Ground friction, variable jumping, coyote time, and wall sliding feel floaty and unresponsive if driven purely by default rigid body forces. Instead, the character controller directly sets kinematic linear velocities while using Box2D raycasts and shape-casts to detect terrain obstacles and ground edges.
2. **Projectiles, Loot & Debris (Dynamic Rigid Bodies)**:
   - Thrown grenades, arrows, falling boulders, severed mechanical parts, and dropped loot items are real Box2D dynamic bodies subjected to gravity, restitution, air drag, and rotational torque.
3. **Terrain & Structures (Static Chain Bodies)**:
   - Solid tilemap boundaries are welded into continuous static edge/chain shapes to prevent internal seam catches.

---

## 2. Collision Category Bitmask Matrix

To ensure that bullets only hit intended targets, sensors do not block walking, and dropped items bounce off the floor without impeding player movement, collision interactions are governed by 16-bit category masks:

```
[Collision Categories]
 0x0001: CategoryWorldSolid      (Static terrain, placed blocks, closed doors)
 0x0002: CategoryPlayerHurtbox   (Player character body hurtbox)
 0x0004: CategoryEnemyHurtbox    (Hostile enemy hurtboxes)
 0x0008: CategoryPlayerAttack    (Sensor hitboxes spawned by player weapons/spells)
 0x0010: CategoryEnemyAttack     (Sensor hitboxes spawned by enemy attacks)
 0x0020: CategoryDynamicLoot     (Dropped items and recovery drones)
 0x0040: CategoryOneWayPlatform  (Wooden platforms that allow drop-through)
 0x0080: CategoryTriggerSensor   (Door sensors, room triggers, quest zones)
 0x0100: CategoryProjectile      (Arrows, ballistic bullets, missiles)
```

### 2.1 Interaction Rules Table

| Source Category | Collides / Overlaps With | Ignored Categories |
|---|---|---|
| **WorldSolid** | PlayerHurtbox, EnemyHurtbox, DynamicLoot, Projectile | PlayerAttack, EnemyAttack, TriggerSensor |
| **PlayerHurtbox** | WorldSolid, OneWayPlatform, EnemyAttack, TriggerSensor | PlayerAttack, DynamicLoot |
| **EnemyHurtbox** | WorldSolid, OneWayPlatform, PlayerAttack, TriggerSensor | EnemyAttack, DynamicLoot |
| **PlayerAttack** | EnemyHurtbox, WorldSolid (for projectiles) | PlayerHurtbox, DynamicLoot, OneWayPlatform |
| **EnemyAttack** | PlayerHurtbox, WorldSolid (for projectiles) | EnemyHurtbox, DynamicLoot, OneWayPlatform |
| **DynamicLoot** | WorldSolid, OneWayPlatform | PlayerHurtbox, EnemyHurtbox, Attacks |
| **Projectile** | WorldSolid, Opposing Hurtbox | Friendly Hurtbox, Loot, Triggers |

---

## 3. Kinematic Controller Pipeline

The `KinematicController` manages humanoids through 5 sequential verification steps per fixed tick:

```
[1. Gather Input & Intent] ── (Move Left/Right, Jump Press/Hold, Dash, Aim Vector)
           │
           ▼
[2. Sensor Raycasts & Environment Probes]
   ├── Ground Raycasts: 3 downward probes (Left Foot, Center, Right Foot)
   ├── Ceiling Probes: 2 upward probes to stop upward velocity on head bonk
   └── Wall Probes: 2 horizontal probes for wall-cling and ledge clambering
           │
           ▼
[3. State Machine Transitions]
   ├── Grounded (Walking, Sprinting, Idle, Crouching)
   ├── Airborne (Jumping, Apex Float, Falling, Coyote Window)
   ├── Wall-Clinging (Sliding down wall, Wall-Jumping)
   └── Dashing (Fixed velocity burst, i-frames active)
           │
           ▼
[4. Velocity Resolution & Collision Sweeps]
   ├── Apply horizontal acceleration and ground/air friction
   ├── Apply vertical gravity acceleration (reduced at jump apex for float feel)
   └── Test Box2D kinematic sweep along proposed delta movement vector
           │
           ▼
[5. Final Position Integration] ── Update Box2D body transform and TransformComponent
```
