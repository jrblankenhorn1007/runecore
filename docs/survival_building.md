# Survival, Settlement Building & Farming Specification

This document provides the complete specification for the environmental survival systems, dynamic day/night cycles, weather patterns, 16x16 grid settlement construction, crop farming, and NPC recruitment in Untitled RPG.

---

## 1. Survival Meters & Environmental Simulation

```
[Survival Drivers]
 ├── Hunger Meter      (0 - 100) -> Depletes with exertion; starves at 0
 ├── Thirst Meter      (0 - 100) -> Depletes with time & heat; halts stamina at 0
 ├── Body Temperature (-50°C to +50°C) -> Driven by biome, weather, clothes, heat sources
 └── Day / Night Cycle (24 min) -> Drives darkness, night spawns, and base raids
```

### 1.1 Hunger & Thirst Decay Rates
- **Hunger (0–100)**:
  - Baseline decay: $-1.0$ point per 18 seconds (approx. 30 real-time minutes to empty).
  - Sprinting, swinging heavy weapons, or digging increases decay rate by up to $1.5\times$.
  - At 0 Hunger: Cannot sprint; max stamina reduced by $50\%$; takes $1\%$ Max HP damage every 3 seconds.
- **Thirst (0–100)**:
  - Baseline decay: $-1.0$ point per 12 seconds (approx. 20 real-time minutes to empty).
  - Ambient temperature $> +30^\circ\text{C}$ doubles thirst decay rate.
  - At 0 Thirst: Stamina regeneration drops to zero; vision blurs.

### 1.2 Body Temperature Dynamics
- **Effective Temperature Equation**:
  $$\text{Effective Temp} = \text{Biome Ambient} + \text{TimeOfDayOffset} + \text{WeatherOffset} + \text{NearbyHeatSources} - \text{ArmorInsulation}$$
- **Temperature Zones**:
  - **Extreme Freezing ($< -10^\circ\text{C}$)**: Movement speed $-30\%$, weapon spread $+50\%$, hypothermia ticks ($2\text{ dmg/s}$). Countered by: Campfires, Torches, Fur/Welder Armor, Spicy Food.
  - **Comfortable ($-10^\circ\text{C}$ to $+35^\circ\text{C}$)**: Normal operating status.
  - **Extreme Overheating ($> +35^\circ\text{C}$)**: Thirst drains at $3\times$ speed, stamina action costs doubled, heatstroke damage ticks. Countered by: Shade, Swimming in water, Cryo-armor, Hydro-Melons.

### 1.3 Day / Night Cycle & Weather
- **24-Minute Cycle**: Day (14 min), Dusk (2 min), Night (6 min), Dawn (2 min).
- **Night Dynamics**: Full darkness requiring torches, flashlights, or thermal optics. Nocturnal enemies spawn with glowing red eyes, deal $+30\%$ damage, and target player settlement doors.
- **Weather States**:
  - *Clear*: Standard ambient conditions.
  - *Rain*: Automatically hydrates outdoor tilled crops; thirst decay $-20\%$; lowers ambient temperature by $5^\circ\text{C}$.
  - *Blizzard*: Extreme cold ($-25^\circ\text{C}$); reduces visibility; walking against wind slows player by $40\%$.
  - *Slag Storm* (Ashen Foundry): Emits falling embers dealing fire damage unless under shelter.
  - *Acid Fog* (Bioluminescent Bog): Gradually corrodes wooden structures and deals toxic damage to unshielded players.

---

## 2. 16x16 Grid Building & Settlement Construction

### 2.1 Building Rules & Material Tiers
- World tiles snap to a rigid **16x16 pixel grid**.
- Placing blocks requires holding the material in inventory and having cursor within 5 tiles of player.
- **Structural Integrity Tiers**:
  1. *Wood Planks & Beams*: 100 HP. Vulnerable to enemy night raids and fire.
  2. *Chiseled Stone*: 300 HP. Immune to Tier 1 night beasts; resistant to blast.
  3. *Reinforced Concrete & Steel*: 800 HP. Completely blast-proof; immune to all standard enemy damage.
  4. *Powered Hard-Light Barrier*: 2000 HP. Generates shield field; requires continuous electrical power.

### 2.2 Power Generation & Illumination
- **Generators**: Steam Boiler (burns wood/coal), Solar Panel (daylight only), Micro-Plasma Turbine.
- **Wiring Grid**: Power wires can be routed through background walls to connect generators to ceiling lights, automated defense turrets, and automated sprinklers.

---

## 3. Farming & Botany

- **Tilling**: Using a Hoe on dirt blocks creates tilled soil.
- **Hydration**: Tilled soil must be hydrated (via rain, manual watering can, or automated sprinkler). Unhydrated soil halts plant growth.
- **Crops & Growth Cycle**:
  1. *Rust-Wheat*: 3 in-game days. Used to bake bread and brew ale.
  2. *Hydro-Melon*: 2 in-game days. High water yield.
  3. *Bioluminescent Moss*: 4 in-game days. Used for night-vision potions and glow lanterns.
  4. *Cyber-Weed*: 5 in-game days. Produces synthetic fibers for advanced armor.
  5. *Soma Berry*: 3 in-game days. Cures poisons and restores health.

---

## 4. NPC Housing & Town Recruitment

When the player constructs an enclosed room meeting standard building criteria, specialized survivor NPCs move into the Haven Hub:

### 4.1 Room Criteria
- Enclosed with solid walls, floor, and ceiling (minimum $8 \times 5$ tiles).
- Contains at least 1 Door or Hatch.
- Contains 1 Light Source (Torch, Lantern, or Electric Light).
- Contains 1 Table and 1 Chair.

### 4.2 Hub NPC Roster
1. **Dr. Raymond (Cyber-Surgeon)**: Installs, uninstalls, and overclocks bionic body augmentations.
2. **Weaver Selene (Arcane Biomancer)**: Binds chimeric beast grafts, crafts enchanted robes, and refines ancient mana crystals.
3. **Blacksmith Hargrove**: Sells basic weapons, ammunition presses, and repairs broken equipment.
4. **Merchant Silas**: Buys salvage and sells seeds, flashlights, wire, and crafting supplies.
5. **Botanist Ivy**: Sells rare crop seeds, growth accelerators, and automated irrigation pipes.
6. **Master Thorne (Trainer)**: Respecs allocated skill points for gold.

