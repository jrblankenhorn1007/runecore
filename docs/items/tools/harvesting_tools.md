# Harvesting Tools, Mining Implements & Geological Scanners Catalog

This document specifies the mining powers, woodcutting speeds, agricultural tile coverage, durability pools, and scanning capabilities for all harvesting and survival tools across Untitled RPG (~120 tool definitions).

---

## 1. Tool Mechanics & Power Thresholds
- **Mining Power**: Determines which block tiers the tool can break, and the number of hits required per block (Standard Dirt: $15\%$, Stone: $35\%$, Iron: $50\%$, Titanium: $75\%$, Cobalt: $90\%$, Adamantite: $110\%$, Precursor Bedrock: $150\%$).
- **Axe Power**: Determines felling speed and wood yield when chopping surface and subterranean trees.
- **Farming Power**: Determines hoe tilling area (Single block, $3 \times 1$ line, $3 \times 3$ grid, or automated).
- **Durability & Repair**: Tools possess finite durability points. When durability drops to 0, tools enter "Broken" state and cannot break blocks until sharpened or repaired at the Anvil or Workbench. High-tier laser drills draw electrical Power instead of losing durability.

---

## 2. Complete Tools Catalog

| ID | Name | Tool Category | Tier | Power Rating | Durability / Draw | Special Properties |
|---|---|---|---|---|---|---|
| `tol_pic_01` | *Rusted Scrap Pickaxe* | Pickaxe | 1 | 35% Mining | 80 Durability | Basic starter tool; breaks stone & copper. |
| `tol_pic_02` | *Refined Copper Pickaxe* | Pickaxe | 1 | 50% Mining | 140 Durability | Breaks iron ore cleanly. |
| `tol_pic_03` | *High-Tensile Steel Pickaxe*| Pickaxe | 3 | 65% Mining | 250 Durability | Speed $+25\%$; breaks deep coal & silver. |
| `tol_pic_04` | *Titanium Razor Pickaxe* | Pickaxe | 4 | 80% Mining | 400 Durability | Breaks volcanic slag & titanium ore. |
| `tol_pic_05` | *Cobalt Glacial Pickaxe* | Pickaxe | 5 | 95% Mining | 600 Durability | Chills mined blocks, prevents cave-ins. |
| `tol_pic_06` | *Dense Tungsten Heavy Pick* | Pickaxe | 5 | 100% Mining | 750 Durability | Cleaves $2 \times 2$ rock chunks at once. |
| `tol_pic_07` | *Adamantite Breaker Pick* | Pickaxe | 6 | 115% Mining | 1200 Durability | Breaks all terrestrial ore blocks. |
| `tol_pic_08` | *Pneumatic Laser Mining Drill*| Power Tool | 7 | 135% Mining | 2 Power/sec | Continuous laser beam mining (3x speed). |
| `tol_pic_09` | *The Architect's Core Drill*| God Tool | 8 | 180% Mining | Indestructible | Mines $3 \times 3$ area instantaneously. |
| `tol_axe_01` | *Scrap Felling Axe* | Wood Axe | 1 | 40% Chopping | 90 Durability | Chops surface trees into timber. |
| `tol_axe_02` | *Refined Copper Wood-Axe* | Wood Axe | 1 | 55% Chopping | 160 Durability | Timber yield $+20\%$. |
| `tol_axe_03` | *Industrial Steel Lumber-Axe*| Wood Axe | 3 | 75% Chopping | 280 Durability | Chops hard iron-wood in Taiga. |
| `tol_axe_04` | *Titanium Chainsaw* | Power Tool | 4 | 110% Chopping | 3 Power/sec | Continuous motor felling (instant chop). |
| `tol_axe_05` | *Plasma Arc Tree-Cutter* | Power Tool | 7 | 150% Chopping | 2 Power/sec | Harvests entire tree from base in 0.5s. |
| `tol_hoe_01` | *Primitive Gardening Hoe* | Farming Tool | 1 | 1 Tile Tilling | 60 Durability | Tills basic dirt blocks. |
| `tol_hoe_02` | *Refined Copper Hoe* | Farming Tool | 1 | 3 Tile Tilling | 120 Durability | Tills a $3 \times 1$ line of soil at once. |
| `tol_hoe_03` | *Steel Aerating Cultivator*| Farming Tool | 3 | 5 Tile Tilling | 240 Durability | Automatically weeds adjacent plots. |
| `tol_hoe_04` | *Titanium Rotary Tiller* | Farming Tool | 4 | 3x3 Grid Tilling| 450 Durability | Tills a $3 \times 3$ block patch in one press. |
| `tol_wat_01` | *Tin Watering Can* | Watering | 1 | 10 Water Uses | Infinite | Refillable at lakes, wells, and rain barrels. |
| `tol_wat_02` | *Pressurized Spray Tank* | Watering | 3 | 40 Water Uses | Infinite | Waters 5 tiles wide per spray. |
| `tol_scn_01` | *Geological Mineral Chisel* | Utility Tool | 2 | Extraction | 150 Durability | Extracts rare gems from rocks unbroken. |
| `tol_scn_02` | *Geiger Radiation Scanner* | Detection | 2 | 20-Tile Range | Battery (50) | Displays ambient radiation levels on HUD. |
| `tol_scn_03` | *Mineral Ultrasound Scanner*| Detection | 4 | 35-Tile Range | Battery (100) | Highlights buried titanium & gold veins. |
| `tol_fsh_01` | *Makeshift Wood Fishing Rod*| Fishing Pole | 1 | 15% Catch Power | 50 Durability | Catches river fish and kelp. |
| `tol_fsh_02` | *Steel High-Tension Rod* | Fishing Pole | 3 | 45% Catch Power | 180 Durability | Reversible winch; catches deep sea predators. |
| `tol_fsh_03` | *Titanium Sonar Fishing Rod*| Fishing Pole | 5 | 80% Catch Power | 400 Durability | Sonar shows fish silhouettes through water. |
