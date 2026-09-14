# Juggernaut (The Warrior / Cyber-Vanguard)

The Juggernaut is the premier frontline bastion and armored colossus in Untitled RPG, embodying the stalwart warrior reinforced by heavy titanium alloy plating, internal shock dampeners, and hydraulic muscle servos.

---

## 1. Class Identity & Playstyle

### 1.1 The Archetype
The Juggernaut dominates narrow corridors and absorbs punishing boss blows that would vaporize lesser combatants. Where other classes dodge or flee, the Juggernaut plants their boots, raises an armored bulwark, and absorbs incoming kinetic force, weaponizing absorbed damage into catastrophic seismic retaliations.

- **Primary Combat Role**: Frontline Tank / Area-of-Effect CC / Heavy Shield Specialist.
- **Weapon Specialization**: Greatswords, War-Hammers, Tower Shields, Pneumatic Maces, Heavy Cleavers.
- **Survival Niche**: Massive carry weight; high environmental resistance to blizzards, heat, and falling debris; structural defense bonuses when fortifying settlement walls.

### 1.2 Baseline Attributes & Derived Stats
- **Strength (STR)**: 15 ($+22.5\%$ melee physical damage, $+30\text{ kg}$ carry weight).
- **Vitality (VIT)**: 12 ($+120$ Max HP, $+0.6\text{ HP/s}$ base regen, $+6\%$ status resistance).
- **Dexterity (DEX)**: 6 (Moderate mobility).
- **Intelligence (INT)**: 5 (Basic utility aptitude).
- **Wisdom (WIS)**: 5 (Standard mental baseline).
- **Cyber-Affinity (CYB)**: 7 ($+70$ Power Capacity, reduced tech humanity penalties).

**Starting Derived Pools**:
- Health: $220\text{ HP}$
- Stamina: $60\text{ Stamina}$
- Mana: $30\text{ Mana}$
- Power: $70\text{ Power}$
- Humanity: $100$
- Stability: $100$

### 1.3 Starting Equipment Kit
- **Main Hand**: Scrap Greatsword (16 physical damage, 1.2 attacks/sec, high knockdown).
- **Off Hand**: Reinforced Iron Kite Shield (Blocks $60\%$ frontal damage, parry window 0.15s).
- **Armor**: Welder's Plated Vest ($+12$ Armor, $-5\%$ move speed penalty, $+15$ heat resist).
- **Consumables**: 5x Sterile Bandages, 2x Repair Slag Canisters.

---

## 2. Signature Class Mechanic: Kinetic Battery

The Juggernaut's reinforced frame is lined with piezoelectric absorption mesh. Taking damage or successfully blocking hostile attacks with a shield charges an internal Kinetic Energy Meter (0–100%):

$$\text{Charge Gained} = \frac{\text{Mitigated Damage Taken}}{\text{Max HP}} \times 100\%$$

- **Discharge**: At 100% Charge, the Juggernaut's next melee strike or active skill detonates in a kinetic shockwave dealing $+150\%$ bonus physical damage in a 3-tile radial blast, knocking all surrounding enemies airborne.

---

## 3. Class Skill Tree & Abilities

The Juggernaut's skill progression emphasizes immovable defense, projectile deflection, seismic fissures, and EMP detonations.

### 3.1 Active Skills (Bound to Hotkeys `Q`, `E`, `R`, `F`)

#### Active Q — Seismic Shockwave
- **Hotbar Slot**: `Q`
- **Resource Cost**: 20 Stamina
- **Cooldown**: 8.0 seconds
- **Effect**: Slams weapon or armored fists into the ground with catastrophic force, sending a ground fissure traveling 8 tiles. Deals $180\%$ physical damage and launches hit enemies into the air, stunning them for 1.0 second upon landing.

#### Active E — Fortress Stance
- **Hotbar Slot**: `E`
- **Resource Cost**: 15 Power
- **Cooldown**: 12.0 seconds
- **Effect**: Locks hydraulic stabilizers into the ground for 5.0 seconds. Armor increased by $+150\%$, reflects $40\%$ of incoming damage back to attackers, and grants complete immunity to knockback and staggers, but movement speed is reduced by $40\%$.

#### Active R — Kinetic Rocket Charge
- **Hotbar Slot**: `R`
- **Resource Cost**: 25 Stamina
- **Cooldown**: 10.0 seconds
- **Effect**: Rockets forward horizontally 6 tiles with shield leading. Deals $140\%$ damage, knocks all enemies aside, and shatters breakable environment blocks and enemy wooden barricades.

#### Active F — Overload EMP Discharge
- **Hotbar Slot**: `F` (Ultimate)
- **Resource Cost**: 50 Power
- **Cooldown**: 30.0 seconds
- **Effect**: Releases all stored battery power in an omnidirectional 360-degree EMP pulse. Deals $350\%$ electric damage in an 8-tile radius, permanently disarming mechanical enemies and disabling boss energy shields for 6 seconds.

---

### 3.2 Key Passive Specializations
1. *Plated Sinew*: Maximum Health increased by $+10\%$.
2. *Reinforced Bulk*: Flat Armor $+15$ when wearing heavy metal chestplates.
3. *Unyielding Stride*: Knockback resistance increased by $+50\%$.
4. *Spiteful Retaliation*: Attackers take 5 flat physical damage whenever they land a melee blow on the Juggernaut.
5. *Heavy Impact*: Jump-landing from greater than 4 tiles releases an automatic radial crushing shockwave.
6. *Kinetic Siphon*: $5\%$ of all physical damage taken is converted directly into stored electrical Power.
7. *Colossus Grip*: Two-handed heavy weapons can be wielded in one hand alongside a shield at a $-15\%$ attack speed penalty.
8. *Internal Dampeners*: Blast and explosive damage taken reduced by $30\%$.
9. *Crushing Momentum*: Dashing into enemies staggers and interrupts their attack windups for 1.2 seconds.
10. *Ironclad Recovery*: Health regeneration increased by $+2.0\text{ HP/s}$ while below $30\%$ HP.
11. *Indomitable Will*: Durations of Freeze, Stun, and Slow debuffs suffered are halved.

---

## 4. Level 20 Free Signature Augmentation

### *Integrated Hydraulic Piston Core*
- **Body Slot**: Torso
- **Augmentation Type**: Heavy Bionic Internal Frame
- **Native Class Cost**: Free (0 surgery credits, 0 Humanity penalty, 0 Power upkeep).
- **Core Functionality**:
  - Replaces mortal ribcage and sternum with titanium-carbide hydraulic load-bearing pistons.
  - Doubles the player's base armor value from all sources.
  - Grants permanent, unbreakable immunity to all physical knockback, knockdown, and stagger effects.
  - Grants $+150$ flat Maximum Health.
- **Cross-Class Exotic Surgery Trade-Off**:
  - Available to other classes via advanced cyber-surgery.
  - Non-native penalty: $-30$ Humanity, $+25\%$ spell mana cost, and heavy armor movement speed penalty is doubled due to physiological strain.
