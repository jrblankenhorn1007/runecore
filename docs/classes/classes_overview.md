# Classes Specification

This document provides the complete, authoritative specification for all 9 character classes in Untitled RPG. At character creation, the player selects one class. The class determines base attributes, starting equipment, unique resource interactions, a dedicated 15-node class skill tree, and a guaranteed Free Signature Augmentation at Level 20.

---

## 1. Class System Architecture & Core Rules

### 1.1 Attribute Baseline
All characters have six core attributes:
- **STR (Strength)**: $+1.5\%$ Melee Physical Damage, $+2\text{ kg}$ Max Carry Weight, reduced heavy armor move penalties.
- **DEX (Dexterity)**: $+1.5\%$ Ranged/Ballistic Damage, $+0.1\%$ Critical Strike Chance, $+0.2\%$ Movement Speed.
- **INT (Intelligence)**: $+2.0\%$ Spell Damage, $+5$ Max Mana, $+1\%$ Crafting Speed.
- **VIT (Vitality)**: $+10$ Max Health, $+0.05\text{ HP/s}$ Health Regeneration, $+0.5\%$ Bleed/Toxin Resistance.
- **WIS (Wisdom)**: $+0.1\text{ MP/s}$ Mana Regeneration, $+1$ Magical Stability, $+1.0\%$ Healing Received.
- **CYB (Cyber-Affinity)**: $+10$ Max Power Capacity, $-1.5\%$ Humanity Penalty on Bionics, $+1.5\%$ Energy Weapon Damage.

Mortal baseline without class modifiers: $100\text{ HP}$, $50\text{ Stamina}$, $50\text{ Mana}$, $50\text{ Power}$, $100\text{ Humanity}$, $100\text{ Stability}$.

### 1.2 Uncapped Leveling & Universal Skill Acquisition
- **Uncapped Max Level**: There is no level cap (Levels $1 \to \infty$). Defeating the final campaign boss (The Architect) is tuned around Level 60, but characters can continue leveling indefinitely in the Infinite Rift.
- **Universal Skill Learning**: While a character begins with their primary class tree, reaching Level 60 unlocks the **Cross-Class Neural Bridge** in the Hub. Players can spend skill points to unlock and master every other class tree in the game. With 50+ skills per class and 100+ shared/crafting skills (over 550 skills in total), an uncapped character can eventually master every single skill and active spell in the game, ascending to godlike status.
- **Attribute Points**: 3 points per level to distribute freely across the 6 attributes with no upper cap.
- **Skill Points**: 1 Class/Specialization Point and 1 Shared/Crafting Point earned on every single level-up indefinitely.
- **Level 20 Milestone**: Upon reaching Level 20, the player automatically receives their **Class Signature Augmentation**. It is installed automatically into its designated body slot with **zero surgery cost**, **zero humanity penalty**, and **zero stability penalty**.

---

## 2. Complete Roster of 9 Classes

```
[Classes]
 ├── Heavy / Melee:       1. Juggernaut     2. Berserker
 ├── Ranged / Infiltration: 3. Gunslinger      4. Phantom
 ├── Casters / Magitech:  5. Technomancer   6. Medic (Biomancer)
 ├── Chimeric / Hybrid:   7. Symbiote
 └── Specialized:         8. Warden         9. Reanimator
```

---

### Class 1: Juggernaut (The Cyber-Vanguard)

#### Overview & Role
The premier frontline tank. Clad in heavy alloy plating and reinforced chassis, the Juggernaut excels at absorbing devastating blows, locking down corridors, and unleashing kinetic shockwaves.

- **Starting Attributes**: STR: 15, VIT: 12, DEX: 6, INT: 5, WIS: 5, CYB: 7.
- **Starting Derived Stats**: HP: $220$, Stamina: $60$, Mana: $30$, Power: $70$, Humanity: $100$, Stability: $100$.
- **Starting Equipment**: Scrap Greatsword (Melee, 16 physical dmg), Reinforced Iron Kite Shield (Offhand, 60% block), Welder's Plated Vest (+12 Armor, -5% Move Speed), 5x Bandages.
- **Signature Mechanic — Kinetic Battery**: Taking damage or successfully blocking attacks generates Kinetic Charge (0–100%). At 100%, next melee strike or active skill triggers a seismic explosion dealing $150\%$ bonus physical damage in a 3-tile radius.

