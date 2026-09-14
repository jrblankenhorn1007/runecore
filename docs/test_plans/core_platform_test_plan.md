# Core Platform Test Plan

This test plan defines the unit tests, verification criteria, input conditions, expected outcomes, and edge cases for the core engine platform files (`src/core/`).

---

## 1. `Application` Test Suite (`src/core/Application.hpp/.cpp`)

### Test Case 1.1: Subsystem Initialization Success
- **Objective**: Verify that `Application::initialize` correctly bootstraps all platform dependencies when valid configuration is provided.
- **Input**: Valid `DisplayConfig` (1280x720, windowed, 60Hz).
- **Assertions**:
  - `initialize()` returns true.
  - Window handle is non-null.
  - Renderer is successfully created.
  - Initial simulation state is set to running.

### Test Case 1.2: Initialization Failure Recovery
- **Objective**: Verify that if display or video subsystem initialization fails, `Application::initialize` cleans up allocated memory and returns false gracefully.
- **Input**: Invalid display dimensions (e.g. 0x0) or forced failure of window creation.
- **Assertions**:
  - `initialize()` returns false.
  - No leaked handles or hanging window contexts remain.

### Test Case 1.3: Clean Shutdown Lifecycle
- **Objective**: Verify that calling `Application::shutdown` releases all GPU textures, UI contexts, and native windows without memory leaks.
- **Input**: An initialized application instance.
- **Assertions**:
  - Window handle is reset to null.
  - Renderer handle is reset to null.
  - Application running flag is set to false.

---

## 2. `Time` Test Suite (`src/core/Time.hpp/.cpp`)

### Test Case 2.1: Fixed Timestep Accumulator
- **Objective**: Verify that `Time::consumeFixedStep` consumes exact 1/60s (0.016667s) slices.
- **Input**: Simulate real elapsed frame delta of 0.050s (3 full ticks + 0.000s remaining).
- **Assertions**:
  - `consumeFixedStep()` returns true exactly 3 times consecutively.
  - Fourth call to `consumeFixedStep()` returns false.

### Test Case 2.2: Delta Time Spiral of Death Clamping
- **Objective**: Verify that massive delta time spikes (e.g. debugging pauses or window drags) are clamped to 0.25s maximum.
- **Input**: Simulate a frame lag spike of 2.50s.
- **Assertions**:
  - Recorded delta time is clamped to exactly 0.25s.
  - Accumulator increases by at most 0.25s, preventing physics freezing.

### Test Case 2.3: Alpha Interpolation Factor Calculation
- **Objective**: Verify that `Time::getAlpha` calculates the exact ratio of remaining accumulator to fixed timestep.
- **Input**: Accumulator has exactly 0.008333s remaining ($50\%$ of 1/60s).
- **Assertions**:
  - `getAlpha()` returns a floating-point value within 0.001 of 0.500.
  - Value is strictly bounded within $[0.0, 1.0]$.

---

## 3. `DisplayManager` Test Suite (`src/core/DisplayManager.hpp/.cpp`)

### Test Case 3.1: Primary Display Querying
- **Objective**: Verify `DisplayManager::detectNativeDisplay` returns positive dimensions and refresh rate.
- **Input**: Operating system display query.
- **Assertions**:
  - Returned width $> 0$ and height $> 0$.
  - Returned refresh rate $\ge 30\text{ Hz}$.

### Test Case 3.2: Resolution List Enumeration
- **Objective**: Verify supported standard resolutions are returned in ascending order.
- **Input**: Call `getAvailableResolutions()`.
- **Assertions**:
  - List contains 1280x720, 1920x1080, 2560x1440, and 3840x2160.
  - No duplicate resolutions exist.

---

## 4. `EventBus` Test Suite (`src/core/EventBus.hpp`)

### Test Case 4.1: Synchronous Event Delivery
- **Objective**: Verify that publishing an event invokes subscribed callbacks with accurate payload data.
- **Input**: Register a listener for `PlayerLeveledUpEvent{newLevel: 10}`. Publish event.
- **Assertions**:
  - Listener callback is executed exactly once.
  - Payload received matches `newLevel == 10`.

### Test Case 4.2: Unsubscription Integrity
- **Objective**: Verify that unsubscribing removes the callback and prevents future invocations.
- **Input**: Subscribe listener, obtain token, unsubscribe token, publish event.
- **Assertions**:
  - Listener callback is not called.

### Test Case 4.3: Multi-Subscriber Type Isolation
- **Objective**: Verify that listeners for Event Type A are not triggered when Event Type B is published.
- **Input**: Listener registered for `EnemyDiedEvent`; publish `CropHarvestedEvent`.
- **Assertions**:
  - `EnemyDiedEvent` listener is not invoked.

---

## 5. `AssetManager` Test Suite (`src/core/AssetManager.hpp/.cpp`)

### Test Case 5.1: Asset Caching & Deduplication
- **Objective**: Verify loading the same asset path twice returns the identical cached handle.
- **Input**: Call `loadTexture("sprites/player.png")` twice.
- **Assertions**:
  - Returned handles point to the exact same memory address.
  - Disk read occurs only on the first call.

### Test Case 5.2: Missing Asset Graceful Error Handling
- **Objective**: Verify loading a non-existent asset path returns null or fallback asset without crashing.
- **Input**: Call `loadTexture("non_existent_file.png")`.
- **Assertions**:
  - Method logs a warning and returns fallback missing-texture handle.
  - Application does not terminate unexpectedly.
