# World, Procedural Dungeons & Bosses Specification

This document provides the complete specification for the overworld biomes, procedural dungeon generation pipeline, 8 dungeon tiers, multi-phase boss encounters, death mechanics, and the Infinite Rift endgame in Untitled RPG.

---

## 1. World Layout & The 20+ Unique Biomes

The world is composed of **over 20 distinct, handcrafted and procedural biomes**, spanning surface lands, hazardous fringe territories, deep subterranean layers, and extra-dimensional rifts. **Every biome hosts its own procedurally generated dungeons, underground vaults, and hidden ruins** that generate unique layouts with biome-specific tilesets, environmental hazards, enemy populations, and loot.

```
[Surface Progression Arc]
Sky Archipelago ── Scorched Desert ── Sunken Megalopolis ── Acidic Salt Flats ── Bioluminescent Bog
                                                │
                                    [THE HAVEN (Central Hub)]
                                                │
Rustwood Forest ── Pine Taiga ── Radioactive Waste ── Iron Jungle ── Ashen Foundry ── Cryo-Glacier
                                                │
                                   [Subterranean Vault Entrances]
```

### 1.1 Surface Biomes (12 Biomes)
1. **The Haven (Central Settlement)**: Safe sanctuary with ruined pre-war buildings, NPC housing plots, fresh water spring, fertile farmland, and the primary descent gateway to the Vaults.
2. **Rustwood Forest**: Temperate woodland littered with mossy war machines, scrap heaps, feral wildlife, and scavenger encampments.
3. **Whispering Pine Taiga**: Cold coniferous forest featuring derelict satellite dishes, wolf packs, and logging ruins.
4. **Ashen Foundry**: Scorched volcanic sector of smoking slag rivers, sulfur vents, and rogue mining machines.
5. **Cryo-Glacier & Neon Peaks**: Sub-zero mountain range with icy precipices, blizzards, and frozen research laboratories.
6. **Bioluminescent Bog**: Phosphorescent wetland choked with giant spore caps, toxic pools, and mutant amphibians.
7. **Sunken Megalopolis**: Half-submerged coastal skyscraper city with flooded subways, bandit towers, and pre-war high-tech caches.
8. **Scorched Glass Desert**: Vitrified desert dunes created by orbital lances; extreme heat, sandstorms, and burrowing worms.
9. **Radioactive Wasteland**: Bombardment crater fields bathed in green fallout; requires hazmat gear or lung bionics to traverse.
10. **Acidic Salt Flats**: Expansive chemical plains with bubbling acid geysers and brittle mineral crusts.
11. **Iron Canopy Jungle**: Dense tropical jungle where ancient biomechanical trees are fused with structural steel beams.
12. **Shattered Sky Archipelago**: High-altitude floating islands held aloft by magnetic anomalies; accessible via jet boots and grapples.

### 1.2 Subterranean & Dimension Biomes (10 Biomes)
13. **Rusted Catacombs**: Ancient stone burial vaults interwoven with Victorian steam pipes and flickering electric lanterns.
14. **Overgrown Bio-Labs**: Shattered underground greenhouses overrun by mutant vines, carnivorous roots, and ruptured stasis vats.
15. **Submerged Cooling Vaults**: Industrial reactor catwalks suspended over deep, electrified cooling pools.
16. **Molten Core Smeltery**: Deep subterranean magma channels with automated crane gantries and molten slag falls.
17. **Cryo-Stasis Depths**: Deep freeze vaults containing frozen precursor personnel and pressurized liquid nitrogen lines.
18. **Void-Warped Factory**: Automated production facilities corrupted by purple spatial rifts, zero-gravity zones, and phantom machinery.
19. **Holy Citadel of Hard-Light**: Pristine geometric white marble sanctuaries illuminated by glowing gold circuits and energy bridges.
20. **The Sunken Orbital Core**: The buried bridge of an ancient planet-harvesting flagship embedded deep in the tectonic bedrock.
21. **Deep Resonant Crystal Caverns**: Subterranean geode caves filled with raw magical power crystals that hum with arcane energy.
22. **The Infinite Rift**: The boundless, shifting post-game endgame dimension of non-Euclidean geometry and escalating mutators.