#### Class Skill Tree (15 Nodes: 4 Actives, 11 Passives)
- **Active Q — Seismic Shockwave** (Rank 1/5): Slam weapon into the ground, sending a shockwave traveling 8 tiles. Deals $180\%$ weapon damage, launching enemies into the air for 1.0s. (Cost: 20 Stamina, CD: 8s).
- **Active E — Fortress Stance** (Rank 1/5): Root feet into ground for 5s. Armor $+150\%$, reflects $40\%$ damage back to attacker, immune to knockback, but movement speed reduced by $40\%$. (Cost: 15 Power, CD: 12s).
- **Active R — Kinetic Charge** (Rank 1/5): Rocket forward 6 tiles. Knocks enemies aside, deals $140\%$ damage, and destroys breakable terrain blocks. (Cost: 25 Stamina, CD: 10s).
- **Active F — Overload EMP Discharge** (Rank 1/5): Releases all stored battery energy in a 360-degree shockwave. Deals $350\%$ electric damage and disables mechanical enemy shields/lasers for 6s. (Cost: 50 Power, CD: 30s).
- **Passive 1 — Plated Sinew**: $+10\%$ Max Health.
- **Passive 2 — Reinforced Bulk**: $+15$ flat Armor when wearing heavy chest armor.
- **Passive 3 — Unyielding Stride**: Knockback resistance $+50\%$.
- **Passive 4 — Spiteful Retaliation**: Attackers take 5 flat physical damage whenever they strike the player.
- **Passive 5 — Heavy Impact**: Falling from greater than 4 tiles releases a ground slam dealing AoE damage.
- **Passive 6 — Kinetic Siphon**: $5\%$ of all physical damage taken is converted directly into Power.
- **Passive 7 — Colossus Grip**: Two-handed heavy weapons can be wielded in one hand at a $-15\%$ attack speed penalty.
- **Passive 8 — Internal Dampeners**: Blast and explosive damage taken reduced by $30\%$.
- **Passive 9 — Crushing Momentum**: Dashing through enemies staggers them for 1.2s.
- **Passive 10 — Ironclad Recovery**: Health regeneration increased by $+2.0\text{ HP/s}$ while below $30\%$ HP.
- **Passive 11 — Indomitable Will**: Freeze and stun durations suffered reduced by $50\%$.

#### Free Level 20 Signature Augmentation
- **Item**: *Integrated Hydraulic Piston Core*
- **Slot**: Torso
- **Type**: Bionic (Free Signature: 0 Humanity penalty, 0 Power upkeep)
- **Effects**: Base Armor $+40$, permanent immunity to knockback and stagger, $+150\text{ Max HP}$.

---

### Class 2: Berserker (The Bio-Bruiser)

#### Overview & Role
A savage melee combatant who uses biological fury, mutated muscle fibers, and pain-induced adrenaline to shred through hordes. Becomes deadlier the closer they are to death.

- **Starting Attributes**: STR: 16, VIT: 14, DEX: 8, INT: 4, WIS: 4, CYB: 4.
- **Starting Derived Stats**: HP: $240$, Stamina: $70$, Mana: $20$, Power: $40$, Humanity: $95$, Stability: $90$.
- **Starting Equipment**: Dual Rusted Cleavers (Dual Melee, 11 dmg each), Torn Hide Harness (+4 Armor, +5% Move Speed), 3x Adrenaline Vials.
- **Signature Mechanic — Blood Frenzy**: Attack speed and life-leech scale inversely with current HP:
  $$\text{Bonus Attack Speed} = (1.0 - \frac{\text{Current HP}}{\text{Max HP}}) \times 50\%$$
  $$\text{Lifesteal} = (1.0 - \frac{\text{Current HP}}{\text{Max HP}}) \times 15\%$$

