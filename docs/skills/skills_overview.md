# Skills & Skill Trees Specification

This document defines the architecture, data schemas, mathematical progression, execution pipeline, and complete specifications for the 500+ active and passive skills in Untitled RPG.

---

## 1. Skill Tree Architecture & Allocation Rules

### 1.1 Progression, Uncapped Scaling & Universal Mastery
- **Level Cap**: **Uncapped** ($1 \to \infty$). Campaign balance targets Level 60 for the final boss encounter against The Architect, but leveling continues indefinitely into the Infinite Rift.
- **Over 500 Total Skills**:
  - 9 Classes with deep 50-node trees (approx. 450 class-specific skills across all archetypes).
  - 40-node Shared Traversal, Combat, and Survival Tree.
  - 48-node Crafting & Engineering Tree.
  - Total catalog: **> 530 unique active and passive skills**.
- **Universal Skill Learning**:
  - While players begin with their selected class tree, reaching Level 60 activates the **Cross-Class Neural Bridge** in the Hub settlement.
  - Players can invest skill points into any other class tree, eventually learning every single skill in the game and ascending to godhood.
- **Points Economy**:
  - Earn 1 Class/Specialization Point and 1 Shared/Crafting Point on every level-up infinitely.
- **Skill Hotbars**:
  - Exactly 4 active skills can be assigned to hotkeys at any time (`Q`, `E`, `R`, `F`).
  - Active skills can come from any unlocked class tree or installed body augmentations.

### 1.2 DAG (Directed Acyclic Graph) & Dependency Rules
- Every node in a tree defines:
  - `id`: Unique string identifier (e.g. `skill_shared_double_jump`).
  - `tier`: Depth in the tree (Tier 1 through Tier 4).
  - `prerequisites`: Array of required node IDs that must have at least 1 rank allocated before unlocking.
  - `requiredPointsInTree`: Minimum total points spent in that tree branch before unlocking higher tiers.
  - `maxRanks`: Maximum point investment (1, 3, or 5).
- **Respec System**:
  - The player can reset allocated skill points at the Hub Trainer NPC (Master Thorne).
  - Cost: 50 gold per allocated point refunded.
  - Respec refunds all points cleanly, recalculating derived stats and unbinding hotkeys.

---

## 2. Complete Shared Skill Tree (40 Nodes)

The Shared Tree is open to all characters regardless of class. It is divided into 4 thematic branches of 10 nodes each.

```
                  [Central Root: Survival Instincts]
                  /           |           |           \
     [Branch 1]          [Branch 2]   [Branch 3]     [Branch 4]
[Mobility & Traversal]  [Survival]   [Weapons/Guns] [Crafting/Tech]
     (10 Nodes)          (10 Nodes)   (10 Nodes)     (10 Nodes)
```

---

### Branch 1: Mobility & Traversal (10 Nodes)

| Node ID | Name | Max Ranks | Prerequisites | Effect per Rank |
|---|---|---|---|---|
| `mob_01` | *Swiftfoot* | 3 | None | $+3\% / +6\% / +10\%$ Base Movement Speed. |
| `mob_02` | *Agile Leap* | 3 | `mob_01` | $+5\% / +10\% / +15\%$ Maximum Jump Height. |
| `mob_03` | *Double Jump* | 1 | `mob_02` | Allows a second jump in mid-air. Consumes 10 Stamina. |
| `mob_04` | *Wall Cling & Slide* | 1 | `mob_02` | Touching a vertical wall slows fall speed by $75\%$ and allows wall-jumping. |
| `mob_05` | *Air Dash* | 2 | `mob_03`, `mob_04` | Pressing `Shift` in air performs a horizontal burst. Rank 1: 4-tile distance; Rank 2: 6-tile distance + 3 i-frames. |
| `mob_06` | *Feather Fall* | 2 | `mob_02` | Fall damage threshold raised; fall damage taken reduced by $35\% / +70\%$. |
| `mob_07` | *Pneumatic Sprint* | 3 | `mob_01` | Sprinting speed bonus increased from $+30\%$ to $+40\% / +50\% / +60\%$. |
| `mob_08` | *Ledge Clamber* | 1 | `mob_04` | Automatically vault over 1-2 tile high ledges without needing to jump. |
| `mob_09` | *Rocket Recovery* | 1 | `mob_05` | Pressing Jump while knocked down immediately recovers to feet, releasing a small knockback burst. |
| `mob_10` | *Terminal Impact* | 2 | `mob_06`, `mob_09` | Holding `S` while falling accelerates downwards; creates a ground shockwave on landing dealing $100 / 200$ physical damage. |

