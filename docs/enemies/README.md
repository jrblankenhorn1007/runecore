# Bestiary Index — Enemies by Biome


**Implemented:** No  
**Implementation:** `Not mapped to runtime code`  
**Asset generated:** No  
**Asset:** No generated asset  

This is the master index for the Untitled RPG bestiary. It cross-references [docs/biomes/master_biomes_index.md](../biomes/master_biomes_index.md) (the 22 canonical biomes, `BIO-01` through `BIO-22`) with a dedicated enemy dossier for every creature that inhabits each zone.

Total catalog: **1,100 enemy dossiers** (50 per biome × 22 biomes), one Markdown file per enemy.

---

## 1. Folder & ID Schema

- Each biome has its own subfolder using a stable lowercase kebab-case name, e.g. `docs/enemies/rustwood-forest/`.
- Each enemy file is named after its enemy name in lowercase kebab-case (e.g. `savage-magma-worm.md`). If names collide across biomes, the stable ID is appended (e.g. `savage-magma-worm-bio-03-en-011.md`). The stable ID remains canonical inside each dossier.
- IDs are permanent identifiers — do not renumber or reuse an ID even if an enemy's name or stats change later.
- Within each biome's 50 enemies:
  - **~46 regular enemies** (`minor` / `standard` / `veteran` power bands) form the common spawn population.
  - **2–4 elite/champion enemies** are marked `⚔ ELITE / CHAMPION ENCOUNTER` — tougher variants with expanded ability counts and better loot odds.
  - **Exactly 1 apex enemy** per biome is marked `⚠ APEX / BIOME BOSS-ADJACENT ENCOUNTER` — the strongest, most narratively significant threat in the zone (not a full scripted raid boss, but a boss-adjacent encounter).

## 2. Dossier Schema

Every enemy dossier follows the same section order:

1. **Header** — Name, ID, biome, tier/level range, family, role, threat rating, and elite/apex marker if applicable.
2. **Combat Stats** — HP, Armor, Movement Speed, Attack Range, Contact Damage, Primary Attack Damage, Primary Attack Cooldown, Stagger Resistance, XP Reward, Aggro Radius, Detection Method.
3. **Elemental Resistances** — Physical / Fire / Frost / Shock / Toxin / Void, expressed as signed percentages.
4. **Defenses & Weaknesses** — A short summary of what mitigates damage against this enemy and what exploits it.
5. **Abilities** — 2–4 named attacks/abilities with one-line effect descriptions.
6. **Lore** — A short narrative paragraph situating the enemy in its biome.
7. **Encounter Notes** — Tactical guidance for players.
8. **Loot Table** — A weighted, percentage-based drop table (see §4).

## 3. Stat Conventions

- **Level Range**: shown as a 2-level band (e.g. `Level 10-12`) reflecting natural variance at spawn; it always falls inside (or, for elites/apex, slightly above) the biome's overall tier band from the master biome index.
- **Threat Rating**: `Minor → Low → Moderate → High → Apocalyptic`, derived from the enemy's power band (minor/standard/veteran/elite/apex), not from raw level alone — a high-level minor enemy is still "Minor" relative to its own biome's elites.
- **Armor**: a flat mitigation value subtracted from incoming physical hits before other resistances apply.
- **Elemental Resistances**: signed percentages. Positive values reduce incoming damage of that type; negative values indicate a **weakness** (the enemy takes *extra* damage of that type). Values are approximately bounded to `-60%` to `+85%`.
- **Stagger Resistance**: percentage chance an enemy resists being staggered/interrupted by a hit; higher values require heavier weapons or coordinated CC to interrupt.
- **Detection Method**: the primary sense an enemy uses to notice the player (sight, sound, scent, heat, vibration, etc.), relevant for stealth play.

## 4. Loot Probability Interpretation

Each dossier's loot table is a **single weighted roll** made on kill: the five rarity rows are mutually exclusive outcomes whose percentages sum to exactly **100%**. Only one row is granted per kill roll (in addition to any guaranteed non-loot-table rewards like XP).