#### Class Skill Tree (15 Nodes: 4 Actives, 11 Passives)
- **Active Q — Primal Cleave** (Rank 1/5): A wide 180-degree sweep dealing $220\%$ physical damage and applying Bleed for 5s. (Cost: 15 Stamina, CD: 4s).
- **Active E — Adrenaline Surge** (Rank 1/5): Sacrifice $10\%$ current HP to gain $+35\%$ attack speed, $+20\%$ move speed, and $+15\%$ lifesteal for 8s. (Cost: 10% Current HP, CD: 15s).
- **Active R — Death-Defying Roar** (Rank 1/5): Unfurl a ferocious roar fearing all non-boss enemies within 8 tiles for 3s and cleansing stuns. (Cost: 20 Stamina, CD: 20s).
- **Active F — Guillotine Leap** (Rank 1/5): Leap 8 tiles into the air and slam down onto target location. Deals $250\%$ damage, scaling up to $500\%$ against targets below $25\%$ HP. (Cost: 30 Stamina, CD: 25s).
- **Passive 1 — Rage Conduit**: Gain $+1\%$ damage for every $2\%$ of missing Health.
- **Passive 2 — Taste of Blood**: Slaying a bleeding target instantly restores $5\%$ Max Health.
- **Passive 3 — Unstoppable Force**: The player cannot be slowed below base walking speed by debuffs.
- **Passive 4 — Frenzy Stacks**: Consecutive melee strikes within 2s grant $+3\%$ attack speed (stacks up to 5 times).
- **Passive 5 — Gore Feast**: Critical hits cause enemies to explode in bone shrapnel, damaging nearby foes.
- **Passive 6 — Savage Vitality**: $+150$ Max Health, but overall Armor value reduced by $10\%$.
- **Passive 7 — Thick Hide**: Reduces incoming physical damage by $1\%$ per 100 current HP.
- **Passive 8 — Brawn Over Brain**: Melee weapons gain additional scaling: $+0.5\%$ damage per point of STR.
- **Passive 9 — Rampage**: Slaying an enemy while Adrenaline Surge is active extends its duration by 1.5s.
- **Passive 10 — Blood-Soaked Blade**: Melee weapon swing reach increased by $+25\%$.
- **Passive 11 — Last Stand**: Taking fatal damage keeps the player alive at 1 HP for 3.0s (60s internal cooldown).

#### Free Level 20 Signature Augmentation
- **Item**: *Chimeric Beast Claws & Tendons*
- **Slot**: Right Arm
- **Type**: Chimeric (Free Signature: 0 Stability upkeep, 0 Mana upkeep)
- **Effects**: Replaces right arm with razor-sharp beast claws; melee attacks gain $+25$ base damage, $+8\%$ permanent lifesteal, and attacks apply Deep Bleed.

---

### Class 3: Gunslinger (The Cyber-Sharpshooter)

#### Overview & Role
A master of ballistic precision, gadgetry, and battlefield distance. Uses firearms, ricocheting slugs, targeting HUDs, and orbital call-ins to eliminate threats before they approach.

- **Starting Attributes**: STR: 8, DEX: 16, VIT: 6, INT: 6, WIS: 6, CYB: 8.
- **Starting Derived Stats**: HP: $160$, Stamina: $60$, Mana: $30$, Power: $80$, Humanity: $100$, Stability: $100$.
- **Starting Equipment**: Scavenger's Revolver (6 rounds, 20 dmg), Box of 60 Light Rounds, Leather Trenchcoat (+6 Armor, +2 Ammo pouches), 2x Frag Grenades.
- **Signature Mechanic — Weakpoint Targeting**: Critical hits on marked enemy weak points (highlighted in red crosshairs) deal $250\%$ critical damage (up from standard $150\%$) and refund 1 bullet directly to the magazine.

#### Class Skill Tree (15 Nodes: 4 Actives, 11 Passives)
- **Active Q — Fan the Hammer** (Rank 1/5): Unload the remaining cylinder in a rapid 6-shot cone spread dealing $6 \times 65\%$ weapon damage. (Cost: 6 Ammo, CD: 6s).
- **Active E — Frag Grenade** (Rank 1/5): Hurl a high-explosive canister that bounces once and detonates for $280\%$ blast damage in a 4-tile radius. (Cost: 1 Grenade or 20 Power, CD: 10s).
- **Active R — Tactical Grapple** (Rank 1/5): Fire a magnetic grapple cable up to 15 tiles, rapidly pulling the player to walls or ceilings. (Cost: 10 Stamina, CD: 5s).
- **Active F — Orbital Beam Strike** (Rank 1/5): Mark target coordinate. After 1.5s delay, an orbital particle lance burns down the column dealing $600\%$ energy damage. (Cost: 40 Power, CD: 45s).
- **Passive 1 — Lead Storm**: $+15\%$ bullet flight speed and $+10\%$ maximum weapon range.
- **Passive 2 — Quickdraw**: Weapon swapping speed $+80\%$; first shot within 1s after swapping has $+25\%$ crit chance.
- **Passive 3 — Recoil Dampeners**: Weapon recoil kickback reduced by $50\%$.
- **Passive 4 — Hollow-Point Rounds**: Ballistic weapon critical hits inflict Bleed for 4s.
- **Passive 5 — Overcharged Cells**: Energy weapons chain electricity to 1 adjacent target for $50\%$ damage.
- **Passive 6 — Deep Bandolier**: Maximum ammo carrying capacity doubled across all ammo types.
- **Passive 7 — Deadeye Focus**: Remaining stationary for 1.0s boosts critical strike multiplier to $3.0\times$.
- **Passive 8 — Shrapnel Ricochet**: Missed bullets have a $25\%$ chance to ricochet off walls into nearby targets.
- **Passive 9 — Heat Dissipation**: Energy weapon overheat buildup rate reduced by $30\%$.
- **Passive 10 — Trick Shot**: Shooting thrown grenades out of mid-air triggers double damage and double blast radius.
- **Passive 11 — Point Blank**: Ballistic firearms deal $+30\%$ bonus damage to targets within 3 tiles.

