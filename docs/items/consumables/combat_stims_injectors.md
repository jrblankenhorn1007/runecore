# Combat Stims, Adrenal Injections & Overdrive Syringes Catalog

This document specifies high-potency combat stimulants, adrenal auto-injectors, and nanite combat cocktails in Untitled RPG (~60 stimulant definitions).

---

## 1. Mechanics & Toxicity Thresholds
- **Delivery Mechanism**: Auto-injectors applied to the neck or thigh in 0.2 seconds without breaking sprint or aiming.
- **Combat Overdrive**: Stims provide massive immediate combat stat multipliers (attack speed, movespeed, damage resistance, pain suppression) followed by a mild physiological crash (slight stamina recovery delay for 10s after wearing off).
- **Synergy with Bionics**: Characters with *Subdermal Wire Lattice* or *Nanite Pain Suppressors* eliminate the post-stim crash completely.

---

## 2. Complete Combat Stims Catalog

| ID | Name | Tier | Primary Combat Buff | Duration | Side Effect / Crash |
|---|---|---|---|---|---|
| `con_stm_01` | *Scavenger Adrenaline Shot* | 1 | $+20\%$ Move Speed, $+15\%$ Attack Speed | 8 secs | $-10$ Stamina upon expiration |
| `con_stm_02` | *Berserk Combat Stim V1* | 2 | $+30\%$ Melee Damage, $+10\%$ Lifesteal | 10 secs | $-15\%$ Armor during stim |
| `con_stm_03` | *Berserk Combat Stim V2* | 4 | $+50\%$ Melee Damage, $+20\%$ Lifesteal | 12 secs | $-10\%$ Armor during stim |
| `con_stm_04` | *Reflex Overdrive Injector* | 3 | Bullet-time for 3.0s (world slows by $50\%$) | 3 secs | Cooldown 60s |
| `con_stm_05` | *Nanite Armor Hardener Shot*| 3 | $+50$ Flat Armor, Knockback Immunity | 12 secs | None |
| `con_stm_06` | *Precision Hyper-Focus Stim* | 2 | $+25\%$ Critical Strike Chance | 10 secs | Vision tunnels slightly |
| `con_stm_07` | *Deadeye Sniper Injector* | 4 | Ballistic bullets gain $100\%$ armor pierce | 8 secs | $-15\%$ Move speed while active |
| `con_stm_08` | *Overclock Energy Battery Stim*| 4 | Power weapon energy consumption reduced by $50\%$| 15 secs| Generates 10 heat units |
| `con_stm_09` | *Aether Conduit Spell Stim* | 4 | Spell mana costs reduced to 0 for 5.0 seconds | 5 secs | $-20$ Mana upon expiration |
| `con_stm_10` | *Titan's Unstoppable Juggernaut Stim*| 5| Cannot be staggered, slowed, frozen, or stunned | 10 secs| Heavy stamina drain |
| `con_stm_11` | *Cellular Hyper-Regen Shot* | 3 | Restores $25\text{ HP/s}$ continuously | 8 secs | None |
| `con_stm_12` | *Superior Military Nanite Surge*| 6 | Restores $60\text{ HP/s}$, $+30\%$ Speed | 10 secs| High credit cost to craft |
| `con_stm_13` | *Ghost Cloaking Stim* | 4 | Turns player invisible for 8 seconds during combat | 8 secs | Breaks on primary attack |
| `con_stm_14` | *Pyrophoric Blood Injector* | 4 | Melee and gun attacks ignite targets in white fire | 12 secs| Ambient body temp $+10^\circ\text{C}$ |
| `con_stm_15` | *Sub-Zero Cryo-Stim* | 5 | Hits inflict heavy Freeze; immune to cold hazards | 12 secs| Ambient body temp $-15^\circ\text{C}$ |
| `con_stm_16` | *Volatile Singularity Stim* | 6 | Slaying enemies triggers gravity explosions | 10 secs| $-10$ Stability during stim |
| `con_stm_17` | *Holy Seraph Light Stim* | 7 | Weapons deal $+50\%$ Holy damage; heals allies | 15 secs| Requires 15 WIS |
| `con_stm_18` | *Precursor Overlord Neuro-Stim*| 8 | All active skill cooldowns reset instantly; $+50\%$ dmg| 10 secs| Ultra-rare precursor drop |
| `con_stm_19` | *God-Slayer Prismatic Injector*| 8 | Invulnerable for 5.0 seconds; damage $+100\%$ | 5 secs | Single-use per dungeon floor |
| `con_stm_20` | *Emergency Revive Auto-Syringe*| 5 | Automatically injects upon taking lethal hit (heals 50%)| Passive| Consumed upon trigger |
