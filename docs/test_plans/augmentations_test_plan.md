# Augmentations & Dual Economy Test Plan

This test plan defines the unit tests, verification criteria, input conditions, expected outcomes, and edge cases for the 11-slot body augmentation system and dual-track biological/technological economy (`src/gameplay/augmentations/`).

---

## 1. `AugmentationManager` Test Suite (`src/gameplay/augmentations/AugmentationManager.hpp/.cpp`)

### Test Case 1.1: 11 Body Slot Compatibility Enforcement
- **Objective**: Verify that an augmentation can only be installed into its designated body slot.
- **Input**:
  - Scenario A: Attempt to install *Plasma Jet Boots* (Legs slot) into the Left Arm slot.
  - Scenario B: Install *Plasma Jet Boots* into the Legs slot.
- **Assertions**:
  - Scenario A fails with slot mismatch error.
  - Scenario B succeeds and equips into Legs slot.

### Test Case 1.2: Cumulative Humanity Subtraction
- **Objective**: Verify that installing bionic augmentations subtracts humanity accurately from mortal baseline (100).
- **Input**:
  - Install *Titanium-Carbide Ribs* ($-10$ Humanity).
  - Install *Synaptic Accelerator* ($-12$ Humanity).
- **Assertions**:
  - Net character Humanity equals $100 - 10 - 12 = 78$.
  - Unequipping *Synaptic Accelerator* restores Humanity to 90.

### Test Case 1.3: Low Humanity Threshold Buff & Debuffs
- **Objective**: Verify that dropping below 50 Humanity halves external healing, and dropping below 20 Humanity applies the "Cyber-Overclock" state.
- **Input**: Install heavy bionics reducing Humanity to 18.
- **Assertions**:
  - Magical healing received modifier equals $0.25$ (reduced by $75\%$).
  - Character receives the `CyberOverclock` buff component ($+15\%$ attack speed, immune to mental debuffs).

### Test Case 1.4: Passive Power Reservation
- **Objective**: Verify that bionics with passive power draw reserve that amount from maximum power capacity.
- **Input**: Character has Max Power $= 100$. Equip *Subdermal Shield* (reserves 15 Power) and *Ocular Scanner* (reserves 10 Power).
- **Assertions**:
  - Available usable Power capacity becomes $100 - 25 = 75$.

---

## 2. `DualEconomy` Test Suite (`src/gameplay/augmentations/DualEconomy.hpp/.cpp`)

### Test Case 2.1: Power Depletion Behavior (0 Power)
- **Objective**: Verify that when electrical Power reaches 0, bionic abilities fail to execute and character suffers movement speed penalties.
- **Input**: Drain player Power to 0.0 units. Attempt to fire *Arm-Mounted Laser Cannon*. Check movement speed.
- **Assertions**:
  - Laser cannon fails to fire.
  - Movement speed is reduced by $30\%$.

### Test Case 2.2: Chimeric Mana Upkeep & Cellular Rejection
- **Objective**: Verify that chimeric grafts drain continuous mana upkeep, and dropping to 0 Mana triggers cellular rejection damage ticks.
- **Input**: Equip *Chimeric Ursine Arm* ($0.8\text{ MP/s}$ upkeep). Set player Mana to 0. Step simulation for $3.0\text{ s}$.
- **Assertions**:
  - Mana drain ticks continuously while Mana $> 0$.
  - When Mana $= 0$, `CellularRejection` status component attaches to player.
  - Player takes $2\%$ Max HP bleed damage every second until Mana is restored above $10\%$.

### Test Case 2.3: Hybrid Power Crystal Synergy
- **Objective**: Verify that socketing an *Astral Power Crystal* in the Heart slot generates both Power and Mana, supporting both bionic and chimeric systems simultaneously.
- **Input**: Equip *Dual Aether-Plasma Core* ($+10\text{ Power/s}$, $+1.0\text{ MP/s}$). Step simulation for $5.0\text{ s}$.
- **Assertions**:
  - Stored Power increases by 50 units.
  - Stored Mana increases by 5.0 units.

---

## 3. `CyberClinic` Test Suite (`src/gameplay/augmentations/CyberClinic.hpp/.cpp`)

### Test Case 3.1: Level 20 Free Signature Augmentation
- **Objective**: Verify that when a character reaches Level 20, their native class signature augmentation installs with zero credit fee, zero humanity cost, and zero stability upkeep.
- **Input**: Level 20 Juggernaut visits clinic to receive *Integrated Hydraulic Piston Core*.
- **Assertions**:
  - Credit balance does not change (free).
  - Net Humanity remains 100 (0 penalty).
  - Piston Core equips into Torso slot successfully.

### Test Case 3.2: Cross-Class Exotic Surgery Penalties
- **Objective**: Verify non-native classes can install other classes' signature augmentations only with schematic, high fee, and increased neural rejection penalties.
- **Input**: Level 30 Mage attempts to install Juggernaut's *Integrated Hydraulic Piston Core*.
- **Assertions**:
  - Fails if rare schematic is missing from inventory.
  - When schematic and materials are present, installation succeeds but applies $-30$ Humanity and $+25\%$ spell mana cost penalty.
