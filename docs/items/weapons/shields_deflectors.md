# Shields, Deflectors & Defensive Off-Hands Catalog

This document specifies the individual base stat roll ranges, block percentage ratings, parry timing windows, stamina and power block costs, and projectile deflection rules for shields and off-hands across all 8 progression tiers in Untitled RPG (~120 shield definitions).

---

## 1. Mechanics & Stat Rolling Parameters
- **Primary Scaling Attribute**: Strength (STR) ($+1.0\%$ block value per point) and Cyber-Affinity (CYB) for energy deflectors.
- **Off-Hand Control**: Raising a shield is bound to Right Mouse Button (RMB).
- **Sub-Types**:
  - *Bucklers & Parrying Daggers*: Low passive block ($40\%$ to $55\%$), generous parry timing window (0.25s to 0.35s). A successful parry stuns the attacker and guarantees a critical strike on next counter-attack.
  - *Kite & Heater Shields*: Balanced frontal block ($70\%$ to $85\%$), moderate parry window (0.15s to 0.20s), standard stamina block cost.
  - *Tower & Fortress Shields*: Extreme frontal block ($90\%$ to $100\%$), absorbs heavy boss slams without guard break, but prevents sprinting while held.
  - *Hard-Light & Holographic Deflectors*: Consumes electrical Power per block instead of Stamina. Perfectly timed blocks deflect hostile projectiles directly back to the shooter.

---

## 2. Complete Shields & Off-Hands Catalog

| ID | Name | Sub-Type | Block % | Parry Window | Resource / Block | Special / Implicit |
|---|---|---|---|---|---|---|
| `wpn_shd_t1_01` | *Makeshift Wooden Buckler* | Buckler | 45% | 0.25s | 8 Stamina | Low weight (2 kg) |
| `wpn_shd_t1_02` | *Reinforced Timber Shield* | Kite Shield | 60% | 0.18s | 12 Stamina | Standard starter shield |
| `wpn_shd_t1_03` | *Rusted Iron Pot Lid* | Buckler | 50% | 0.28s | 10 Stamina | High parry stagger |
| `wpn_shd_t1_04` | *Scrap Metal Tower Shield* | Tower Shield| 80% | 0.10s | 18 Stamina | Knockback immunity while held |
| `wpn_shd_t1_05` | *Goliath Excavator Shovel Shield*| Tower Shield| 85% | 0.12s | 20 Stamina | Boss drop: Frontal fire resist $+30\%$ |
| `wpn_shd_t2_01` | *Refined Bronze Buckler* | Buckler | 55% | 0.30s | 8 Stamina | Counter-crit $+25\%$ dmg |
| `wpn_shd_t2_02` | *Refined Iron Kite Shield* | Kite Shield | 75% | 0.18s | 14 Stamina | Blocks physical arrows cleanly |
| `wpn_shd_t2_03` | *Bio-Lab Spore Shield* | Kite Shield | 70% | 0.15s | 12 Stamina | Releases toxic spore on parry |
| `wpn_shd_t2_04` | *Mother Chimera Chitin Carapace*| Tower Shield| 88% | 0.14s | 16 Stamina | Boss drop: Reflects 20% melee |
| `wpn_shd_t3_01` | *Steel Riot Shield* | Tower Shield| 85% | 0.15s | 16 Stamina | Bulletproof frontal arc |
| `wpn_shd_t3_02` | *Steam-Vented Deflector* | Kite Shield | 78% | 0.20s | 14 Stamina | Vents steam on block |
| `wpn_shd_t3_03` | *Holographic Forcefield Emitter*| Energy Shield| 100% | 0.22s | 8 Power/block | Deflects bullets back to shooter |
| `wpn_shd_t3_04` | *Hydro-Turbine Water Shield*| Kite Shield | 80% | 0.18s | 12 Stamina | Boss drop: Extinguishes burning |
| `wpn_shd_t4_01` | *Titanium Tactical Shield* | Kite Shield | 82% | 0.22s | 10 Stamina | 0 Movement speed penalty |
| `wpn_shd_t4_02` | *Molten Crucible Tower Shield*| Tower Shield| 92% | 0.12s | 18 Stamina | Immune to lava floor damage |
| `wpn_shd_t4_03` | *Forge-Master Vulcan Crucible*| Tower Shield| 95% | 0.14s | 20 Stamina | Boss drop: Parrying detonates slag |
| `wpn_shd_t5_01` | *Glacial Cobalt Tower Shield*| Tower Shield| 94% | 0.12s | 18 Stamina | Chills melee attackers for 3s |
| `wpn_shd_t5_02` | *Cryo-Deflector Disc* | Energy Shield| 100% | 0.25s | 10 Power/block| Freezes deflected projectiles |
| `wpn_shd_t5_03` | *Absolute Zero Ice Wall* | Tower Shield| 96% | 0.15s | 22 Stamina | Boss drop: Creates physical ice wall |
| `wpn_shd_t6_01` | *Void Singularity Ward* | Kite Shield | 88% | 0.20s | 12 Mana/block | Absorbs projectile damage as Mana |
| `wpn_shd_t6_02` | *Gravity Distortion Aegis* | Energy Shield| 100% | 0.25s | 12 Power/block| Slows incoming projectiles by 80% |
| `wpn_shd_t6_03` | *Dimensional Assembler's Shield*| Tower Shield| 98% | 0.15s | 20 Stamina | Boss drop: Inverts attacker trajectory |
| `wpn_shd_t7_01` | *Archon Hard-Light Great-Aegis*| Energy Shield| 100% | 0.28s | 10 Power/block| Deflects boss lasers |
| `wpn_shd_t7_02` | *Seraphic Light-Wing Buckler* | Buckler | 70% | 0.35s | 6 Stamina | Parry heals player for 50 HP |
| `wpn_shd_t7_03` | *Archon Prime's Bastion Barrier*| Energy Shield| 100% | 0.30s | 15 Power/block| Boss drop: Deployable stationary dome |
| `wpn_shd_t8_01` | *The Architect's Event Horizon*| Energy Shield| 100% | 0.35s | 8 Power/block | Absorbs 100% of all damage types |
| `wpn_shd_t8_02` | *God-Slayer Prismatic Aegis* | Tower Shield| 100% | 0.30s | 10 Stamina | 5 Affixes + permanent knockback immune |
| `wpn_shd_t8_03` | *Infinity Chrono-Deflector* | Energy Shield| 100% | 0.40s | 5 Power/block | Parry rewinds incoming attacks |
