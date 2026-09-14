#pragma once
#include <entt/entt.hpp>
#include "gameplay/items/Item.hpp"
#include "gameplay/items/Inventory.hpp"
#include "physics/CollisionWorld.hpp"
#include "core/Math.hpp"

struct DroppedItemComponent {
    Item item;
    float pickupDelay{0.25f}; // Prevent immediate accidental pickup on drop
    float despawnTimer{300.0f}; // 5 minutes
};

class LootSystem {
public:
    entt::entity spawnLoot(
        entt::registry& registry,
        const Vec2& position,
        const Item& item,
        const Vec2& initialVelocity = Vec2{0.0f, -50.0f}
    );

    void update(
        entt::registry& registry,
        const CollisionWorld& world,
        Inventory& playerInventory,
        const Vec2& playerPosition,
        float dt,
        float magnetRadius = 64.0f
    );
};
