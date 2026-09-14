# Medic / Biomancer (The Cleric / Nanite Restorer)

The Medic / Biomancer is the primary healer, bio-engineer, and chemical warfare specialist of Untitled RPG, utilizing medical nanite clouds, cellular reconstitution injections, acid bio-mist, and protective overshields.

---

## 1. Class Identity & Playstyle

### 1.1 The Archetype
Merging the sacred healing arts of the cleric with cutting-edge nanomedicine, the Medic preserves their own life and the vitality of allies through autonomous nanite clouds. In combat, they reverse the polarity of their bio-tools, deploying corrosive spores, toxic contagion fields, and armor-melting darts.

- **Primary Combat Role**: Combat Healer / Chemical Debuffer / Bio-Support / Sustained DoT.
- **Weapon Specialization**: Pneumatic Syringe Guns, Dart Blasters, Surgical Scalpels, Chemical Sprayers, Bio-Staves.
- **Survival Niche**: Total immunity to poisoned water and spoiled food; rapid recovery from broken limbs; double herb harvesting yield; brews advanced vaccines.

### 1.2 Baseline Attributes & Derived Stats
- **Strength (STR)**: 7 ($+10.5\%$ physical damage).
- **Dexterity (DEX)**: 8 ($+12.0\%$ speed/accuracy).
- **Vitality (VIT)**: 12 ($+120$ Max HP, $+0.6\text{ HP/s}$ regen).
- **Intelligence (INT)**: 10 ($+20.0\%$ spell power, $+50$ Max Mana).
- **Wisdom (WIS)**: 14 ($+1.4\text{ MP/s}$ mana regen, $+14$ stability, $+14\%$ healing received).
- **Cyber-Affinity (CYB)**: 6 ($+60$ Power Capacity).

**Starting Derived Pools**:
- Health: $220\text{ HP}$
- Stamina: $50\text{ Stamina}$
- Mana: $90\text{ Mana}$
- Power: $60\text{ Power}$
- Humanity: $100$
- Stability: $100$

### 1.3 Starting Equipment Kit
- **Main Hand**: Pneumatic Syringe Gun (15 physical/toxin damage, fires needle darts).
- **Ammunition**: 80x Medical Needle Darts.
- **Armor**: Bio-Hazard Hazard Suit ($+8$ Armor, immune to natural poison, $+20$ acid resist).
- **Consumables**: 5x Medical Nanite Packs, 3x Detox Syringes.

---

## 2. Signature Class Mechanic: Nanite Swarm Aura

The Medic continuously emits a 4-tile bio-aura of microscopic medical nanites:
- **Allies & Self**: Regenerate $2.0\text{ HP/s}$ continuously and cleanse poison/bleed debuffs $50\%$ faster.
- **Enemies Inside Aura**: Suffer cellular decay, taking $15\text{ toxin damage/s}$ and having their health regeneration halted.

---

## 3. Class Skill Tree & Abilities

### 3.1 Active Skills (Bound to Hotkeys `Q`, `E`, `R`, `F`)

#### Active Q — Nanite Injection Dart
- **Hotbar Slot**: `Q`
- **Resource Cost**: 20 Mana
- **Cooldown**: 4.0 seconds
- **Effect**: Fires a smart syringe dart toward the crosshair. If striking an ally or self: heals 80 HP over 4 seconds. If striking an enemy: deals 100 toxic damage and weakens target armor by $20\%$ for 6 seconds.

#### Active E — Healing Field Generator
- **Hotbar Slot**: `E`
- **Resource Cost**: 30 Power
- **Cooldown**: 16.0 seconds
- **Effect**: Deploys a medical beacon on the ground creating a 6-tile radius circle of restoration for 10.0 seconds. Restores $15\text{ HP/s}$ and cleanses debuffs from all friendly entities within.

#### Active R — Bio-Contagion Cloud
- **Hotbar Slot**: `R`
- **Resource Cost**: 35 Mana
- **Cooldown**: 14.0 seconds
- **Effect**: Releases an expanding cloud of virulent necrotic spores for 6 seconds. Enemies inside take continuous acid damage; any enemy that dies while inside the cloud bursts, spreading the spore cloud to adjacent areas.

#### Active F — Cellular Overdrive
- **Hotbar Slot**: `F` (Ultimate)
- **Resource Cost**: 50 Mana
- **Cooldown**: 45.0 seconds
- **Effect**: Floods the body with synthetic adrenal hormones and self-repair nanites: restores $50\%$ Maximum Health instantly and boosts move speed and attack speed by $+30\%$ for 8.0 seconds.

---

### 3.2 Key Passive Specializations
1. *Hippocratic Oath*: All healing performed and received increased by $+15\%$.
2. *Antidote Synthesis*: Complete immunity to natural poisons, venoms, and chemical warfare agents.
3. *Combat Syringe*: Dart and needle weapons gain $+25\%$ projectile speed and pierce through 1 target.
4. *Sympathetic Link*: Healing friendly NPCs or summons restores $25\%$ of that amount to the player.
5. *Nanite Armor*: Healing received while at $100\%$ HP converts into an absorption overshield up to $20\%$ Max HP.
6. *Transfusion*: Melee attacks leech $3\%$ of damage dealt as healing.
7. *Sterile Scalpels*: Daggers and surgical blades gain $+15\%$ critical strike chance.
8. *Defibrillation*: Electric damage inflicted has a $20\%$ chance to stun enemies for 2.0 seconds.
9. *Adrenaline Mist*: Healing Field Generator also grants $+50\%$ stamina regeneration to allies inside.
10. *Biomass Recycler*: Gathering wild herbs and plants yields double materials.
11. *Vitality Resonator*: Permanent passive health regeneration increased by $+1.5\text{ HP/s}$.

---

## 4. Level 20 Free Signature Augmentation

### *Subdermal Cellular Replicator*
- **Body Slot**: Skin / Dermis
- **Augmentation Type**: Advanced Bionic Dermal Mesh
- **Native Class Cost**: Free (0 surgery credits, 0 Humanity penalty, 0 Power upkeep).
- **Core Functionality**:
  - Automatically intercepts fatal damage once every 300 seconds (5 minutes).
  - Instantly revives the player to $50\%$ Maximum Health.
  - Releases a blinding white flash of light, stunning all adjacent enemies for 3.0 seconds.
- **Cross-Class Exotic Surgery Trade-Off**:
  - Non-native installation penalty: $-25$ Humanity, 10 Power/s continuous upkeep, and $-10\%$ physical melee damage.
