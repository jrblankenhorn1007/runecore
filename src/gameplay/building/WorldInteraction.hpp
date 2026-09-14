#pragma once
#include <entt/entt.hpp>
#include "core/Math.hpp"
#include "physics/CollisionWorld.hpp"
#include "procgen/Tilemap.hpp"
#include "gameplay/items/Inventory.hpp"
#include "gameplay/items/LootSystem.hpp"

enum class WorldZone {
    Overworld,
    Dungeon
};

class WorldInteraction {
public:
    WorldInteraction(CollisionWorld& physics, Tilemap& tilemap, LootSystem& loot);

    bool mineTile(entt::registry& registry, const Vec2& playerPos, const Vec2& targetWorldPos, float reachDistance = 80.0f);
    bool placeBlock(Inventory& inv, const std::string& itemId, const Vec2& playerPos, const Vec2& targetWorldPos, float reachDistance = 80.0f, uint16_t blockType = 1);

private:
    CollisionWorld& m_physics;
    Tilemap& m_tilemap;
    LootSystem& m_loot;
};

class DungeonTransitionManager {
public:
    DungeonTransitionManager();

    WorldZone getCurrentZone() const { return m_currentZone; }
    int getCurrentDungeonTier() const { return m_currentDungeonTier; }
    bool isBossDefeated() const { return m_bossDefeated; }
    bool canExitDungeon() const { return m_bossDefeated; }

    void enterDungeon(int tier);
    void setBossDefeated(bool defeated) { m_bossDefeated = defeated; }
    void exitDungeon();

private:
    WorldZone m_currentZone{WorldZone::Overworld};
    int m_currentDungeonTier{1};
    bool m_bossDefeated{false};
};
