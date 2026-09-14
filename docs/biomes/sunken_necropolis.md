# Biome Dossier: Sunken Necropolis & Deep Catacombs

This document specifies the environmental conditions, hazards, geology, fauna, dungeon encounters, and loot tables for the **Sunken Necropolis & Deep Catacombs (Biome 08)** in Untitled RPG.

---

## 1. Biome Profile & Environmental Hazards
- **Biome ID & Tier**: `BIO-08`, Tier 3 Subterranean.
- **Location & Depths**: Deep underground beneath the Subterranean Caverns ($Y = -250$ to $Y = -500$).
- **Environmental Hazards**:
  - **Miasma of Decay**: Areas filled with lingering necrotic smog; standing without a gas mask or toxin scrubber drains 8 HP/s and inflicts Necrotic Rot.
  - **Cursed Tombs**: Opening sealed sarcophagi has a 50% chance to summon wraith guards or inflict the "Curse of Frailty" (-20% armor for 5 minutes).
  - **Bone Traps**: Spring-loaded bone spike floors and collapsing stone crypt ceilings.
- **Ambient Temperature**: 8°C (Damp, chilling draft).

---

## 2. Geological Composition & Harvestable Resources
- **Terrain Blocks**: Ossified Bone Blocks, Black Crypt Slate, Carved Gargoyle Stonework, Rotten Wood Coffins, Cursed Soil.
- **Ores & Minerals**:
  - **Abundant**: Black Slate, Fossilized Bones, Silver Veins.
  - **Moderate**: Lead Ore, Cursed Obsidian, Amethyst Shards.
  - **Rare**: Soul-Stones, Grave-Gold Inlays, Necrotic Shards.
- **Flora & Fungi**:
  - **Grave-Lichen**: Grows on ancient tombstones; used in necromantic potions.
  - **Ghost-Cap Mushrooms**: Translucent fungi that glow with ethereal blue light; used in invisibility serums.
  - **Corpse-Vine Weeds**: Thorny vines that feed on decomposing matter; yields tough necrotic fiber.

---

## 3. Native Fauna, Undead & Hostiles

| Entity ID | Monster Name | Family | Behavior & Attacks | Primary Drops |
|---|---|---|---|---|
| MOB-NEC-01 | **Crypt Skeleton Swordsman** | Undead / Skeleton | Dual-wields rusted scimitars; blocks strikes with buckler; rattles bones to alert room. | Clean Bones, Bone Shards, Rusted Iron. |
| MOB-NEC-02 | **Rot-Ghouls** | Undead / Corpse | Crawls rapidly on all fours; pounces on player to chew vitals; inflicts Rot disease. | Rotten Flesh, Diseased Claws. |
| MOB-NEC-03 | **Tomb Banshee** | Undead / Wraith | Flies through walls; screams to disorient and silence spellcasting; immune to physical damage. | Ectoplasm, Banshee Veil. |
| MOB-NEC-04 | **Necromancer Acolyte** | Cultist / Humanoid | Casts dark shadow bolts; raises fallen skeleton minions endlessly until slain. | Necromancer Robes, Dark Parchment. |
| MOB-NEC-05 | **Bone-Colossus (Mini-Boss)** | Undead / Construct | Massive 4-meter giant built from hundreds of ribcages and skulls; colossal club slam. | Behemoth Bone, Titan Marrow. |

---

## 4. Procedural Dungeon: The Tomb of the Lich-King
- **Dungeon Structure**: Sprawling subterranean mausoleum complex with multi-tier crypt halls, sarcophagus chambers, sacrificial altars, and deep flooded catacombs.
- **Puzzles & Mechanisms**: Turning gargoyle statues to face the central blood fountain; locating 3 silver keys from crypt guardians to unlock the Grand Crypt Door.
- **Dungeon Boss: Arch-Lich Malakor (Level 28 Dungeon Boss)**
  - **Arena**: Grand vaulted ossuary chamber surrounded by 4 soul-reaping obelisks.
  - **Phase 1 (100%–60% HP)**: Hovers above ground, firing waves of seeking shadow skulls, summoning skeletal legions, and teleporting away when approached.
  - **Phase 2 (60%–20% HP)**: Activates the 4 soul obelisks, gaining an impenetrable bone shield. Player must destroy the 4 obelisks while dodging falling bone spikes.
  - **Phase 3 (20%–0% HP)**: Enters Death Nova frenzy, sweeping the room with necrotic laser beams and raising all fallen minions as exploding bone bombs.
  - **Guaranteed Drops**: Malakor's Soul Scythe (T3 Legendary Scythe), Robes of the Undying, Crown of Bone, 2x Precursor Datacubes.