---

## 2. Procedural Dungeon Generation Engine (Dungeons in Every Biome)

Every biome features entrances to procedurally generated dungeons (Vaults, Bunkers, Mines, Crypts, and Alien Ruins). Entering a dungeon generates a unique layout using hybrid Binary Space Partitioning (BSP) and prefab-room socketing:

```
[Enter Biome Dungeon Gate]
         │
         ▼
[BSP Space Partitioning] ─── Subdivides grid into leaves (minimum 16x12 tiles)
         │
         ▼
[Biome Prefab Room Sockets] ── Sockets Tiled templates (combat arenas, traps, puzzle rooms, treasure vaults)
         │
         ▼
[Corridor & Platform Generation] ── Navigable corridors with biome-specific hazard blocks (acid, lava, ice)
         │
         ▼
[Tile Autotiling & Edge Welding] ── Replaces edges with 16x16 autotile rules for that biome
         │
         ▼
[Entity Spawning] ─── Places biome-scaled enemies, loot chests, locked keycard gates, and ambient traps
         │
         ▼
[Boss / Vault Chamber] ─── Attaches locked arena containing biome mini-boss or tier campaign boss
```

### 2.1 Death & Recovery Rules (No Permadeath)
- **Defeat Behavior**: When health drops to 0 inside a dungeon:
  - The player's consciousness is recalled to their Haven bed or medical stasis pod.
  - **All equipped gear, weapons, armor, and body augmentations are preserved**.
  - **$25\%$ of carried raw materials, scrap, and credits** are dropped into a **Recovery Drone** at the death coordinates.
  - Returning to that floor and interacting with the drone recovers all dropped materials.

---

## 3. The 8 Campaign Dungeon Tiers & Multi-Phase Boss Encounters

### Tier 1: The Rusted Catacombs
- **Biome**: Crumbling stone tombs intermeshed with leaking steam pipes and rusted machinery.
- **Enemies**: Scrap Scavengers, Rabid Cyber-Hounds, Steam Sentry Golems.
- **Boss: MK-1 Goliath Excavator**:
  - *Phase 1*: Dual-tread mining mech; charges across the arena bouncing off walls; fires arced rivet bursts.
  - *Phase 2 (50% HP)*: Detaches treads to grip ceiling pipes; drops boiling hydraulic oil onto the player before slamming down.

### Tier 2: The Overgrown Bio-Labs
- **Biome**: Shattered hydroponic domes overtaken by predatory vines and ruptured genetic vats.
- **Enemies**: Spore Spitters, Chimeric Vine Thralls, Acid Burrowers.
- **Boss: Grafted Mother Chimera**:
  - *Phase 1*: Massive quadruped blending bear torso and mantis forelegs; sweeps arena with horizontal claws and launches toxic spore pods.
  - *Phase 2 (40% HP)*: Enters bio-frenzy; clings to side walls, spraying quills in bullet-hell patterns; summons vine tentacles from floor.

### Tier 3: The Submerged Cooling Vaults
- **Biome**: Flooded industrial gantries over electrified cooling fluids; steam valves and water turbines.
- **Enemies**: Shock Drones, Waterlogged Servitors, Arc Eels.
- **Boss: Hydro-Turbine Overlord**:
  - *Phase 1*: Heavy diving mech armed with water cannons and Tesla coils; floods arena floor sections, conducting shock damage.
  - *Phase 2 (50% HP)*: Activates arena whirlpool; launches tracking torpedoes while protected by an electric forcefield.