#### Free Level 20 Signature Augmentation
- **Item**: *Sub-Orbital Target Link*
- **Slot**: Eyes
- **Type**: Bionic (Free Signature: 0 Humanity penalty, 0 Power upkeep)
- **Effects**: Thermal night vision; highlights enemy weakpoints through walls; ballistic bullets gain smart ricochet tracking towards target weakpoints.

---

### Class 4: Phantom (The Nano-Infiltrator)

#### Overview & Role
A stealth-oriented assassin utilizing optical camouflage, monomolecular daggers, teleportation blinks, and toxic coatings to strike unseen and vanish.

- **Starting Attributes**: STR: 6, DEX: 16, VIT: 8, INT: 8, WIS: 5, CYB: 7.
- **Starting Derived Stats**: HP: $180$, Stamina: $70$, Mana: $40$, Power: $70$, Humanity: $100$, Stability: $100$.
- **Starting Equipment**: Dual Carbon Daggers (Fast Melee, 12 dmg, 25% crit), Shadow Cloak (+5 Armor, -40% enemy detection radius), 5x Throwing Needles.
- **Signature Mechanic — Cloak & Ambush**: Entering stealth (via skill or standing still in shadows) renders the player invisible to enemies. The first attack breaking stealth is an automatic critical strike dealing $+200\%$ bonus ambush damage.

#### Class Skill Tree (15 Nodes: 4 Actives, 11 Passives)
- **Active Q — Shadow Blink** (Rank 1/5): Instantly teleport 6 tiles towards cursor, leaving a smoke cloud that blinds enemies for 2s. (Cost: 15 Stamina, CD: 6s).
- **Active E — Optical Camouflage** (Rank 1/5): Enter total invisibility for 6s. Moving or attacking does not break cloak for the first 1.5s. (Cost: 20 Power or 25 Mana, CD: 14s).
- **Active R — Shuriken Flurry** (Rank 1/5): Hurl 5 piercing shurikens in a spread that penetrate through enemies and inflict Neurotoxin. (Cost: 15 Stamina, CD: 8s).
- **Active F — Executioner's Dance** (Rank 1/5): Teleport rapidly between up to 5 enemies within 10 tiles, slashing each for $200\%$ damage with total invulnerability frames. (Cost: 35 Stamina, CD: 30s).
- **Passive 1 — Silent Stride**: Enemy visual and sound detection radius reduced by $40\%$.
- **Passive 2 — Lethal Precision**: Base critical strike chance $+5\%$.
- **Passive 3 — Backstab Protocol**: Attacks striking an enemy from behind deal $+40\%$ bonus damage.
- **Passive 4 — Neurotoxin Weave**: Daggers and thrown weapons apply stacking poison (slows by $5\%$ and deals damage).
- **Passive 5 — Acrobatic Dash**: Dashing stamina cost reduced by $30\%$; dash distance increased by 1 tile.
- **Passive 6 — Phase Shift**: Dodging through an attack with a dash restores 10 Stamina.
- **Passive 7 — Coup de Grace**: Deal $+50\%$ damage to enemies currently suffering from Stun, Freeze, or Blind.
- **Passive 8 — Holographic Decoy**: Teleporting leaves behind a holographic clone that taunts enemies for 2.5s.
- **Passive 9 — Twin Blade Mastery**: Dual-wielding daggers increases weapon attack speed by $+20\%$.
- **Passive 10 — Emergency Smoke**: Taking damage exceeding $30\%$ max HP automatically deploys a smoke bomb.
- **Passive 11 — Adrenaline Flow**: Landing a critical strike refunds 5 Stamina.

#### Free Level 20 Signature Augmentation
- **Item**: *Nano-Wire Monomolecular Daggers*
- **Slot**: Hands
- **Type**: Bionic (Free Signature: 0 Humanity penalty, 0 Power upkeep)
- **Effects**: Retractable monomolecular blades extend from fingertips; attacks completely ignore enemy armor and strikes from stealth deal $400\%$ damage.

---

### Class 5: Technomancer (The Arcane-Circuit Caster)

#### Overview & Role
A hybrid scholar bridging forgotten spellcraft and advanced electronics. Powers arcane incantations with battery cells and overclocked wands, devastating rooms with elemental plasma and spatial rifts.

