# Functions & API Reference Specification

This document provides the complete functional specification for all planned classes, systems, and free functions across the Untitled RPG codebase. It outlines function responsibilities, input parameters, return values, expected state mutations, and error handling behaviors without implementation code.

---

## 1. Core Platform Layer (`src/core/`)

### 1.1 `Application` (`src/core/Application.hpp/.cpp`)
- `initialize(Config config) -> Boolean`:
  - Initializes platform subsystems (SDL3 video, audio, gamepads), creates native application window via `DisplayManager`, instantiates `Renderer`, initializes `InputManager`, and constructs the primary `SimulationCore`. Returns true if all systems initialize successfully; logs critical failure and returns false otherwise.
- `run() -> Void`:
  - Runs the main application loop: polls OS events, accumulates delta time, triggers deterministic fixed simulation steps at 60 Hz, invokes interpolated rendering, and presents frames.
- `shutdown() -> Void`:
  - Releases all graphical render targets, closes open audio streams, terminates UI contexts, destroys the native window, and calls SDL subsystem shutdowns cleanly.
- `processEvents() -> Void`:
  - Drains the SDL event queue, routes raw input events to `InputManager` and Dear ImGui, and processes global application events (e.g. window resize, close request, focus lost).
- `stepSimulation(Float fixedDeltaTime) -> Void`:
  - Dispatches one fixed tick to the active game state, stepping character physics, AI behaviors, combat hitboxes, survival timers, and world generation.

### 1.2 `Time` (`src/core/Time.hpp/.cpp`)
- `update() -> Void`:
  - Samples high-resolution system clock, calculates frame elapsed delta time, clamps delta to maximum threshold (0.25s) to prevent physics spirals, adds delta to the fixed-step accumulator, and increments total frame count.
- `consumeFixedStep() -> Boolean`:
  - Checks if accumulator is greater than or equal to 1/60s (0.016667s). If true, subtracts 1/60s from accumulator and returns true; otherwise returns false.
- `getAlpha() -> Float`:
  - Returns fractional ratio of remaining accumulator divided by 1/60s (value in range 0.0 to 1.0) used for sub-pixel render position interpolation.
- `getDeltaTime() -> Float`: Returns elapsed real delta time of the most recent frame.
- `getTotalTime() -> Float`: Returns total simulation uptime in seconds.

### 1.3 `DisplayManager` (`src/core/DisplayManager.hpp/.cpp`)
- `detectNativeDisplay() -> DisplayConfig`:
  - Queries OS via SDL3 for primary monitor physical pixel dimensions, color bit depth, and refresh rate. Returns a populated configuration defaulting to Borderless Fullscreen at native resolution.
- `applyDisplayMode(WindowHandle window, DisplayConfig config) -> Boolean`:
  - Reconfigures the native window mode (Fullscreen, Borderless, Windowed), dimensions, and V-Sync state. Handles macOS Retina scaling factors.
- `getAvailableResolutions() -> List<Resolution>`:
  - Enumerates all supported standard resolutions (720p, 1080p, 1440p, 4K, 16:10 MacBook native, Ultrawide).

### 1.4 `EventBus` (`src/core/EventBus.hpp`)
- `subscribe<EventType>(CallbackFunction handler) -> SubscriptionToken`:
  - Registers a listener callback for a specific event type. Returns a subscription handle used for deregistration.
- `unsubscribe(SubscriptionToken token) -> Void`:
  - Removes a registered callback from the listener registry.
- `publish<EventType>(EventType eventData) -> Void`:
  - Immediately dispatches event data synchronously to all subscribed listeners in order of registration.

### 1.5 `AssetManager` (`src/core/AssetManager.hpp/.cpp`)
- `loadTexture(String assetPath) -> TextureHandle`:
  - Loads a PNG sprite sheet into GPU memory, caching it by path. Returns cached handle on subsequent calls.
- `loadFont(String fontPath, Integer pointSize) -> FontHandle`:
  - Loads TrueType font glyphs rendered for a specific pixel size.
- `loadJSON(String dataPath) -> JSONDocument`:
  - Reads and parses a structured data file from `assets/data/`.
- `unloadAll() -> Void`:
  - Flushes all cached textures, fonts, and documents from RAM and VRAM during scene transitions.

---

## 2. Rendering Pipeline (`src/render/`)

### 2.1 `Renderer` (`src/render/Renderer.hpp/.cpp`)
- `initialize(WindowHandle window, DisplayConfig config) -> Boolean`:
  - Creates the SDL3 hardware-accelerated renderer and allocates the low-resolution internal virtual canvas texture with nearest-neighbor scaling.
