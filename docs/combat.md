# Combat & Damage Mechanics Specification

This document defines the physics-driven combat engine, damage calculation pipeline, status effect state machines, and Terraria-like game feel architecture for Untitled RPG.

---

## 1. Combat Design Pillars & Feel

1. **Precision 360-Degree Mouse Aiming**:
   - The player's torso, arms, and weapon aim dynamically towards the mouse cursor.
   - Character sprite flips horizontally across the vertical axis when aiming left vs right.
2. **Kinematic Sensor Hitboxes**:
   - Attacks (melee swings, thrusts, projectile explosions) spawn temporary Box2D sensor shapes.
   - Sensor tracks an internal list of entity IDs hit during that specific attack cycle to guarantee that an attack damages an entity exactly once per swing.
3. **Hitstop (Screen Impact Freeze)**:
   - When a heavy weapon or critical strike lands, simulation ticks freeze for 2 to 4 frames (33ms to 66ms) while rendering continues.
4. **Sinusoidal Screen Shake**:
   - Explosions and heavy hits add trauma (0.0 to 1.0) to the camera. Camera offset calculates:
     $$\text{Offset} = \text{Trauma}^2 \times \text{MaxShake} \times \sin(\text{Time} \times \text{Frequency})$$
5. **Floating Combat Popups**:
   - Numbers arc upwards with randomized horizontal velocity, fading out over 0.8 seconds.
   - Color coding: White (Physical), Yellow (Crit), Blue (Electric/Energy), Orange (Fire), Cyan (Frost), Green (Poison), Purple (Void/Dark), Gold (Holy).

---

## 2. The Comprehensive Damage Calculation Pipeline

When an attack hitbox makes contact with a target hurtbox:

```
[Raw Weapon Base Damage]
            │
            ▼
[Apply Attribute Scaling] ─── STR (Melee), DEX (Ballistic), INT (Magic), CYB (Energy)
            │
            ▼
[Apply Passive & Tree Modifiers]
            │
            ▼
[Roll Critical Strike] ─── If (Random(0, 1) < CritChance) ──► Multiply by CritMultiplier (Base 1.5x)
            │
            ▼
[Mitigate with Target Armor / Resistance]
            │
            ▼
[Check Vulnerabilities & Shield Block] ─── Frontal Shield Block reduces damage by Block %
            │
            ▼
[Apply Damage to Health / Mana / Shields]
            │
            ▼
[Trigger Status Effects] ─── Burn, Freeze, Shock, Toxin, Bleed, Stun
            │
            ▼
[Apply Box2D Knockback Impulse & Hitstop]
```

### 2.1 The Mathematical Formulas
- **Attribute Scaling**:
  $$\text{Scaled Damage} = \text{Base Damage} \times (1.0 + \text{Attribute} \times 0.015)$$
- **Armor Mitigation Formula**:
  $$\text{Damage Reduction} = \frac{\text{Armor}}{\text{Armor} + 100}$$
  $$\text{Final Damage Taken} = \text{Incoming Damage} \times (1.0 - \text{Damage Reduction}) \times (1.0 - \text{Resistance})$$
  *(Minimum damage is always 1).*

---

## 3. Status Effects State Machine

| Status Effect | Trigger Element | Duration | Gameplay Effect |
|---|---|---|---|
| **Burn** | Fire / Plasma | 5.0s | Ticks $8\%$ weapon damage as fire every 0.5s; sheds dynamic orange light in dark areas. |
| **Freeze** | Frost / Cryo | 2.5s | Target cannot move, jump, or attack. Taking a heavy blunt hit shatters freeze for $+50\%$ bonus damage. |
| **Shock** | Electric / Lightning | 1.0s | Chains electrical arc to up to 2 adjacent entities; $20\%$ chance to interrupt current action. |
| **Toxin / Poison** | Nature / Spores / Bio | 8.0s | Ticks continuous acid damage; reduces target healing received by $50\%$ and shreds Armor by $15\%$. |
| **Bleed** | Sharp Melee / Hollow-Point| 6.0s | Ticks damage based on target movement speed (moving faster accelerates bleed damage). |
| **Stun** | Heavy Blunt / Shield Bash | 1.5s | Target immobilized and incapacitated. |

