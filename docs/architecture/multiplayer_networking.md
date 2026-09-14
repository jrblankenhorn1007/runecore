# Multiplayer Architecture & Headless Simulation Roadmap

This document outlines the software design boundaries, client-server simulation separation, and network synchronization roadmap enabling Untitled RPG to transition seamlessly from a single-player launch to an online cooperative multiplayer experience in future updates.

---

## 1. Architectural Separation of Simulation & Presentation

To prevent the common pitfall where single-player games must be completely rewritten to support multiplayer, Untitled RPG strictly separates **Deterministic Simulation** from **Client Presentation**:

```
[Local Input / Network Packet]
             │
             ▼
[Deterministic Simulation Core (Headless)]
 ├── EnTT Registry (Entities & Pure Data Components)
 ├── Box2D Physics World (Stepped deterministically at 60 Hz)
 ├── Combat, AI, Skills, and Survival Systems
 └── Seeded PRNG (Synchronized pseudo-random generator)
             │
   Produces Snapshot State
             │
             ▼
[Presentation Layer (Client-Only)]
 ├── SDL3 Hardware Renderer & Shaders
 ├── Audio System & Positional SFX
 ├── UI Window Layouts & Hover Tooltips
 └── Camera Tracking & Screen Shake
```

- **Headless Capable**: The simulation core can compile and execute as a standalone, headless server binary with zero windowing or graphics dependencies.
- **Identical Single-Player Execution**: In single-player mode, the client runs an internal headless simulation instance on the local thread.

---

## 2. Network Synchronization Strategy (Future Multiplayer Roadmap)

When online multiplayer is enabled, the architecture employs a **Client-Side Prediction with Server Reconciliation** model:

```
[Client 1] ─── Sends Input Commands ───► [Authoritative Server] ◄─── Sends Input ─── [Client 2]
    │                                              │                                    │
Predicts Movement                               Executes 60Hz                      Predicts Movement
Locally & Renders                               Simulation Step                     Locally & Renders
    │                                              │                                    │
    ▼                                              ▼                                    ▼
Reconciles State ◄────── Broadcasts Authoritative World Snapshots ──────► Reconciles State
```

### 2.1 Key Networking Rules
1. **Authoritative Server**:
   - Damage calculations, loot drops, procedural dungeon layout generation, and enemy AI state decisions are verified exclusively on the server. Clients never dictate damage or item spawns.
2. **Client-Side Movement Prediction**:
   - The local player character moves immediately in response to user inputs without waiting for server round-trip latency.
   - The client caches past unacknowledged input frames. When an authoritative state packet arrives from the server, the client compares positions: if a discrepancy exceeds the threshold (e.g. $> 0.1$ tiles), the client snaps to the server position and replays subsequent cached inputs.
3. **Delta Snapshot Compression**:
   - Entity transforms and health states are serialized into binary bit-packed packets, transmitting only modified component fields (dirty flags) to minimize bandwidth.
4. **Deterministic Procgen Seeding**:
   - When generating a dungeon vault or Infinite Rift floor, the server transmits only the `WorldSeed` and `BiomeType` integer identifiers. Both server and clients execute the identical BSP generator algorithm locally, producing matching floor layouts with zero geometry bandwidth overhead.