- `beginScene() -> Void`:
  - Binds the internal virtual canvas as the active render target, clearing it to the ambient background color.
- `endScene() -> Void`:
  - Rebinds the native window backbuffer, clears the backbuffer with black pillarbox/letterbox margins, calculates the maximum integer scaling factor, and renders the scaled virtual canvas centered in the viewport.
- `present() -> Void`:
  - Swaps GPU backbuffers, respecting active V-Sync settings.
- `drawFilledRect(Float x, Float y, Float width, Float height, Color color) -> Void`:
  - Renders a colored quad directly to the active canvas.

### 2.2 `Camera` (`src/render/Camera.hpp/.cpp`)
- `update(Vector2 targetPosition, Float deltaTime) -> Void`:
  - Smoothly interpolates camera center toward target (player) within deadzone margins, clamping viewport coordinates to level boundary extremes.
- `addTrauma(Float amount) -> Void`:
  - Adds screen shake trauma (clamped 0.0 to 1.0) caused by explosions or heavy impacts.
- `applyShake() -> Vector2`:
  - Computes sinusoidal camera offset from squared trauma, decaying trauma over time.
- `worldToScreen(Vector2 worldCoordinates) -> Vector2`:
  - Translates world coordinates into pixel-snapped screen viewport coordinates.

### 2.3 `TilemapRenderer` (`src/render/TilemapRenderer.hpp/.cpp`)
- `loadMap(String mapFilePath) -> MapData`:
  - Parses Tiled `.tmj` file, extracting tileset references, tile layer grids, collision layers, and object spawn markers.
- `renderLayer(String layerName, Camera camera) -> Void`:
  - Iterates visible tile coordinates within camera bounding box, drawing corresponding 16x16 pixel sprites from the cached atlas.

### 2.4 `LightingSystem` (`src/render/LightingSystem.hpp/.cpp`)
- `setAmbientLight(Float darknessFactor, Color tint) -> Void`:
  - Sets darkness overlay opacity driven by the day/night cycle and subterranean depth.
- `addPointLight(Vector2 worldPosition, Float radiusPixels, Color lightColor) -> Void`:
  - Stamps a soft additive radial light mask into the lighting buffer (for torches, campfires, and laser blasts).
- `compositeLighting() -> Void`:
  - Multiplies the light buffer over the scene before UI rendering.

---

## 3. Input & Controls (`src/input/`)

### 3.1 `InputManager` (`src/input/InputManager.hpp/.cpp`)
- `update() -> Void`:
  - Copies current action states to previous frame states, clearing relative mouse deltas.
- `handleEvent(RawInputEvent event) -> Void`:
  - Translates raw SDL keyboard, mouse, and gamepad events into abstract gameplay actions (`Action::MoveLeft`, `Action::Jump`, `Action::AttackPrimary`, etc.).
- `isActionDown(Action action) -> Boolean`: Returns true if the action key is currently held down.
- `isActionPressed(Action action) -> Boolean`: Returns true only on the initial frame the action was triggered.
- `isActionReleased(Action action) -> Boolean`: Returns true only on the frame the action was released.
- `getCursorWorldPosition(Camera camera) -> Vector2`:
  - Translates current mouse screen coordinate through camera transform into world space coordinates for weapon aiming.

---

## 4. Physics & Movement (`src/physics/`)

### 4.1 `PhysicsWorld` (`src/physics/PhysicsWorld.hpp/.cpp`)
- `initialize(Vector2 gravity) -> Void`:
  - Constructs Box2D v3 simulation world with standard downward gravitational acceleration.
- `step(Float fixedDeltaTime) -> Void`:
  - Advances dynamic Box2D physics bodies, resolves sensor overlap triggers, and updates transform matrices.
- `createStaticChainBody(List<Vector2> vertices, CollisionCategory category) -> BodyHandle`:
  - Creates smooth edge/chain static bodies for tilemap collision without internal seam snags.

### 4.2 `KinematicController` (`src/physics/KinematicController.hpp/.cpp`)
- `update(EntityHandle entity, InputState input, Float deltaTime) -> Void`:
  - Executes platformer movement: applies horizontal acceleration and friction, evaluates ground raycasts, manages variable jump impulse based on jump key duration, ticks coyote time (0.08s window after leaving a ledge), and processes jump buffering (0.1s early press memory).
