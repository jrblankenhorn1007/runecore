# Universal Common Skill Trees: Survival, Cybernetics, Mobility & General Combat

This document specifies the four Universal Skill Trees available to **all 9 classes** in Untitled RPG. These skill trees ensure that every character can tailor their survival capabilities, mobility mechanics, augmentation integration, and base combat proficiencies regardless of their starting archetype.

---

## 1. Universal Progression Mechanics
- **Uncapped Learning**: All universal skills are purchased with universal Skill Points ($SP$) gained upon leveling up (1 SP per level) or discovering ancient Precursor Datacubes / Monoliths.
- **No Class Restrictions**: Any class can invest in any node as long as prerequisites and level requirements are met.
- **Dual Resource Synergy**: Skills leverage both Mana and Bionic Power pools, allowing seamless hybrid builds.

---

## 2. Common Skill Tree 1: Wilderness & Base Survival (20 Skills)

| ID | Skill Name | Type | Req Lvl | Prerequisite | Mechanics & Stat Scaling |
|---|---|---|---|---|---|
| SURV-01 | **Iron Stomach** | Passive | 1 | None | Decreases food poisoning chance by 50%; spoiled food restores 50% normal hunger. |
| SURV-02 | **Efficient Metabolism** | Passive | 3 | SURV-01 | Hunger and Thirst depletion rates are reduced by 15% (+1% per point, max 30%). |
| SURV-03 | **Forager's Eye** | Passive | 1 | None | Forageable plants, berries, and herbs are highlighted through terrain; +25% harvest yield. |
| SURV-04 | **Field Triage** | Active (0 MP) | 5 | SURV-01 | Bandages and medical consumables apply 40% faster and stop bleeding immediately. (Cooldown: 15s) |
| SURV-05 | **Campfire Master** | Passive | 5 | SURV-03 | Campfires and field stoves burn fuel 50% longer; cooking food gives +10% bonus stat duration. |
| SURV-06 | **Thermal Adaptation** | Passive | 8 | SURV-02 | +15 Cold Resistance and +15 Heat Resistance; delays hypothermia/hyperthermia onset by 30s. |
| SURV-07 | **Pack Mule** | Passive | 10 | None | Increases base inventory weight capacity by +25kg (+5kg per rank). |
| SURV-08 | **Deep Diver's Breath** | Passive | 12 | SURV-06 | Increases underwater lung capacity by +100%; reduces drowning damage tick rate by 50%. |
| SURV-09 | **Mineral Prospector** | Passive | 10 | SURV-03 | Ore veins within 12 tiles shimmer faintly; pickaxes deal +25% damage to mineral blocks. |
| SURV-10 | **Trapper's Knowledge** | Passive | 14 | SURV-05 | Crafted animal snares and pit traps deal +50% damage and capture small game 2x faster. |
| SURV-11 | **Field Butchery** | Passive | 16 | SURV-10 | Harvesting animal corpses yields +50% meat, hides, and rare monster trophies. |
| SURV-12 | **Fortified Architecture** | Passive | 18 | SURV-07 | Player-built structures (walls, doors, platforms) have +35% maximum durability. |
| SURV-13 | **Hydro-Electrician** | Passive | 20 | SURV-12 | Generators produce +20% more power output; irrigation pipes water crops 25% faster. |
| SURV-14 | **Shelter Comfort** | Passive | 22 | SURV-12 | Resting in an enclosed base grants the "Well-Rested" buff (+15% XP gain for 30 minutes). |
| SURV-15 | **Immune Fortification** | Passive | 25 | SURV-06 | Increases resistance to Poison, Rot, Radiation, and Bleed status effects by +30%. |
| SURV-16 | **Salvage Scavenger** | Passive | 28 | SURV-09 | Breaking technological scrap and crates yields +40% electronic components and copper wire. |
| SURV-17 | **Botanical Green Thumb** | Passive | 30 | SURV-03 | Farmed crops have a 25% chance to immediately re-seed themselves upon harvest. |
| SURV-18 | **Emergency Shelter Drop** | Active (50 MP) | 35 | SURV-14 | Deploys a temporary 3x3 nano-barrier that blocks enemy projectiles and harsh weather for 20s. (CD: 120s) |
| SURV-19 | **Apex Hunter's Instinct** | Passive | 40 | SURV-11 | Mini-bosses and elite monsters appear on the minimap within a 60-tile radius. |
| SURV-20 | **Survival Sovereign** | Passive | 50 | SURV-15, 19 | When taking fatal damage, survive at 1 HP with 4 seconds of invulnerability. (Cooldown: 600s) |

