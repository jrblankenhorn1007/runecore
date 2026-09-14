# Berserker (The Barbarian / Bio-Bruiser)

The Berserker is the premier high-risk, high-reward melee combatant in Untitled RPG, embodying the brutal archetype of the primal barbarian enhanced by volatile chimeric muscle tissue, hyper-adrenal gland mutations, and savage instinct.

---

## 1. Class Identity & Playstyle

### 1.1 The Archetype
Driven by pain and biological fury, the Berserker gains immense combat power as their health declines. Rather than relying on heavy mechanical armor or complex spell incantations, the Berserker relies on biological resilience, rapid laceration attacks, and life-leeching frenzies to remain alive in the thick of monster hordes.

- **Primary Combat Role**: Frontline Bruiser / Sustained Melee DPS / Lifesteal Tank.
- **Weapon Specialization**: Dual Cleavers, Great-Axes, Two-Handed Heavy Blades, Chimeric Claws, Spiked Clubs.
- **Survival Niche**: High biological metabolism; natural resistance to physical staggers and crowd control; high resistance to environmental freezing; thrives on raw meat consumption.

### 1.2 Baseline Attributes & Derived Stats
- **Strength (STR)**: 16 ($+24.0\%$ melee physical damage, $+32\text{ kg}$ carry weight).
- **Vitality (VIT)**: 14 ($+140$ Max HP, $+0.7\text{ HP/s}$ base regen, $+7\%$ toxin/bleed resistance).
- **Dexterity (DEX)**: 8 ($+12.0\%$ physical speed/crit).
- **Intelligence (INT)**: 4 (Low spell aptitude).
- **Wisdom (WIS)**: 4 (Low natural mana pool).
- **Cyber-Affinity (CYB)**: 4 (Low tech tolerance).

**Starting Derived Pools**:
- Health: $240\text{ HP}$
- Stamina: $70\text{ Stamina}$
- Mana: $20\text{ Mana}$
- Power: $40\text{ Power}$
- Humanity: $95$ (Natural primal detachment)
- Stability: $90$ (High compatibility with chimeric beast grafts)

### 1.3 Starting Equipment Kit
- **Main Hand**: Rusted Scrap Cleaver (11 physical damage, 2.2 attacks/sec, high stagger).
- **Off Hand**: Jagged Meat Hook (9 physical damage, $15\%$ bleed chance).
- **Armor**: Torn Beast-Hide Harness ($+4$ Armor, $+5\%$ movement speed, $+10$ cold insulation).
- **Consumables**: 3x Adrenaline Vials (instant $+30\%$ attack speed for 6 seconds), 5x Raw Jerky.

---

## 2. Signature Class Mechanic: Blood Frenzy

The Berserker's body pumps volatile adrenal mutagen when injured. Attack speed, life-leech, and physical movement scale dynamically inversely with current health percentage:

$$\text{Bonus Attack Speed} = \left(1.0 - \frac{\text{Current HP}}{\text{Max HP}}\right) \times 50\%$$
$$\text{Bonus Lifesteal} = \left(1.0 - \frac{\text{Current HP}}{\text{Max HP}}\right) \times 15\%$$
$$\text{Damage Resistance Bonus} = \left(1.0 - \frac{\text{Current HP}}{\text{Max HP}}\right) \times 20\%$$

- **Gameplay Impact**: At $100\%$ HP, the Berserker plays as a sturdy melee fighter. At $20\%$ HP, the Berserker becomes an unstoppable whirlwind of blades, attacking $+40\%$ faster and restoring $12\%$ of all damage dealt directly as health with each strike.

---

## 3. Class Skill Tree & Abilities

The Berserker's skill progression emphasizes physical cleaves, movement leaps, battle shouts, bleed exploitation, and death-defying passives.

### 3.1 Active Skills (Bound to Hotkeys `Q`, `E`, `R`, `F`)

