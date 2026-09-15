# Gunslinger (The Ranger / Cyber-Sharpshooter)

**Asset generated:** Yes
**Asset:** `assets/generated/classes/gunslinger/sprite/source.png`

![Gunslinger](../../assets/generated/classes/gunslinger/sprite/source.png)

The Gunslinger is the master of long-range ballistic marksmanship, high-tech weapon handling, tactical gadgetry, and battlefield distance control in Untitled RPG.

---

## 1. Class Identity & Playstyle

### 1.1 The Archetype
Combining the keen tracking and wilderness scouting of the traditional ranger with high-velocity ballistic firearms, targeting optics, and magnetic grappling cables, the Gunslinger excels at eliminating enemies from maximum range before threats can close the distance.

- **Primary Combat Role**: Long-Range Physical DPS / Ballistic Weapon Specialist / Sniper.
- **Weapon Specialization**: Revolvers, Lever-Action Carbines, Shotguns, Sniper Rifles, Rotary Autocannons, Hand Mortars.
- **Survival Niche**: Extended vision in darkness; fast foraging of metals and gunpowder materials; tracks animal movements on minimap; efficient hunting.

### 1.2 Baseline Attributes & Derived Stats
- **Strength (STR)**: 8 ($+12.0\%$ melee damage, $+16\text{ kg}$ carry weight).
- **Dexterity (DEX)**: 16 ($+24.0\%$ ranged damage, $+1.6\%$ crit chance, $+3.2\%$ move speed).
- **Vitality (VIT)**: 6 ($+60$ Max HP).
- **Intelligence (INT)**: 6 (Engineering and gunpowder synthesis).
- **Wisdom (WIS)**: 6 (Target anticipation).
- **Cyber-Affinity (CYB)**: 8 ($+80$ Power Capacity, laser sights).

**Starting Derived Pools**:
- Health: $160\text{ HP}$
- Stamina: $60\text{ Stamina}$
- Mana: $30\text{ Mana}$
- Power: $80\text{ Power}$
- Humanity: $100$
- Stability: $100$

### 1.3 Starting Equipment Kit
- **Main Hand**: Scavenger's Revolver (20 physical damage, 6-round cylinder, 1.4s reload, light ammo).
- **Ammunition**: Box of 120 Light Ballistic Rounds.
- **Armor**: Leather Scout Trenchcoat ($+6$ Armor, $+2$ ammo pouches, $+10\%$ reload speed).
- **Consumables**: 2x Frag Grenades, 1x Optical Flare.

---

## 2. Signature Class Mechanic: Tactical Reload & Weakpoint Aim

The Gunslinger's precision crosshair projects optical scanning vectors onto all visible enemies. Red glowing **Weakpoint Markers** (heads, core vents, fuel tanks) appear on targets:
- **Precision Criticals**: Striking a marked weakpoint deals an automatic **$250\%$ Critical Damage** (compared to normal $150\%$).
- **Tactical Chambering**: Scoring a weakpoint critical strike instantly chambers 1 free round into the active magazine without drawing from ammunition reserves.

---

## 3. Class Skill Tree & Abilities

### 3.1 Active Skills (Bound to Hotkeys `Q`, `E`, `R`, `F`)

#### Active Q — Fan the Hammer
- **Hotbar Slot**: `Q`
- **Resource Cost**: 6 Ammo
- **Cooldown**: 6.0 seconds
- **Effect**: Rapidly unloads the entire cylinder/magazine in a tight 30-degree cone towards the crosshair, firing 6 bullets in 0.4 seconds dealing $6 \times 65\%$ weapon damage.

#### Active E — High-Explosive Frag Grenade
- **Hotbar Slot**: `E`
- **Resource Cost**: 1 Grenade or 20 Power
- **Cooldown**: 10.0 seconds
- **Effect**: Hurls a fragmentation canister that bounces off walls once before violently detonating for $280\%$ blast damage in a 4-tile radial area, shattering armor and sending enemies sprawling.

#### Active R — Magnetic Grappling Hook
- **Hotbar Slot**: `R`
- **Resource Cost**: 10 Stamina
- **Cooldown**: 5.0 seconds
- **Effect**: Fires a high-tensile magnetic cable up to 15 tiles toward terrain or walls, instantly pulling the player at high velocity to the target location.

#### Active F — Orbital Satellite Particle Lance
- **Hotbar Slot**: `F` (Ultimate)
- **Resource Cost**: 40 Power
- **Cooldown**: 45.0 seconds
- **Effect**: Paints a coordinate column with a target laser. After a 1.2s delay, an orbital particle beam incinerates everything in a 3-tile wide column from the sky down to bedrock, dealing $600\%$ energy damage.

---

### 3.2 Key Passive Specializations
1. *Lead Storm*: Bullet velocity increased by $+15\%$ and weapon effective range $+10\%$.
2. *Quickdraw*: Weapon swapping speed $+80\%$; first shot within 1.0s of swapping has $+25\%$ crit chance.
3. *Recoil Stabilizers*: Weapon kickback and barrel climb reduced by $50\%$.
4. *Hollow-Point Rounds*: Ballistic critical strikes inflict heavy Bleed for 4.0 seconds.
5. *Overcharged Cells*: Energy firearms chain electricity to 1 adjacent target for $50\%$ damage.
6. *Deep Bandolier*: Maximum ammunition capacity doubled across all ammo categories.
7. *Deadeye Stance*: Standing completely stationary for 1.0s elevates critical strike multiplier to $3.0\times$.
8. *Shrapnel Ricochet*: Missed shots have a $25\%$ chance to ricochet off hard surfaces toward nearby enemies.
9. *Heat Radiators*: Energy weapon overheat buildup reduced by $30\%$.
10. *Trick Shot*: Shooting active thrown grenades out of the air triggers double damage and double explosion radius.
11. *Point Blank*: Firearms deal $+30\%$ bonus damage against targets within 3 tiles.

---

## 4. Level 20 Free Signature Augmentation

### *Sub-Orbital Target Link*
- **Body Slot**: Eyes
- **Augmentation Type**: Cybernetic Optical Array
- **Native Class Cost**: Free (0 surgery credits, 0 Humanity penalty, 0 Power upkeep).
- **Core Functionality**:
  - Replaces mortal eyes with advanced thermal and sub-orbital telemetry sensors.
  - Highlights enemies, ore deposits, and dungeon traps through solid walls.
  - Ballistic bullets fired gain smart tracking, curving trajectory slightly to strike designated weak points.
- **Cross-Class Exotic Surgery Trade-Off**:
  - Non-native installation penalty: $-20$ Humanity, 5 Power/s continuous upkeep, and $-10\%$ melee attack speed.
