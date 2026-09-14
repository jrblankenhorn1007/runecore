# Rendering Pipeline & Integer Pixel Canvas Specification

This document specifies the visual rendering pipeline, low-resolution virtual canvas architecture, nearest-neighbor integer scaling, parallax background systems, dynamic 2D lighting, and sub-pixel frame interpolation in Untitled RPG.

---

## 1. Pixel-Art Virtual Canvas Architecture

To deliver crisp, authentic 16x16 indie pixel art without uneven pixel shimmer or diagonal distortion, Untitled RPG uses a **two-stage virtual canvas**:

```
[Virtual Internal Canvas (e.g. 640x360)]
              │
    Render all game entities, tilemaps, particles, and lighting
              │
              ▼
[Nearest-Neighbor Integer Upscaling Pass]
              │
    Scale canvas by exact integer multiplier (e.g., 3x, 4x, 5x)
              │
              ▼
[Display Viewport (e.g. 2560x1440)]
    Centered with black letterboxing / pillarboxing margins
```

### 1.1 Resolution Adaptation & Integer Scaling Math
1. **Target Internal Height**: Fixed at **360 vertical pixels** (base 16:9 equivalent to $640 \times 360$, providing a comfortable vertical field of view of 22.5 tiles high).
2. **Dynamic Aspect Ratio Width**:
   - The internal canvas width adapts to the native monitor aspect ratio:
     $$\text{Internal Width} = \lfloor 360 \times \text{Aspect Ratio} \rfloor$$
     *(e.g., $576 \times 360$ for 16:10 MacBook screens, $640 \times 360$ for 16:9 displays, $840 \times 360$ for 21:9 Ultrawide).*
3. **Clean Integer Scale Factor**:
   - The maximum integer multiplier that fits within the native window resolution is chosen:
     $$\text{Scale Factor} = \max\left(1, \; \min\left(\left\lfloor \frac{\text{Window Width}}{\text{Internal Width}} \right\rfloor, \; \left\lfloor \frac{\text{Window Height}}{\text{Internal Height}} \right\rfloor\right)\right)$$
4. **Pillarbox & Letterbox Centering**:
   - The scaled canvas is centered on the window backbuffer, rendering black bars in remaining margins to preserve pixel aspect purity.

---

## 2. Multi-Pass Frame Rendering Order

Each visual frame is rendered through a sequence of discrete passes:

```
[Pass 1: Parallax Background Layers]
 ├── Sky & celestial bodies (Sun, Moon, Aurora Borealis)
 ├── Distant mountains / ruined skyline (Scroll Factor: 0.15x)
 ├── Midground trees / factory towers (Scroll Factor: 0.40x)
 └── Near background walls (Scroll Factor: 0.75x)

[Pass 2: World Tilemap Layers]
 ├── Background wallpaper tiles (faded tint)
 ├── Solid terrain blocks & one-way platforms
 └── Foreground clutter (grass tufts, flowers, debris)

[Pass 3: Entity Sprite Batching]
 ├── Placed furniture, campfires, crafting stations
 ├── NPC and enemy animated sprites
 ├── Player character sprite (body, head, weapons, aiming arms)
 └── Dynamic projectiles & particle effects

[Pass 4: 2D Dynamic Lighting & Shadow Composite]
 ├── Ambient darkness layer (driven by Day/Night cycle & depth)
 ├── Subtractive light masks (torches, campfires, laser beams)
 └── Multiply composite onto scene

[Pass 5: Post-Processing & Screen Shake]
 ├── Sinusoidal camera trauma shake offset
 └── Flash effects (hitstop flash, EMP shockwaves)

[Pass 6: UI & Debug Layer (Direct to Backbuffer)]
 ├── Player HUD (HP, Stamina, Mana, Power bars, Hotbar)
 ├── Active modal windows (Inventory, Skill Tree, Crafting)
 ├── Floating combat numbers & item hover tooltips
 └── Dear ImGui debug overlay (in debug builds)
```

---

## 3. Sub-Pixel Frame Interpolation

While physics simulation ticks at fixed 60 Hz intervals, the renderer executes at the native display refresh rate (e.g. 120 Hz, 144 Hz, 240 Hz ProMotion). To eliminate visual stutter:
- Every entity stores its `PreviousTransform` alongside its `CurrentTransform`.
- Rendered visual coordinates interpolate linearly using the tick alpha fraction:
  $$\text{Render Position} = \text{Previous Position} \times (1.0 - \alpha) + \text{Current Position} \times \alpha$$
- Positions are then snapped to integer virtual pixels immediately before drawing to ensure pixel grid fidelity.