- **Starting Attributes**: STR: 5, DEX: 6, VIT: 7, INT: 16, WIS: 10, CYB: 6.
- **Starting Derived Stats**: HP: $170$, Stamina: $50$, Mana: $130$, Power: $60$, Humanity: $100$, Stability: $100$.
- **Starting Equipment**: Circuit-Etched Focus Wand (14 magic dmg, 4 MP cost), Conduit Robes (+4 Armor, +20 Max Mana), 3x Mana Batteries.
- **Signature Mechanic — Spell Overclock**: Spells can be overcharged by tapping RMB: consumes 10 Power to double projectile speed, grant $100\%$ pierce, and cause an electric burst upon impact.

#### Class Skill Tree (15 Nodes: 4 Actives, 11 Passives)
- **Active Q — Arcane Plasma Bolt** (Rank 1/5): Fire a piercing orb of concentrated magical plasma dealing $160\%$ spell damage. (Cost: 15 Mana, CD: 2s).
- **Active E — Tesla Coil Pylon** (Rank 1/5): Deploy a deployable stationary pylon that shocks up to 3 nearby enemies every 1.0s with chain lightning. (Cost: 25 Power or 30 Mana, CD: 12s).
- **Active R — Quantum Rift Barrier** (Rank 1/5): Project a distortion field for 6s that slows enemy bullets by $80\%$ and amplifies allied projectiles passing through by $+30\%$. (Cost: 35 Mana, CD: 18s).
- **Active F — Singularity Collapse** (Rank 1/5): Spawn a gravitational vortex at target location, pulling all enemies inward before detonating for $450\%$ spatial damage. (Cost: 60 Mana, CD: 40s).
- **Passive 1 — Arcane Flux**: $+15\%$ Maximum Mana.
- **Passive 2 — Overclocked Wands**: Wand and staff firing speed increased by $+20\%$.
- **Passive 3 — Static Discharge**: Casting a spell charges next physical attack with $+25$ electric damage.
- **Passive 4 — Superconductor**: Chain lightning spells chain to $+2$ additional targets.
- **Passive 5 — Mana Shield**: $25\%$ of incoming damage is subtracted from Mana before affecting Health.
- **Passive 6 — Thermodynamic Shift**: Burning targets hit with frost spells shatter for $+35\%$ bonus damage.
- **Passive 7 — Cyber-Arcane Resonance**: Spell damage increased by $+0.5\%$ per point of CYB.
- **Passive 8 — Essence Battery**: Defeating an enemy with a spell restores $4\%$ Max Mana and 5 Power.
- **Passive 9 — Plasma Infusion**: Energy weapon kills grant $+10\%$ spell damage for 8s (stacks 3 times).
- **Passive 10 — Channeled Speed**: Casting channeled spells grants $+20\%$ movement speed while channeling.
- **Passive 11 — Archmage Circuitry**: Cooldowns of all active spells reduced by $15\%$.

#### Free Level 20 Signature Augmentation
- **Item**: *Runic Micro-Reactor Core*
- **Slot**: Heart / Core
- **Type**: Magitech (Free Signature: 0 Humanity penalty, 0 Stability upkeep)
- **Effects**: Generates 20 Power/s; converts $50\%$ of all power generated into continuous Mana regeneration; grants $+100$ Max Mana and $+50$ Max Power.

---

### Class 6: Medic / Biomancer (The Nanite Restorer)

#### Overview & Role
A combat surgeon and genetic healer. Masters self-repair nanites, toxic contagion clouds, medical darts, and bio-shields to maintain survivability while decaying enemies from the inside.

- **Starting Attributes**: STR: 7, DEX: 8, VIT: 12, INT: 10, WIS: 14, CYB: 6.
- **Starting Derived Stats**: HP: $220$, Stamina: $50$, Mana: $90$, Power: $60$, Humanity: $100$, Stability: $100$.
- **Starting Equipment**: Pneumatic Syringe Gun (15 physical/toxin dmg, fires needle darts), Bio-Hazard Suit (+8 Armor, immune to natural poison), 5x Medical Nanite Packs.
- **Signature Mechanic — Nanite Hive Aura**: Continuously radiates a 4-tile bio-aura: allies and self regenerate $2.0\text{ HP/s}$, while enemies inside suffer continuous cellular decay ($15\text{ toxin dmg/s}$).

