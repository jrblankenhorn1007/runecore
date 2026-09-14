# Input System & Action Mapping Specification

This document specifies the input capture architecture, abstract action mapping, gamepad axis deadzones, and 360-degree mouse aiming systems for Untitled RPG.

---

## 1. Abstract Action Architecture

Hardcoding specific physical keyboard keys or controller buttons into gameplay systems is strictly prohibited. The input layer translates all physical device signals into an abstract `PlayerAction` enumeration:

```
[Hardware Input Devices]
 ├── Keyboard (SDL Scancodes)
 ├── Mouse (Buttons, Wheel, Relative Movement)
 └── Gamepad (Analog Sticks, Triggers, Face Buttons)
           │
           ▼
[InputManager Translation & Action Mapper]
           │
           ▼
[Abstract Gameplay Actions (PlayerIntent)]
 ├── MoveHorizontal (-1.0 to +1.0)
 ├── MoveVertical   (-1.0 to +1.0)
 ├── Jump, Dash, Interact
 ├── AttackPrimary, AttackSecondary
 ├── SkillQ, SkillE, SkillR, SkillF
 ├── HotbarSelect (Slot 1 - 8)
 └── ToggleInventory, ToggleMap, Pause
```

---

## 2. Default Input Bindings Table

| Action Name | Keyboard + Mouse (Primary) | Gamepad Controller (Standard Layout) |
|---|---|---|
| **Move Left / Right** | `A` / `D` | Left Analog Stick (X-Axis) |
| **Aim / Look (360°)** | Mouse Cursor Position | Right Analog Stick (X & Y Axes) |
| **Climb Up / Aim Up** | `W` | Left Analog Stick (Up) |
| **Crouch / Drop Down**| `S` | Left Analog Stick (Down) |
| **Jump / Thrusters** | `Space` | Face Button Bottom (`A` / Cross) |
| **Dash / Evade** | `Left Shift` | Left Bumper (`LB` / `L1`) |
| **Primary Attack** | Left Mouse Button | Right Trigger (`RT` / `R2`) |
| **Secondary / Shield**| Right Mouse Button | Left Trigger (`LT` / `L2`) |
| **Skill Q** | `Q` | Face Button Left (`X` / Square) |
| **Skill E** | `E` | Face Button Top (`Y` / Triangle) |
| **Skill R** | `R` | Face Button Right (`B` / Circle) |
| **Skill F (Ultimate)**| `F` | Right Bumper (`RB` / `R1`) |
| **Interact / Talk** | `E` or `W` (Contextual) | Face Button Bottom (`A` / Cross) |
| **Hotbar Slots 1–8** | Number Keys `1` through `8` | D-Pad Left / Right (Cycle hotbar) |
| **Inventory / Craft** | `Tab` | View / Select Button |
| **Skill Tree Screen** | `K` or `N` | D-Pad Up |
| **Pause / Menu** | `Escape` | Menu / Start Button |

---

## 3. 360-Degree Aiming & Game Feel Handling

1. **Mouse Aim Vector**:
   - Computes normalized vector from character shoulder pivot to world cursor coordinates:
     $$\text{AimVector} = \frac{\text{CursorWorldPos} - \text{PlayerCenter}}{\|\text{CursorWorldPos} - \text{PlayerCenter}\|}$$
   - Character torso and active weapon sprite rotate around the shoulder joint to match angle $\theta = \text{atan2}(v_y, v_x)$.
   - Sprite flips horizontally along Y-axis when aim vector crosses the vertical midline.
2. **Gamepad Analog Deadzones**:
   - Radial inner deadzone ($15\%$) to eliminate stick drift.
   - Outer deadzone ($90\%$) for instant maximum velocity registration.
   - Dual-stick aiming curves with optional target magnet-assist for controllers.
