#include "gameplay/building/WorldInteraction.hpp"
#include <cmath>

WorldInteraction::WorldInteraction(CollisionWorld& physics, Tilemap& tilemap, LootSystem& loot)
    : m_physics(physics), m_tilemap(tilemap), m_loot(loot) {}

bool WorldInteraction::mineTile(
    entt::registry& registry,
    const Vec2& playerPos,
    const Vec2& targetWorldPos,
    float reachDistance
) {
    if (playerPos.distanceTo(targetWorldPos) > reachDistance) {
        return false;
    }

    float tileSize = m_physics.getTileSize();
    int tx = static_cast<int>(std::floor(targetWorldPos.x / tileSize));
    int ty = static_cast<int>(std::floor(targetWorldPos.y / tileSize));

    if (!m_physics.isSolid(tx, ty)) {
        return false; // Nothing to mine
    }

    uint16_t blockId = m_tilemap.getBlock(tx, ty, BlockLayer::Foreground);

    // Turn tile to air
    m_physics.setTile(tx, ty, TileType::Empty);
    m_tilemap.setBlock(tx, ty, BlockLayer::Foreground, 0);

    // Spawn dropped resource loot item
    Item drop;
    drop.category = ItemCategory::Material;
    drop.stackable = true;
    drop.quantity = 1;

    if (blockId == 2) {
        drop.id = "mat_iron_ore";
        drop.name = "Iron Ore";
    } else if (blockId == 3) {
        drop.id = "mat_wood_plank";
        drop.name = "Wood Plank";
    } else {
        drop.id = "mat_stone_block";
        drop.name = "Stone Block";
    }

    Vec2 lootSpawnPos{tx * tileSize + (tileSize * 0.5f), ty * tileSize + (tileSize * 0.5f)};
    m_loot.spawnLoot(registry, lootSpawnPos, drop, Vec2{0.0f, -40.0f});

    return true;
}

bool WorldInteraction::placeBlock(
    Inventory& inv,
    const std::string& itemId,
    const Vec2& playerPos,
    const Vec2& targetWorldPos,
    float reachDistance,
    uint16_t blockType
) {
    if (playerPos.distanceTo(targetWorldPos) > reachDistance) {
        return false;
    }

    if (!inv.hasItem(itemId, 1)) {
        return false;
    }

    float tileSize = m_physics.getTileSize();
    int tx = static_cast<int>(std::floor(targetWorldPos.x / tileSize));
    int ty = static_cast<int>(std::floor(targetWorldPos.y / tileSize));

    if (m_physics.isSolid(tx, ty)) {
        return false; // Already occupied
    }

    // Deduct block item from inventory
    inv.removeItem(itemId, 1);

    m_physics.setTile(tx, ty, TileType::Solid);
    m_tilemap.setBlock(tx, ty, BlockLayer::Foreground, blockType);

    return true;
}

DungeonTransitionManager::DungeonTransitionManager() = default;

void DungeonTransitionManager::enterDungeon(int tier) {
    m_currentZone = WorldZone::Dungeon;
    m_currentDungeonTier = tier;
    m_bossDefeated = false;
}

void DungeonTransitionManager::exitDungeon() {
    m_currentZone = WorldZone::Overworld;
    m_bossDefeated = false;
}