### Tier 4: The Molten Core Smeltery
- **Biome**: Suspended catwalks over boiling molten iron; automated ladle cranes and blast vents.
- **Enemies**: Magma Walkers, Thermite Troopers, Molten Slimes.
- **Boss: Forge-Master Vulcan**:
  - *Phase 1*: Giant molten cyborg with a magma warhammer; slams anvil to send fire shockwaves across platforms.
  - *Phase 2 (30% HP)*: Discards outer plating, bursting into plasma flames; dashes across platforms leaving fire trails; triggers falling ceiling slag.

### Tier 5: The Cryo-Stasis Depths
- **Biome**: Corridors of blue neon encased in sheets of ice; leaking nitrogen conduits and frozen humanoid pods.
- **Enemies**: Cryo-Snipers, Frozen Husks, Ice Shard Golems.
- **Boss: Absolute Zero Commander**:
  - *Phase 1*: Armored commander in an anti-matter exo-suit; fires sweeping freeze lasers that turn platforms into zero-friction ice.
  - *Phase 2 (50% HP)*: Summons a howling blizzard reducing player vision; blinks rapidly leaving delayed-blast frost charges.

### Tier 6: The Void-Warped Factory
- **Biome**: Assembly lines twisted by purple dimensional tears; floating scrap and inverted gravity anomalies.
- **Enemies**: Warp Phantoms, Dimensional Walkers, Corrupted Assembly Arms.
- **Boss: The Dimensional Assembler**:
  - *Phase 1*: Eldritch machine brain connected to automated conveyor presses; fabricates cyber-minions while firing void lasers.
  - *Phase 2 (40% HP)*: Inverts room gravity intermittently; summons black hole singularities that drag the player towards crusher presses.

### Tier 7: The Holy Citadel of Hard-Light
- **Biome**: Pristine geometric white marble infused with gold circuit traces and floating hard-light platforms.
- **Enemies**: Light Sentinels, Archon Turrets, Solar Crusaders.
- **Boss: Archon Prime, Seraph of Logic**:
  - *Phase 1*: Four-winged biomechanical angel with floating laser funnels; slashes with dual hard-light broadswords.
  - *Phase 2 (30% HP)*: Summons interlocking geometric light pillars across the arena; unleashes full-screen spiral laser barrages.

### Tier 8: The Sunken Orbital Core (The Final Boss)
- **Biome**: The crashed bridge of an ancient planetary-harvester flagship embedded deep within the tectonic mantle.
- **The Final Boss: THE ARCHITECT**:
  - *Phase 1: Orbital Matrix Relay*: The Architect operates from the central computer mainframe; deploys moving laser grids, descending crushing ceilings, and orbital particle beams.
  - *Phase 2: The Transcendent Chimera Core*: The core violently detaches from the wall, growing massive biomechanical limbs, energy wings, and arcane eye arrays. Attacks with combined fire, frost, shock, and void elements while actively pursuing the player.
  - *Phase 3: Singularity Avatar*: Down to the exposed, shattered neural core. Gravity distorts; time slows in pulses. The Architect unleashes dimension-cleaving shockwaves and summons shadow clones of the player's own class.
  - *Defeat*: The Architect is overthrown, stabilizing the planetary energy grid. Unlocks the permanent portal to the Infinite Rift.

---

## 4. The Endgame: The Infinite Rift

- Located in the deepest chamber of the Haven once The Architect is defeated.
- **Endless Scaling Floors**: Depth 1, 2, 3... $\infty$.
- **Randomized Floor Mutators**:
  - *Solar Overdrive*: Heat damage $+100\%$, enemies explode on death.
  - *Null-Magic Zone*: Mana costs doubled; energy weapon damage $+50\%$.
  - *Nanite Swarm*: Enemies regenerate health continuously until ignited.
  - *Zero-G*: Jump height doubled, fall speed reduced by $50\%$.
- **Prismatic Gear Drops**: Exclusive Tier 9+ Prismatic weapons and armor with 5 randomized affixes and 2 unique legendary perks.