| Rarity | Regular Enemy Odds | Elite Odds | Apex Odds |
|---|---|---|---|
| Common | 55% | 45% | 30% |
| Uncommon | 28% | 30% | 30% |
| Rare | 12% | 17% | 25% |
| Very Rare | 4% | 6% | 11% |
| Super Rare | 1% | 2% | 4% |

- **Common** drops are currency plus small stacks of the biome's primary harvestable material.
- **Uncommon** drops are secondary biome materials or a common-tier gear roll appropriate to the enemy's combat role.
- **Rare** drops are a named crafting trophy (e.g. `"<Enemy Name>'s Claw"`) or a rare-tier gear roll.
- **Very Rare** drops guarantee a high-quality roll of the biome's signature material.
- **Super Rare** drops are a unique, named Legendary-tier relic tied to that specific enemy — these are intentionally rare (1–4%) to preserve their prestige.

Elites and the apex enemy use shifted weight tables (still summing to 100%) that favor better outcomes, reflecting their higher difficulty and narrative significance.

## 5. Biome Index

| Biome ID | Biome Name | Tier | Folder | Enemies |
|---|---|---|---|---|
| BIO-01 | The Haven (Hub Valley) | T1 | [the-haven/](the-haven/) | 50 |
| BIO-02 | Rustwood Forest | T1 | [rustwood-forest/](rustwood-forest/) | 50 |
| BIO-03 | Ashen Foundry & Slag Heaps | T2 | [ashen-foundry/](ashen-foundry/) | 50 |
| BIO-04 | Cryo-Glacier & Frost Peaks | T2 | [cryo-glacier/](cryo-glacier/) | 50 |
| BIO-05 | Bioluminescent Fungal Bog | T3 | [bioluminescent-bog/](bioluminescent-bog/) | 50 |
| BIO-06 | Ancient Ruined Megacity | T3 | [megacity-ruins/](megacity-ruins/) | 50 |
| BIO-07 | Subterranean Caverns | T2 | [subterranean-caverns/](subterranean-caverns/) | 50 |
| BIO-08 | Sunken Necropolis | T3 | [sunken-necropolis/](sunken-necropolis/) | 50 |
| BIO-09 | Volcanic Core & Magma Trenches | T4 | [volcanic-core/](volcanic-core/) | 50 |
| BIO-10 | Toxic Waste Tunnels | T3 | [toxic-waste-tunnels/](toxic-waste-tunnels/) | 50 |
| BIO-11 | Sunken Oceanic Trenches | T4 | [sunken-oceanic-trenches/](sunken-oceanic-trenches/) | 50 |
| BIO-12 | Floating Astral Sky Islands | T5 | [floating-astral-islands/](floating-astral-islands/) | 50 |
| BIO-13 | Crystal Spires & Geodes | T4 | [crystal-spires/](crystal-spires/) | 50 |
| BIO-14 | Haunted Graveyards & Mire | T3 | [haunted-graveyards/](haunted-graveyards/) | 50 |
| BIO-15 | Cyber-Wasteland Bunkers | T5 | [cyber-wasteland/](cyber-wasteland/) | 50 |
| BIO-16 | Mutagenic Flesh-Pits | T5 | [mutagenic-flesh-pits/](mutagenic-flesh-pits/) | 50 |
| BIO-17 | Chrono-Distortion Desert | T5 | [chrono-distortion-desert/](chrono-distortion-desert/) | 50 |
| BIO-18 | Petrified Ancient Forest | T4 | [petrified-forest/](petrified-forest/) | 50 |
| BIO-19 | Radioactive Crater Basin | T5 | [radioactive-crater/](radioactive-crater/) | 50 |
| BIO-20 | Magnetic Thunder-Crags | T5 | [magnetic-thunder-crags/](magnetic-thunder-crags/) | 50 |
| BIO-21 | Precursor Orbital Tether | T6 | [orbital-tether/](orbital-tether/) | 50 |
| BIO-22 | The Infinite Void Rift | T7 | [infinite-void-rift/](infinite-void-rift/) | 50 |

**Total: 1,100 enemy dossiers across 22 biomes.**