---

### Branch 2: Survival & Constitution (10 Nodes)

| Node ID | Name | Max Ranks | Prerequisites | Effect per Rank |
|---|---|---|---|---|
| `surv_01` | *Hearty Metabolism* | 3 | None | Maximum Hunger bar increased by $+15\% / +30\% / +50\%$. |
| `surv_02` | *Camel's Endurance* | 3 | None | Thirst depletion rate reduced by $15\% / +30\% / +45\%$. |
| `surv_03` | *Insulated Dermis* | 3 | `surv_01`, `surv_02` | Resistance to environmental freezing and heatstroke $+10\% / +20\% / +35\%$. |
| `surv_04` | *Iron Stomach* | 1 | `surv_01` | Eating raw meat or unpurified water grants 0 risk of food poisoning or parasites. |
| `surv_05` | *Deep Slumber* | 2 | `surv_03` | Resting at beds or campfires recovers HP and Stamina $50\% / +100\%$ faster. |
| `surv_06` | *Brawny Spine* | 3 | `surv_01` | Maximum inventory carry weight increased by $+10\text{ kg} / +20\text{ kg} / +35\text{ kg}$. |
| `surv_07` | *Gourmet Nutrition* | 2 | `surv_04` | Consuming cooked meals increases stat buff durations by $+50\% / +100\%$. |
| `surv_08` | *Well-Fed Vigor* | 2 | `surv_07` | When Hunger and Thirst are both above $80\%$, gain $+8 / +15$ Armor and $+5\% / +10\%$ Move Speed. |
| `surv_09` | *Second Wind* | 1 | `surv_05` | When Stamina reaches 0, instantly restores $50\%$ Stamina (120s cooldown). |
| `surv_10` | *Inoculation* | 2 | `surv_03`, `surv_08` | Poison, burn, bleed, and frostbite durations against the player reduced by $25\% / +50\%$. |

---

### Branch 3: Weapons & Combat Mastery (10 Nodes)

| Node ID | Name | Max Ranks | Prerequisites | Effect per Rank |
|---|---|---|---|---|
| `comb_01` | *Honed Edges* | 3 | None | Physical melee weapon damage increased by $+3\% / +6\% / +10\%$. |
| `comb_02` | *Steady Hands* | 3 | None | Projectile spread and bullet inaccuracy reduced by $15\% / +30\% / +45\%$. |
| `comb_03` | *Executioner* | 3 | `comb_01` | Critical strike damage multiplier increased by $+0.15\times / +0.30\times / +0.50\times$. |
| `comb_04` | *Speed Loader* | 2 | `comb_02` | Reload speed of ballistic firearms increased by $+20\% / +40\%$. |
| `comb_05` | *Power Conduit* | 2 | `comb_02` | Energy weapon power drain per shot reduced by $15\% / +30\%$. |
| `comb_06` | *Heavy Impact* | 2 | `comb_01` | Knockback imparted to enemies increased by $+20\% / +40\%$. |
| `comb_07` | *Armor Piercer* | 3 | `comb_03` | Attacks ignore $4 / 8 / 12$ points of enemy physical and energy armor. |
| `comb_08` | *Adrenaline Surge* | 2 | `comb_06` | Slaying an elite or boss restores $10\% / +20\%$ Max Health and $15 / 30$ Power. |
| `comb_09` | *Point-Blank Brawler* | 2 | `comb_04` | Firearms and wands deal $+15\% / +30\%$ damage against targets within 3 tiles. |
| `comb_10` | *Master of Arms* | 1 | `comb_07`, `comb_09` | Weapon swapping delay reduced by $60\%$; weapon stamina cost reduced by $20\%$. |

