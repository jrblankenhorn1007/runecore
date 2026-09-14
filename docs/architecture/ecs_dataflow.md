# Entity Component System (ECS) & Dataflow Architecture

This document specifies the internal Entity Component System architecture, memory layout, entity lifecycles, and system execution graphs for Untitled RPG using **EnTT**.

---

## 1. Core Principles of ECS in Untitled RPG

1. **Entities as Lightweight Identifiers**:
   - Entities are simple unsigned 32-bit integer identifiers (`entt::entity`) that serve as keys into component pools. Entities have zero methods and hold zero direct state.
2. **Pure Data Components (PODs)**:
   - Components are plain data structs. They contain no game logic, no virtual dispatch, and no cross-component pointers. Component memory is packed contiguously inside sparse sets managed by EnTT, guaranteeing maximum CPU L1/L2 cache locality during batch processing.
3. **Stateless Systems**:
   - Systems are free functions or lightweight functors that take a reference to the active `entt::registry` and delta time. Systems query matching component views/groups, iterate contiguous component arrays sequentially, and publish state changes to the `EventBus`.

---

## 2. Component Taxonomy & Layouts

```
[Entity Archetypes]
 ├── Player Entity        -> Transform, Velocity, KinematicController, Stats, Attributes,
 │                           Inventory, Equipment, Augmentations, Health, Stamina, Mana, Power
 ├── Enemy Entity         -> Transform, Velocity, AIBehavior, Stats, Health, Box2DCollider,
 │                           LootDropTable, StatusEffects
 ├── Projectile Entity    -> Transform, Velocity, ProjectileData, Box2DSensor, Lifetime
 ├── Placed Block Entity  -> GridCoordinate, StructuralBlock, Durability, Flammable
 ├── Dropped Item Entity  -> Transform, Box2DDynamicBody, ItemInstance, PickupSensor
 └── Sensor Hitbox Entity -> Transform, Box2DSensor, DamagePayload, HitDeduplicationList
```

### 2.1 Spatial & Physical Components
- `TransformComponent`: World X and Y coordinates (floating-point sub-pixel positions), rotation angle in radians, and scale factors.
- `PreviousTransformComponent`: Previous tick transform coordinates used to calculate alpha sub-pixel interpolation for the visual renderer.
- `VelocityComponent`: Linear velocity vector $(v_x, v_y)$ and maximum speed thresholds.
- `PhysicsBodyComponent`: Wrapper around the Box2D body handle, tracking body type (Static, Kinematic, or Dynamic) and active fixture filters.

### 2.2 Gameplay & Combat Components
- `AttributesComponent`: Core attributes (Strength, Dexterity, Intelligence, Vitality, Wisdom, Cyber-Affinity).
- `StatsComponent`: Aggregate derived statistics (Max Health, Max Stamina, Max Mana, Max Power, Armor, Critical Chance, Critical Multiplier, Movement Speed).
- `HealthComponent`: Current health points, invulnerability frame counter, and regeneration timer.
- `StaminaComponent`: Current stamina points, exertion drain rate, and recharge delay timer.
- `ManaComponent`: Current mana points, continuous spell upkeep reservations, and regeneration rate.
- `PowerComponent`: Current electrical power capacity, passive bionic reservations, and generation rate.
- `StatusEffectsComponent`: Dynamic container of active timed conditions (Burn, Freeze, Shock, Toxin, Bleed, Stun).

### 2.3 Inventory, Augmentation & Progression Components
- `InventoryComponent`: 8-slot hotbar array, 32-slot backpack array, active hotbar index, and carried mass tracking.
- `EquipmentComponent`: Equipped armor slots (Head, Chest, Legs, Boots), weapon slots (Main Hand, Off Hand), and accessory slots (Ring 1, Ring 2, Amulet).
- `AugmentationComponent`: 11 body slot instances, net Humanity penalty, and active Stability upkeep.
- `SkillProgressionComponent`: Class tree node allocations, shared tree node allocations, available unspent points, and active 4-key hotbar bindings (`Q`, `E`, `R`, `F`).

---

## 3. System Execution Graph & Update Phasing

During each 60 Hz simulation tick, systems execute in strict phased dependency order:

```
[Phase 1: Input & Intent Resolution]
 ├── InputActionSystem: Translates raw keyboard/mouse into PlayerIntentComponent.
 └── AIPerceptionSystem: Updates enemy sensory cones and targets nearest hostiles.

[Phase 2: Movement & Kinematic Planning]
 ├── KinematicControllerSystem: Applies walk, jump impulse, coyote time, and wall cling.
 └── PathfindingSystem: Computes enemy steering vectors along navmesh grids.

[Phase 3: Physics Step & Sensor Queries]
 ├── PhysicsWorldStep: Advances Box2D v3 simulation by 1/60s.
 └── RaycastGroundCheckSystem: Validates terrain contact and updates grounded flags.

[Phase 4: Combat Overlaps & Damage Pipeline]
 ├── HitboxSpawnSystem: Creates kinematic attack sensors oriented to aim vectors.
 ├── HitboxResolutionSystem: Resolves overlaps, deducts hit-deduplication, calculates damage.
 └── ProjectileImpactSystem: Explodes missiles, penetrates targets, applies impact impulses.

[Phase 5: Status Effects & Resource Simulation]
 ├── StatusEffectSystem: Advances timers, ticks burn/bleed/toxin damage, cleanses expired debuffs.
 ├── DualEconomySystem: Evaluates Power drain and Chimeric Cellular Rejection.
 └── SurvivalMeterSystem: Ticks hunger and thirst decay, evaluates thermal exposure.

[Phase 6: World, Environment & Lifecycle]
 ├── DayNightCycleSystem: Advances diurnal clocks, updates ambient darkness parameters.
 ├── CropGrowthSystem: Hydrates tilled soil and advances plant growth stages.
 └── EntityReaperSystem: Despawns dead entities, drops loot, and triggers recovery drones.
```
