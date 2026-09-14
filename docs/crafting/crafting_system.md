# Crafting Tree & Item Modification Specification

This document provides the exhaustive specification for the crafting systems, crafting skill trees, material processing pipelines, and the deterministic item stat-crafting / modification system in Untitled RPG.

---

## 1. Crafting Architecture & Core Pillars

### 1.1 Design Pillars
1. **Meaningful Player Agency**: Crafting is not a pure RNG lottery; players can target, add, upgrade, reroll, and lock specific stats onto equipment using harvested monster parts, tech components, and alchemical catalysts.
2. **Dedicated Crafting Progression**: Crafting utilizes its own **Crafting Specialization Tree**, leveling up through gathering, discovery, and smithing to unlock masterwork recipes, affix tier upgrades, and reduced fracture rates.
3. **Endgame Viability**: Crafted gear can rival or surpass dropped legendary items when invested with rare high-tier reagents, specialized catalysts, and perfect stat rolls.
4. **Integration with Survival & World**: High-tier crafting requires specialized stations placed in suitable player-built workshops powered by the settlement electrical grid.

---

## 2. The Crafting Specialization Tree

In addition to combat skill trees, players earn **Crafting Mastery Points** by discovering recipes, deconstructing items, and crafting equipment. The Crafting Tree features 5 specialized branches:

```
                  [Central Core: Scavenger's Ingenuity]
                  /           |            |           \
           [Weaponsmith] [Armor-Plater] [Cyber-Eng] [Bio-Alchemist]
                 \            |            |           /
                  [Master Artificer: Prismatic Forging]
```

### 2.1 Branch 1: Weaponsmithing (12 Nodes)
1. *Keen Edge*: Base damage of all crafted melee weapons increased by $+5\% / +10\% / +15\%$.
2. *Rifling Precision*: Crafted ballistic firearms gain $+10\% / +20\%$ bullet velocity and $-15\%$ spread.
3. *Tempered Steel*: Melee weapon durability increased by $+50\%$.
4. *Affix Catalyst (Offense)*: Increases probability of rolling Tier 1-2 offensive affixes (Physical dmg, Attack speed) by $+25\%$.
5. *Chamber Optimizer*: Crafted firearms have $+10\%$ increased magazine capacity.
6. *Heavy Forging*: Heavy two-handed weapons gain $+15\%$ base knockback.
7. *Serrated Molds*: Crafted edged weapons have a guaranteed implicit Bleed on crit.
8. *Precision Balance*: Stamina consumption of crafted melee weapons reduced by $15\%$.
9. *High-Caliber Machining*: Firearms roll higher base damage ranges (minimum damage roll $+15\%$).
10. *Master Blacksmith*: Eliminates material waste: dismantling crafted weapons refunds $90\%$ of components.
11. *Signature Etching*: Crafted weapons gain an extra empty affix slot.
12. *Mythic Armaments*: Unlocks crafting of Tier 8 & Prismatic weapon blueprints.

### 2.2 Branch 2: Armor-Plating & Tailoring (12 Nodes)
1. *Thickened Weave*: Base armor value of crafted armor increased by $+8\% / +15\%$.
2. *Insulation Lining*: Crafted armor provides $+15$ Cold and $+15$ Heat resistance.
3. *Lightweight Alloys*: Movement speed penalty of heavy armor reduced by $50\%$.
4. *Affix Catalyst (Defense)*: Increases probability of rolling high-tier defensive affixes (Health, Armor) by $+25\%$.
5. *Flexible Joints*: Crafted boots increase dodge distance by $+1$ tile.
6. *Padded Backing*: Blunt/crushing damage taken reduced by $10\%$ when wearing full crafted set.
7. *Reinforced Seams*: Armor takes $50\%$ less durability damage from combat hits.
8. *Hazmat Sealing*: Crafted armor grants $+30\%$ resistance to environmental acid and radiation.
9. *Spike Inlays*: Melee attackers take 15 physical damage when striking player wearing crafted chest armor.
10. *Hardened Plates*: Critical hit damage taken reduced by $30\%$.
11. *Socket Broach*: Automatically adds 1 additional Gem/Rune socket to crafted chest and head gear.
12. *Aegis Masterwork*: Crafted chestplates gain a unique passive shield absorbing 200 damage.

### 2.3 Branch 3: Cyber-Engineering & Electronics (12 Nodes)
1. *Circuit Soldering*: Power capacity of crafted energy weapons and bionics $+15\%$.
2. *Superconducting Wire*: Energy weapons consume $15\%$ less Power per shot.
3. *Coolant Routing*: Reduces energy weapon heat buildup rate by $25\%$.
4. *Affix Catalyst (Tech)*: Boosts odds of rolling Electric/Energy and Power Capacity affixes.
5. *Overclocked Coils*: Crafted energy beam weapons tick damage $20\%$ faster.
6. *Shield Generator Fabrication*: Unlocks crafting of portable energy shield off-hands.
7. *Lithium-Ion Synthesis*: Crafted battery cells provide $+50\%$ total stored energy.
8. *Sensor Calibration*: Crafted optical bionics gain $+20\%$ scanning radius.
9. *Turret Automation*: Crafted settlement automated defense turrets gain $+30\%$ health and fire rate.
10. *Nanite Infusion*: Installed bionics repaired automatically over time without clinic costs.
11. *Power Matrix*: Adds $+30$ Power capacity to any armor piece via mod bench.
12. *Cyborg Singularity*: Unlocks crafting of prototype Tier 8 bionic limbs and laser cannons.