---

## 3. Common Skill Tree 2: Bionic Integration & Cybernetics (15 Skills)

| ID | Skill Name | Type | Req Lvl | Prerequisite | Mechanics & Stat Scaling |
|---|---|---|---|---|---|
| CYB-01 | **Internal Wiring** | Passive | 1 | None | Increases Max Bionic Power capacity by +25 (+5 per rank). |
| CYB-02 | **Subdermal Grounding** | Passive | 5 | CYB-01 | Reduces electrical shock damage taken by 25%; eliminates power drain from EMP status. |
| CYB-03 | **Dynamo Overdrive** | Active (20 Pwr)| 8 | CYB-01 | Instantly vents 20 Power to grant +20% movement speed and attack speed for 6 seconds. (CD: 25s) |
| CYB-04 | **Thermal Dissipation** | Passive | 10 | CYB-02 | Reduces overheating penalty on energy weapons and rapid-fire bionics by 30%. |
| CYB-05 | **Prosthetic Re-Calibration**| Passive | 12 | CYB-01 | Bionic limb augmentations grant +10% additional base attribute points (STR/DEX). |
| CYB-06 | **Biocompatibility Matrix** | Passive | 15 | CYB-05 | Lowers total Cybernetic Strain by 20%, allowing heavier bionic implants without penalty. |
| CYB-07 | **Kinetic Capacitor** | Passive | 18 | CYB-03 | Moving, jumping, and taking physical hits generates +2 Bionic Power per second. |
| CYB-08 | **Micro-Thruster Burst** | Active (15 Pwr)| 20 | CYB-07 | Fires directional palm/heel thrusters to perform an omnidirectional aerial dash. (CD: 6s) |
| CYB-09 | **Nanite Auto-Stitcher** | Passive | 25 | CYB-06 | When HP drops below 30%, automatically consumes 30 Power to heal 15% Max HP over 3s. (CD: 45s) |
| CYB-10 | **Ocular Weakpoint Scanner** | Passive | 28 | CYB-05 | Head/eye augmentations grant +8% Critical Strike Chance against mechanical and cyborg enemies. |
| CYB-11 | **Power Conduit Siphon** | Passive | 32 | CYB-07 | Killing robotic or electronic foes restores 15 Bionic Power and 5% shield durability. |
| CYB-12 | **High-Voltage Arc Discharge**| Active (35 Pwr)| 36 | CYB-08 | Discharges an omnidirectional EMP shockwave dealing 80 Shock Dmg and stunning nearby foes for 2s. (CD: 30s) |
| CYB-13 | **Surgical Overhaul** | Passive | 40 | CYB-06 | Unlocks a 12th hidden augmentation micro-socket in the Neural Matrix slot. |
| CYB-14 | **Precursor Code Translation**| Passive | 45 | CYB-10 | Automated turrets and defense drones deal +25% damage and track targets 50% faster. |
| CYB-15 | **Singularity Battery Core** | Passive | 55 | CYB-13 | Doubles Max Bionic Power capacity; passive power regeneration rate increased by +100%. |

---

## 4. Common Skill Tree 3: Acrobatic Mobility & Traversal (15 Skills)