#### Class Skill Tree (15 Nodes: 4 Actives, 11 Passives)
- **Active Q — Nanite Dart** (Rank 1/5): Fire a smart syringe. If hitting ally/self: heals 80 HP over 4s. If hitting enemy: deals 100 toxin damage and shreds armor by $20\%$ for 6s. (Cost: 20 Mana, CD: 4s).
- **Active E — Healing Field Beacon** (Rank 1/5): Throw a medical pylon creating a 6-tile radius circle restoring $15\text{ HP/s}$ and cleansing debuffs for 10s. (Cost: 30 Power, CD: 16s).
- **Active R — Bio-Contagion Cloud** (Rank 1/5): Release an expanding spore cloud dealing continuous necrotic damage; killed enemies burst, spreading the cloud. (Cost: 35 Mana, CD: 14s).
- **Active F — Cellular Overdrive** (Rank 1/5): Flood system with adrenal nanites: instantly restores $50\%$ Max HP and grants $+30\%$ move and attack speed for 8s. (Cost: 50 Mana, CD: 45s).
- **Passive 1 — Hippocratic Mastery**: All healing performed and received increased by $+15\%$.
- **Passive 2 — Antidote Synthesis**: Complete immunity to natural poisons, venoms, and acid rain.
- **Passive 3 — Needle Velocity**: Syringe and dart weapons gain $+30\%$ projectile speed and pierce.
- **Passive 4 — Sympathetic Transfusion**: Healing summons or friendly NPCs restores $25\%$ of that amount to the player.
- **Passive 5 — Nanite Overshield**: Healing received while at $100\%$ HP converts into a temporary barrier up to $20\%$ Max HP.
- **Passive 6 — Leeching Strike**: Melee attacks heal the player for $3\%$ of damage dealt.
- **Passive 7 — Surgical Scalpels**: One-handed blades and daggers gain $+15\%$ critical strike chance.
- **Passive 8 — Defibrillator Pulse**: Electric damage inflicted on enemies has a $20\%$ chance to stun them for 2s.
- **Passive 9 — Adrenal Mist**: Healing Field Beacon also grants $+50\%$ stamina regeneration to allies inside.
- **Passive 10 — Biomass Harvesting**: Gathering wild plants yields double herbs and alchemical reagents.
- **Passive 11 — Cellular Resilience**: Base health regeneration permanently increased by $+1.5\text{ HP/s}$.

#### Free Level 20 Signature Augmentation
- **Item**: *Subdermal Cellular Replicator*
- **Slot**: Skin / Dermis
- **Type**: Bionic (Free Signature: 0 Humanity penalty, 0 Power upkeep)
- **Effects**: Prevents fatal damage once every 300s, instantly restoring the player to $50\%$ Max HP and emitting a blinding flash that stuns nearby attackers for 3s.

---

### Class 7: Symbiote (The Chimeric Shifter)

#### Overview & Role
A wild hybrid that has grafted living beast dna and chimeric tissue into their flesh. Seamlessly transforms between specialized primal forms to dominate close-quarters combat and rugged survival.

- **Starting Attributes**: STR: 12, DEX: 10, VIT: 14, INT: 6, WIS: 10, CYB: 4.
- **Starting Derived Stats**: HP: $240$, Stamina: $70$, Mana: $80$, Power: $40$, Humanity: $90$, Stability: $90$.
- **Starting Equipment**: Grafted Chitin Claws (16 physical dmg), Living Moss Wrap (+6 Armor, +1 HP/s in daylight), 3x Wild Jerky.
- **Signature Mechanic — Metamorphic Forms**: Pressing `E` toggles between two specialized beast forms without cooldown:
  - **Ursine Form**: $+50\%$ Armor, $+25\%$ Max HP, $+30\%$ Knockback, $-15\%$ Movement Speed.
  - **Lupine Form**: $+30\%$ Movement Speed, $+50\%$ Jump Height, $+20\%$ Attack Speed, $-15\%$ Armor.