### 2.4 Branch 4: Bio-Alchemy & Chimeric Synthesis (12 Nodes)
1. *Distillation Purity*: Crafted potions have $+25\%$ increased potency and $+50\%$ duration.
2. *Herbalist Yield*: Gathering alchemical herbs yields $+50\%$ bonus reagents.
3. *Antidote Formulation*: Unlocks crafting of universal detox serums and disease cures.
4. *Chimeric Binding*: Reduces magical stability upkeep of crafted chimeric grafts by $25\%$.
5. *Catalyst Preservation*: $20\%$ chance not to consume rare alchemical catalysts during crafting.
6. *Graft Cultivation*: Unlocks bio-vat incubation of chimeric organs (Bear Arms, Drake Lungs).
7. *Mutagenic Elixirs*: Unlocks crafting of permanent stat-boosting mutagens (limit 5 per character).
8. *Spores & Toxins*: Crafted poison flasks and darts deal $+35\%$ damage over time.
9. *Essence Extraction*: Defeated bosses yield Pure Elemental Essences when harvested.
10. *Cellular Stabilization*: Completely prevents Cellular Rejection damage when chimeric mana dips to 0.
11. *Philosopher's Crucible*: Transmutes common iron into rare titanium and adamantite.
12. *Primal Grafting*: Unlocks fabrication of ancient chimeric apex beasts limbs.

---

## 3. The Item Stat-Crafting & Modification System

Equipment can be taken to the **Modification Forge & Cyber-Bench** in the Haven settlement to customize, add, upgrade, or re-roll its stats.

```
[Target Item Placed in Bench]
            │
            ├── 1. Add Stat (Infuse Crafting Shard into Empty Affix Slot)
            ├── 2. Upgrade Stat Tier (Tier 1 -> Tier 7 using Catalysts)
            ├── 3. Reforge Values (Re-roll numbers within current tier range)
            ├── 4. Anfractuous Reforge (Reroll all affixes completely)
            ├── 5. Socket Punch & Gem Inlay (Add socket -> Socket Rune/Core)
            └── 6. Seal / Lock Affix (Prevent stat from being altered)
```

### 3.1 Stat Modification Operations

#### 1. Affix Infusion (Adding Stats)
- Requires an item with at least one **Empty Affix Slot** (Common: 0, Uncommon: 1 max, Rare: 2 max, Epic: 3 max, Legendary: 4 max).
- Consumes a **Stat Shard** (e.g. *Shard of Striking* for Physical Dmg, *Shard of Vitality* for Health, *Shard of Overclocking* for Power).
- Inserts that affix at **Tier 1** onto the item.

#### 2. Affix Upgrading (Tier 1 to Tier 7)
- Upgrades an existing affix to the next higher tier (e.g., Tier 2 *Volcanic* [+12 Fire Dmg] $\to$ Tier 3 *Volcanic* [+18 Fire Dmg]).
- Consumes **Refined Nanite Flux** and **Monster Biomass**.
- **Instability & Fracture Risk**:
  - Each item has an **Instability Rating** (0 to 100).
  - Adding or upgrading affixes increases Instability by $+5$ to $+15$.
  - Attempting an upgrade rolls against the item's Instability:
    - *Success*: Stat upgrades; Instability rises.
    - *Critical Success*: Stat upgrades with zero Instability added.
    - *Fracture*: The item becomes "Fractured" — it remains completely usable with all its current stats, but no further crafting modifications can ever be performed on it.

#### 3. Value Reforging (Calibration)
- Consumes a **Nanite Calibration Core**.
- Re-rolls the numerical value of all existing affixes within their current tier ranges (e.g., if a Tier 4 STR roll is $+10$ to $+14$, and rolled $+10$, calibration rolls it again with equal probability).

#### 4. Total Reforge (Scrambling)
- Consumes an **Entropic Plasma Catalyst**.
- Wipes all affixes on a non-unique item and re-rolls random affixes matching the item's rarity and level tier.

#### 5. Sockets & Inlays
- Sockets (1 to 3 depending on item type) can be punched into equipment using a **Plasma Drill**.
- Players can socket:
  - *Power Crystals*: Boosts Max Power or Mana.
  - *Runic Skulls*: Adds Life-leech or Status Resistance.
  - *Elemental Chips*: Adds flat elemental damage to weapons.

#### 6. Affix Sealing
- Consumes an ultra-rare **Stasis Seal**.
- Permanently locks one chosen affix on the item: that affix can never be removed, rerolled, or modified, and does not count toward the item's max affix cap, effectively granting a bonus 5th affix slot.