| ID | Skill Name | Type | Req Lvl | Prerequisite | Mechanics & Stat Scaling |
|---|---|---|---|---|---|
| MOB-01 | **Agile Footing** | Passive | 1 | None | Increases base movement and sprint speed by +8%. |
| MOB-02 | **Ledge Grab & Vault** | Passive | 3 | MOB-01 | Player automatically latches onto platform ledges and vaults upward effortlessly. |
| MOB-03 | **Wall Slide & Kick** | Passive | 5 | MOB-02 | Allows sliding down vertical walls to slow falls; pressing Jump performs a Wall Jump. |
| MOB-04 | **Double Jump** | Passive | 8 | MOB-03 | Grants an additional jump mid-air (50% normal jump height). |
| MOB-05 | **Roll & Break Fall** | Passive | 10 | MOB-01 | Landing from extreme heights triggers an automatic combat roll, nullifying fall damage up to 20 blocks. |
| MOB-06 | **Combat Slide** | Active (15 Sta)| 12 | MOB-05 | Crouching while sprinting executes a low-profile slide under obstacles, evading high attacks. |
| MOB-07 | **Air Dash** | Active (20 Sta)| 15 | MOB-04 | Propels the character horizontally forward through the air with 0.25s of invulnerability frames. (CD: 4s) |
| MOB-08 | **Fluid Momentum** | Passive | 18 | MOB-07 | Chaining a slide, wall jump, and dash increases movement speed by +25% for 4 seconds. |
| MOB-09 | **Cat-Like Reflexes** | Passive | 22 | MOB-05 | Increases base Dodge/Evasion chance by +6%; recovery time from knockdowns is halved. |
| MOB-10 | **Triple Jump Surge** | Passive | 26 | MOB-04 | Upgrades Double Jump to a Triple Jump; third jump leaves a small kinetic shockwave. |
| MOB-11 | **Grapple Line Mastery** | Passive | 30 | MOB-03 | Grappling hooks and zip-lines reel in 40% faster and have +5 blocks extended reach. |
| MOB-12 | **Phase Slip** | Active (25 MP) | 35 | MOB-09 | Dematerializes into an ethereal mist for 1.2 seconds, phasing through enemies and hazards. (CD: 18s) |
| MOB-13 | **Sonic Sprint** | Passive | 40 | MOB-08 | Sprinting continuously for 3 seconds builds super-speed (+40% speed), breaking through wooden barricades. |
| MOB-14 | **Zero-G Aerodynamics** | Passive | 45 | MOB-10 | Air friction is reduced by 50%; horizontal aerial control and glide distance increased by +35%. |
| MOB-15 | **Blink Step** | Active (30 MP) | 55 | MOB-12 | Instantly teleports 8 tiles in the aimed direction, resetting air-jump counter. (CD: 10s) |

---

## 5. Common Skill Tree 4: General Combat & Weapon Drills (15 Skills)

| ID | Skill Name | Type | Req Lvl | Prerequisite | Mechanics & Stat Scaling |
|---|---|---|---|---|---|
| CMB-01 | **Weapon Handling Fundamentals** | Passive | 1 | None | Increases all physical and elemental weapon damage by +5%. |
| CMB-02 | **Quickdraw Reflexes** | Passive | 3 | CMB-01 | Weapon swapping speed is increased by +50%; grants +10% crit chance for 2s after swapping. |
| CMB-03 | **Precision Stance** | Passive | 6 | CMB-01 | Standing still for 1.5 seconds tightens weapon spread by 40% and grants +8% Critical Chance. |
| CMB-04 | **Armor Conditioning** | Passive | 8 | None | Reduces the movement speed penalty of Heavy and Medium armor by 50%. |
| CMB-05 | **Guard Deflection** | Active (15 Sta)| 10 | CMB-04 | Raising a weapon or shield within 0.2s of an enemy strike parries the hit, staggering the foe. |
| CMB-06 | **Point-Blank Execution** | Passive | 14 | CMB-02 | Attacks against enemies within 3 tiles deal +15% damage. |
| CMB-07 | **Bleed Opportunist** | Passive | 18 | CMB-01 | Attacks against bleeding or burning targets deal +12% bonus damage. |
| CMB-08 | **Second Wind** | Active (0 MP) | 22 | CMB-04 | Instantly restores 100% Stamina and grants 25% stamina cost reduction for 8 seconds. (CD: 60s) |
| CMB-09 | **Armor Piercer** | Passive | 26 | CMB-06 | All physical attacks ignore 15% of the enemy's total armor rating. |
| CMB-10 | **Culling the Weak** | Passive | 30 | CMB-07 | Enemies with less than 20% health take +30% increased damage from all sources. |
| CMB-11 | **Battle Frenzy** | Passive | 35 | CMB-10 | Killing an enemy grants +5% attack speed and +3% movement speed for 6s (stacks up to 5 times). |
| CMB-12 | **Defensive Bulwark** | Passive | 40 | CMB-05 | When suffering a critical hit, gain a barrier absorbing damage equal to 20% Max HP for 4s. (CD: 40s) |
| CMB-13 | **Relentless Assault** | Passive | 45 | CMB-11 | Landing 5 consecutive hits without taking damage increases Critical Damage by +40%. |
| CMB-14 | **Tactical Reload / Resheathe** | Passive | 50 | CMB-02 | Emptying a magazine or executing a combo finisher automatically grants a 2-second speed burst (+25%). |
| CMB-15 | **Grandmaster of War** | Passive | 60 | CMB-09, 13 | All weapon damage increased by +15%; critical strikes have a 20% chance to duplicate hit damage. |