#### Class Skill Tree (15 Nodes: 4 Actives, 11 Passives)
- **Active Q — Chimeric Maul** (Rank 1/5): Vicious claw slash dealing $180\%$ physical damage; restores 8 Stamina on hit. (Cost: 15 Stamina, CD: 3s).
- **Active E — Form Shift (Ursine / Lupine)**: Toggles active metamorphosis form. (Cost: 10 Mana, CD: 1s).
- **Active R — Briar Bramble Entanglement** (Rank 1/5): Summon a patch of thorned roots that traps enemies for 3s and deals continuous bleed/nature damage. (Cost: 20 Mana, CD: 8s).
- **Active F — Apex Chimera Unleashed** (Rank 1/5): Grow massive chimeric wings and venomous horns for 10s: grants flight, double melee range, and shockwaves on every attack. (Cost: 40 Mana, CD: 35s).
- **Passive 1 — Feral Senses**: Highlights all enemies and prey animals within 30 tiles on the minimap.
- **Passive 2 — Grafted Fortitude**: $+120$ flat Max Health.
- **Passive 3 — Stalker's Stride**: Movement speed in forests, caves, and swamps increased by $+20\%$.
- **Passive 4 — Chitin Spikes**: Reflects $15\%$ of incoming melee damage back onto the attacker.
- **Passive 5 — Photosynthesis**: Outdoors in daylight, regenerate $1.0\text{ HP/s}$ and $1.0\text{ MP/s}$.
- **Passive 6 — Savage Rend**: Claw attacks apply Deep Wound, reducing target armor by $5\%$ per hit (up to $25\%$).
- **Passive 7 — Primal Stamina**: Stamina regeneration delay after performing actions reduced by $50\%$.
- **Passive 8 — Rooted Stance**: Standing still for 1.0s increases physical resistance by $+25\%$.
- **Passive 9 — Chimeric Vitality**: Meat food items grant triple the duration of hunger satisfaction.
- **Passive 10 — Pack Instinct**: Summons, tamed pets, and friendly creatures gain $+30\%$ health and damage.
- **Passive 11 — Adaptive Carapace**: Taking elemental damage reduces subsequent damage of that same element by $20\%$ for 8s.

#### Free Level 20 Signature Augmentation
- **Item**: *Symbiotic Chimeric Carapace*
- **Slot**: Torso
- **Type**: Chimeric (Free Signature: 0 Stability upkeep, 0 Mana upkeep)
- **Effects**: Living carapace covers chest and back; generates $2\%$ Max HP and $2\%$ Max Stamina every 3s; grants $+30$ Armor and $+20$ Cold/Heat resistance.

---

### Class 8: Warden (The Hard-Light Templar)

#### Overview & Role
A righteous bastion wielding hard-light energy emitters and holy zeal. Uses defensive forcefields, projectile-deflecting shields, and concentrated beams of solar judgment to protect ground and smite corruption.

- **Starting Attributes**: STR: 12, DEX: 7, VIT: 12, INT: 10, WIS: 8, CYB: 8.
- **Starting Derived Stats**: HP: $220$, Stamina: $60$, Mana: $70$, Power: $70$, Humanity: $100$, Stability: $100$.
- **Starting Equipment**: Radiant Broadsword (18 physical/holy dmg), Hard-Light Deflector Shield (Blocks 75%), Crusader Breastplate (+14 Armor), 3x Holy Salves.
- **Signature Mechanic — Aegis Retaliation**: Holding RMB raises a hard-light barrier. Perfectly timing a block right before an enemy hit deflects projectiles and stuns melee attackers, empowering next attack with $+100\%$ holy damage.

#### Class Skill Tree (15 Nodes: 4 Actives, 11 Passives)
- **Active Q — Radiant Smite** (Rank 1/5): Infuse weapon with blazing plasma, striking for $220\%$ holy/energy damage and blinding target for 2.5s. (Cost: 18 Mana, CD: 4s).
- **Active E — Bastion Shield Bash** (Rank 1/5): Dash forward with shield raised, deflecting all projectiles and knocking enemies back 5 tiles with a 1.5s stun. (Cost: 15 Stamina, CD: 6s).
- **Active R — Consecrated Dome** (Rank 1/5): Consecrate an 8-tile zone for 8s: allies gain $+20$ Armor and $12\text{ HP/s}$; undead and cybernetic enemies take $25\text{ holy dmg/s}$. (Cost: 30 Mana, CD: 15s).
- **Active F — Dawn Ray Judgment** (Rank 1/5): Channel a brilliant vertical pillar of light from the sky for 3s dealing continuous ticks of $140\%$ holy damage. (Cost: 50 Mana, CD: 35s).
- **Passive 1 — Vanguard Resolve**: Armor increased by $+12\%$ while wielding any shield.
- **Passive 2 — Righteous Retribution**: Parrying an attack releases a burst of light dealing 45 damage to nearby foes.
- **Passive 3 — Unwavering Faith**: Debuff and status effect durations suffered reduced by $30\%$.
- **Passive 4 — Shield Wall**: Projectiles striking the shield have a $40\%$ chance to ricochet straight back at the shooter.
- **Passive 5 — Bulwark Aura**: Standing within 6 tiles of friendly NPCs or pets grants them $+20\%$ damage mitigation.
- **Passive 6 — Hard-Light Blades**: All weapon attacks deal an additional $+15\%$ holy/energy damage.
- **Passive 7 — Beacon of Hope**: Healing potions heal an additional $+25\%$ health.
- **Passive 8 — Zealot's Stride**: Armor weight movement penalties reduced by $100\%$.
- **Passive 9 — Holy Vengeance**: Dropping below $25\%$ HP triggers an automatic flash of light blinding enemies for 4s (90s CD).
- **Passive 10 — Sanctified Metal**: Melee strikes deal $+35\%$ bonus damage against undead, demons, and corrupted machines.
- **Passive 11 — Divine Bastion**: $+100$ Max Health and $+60$ Max Mana.