---

### Branch 4: Crafting, Engineering & Scavenging (10 Nodes)

| Node ID | Name | Max Ranks | Prerequisites | Effect per Rank |
|---|---|---|---|---|
| `craft_01` | *Scrap Hound* | 3 | None | Defeated enemies and broken containers drop $+15\% / +30\% / +50\%$ more scrap and credits. |
| `craft_02` | *Efficient Smelting* | 2 | None | Smelting ores into ingots at the forge uses $25\% / +50\%$ less coal/fuel. |
| `craft_03` | *Fortified Architecture* | 2 | `craft_01` | Placed walls, doors, and barricades gain $+40\% / +80\%$ Max Durability. |
| `craft_04` | *Artisan Machinist* | 2 | `craft_02` | Crafted weapons and armor have a $25\% / +50\%$ chance to roll an extra affix slot. |
| `craft_05` | *Alchemical Efficiency*| 2 | `craft_02` | Brewing potions produces an extra bonus potion $20\% / +40\%$ of the time. |
| `craft_06` | *Battery Tuning* | 3 | `craft_01` | Installed bionic augmentations gain $+10\% / +20\% / +30\%$ Max Power capacity. |
| `craft_07` | *Green Thumb* | 2 | `craft_05` | Farm crops grow $20\% / +40\%$ faster. |
| `craft_08` | *Scrapper's Eye* | 2 | `craft_04` | Dismantling equipment refunds $75\% / +90\%$ of raw crafting ingredients (up from $50\%$). |
| `craft_09` | *Reinforced Settlement* | 2 | `craft_03` | Settlement structures take $50\% / +75\%$ less damage from enemy night raids. |
| `craft_10` | *Master Cyber-Artificer*| 1 | `craft_06`, `craft_08` | Reduces credit and material cost of Cyber-Clinic surgeries by $30\%$. |

---

## 3. Class Skill Tree Specifications

Each of the 9 classes possesses a 15-node tree containing 4 active skills (assigned to hotkeys `Q`, `E`, `R`, `F`) and 11 passive nodes. For full thematic descriptions and base values, see [docs/design/classes.md](docs/design/classes.md).

### 3.1 Mathematical Scaling Formula for Actives
All active skills calculate outgoing damage and effectiveness using:
$$\text{Skill Damage} = \text{Base Damage} \times (1.0 + (\text{Rank} - 1) \times 0.25) \times (1.0 + \text{Attribute Scaling}) \times \text{Affix Multipliers}$$
- Cooldown decreases by $8\%$ per rank above Rank 1.
- Resource cost (Stamina/Mana/Power) increases by $5\%$ per rank to balance scaling output.

---

## 4. Skill Execution & Runtime Pipeline

When the player triggers a skill hotkey (`Q`, `E`, `R`, `F`):

```
[Key Press Detected (e.g. 'Q')]
            │
            ▼
[Can Cast Check] ─── Fail (On CD or Out of Resource) ──► Play Fail SFX / UI Shake
            │ Pass
            ▼
[Deduct Resource] (Stamina, Mana, or Power)
            │
            ▼
[Start Cooldown Timer]
            │
            ▼
[Set Character Animation State] (e.g. Swing, Cast, Aim)
            │
            ▼
[Spawn Gameplay Entity] ──┬── Melee: Kinematic Hitbox Sensor
                          ├── Ranged: Dynamic Projectile Entity
                          ├── Barrier: Static Shield Entity
                          └── Self-Buff: Attach Buff Component
            │
            ▼
[Emit EventBus Signal] (e.g. `EventSkillCast{entity, skillId}`)
```