#### Active Q — Primal Cleave
- **Hotbar Slot**: `Q`
- **Resource Cost**: 15 Stamina
- **Cooldown**: 4.0 seconds (decreases with rank)
- **Effect**: Performs a sweeping 180-degree horizontal arc with active melee weapons, hitting all enemies in front for $220\%$ weapon physical damage and inflicting Bleed for 5 seconds. Bleeding enemies take damage every second, accelerated when they move.

#### Active E — Adrenaline Surge
- **Hotbar Slot**: `E`
- **Resource Cost**: $10\%$ Current HP (health sacrifice)
- **Cooldown**: 15.0 seconds
- **Effect**: Willingly lacerates flesh to flood the nervous system with combat stims for 8 seconds. Grants $+35\%$ attack speed, $+20\%$ movement speed, and $+15\%$ lifesteal. Defeating an enemy while active extends the duration by 1.5 seconds.

#### Active R — Death-Defying Roar
- **Hotbar Slot**: `R`
- **Resource Cost**: 20 Stamina
- **Cooldown**: 20.0 seconds
- **Effect**: Releases a deafening battle cry that cleanses active stuns and slows from the player, while inflicting Fear on all non-boss enemies within an 8-tile radius for 3.0 seconds, causing them to flee and drop their guard ($-25\%$ armor).

#### Active F — Guillotine Leap
- **Hotbar Slot**: `F` (Ultimate)
- **Resource Cost**: 30 Stamina
- **Cooldown**: 25.0 seconds
- **Effect**: Leaps up to 8 tiles horizontally and vertically, crashing down upon the target coordinate with devastating downward force. Deals $250\%$ weapon damage in a 3-tile impact radius, scaling up to $500\%$ critical execute damage against enemies below $25\%$ HP.

---

### 3.2 Key Passive Specializations
1. *Rage Conduit*: Gain $+1\%$ damage for every $2\%$ of missing Health.
2. *Taste of Blood*: Slaying a bleeding target instantly restores $5\%$ of Maximum Health.
3. *Unstoppable Force*: The player cannot be slowed below base walking speed by enemy debuffs or terrain mud.
4. *Frenzy Stacks*: Consecutive melee strikes landed within 2.0s grant $+3\%$ attack speed (stacks up to 5 times for $+15\%$).
5. *Gore Feast*: Critical strikes cause enemies to explode in jagged bone shrapnel, dealing physical damage to adjacent targets.
6. *Savage Vitality*: Maximum Health increased by $+150\text{ HP}$, but total Armor value is reduced by $10\%$ due to reckless defense.
7. *Thick Hide*: Reduces all incoming physical damage by $1\%$ per 100 current HP.
8. *Brawn Over Brain*: Melee weapon scaling gains an additional $+0.5\%$ damage bonus per point of total STR.
9. *Rampage*: Slaying an enemy while Adrenaline Surge is active extends its buff duration by 1.5 seconds.
10. *Blood-Soaked Reach*: Melee weapon swing reach and arc width increased by $+25\%$.
11. *Last Stand*: Taking lethal damage keeps the player alive at 1 HP for 3.0 seconds with total damage immunity (60-second internal cooldown).

---

## 4. Level 20 Free Signature Augmentation

### *Chimeric Beast Claws & Tendons*
- **Body Slot**: Right Arm
- **Augmentation Type**: Chimeric Graft (Living Apex Predator Tissue)
- **Native Class Cost**: Free (0 surgery credits, 0 Humanity penalty, 0 Stability upkeep).
- **Core Functionality**:
  - Physically replaces the player's right forearm with chitinous claws and braided muscle tendons.
  - Adds $+25$ flat physical damage to all melee attacks.
  - Grants permanent $+8\%$ lifesteal on hit.
  - Melee strikes apply Deep Bleed, which permanently shreds enemy armor by $2\%$ per hit (up to $20\%$).
- **Cross-Class Exotic Surgery Trade-Off**:
  - Non-Berserker characters (such as Mages or Gunslingers) can install this graft only after finding rare apex genetic blueprints in Tier 5+ Bio-Labs.
  - Non-native installation penalty: $-25$ Magical Stability, $2.0\text{ MP/s}$ continuous mana upkeep, and $-15\%$ ranged projectile accuracy.