- `handleWallInteractions(EntityHandle entity) -> Void`:
  - Detects vertical wall proximity, applies wall-cling friction reduction, and enables wall-jumping.
- `handleOneWayPlatforms(EntityHandle entity, Boolean dropDownRequested) -> Void`:
  - Toggles collision filtering to permit dropping down through wooden platforms when pressing Down + Jump.

---

## 5. Combat & Damage Pipeline (`src/gameplay/combat/`)

### 5.1 `CombatSystem` (`src/gameplay/combat/CombatSystem.hpp/.cpp`)
- `spawnAttackHitbox(EntityHandle attacker, WeaponDefinition weapon, Vector2 aimDirection) -> EntityHandle`:
  - Instantiates a short-lived kinematic sensor hitbox entity oriented along the aim vector. Initializes a hit-deduplication list containing only the attacker ID.
- `resolveHitboxOverlap(EntityHandle hitbox, EntityHandle targetHurtbox) -> Void`:
  - Checks if target ID is present in the hitbox's hit-deduplication list. If present, ignores contact. If absent, adds target ID to the list and routes attack data into `calculateDamage`.
- `calculateDamage(DamageContext context) -> DamageResult`:
  - Implements the complete damage pipeline: weapon base damage $\to$ primary attribute scaling $\to$ tree modifier multiplication $\to$ critical strike evaluation $\to$ target armor mitigation ($Damage \times (1 - \frac{Armor}{Armor + 100})$) $\to$ elemental resistance subtraction.
- `applyDamage(EntityHandle target, DamageResult result) -> Void`:
  - Subtracts net damage from target health, generates floating combat text entity, applies knockback impulse vector, checks for lethal damage (triggering death event), and applies status effects.
- `triggerHitstop(Integer frameCount) -> Void`:
  - Freezes gameplay physics simulation for 2 to 4 frames while keeping visual rendering active to convey weight.

### 5.2 `StatusEffectSystem` (`src/gameplay/combat/StatusEffectSystem.hpp/.cpp`)
- `applyStatusEffect(EntityHandle target, StatusEffectType type, Float duration, Float potency) -> Void`:
  - Adds or refreshes a status component (Burn, Freeze, Shock, Toxin, Bleed, Stun) on the target entity.
- `tickEffects(Float fixedDeltaTime) -> Void`:
  - Advances timers on all active status effects, ticks damage over time, enforces movement locks on Freeze/Stun, and cleanses expired status components.

---

## 6. Skills & Leveling (`src/gameplay/skills/` & `src/gameplay/stats/`)

### 6.1 `SkillTreeManager` (`src/gameplay/skills/SkillTreeManager.hpp/.cpp`)
- `canAllocateNode(EntityHandle player, String skillId) -> Boolean`:
  - Evaluates whether the player has available skill points, meets tree depth requirements, and has unlocked all prerequisite parent nodes in the DAG.
- `allocateNode(EntityHandle player, String skillId) -> Boolean`:
  - Spends 1 skill point, increments node rank, applies passive stat modifications to the player, and unlocks dependent downstream nodes.
- `respecTree(EntityHandle player, String treeId) -> Void`:
  - Deducts gold fee, resets all allocated nodes in the tree, cleanses granted passive stat bonuses, and refunds all points to the available point pool.

### 6.2 `ActiveSkillSystem` (`src/gameplay/skills/ActiveSkillSystem.hpp/.cpp`)
- `assignSkillToHotbar(EntityHandle player, Integer slotIndex, String skillId) -> Boolean`:
  - Binds an active skill to one of the 4 hotkey slots (`Q`, `E`, `R`, `F`).
- `triggerHotbarSkill(EntityHandle player, Integer slotIndex) -> Boolean`:
  - Checks resource availability (Stamina, Mana, or Power) and active cooldown timer. If valid, deducts resource, initiates cooldown timer, plays cast animation, and spawns the ability entity (projectile, shockwave, or defensive ward).

### 6.3 `UniversalMastery` (`src/gameplay/skills/UniversalMastery.hpp/.cpp`)
- `unlockNeuralBridge(EntityHandle player) -> Boolean`:
  - Verifies character is Level 60+. Unlocks cross-class skill point investment across all 9 class trees.

---

## 7. Augmentations & The Dual Economy (`src/gameplay/augmentations/`)

