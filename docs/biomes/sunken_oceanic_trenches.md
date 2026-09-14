# Biome Dossier: Sunken Oceanic Trenches & Coral Reefs

This document specifies the environmental conditions, hazards, geology, fauna, dungeon encounters, and loot tables for the **Sunken Oceanic Trenches & Coral Reefs (Biome 11)** in Untitled RPG.

---

## 1. Biome Profile & Environmental Hazards
- **Biome ID & Tier**: `BIO-11`, Tier 4 Aquatic.
- **Location & Depths**: Submerged ocean biome along the far eastern and western continental shelves ($X > 5000$, $Y = 0$ to $Y = -600$).
- **Environmental Hazards**:
  - **Submersion & Drowning**: Infinite water medium; players without Diving Helmets, Gills, or Submersible Bionics deplete oxygen within 30 seconds and suffer 20 drowning damage/s.
  - **Crushing Hydrostatic Pressure**: Below $Y = -300$, water pressure crushes unreinforced bodies, dealing 15 damage/s unless equipped with Pressure-Sealed Armor or Titanium Skeleton.
  - **Abyssal Darkness**: Trenches below $Y = -200$ receive no sunlight; requires submersible spotlights or bioluminescent lamps.
- **Ambient Temperature**: 4°C to 12°C (Cold ocean currents).

---

## 2. Geological Composition & Harvestable Resources
- **Terrain Blocks**: Coral Reef Blocks, Ocean Silt, Basalt Sea-Floor, Sunken Steel Hull Plates, Sea-Glass.
- **Ores & Minerals**:
  - **Abundant**: Sea-Salt, Calcite Coral, Sandstone.
  - **Moderate**: Ocean Copper, Basalt Slabs, Mother-of-Pearl.
  - **Rare**: Black Pearl Geodes, Abyssal Titanium, Sunken Gold Bullion.
- **Flora & Fungi**:
  - **Bioluminescent Kelp**: Towering glowing seaweed providing ambient light and oxygen air bubbles.
  - **Anemone Tendrils**: Harvested for paralytic neurotoxins.
  - **Deep Sea Sponges**: Used for high-grade filtration cartridges and medical swabs.

---

## 3. Native Fauna, Leviathans & Hostiles

| Entity ID | Monster Name | Family | Behavior & Attacks | Primary Drops |
|---|---|---|---|---|
| MOB-SEA-01 | **Razor-Tooth Reef Shark** | Aquatic / Fish | Circles target at high speed; lunges to bite; causes heavy bleed. | Shark Fins, Serrated Teeth. |
| MOB-SEA-02 | **Electric Jellyfish Swarm** | Aquatic / Cnidaria | Floats gently in vertical corridors; zaps players for 60 shock damage on touch. | Jellyfish Stinger, Shock Mucus. |
| MOB-SEA-03 | **Sunken Automaton Diver** | Construct / Automaton | Walks heavily along sea floor; fires harpoon gun to impale and drag player. | Brass Diving Plate, Harpoons. |
| MOB-SEA-04 | **Abyssal Angler Leviathan** | Deep Fish / Horror | Uses glowing lure to mesmerize; suddenly lunges with massive jaw, swallowing player. | Angler Lure, Abyssal Teeth. |
| MOB-SEA-05 | **Void Kraken (Elite)** | Cephalopod / Beast | Enormous 8-tentacled titan; smashes platforms, creates whirlpools, spits ink clouds. | Kraken Tentacle, Abyssal Chitin. |

---

## 4. Procedural Dungeon: Sunken Precursor Research Dreadnought
- **Dungeon Structure**: Massive flooded naval dreadnought resting on an underwater abyss trench ridge. Features flooded engine compartments, airlock decompression chambers, drainage pump rooms, and torpedo launch tubes.
- **Puzzles & Mechanisms**: Activating emergency bilge pumps using generator batteries to drain specific flooded corridors, allowing dry combat and unlocking blast doors.
- **Dungeon Boss: The Submerged Kraken Titan (Level 42 Dungeon Boss)**
  - **Arena**: Flooded central reactor bay surrounded by rusted catwalks and pressurized glass observation domes.
  - **Phase 1 (100%–50% HP)**: Flails massive barbed tentacles through cracked observation windows, creates violent whirlpool currents that drag player into turbine blades, and spits blinding ink clouds.
  - **Phase 2 (50%–0% HP)**: Enters reactor bay directly; electrifies surrounding water with bioluminescent shock bursts, sweeps tentacles across entire arena, and summons swarms of abyssal eels.
  - **Guaranteed Drops**: Trident of the Leviathan (T4 Polearm), Deep-Diver Oxygen Recycler (Lung Augment), Abyssal Pearl Relic, 2x Precursor Datacubes.
