# User Interface Hierarchy & Layout Architecture

This document specifies the user interface layer, modal window hierarchy, HUD layouts, drag-and-drop inventory interactions, and tooltip rendering pipeline for Untitled RPG.

---

## 1. UI Layer Hierarchy & Window Manager

All interface screens are organized into a strict visual z-order stack:

```
[Top: Debug Layer (Z: 100)] ─── Dear ImGui console, FPS counter, memory monitors
            │
[Modal Windows (Z: 80)] ────── Dialogue boxes, confirmation prompts, death screens
            │
[Game Menus (Z: 60)] ───────── Pause menu, audio/video settings, keybinding rebinder
            │
[Gameplay Panels (Z: 40)] ──── Inventory grid, 11-slot Cyber-Clinic, Skill Tree, Crafting Bench
            │
[HUD Overlay (Z: 20)] ──────── HP, Stamina, Mana, Power bars, 8-slot hotbar, minimap
            │
[Bottom: World Canvas (Z: 0)] ─ Floating combat text, overhead enemy health bars
```

- **Modal Window Focus Stack**:
  - Only the topmost active gameplay window captures mouse clicks and keyboard events.
  - Opening a full-screen menu (e.g. Skill Tree or Pause) pauses game simulation in single-player mode.
  - Pressing `Escape` or `Tab` cleanly closes the topmost active window.

---

## 2. In-Game HUD Layout

The heads-up display is rendered around the screen perimeter to keep the center field of view clear for platforming and combat:

```
┌────────────────────────────────────────────────────────────────────────┐
│ [HP Bar: 240/240]            [Minimap: Rustwood]    [Time: 14:20 Dusk] │
│ [Stamina: 70/70]                                    [Temp: +18°C]      │
│ [Mana: 90/90]                                       [Hunger: 85%]      │
│ [Power: 60/60]                                      [Thirst: 70%]      │
│                                                                        │
│                                                                        │
│                                                                        │
│                                                                        │
│                       [Crosshair + Reticle]                            │
│                                                                        │
│                                                                        │
│ [Q: Shock] [E: Wall] [R: Roar] [F: Guillotine]                         │
│ [1] [2] [3] [4] [5] [6] [7] [8]  <- (Hotbar: Weapons, Tools, Potions)  │
└────────────────────────────────────────────────────────────────────────┘
```

---

## 3. Inventory & Drag-and-Drop Interaction Pipeline

1. **Slot State Tracking**:
   - Every grid slot tracks: item definition reference, stack quantity, rolled base stats, affix list, and durability.
2. **Mouse Interactions**:
   - *Left Click*: Selects / picks up entire stack onto mouse cursor. Clicking another slot drops or swaps contents.
   - *Right Click*: Splits stack in half, or places 1 item from cursor stack into clicked slot.
   - *Shift + Left Click*: Fast-transfers item between Backpack and Storage Chest / Hotbar.
3. **Item Tooltip Generation**:
   - Hovering over an item slot triggers an adaptive tooltip floating beside the cursor:
     - Item display name with rarity border color.
     - Equipment slot and level requirement.
     - Rolled base damage and attack speed with percentile grade.
     - Affix list color-coded by elemental type.
     - Durability bar and vendor credit value.