#### Free Level 20 Signature Augmentation
- **Item**: *Hard-Light Aegis Projector*
- **Slot**: Left Arm
- **Type**: Magitech (Free Signature: 0 Humanity penalty, 0 Power upkeep)
- **Effects**: Generates an invulnerable 6-second dome shield (cooldown 45s) that blocks all hostile projectiles while allowing allied attacks to shoot out freely.

---

### Class 9: Reanimator (The Cyber-Necromancer)

#### Overview & Role
A grim technician who commands both cybernetic drones and reanimated biomechanical corpses. Collects soul fragments and discarded scrap from fallen foes to construct an autonomous army.

- **Starting Attributes**: STR: 6, DEX: 7, VIT: 8, INT: 15, WIS: 8, CYB: 12.
- **Starting Derived Stats**: HP: $180$, Stamina: $50$, Mana: $110$, Power: $90$, Humanity: $90$, Stability: $90$.
- **Starting Equipment**: Scrap Scythe (15 dark dmg), Soul Siphon Wand (12 dmg, siphons souls), Servo-Jacket (+6 Armor, +1 Minion Capacity), 3x Battery Cells.
- **Signature Mechanic — Soul Assembler**: Slaying enemies yields Soul Fragments. The Reanimator consumes these fragments to build and maintain up to 4 autonomous minions (flying laser drones or cyber-skeletal warriors).

#### Class Skill Tree (15 Nodes: 4 Actives, 11 Passives)
- **Active Q — Soul Harvest Dart** (Rank 1/5): Siphon life energy from target dealing 90 dark damage and generating 1 guaranteed Soul Fragment. (Cost: 15 Mana, CD: 3s).
- **Active E — Fabricate Minion (Drone / Thrall)** (Rank 1/5): Assemble a minion: Drone fires ranged lasers; Thrall engages in melee with bone-blades. (Cost: 1 Soul Fragment, CD: 5s).
- **Active R — Corpse Detonation** (Rank 1/5): Detonate a target minion or fallen enemy corpse in an acidic shrapnel blast dealing $260\%$ damage. (Cost: 20 Mana, CD: 6s).
- **Active F — Swarm Overdrive** (Rank 1/5): Overclock all active minions for 10s: they grow $50\%$ larger, gain $+100\%$ attack speed, and radiate radioactive poison. (Cost: 50 Mana, CD: 40s).
- **Passive 1 — Harvest Protocol**: Defeating any enemy has a $35\%$ chance to automatically yield a Soul Fragment.
- **Passive 2 — Reinforced Chassis**: Minions gain $+40\%$ Max Health and $+15$ Armor.
- **Passive 3 — Drone Multi-Beam**: Laser drones fire 2 parallel beams instead of 1.
- **Passive 4 — Necrotic Siphon**: Whenever a minion strikes an enemy, the player restores 2 HP and 1 Mana.
- **Passive 5 — Dark Metallurgy**: Crafting and repairing gear costs $20\%$ less metal and scrap.
- **Passive 6 — Expanded Hangar**: Maximum minion cap increased by $+2$ (Total 6 active minions).
- **Passive 7 — Acidic Fallout**: Corpse detonations leave an acid pool on the floor dealing damage for 5s.
- **Passive 8 — Unholy Resonator**: Minion attack damage increased by $+1.5\%$ per point of INT.
- **Passive 9 — Self-Destruct Matrix**: Minions explode automatically upon death dealing $150\%$ damage to nearby enemies.
- **Passive 10 — Shadow Ward**: While at least 2 minions are alive, the player takes $15\%$ less damage from all sources.
- **Passive 11 — Master of the Grave**: Minions inherit $50\%$ of the player's critical strike chance and armor penetration.

#### Free Level 20 Signature Augmentation
- **Item**: *Automated Minion Assembler Spine*
- **Slot**: Nervous System
- **Type**: Bionic (Free Signature: 0 Humanity penalty, 0 Power upkeep)
- **Effects**: Installed along the spine; whenever a minion dies, it is automatically reassembled instantly without consuming Soul Fragments (cooldown 12s).