### 7.1 `AugmentationManager` (`src/gameplay/augmentations/AugmentationManager.hpp/.cpp`)
- `canEquipAugmentation(EntityHandle player, AugmentationDefinition augment) -> EquipCheckResult`:
  - Validates slot compatibility (1 of 11 body slots), checks character level requirement, verifies Power capacity headroom, and checks if cross-class exotic surgery conditions are met.
- `equipAugmentation(EntityHandle player, AugmentationDefinition augment) -> Boolean`:
  - Places augment into designated body slot, deducts Humanity cost, reserves passive Power, records Mana upkeep, and binds granted active/passive abilities.
- `unequipAugmentation(EntityHandle player, BodySlot slot) -> Boolean`:
  - Removes augment from slot, restores Humanity, releases Power reservation, and unbinds associated abilities.
- `updateDualEconomy(EntityHandle player, Float fixedDeltaTime) -> Void`:
  - Ticks continuous power and mana regeneration. If Power reaches 0, disables active bionic functions and applies move speed penalty. If Mana reaches 0 while wearing chimeric grafts, triggers Cellular Rejection damage ticks.

---

## 8. Items, Loot & Crafting (`src/gameplay/items/` & `src/gameplay/crafting/`)

### 8.1 `ItemFactory` (`src/gameplay/items/ItemFactory.hpp/.cpp`)
- `createItemInstance(String baseItemId, Float qualityBonus) -> ItemInstance`:
  - Looks up base item definition, rolls individual base stats using triangular probability distributions, applies quality scaling, rolls affixes matching rarity tier budget, and returns unique instantiated data object.

### 8.2 `InventorySystem` (`src/gameplay/items/InventorySystem.hpp/.cpp`)
- `addItem(InventoryComponent& inventory, ItemInstance item) -> Boolean`:
  - Searches hotbar and backpack for matching stackable slots under max capacity. If found, increments stack; otherwise places item in first empty slot. Returns false if inventory is completely full.
- `removeItem(InventoryComponent& inventory, Integer slotIndex, Integer quantity) -> Boolean`:
  - Decrements slot count, clearing the slot if quantity reaches zero.
- `equipItem(EntityHandle player, Integer sourceSlotIndex, EquipmentSlot targetSlot) -> Boolean`:
  - Moves item from backpack/hotbar into equipment slot, swapping with existing equipped item if present, and recalculates aggregate player equipment stats.

### 8.3 `ModificationForge` (`src/gameplay/crafting/ModificationForge.hpp/.cpp`)
- `infuseStatShard(ItemInstance& item, StatShardItem shard) -> ModificationResult`:
  - Inserts chosen stat into an empty affix slot at Tier 1, incrementing item Instability.
- `upgradeStatTier(ItemInstance& item, Integer affixIndex) -> ModificationResult`:
  - Checks item Instability against fracture probability. If successful, advances affix to next higher tier (Tier 1 to 7) and raises Instability. If fracture occurs, flags item as Fractured, prohibiting future modifications.
- `calibrateValues(ItemInstance& item, CalibrationCore core) -> ModificationResult`:
  - Re-rolls the numerical values of all active affixes within their existing tier minimum and maximum bounds.
- `punchSocket(ItemInstance& item) -> Boolean`:
  - Adds a gem/rune socket to item up to category maximum.

---

## 9. Procedural Dungeon Generation (`src/procgen/`)

### 9.1 `DungeonGenerator` (`src/procgen/DungeonGenerator.hpp/.cpp`)
- `generateDungeon(BiomeType biome, Integer depthTier, Integer randomSeed) -> DungeonLayout`:
  - Coordinates BSP space partitioning, sockets biome-specific prefab rooms (combat, treasure, puzzle), connects rooms via horizontal and vertical corridors, applies 16x16 autotile rules, places entrance/exit gates, and attaches the terminal boss chamber.
- `validateLayout(DungeonLayout layout) -> Boolean`:
  - Executes Breadth-First Search (BFS) pathfinding between Entrance and Boss Arena, asserting guaranteed traversal connectivity without blocking geometry.

---

## 10. Persistence & Saves (`src/save/`)

### 10.1 `SaveManager` (`src/save/SaveManager.hpp/.cpp`)
- `saveGame(Integer slotIndex, GameState state) -> Boolean`:
  - Serializes character attributes, uncapped skill trees, installed augmentations, inventory items, settlement tile grid modifications, and world flags into JSON. Writes to disk atomically with SHA-256 checksum validation.
- `loadGame(Integer slotIndex) -> GameState`:
  - Reads save file, validates checksum against tampering, deserializes data objects, reconstructs ECS entities, and restores world state.
