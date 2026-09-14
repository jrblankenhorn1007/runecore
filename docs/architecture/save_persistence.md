# Persistence & Save Architecture Specification

This document specifies the save/load architecture, state serialization, data integrity verification, and version migration protocols for Untitled RPG.

---

## 1. Save File Structure & Serialization Strategy

All player progress, world modifications, and character states are persisted as structured JSON documents saved into the platform's local application storage directory (e.g. `~/Library/Application Support/untitled_rpg/saves/` on macOS).

```
save_slot_01/
├── meta.json         # Slot preview: Character name, class, level, playtime, thumbnail
├── character.json    # Attributes, uncapped XP, skill allocations, 11-slot augmentations
├── inventory.json    # 8-slot hotbar, 32-slot backpack, equipped gear, storage chests
├── world.json        # 16x16 placed/broken tiles, electrical wires, crop growth timers
└── state.checksum    # SHA-256 cryptographic hash of all slot files for anti-corruption
```

---

## 2. Atomic Writing & Anti-Corruption Protocol

To prevent save file corruption during sudden system shutdowns, battery exhaustion, or application crashes:
1. **Write to Temporary File**: All JSON data is serialized to a temporary buffer file (`character.json.tmp`).
2. **Flush to Disk**: File stream executes `fsync()` to ensure complete physical disk writing.
3. **Atomic Rename**: The temporary file is renamed over the target file (`character.json.tmp` $\to$ `character.json`) via atomic OS file-system operations.
4. **Checksum Verification**: On boot, the engine recomputes the SHA-256 checksum and compares it against `state.checksum`. If a mismatch is detected, the engine automatically rolls back to the previous backup snapshot (`save_slot_01_backup/`).

---

## 3. Data Schema Versioning & Forward Migration

As new skills, items, biomes, and augmentations are added across game updates, existing player save files are automatically migrated:
- Every save file includes a `schemaVersion` integer.
- The `SaveManager` registers linear migration passes:
  $$\text{Version } 1 \to \text{Version } 2 \to \text{Version } 3$$
- If a player loads a save from an older version, the migration passes inject missing default fields, recalculate derived stats, and preserve all existing items and skill investments.
