#include "gameplay/items/LootSystem.hpp"
#include "ecs/Components.hpp"
#include <vector>
#include <algorithm>

entt::entity LootSystem::spawnLoot(
    entt::registry& registry,
    const Vec2& position,
    const Item& item,
    const Vec2& initialVelocity
) {
    auto loot = registry.create();
    registry.emplace<TransformComponent>(loot, position);
    registry.emplace<VelocityComponent>(loot, initialVelocity, 300.0f);
    registry.emplace<ColliderComponent>(loot, Rect{-4.0f, -4.0f, 8.0f, 8.0f});

    DroppedItemComponent dropComp;
    dropComp.item = item;
    dropComp.pickupDelay = 0.25f;
    dropComp.despawnTimer = 300.0f;
    registry.emplace<DroppedItemComponent>(loot, dropComp);

    return loot;
}

void LootSystem::update(
    entt::registry& registry,
    const CollisionWorld& world,
    Inventory& playerInventory,
    const Vec2& playerPosition,
    float dt,
    float magnetRadius
) {
    std::vector<entt::entity> toCollect;
    Rect lootBox{-4.0f, -4.0f, 8.0f, 8.0f};

    auto view = registry.view<DroppedItemComponent, TransformComponent, VelocityComponent>();
    for (auto [e, drop, trans, vel] : view.each()) {
        drop.despawnTimer -= dt;
        if (drop.despawnTimer <= 0.0f) {
            toCollect.push_back(e); // Despawn
            continue;
        }

        if (drop.pickupDelay > 0.0f) {
            drop.pickupDelay = std::max(0.0f, drop.pickupDelay - dt);
        }

        float distToPlayer = trans.position.distanceTo(playerPosition);

        // Magnetic Attraction
        if (drop.pickupDelay <= 0.0f && distToPlayer <= magnetRadius) {
            Vec2 pullDir = (playerPosition - trans.position).normalized();
            float pullSpeed = 180.0f * (1.0f - (distToPlayer / magnetRadius)) + 60.0f;
            vel.linear = pullDir * pullSpeed;

            // Direct collection if close enough (within 12px)
            if (distToPlayer <= 12.0f) {
                if (playerInventory.addItem(drop.item)) {
                    toCollect.push_back(e);
                    continue;
                }
            }
        } else {
            // Apply standard gravity and deceleration
            vel.linear.y += 500.0f * dt;
            vel.linear.y = std::min(vel.linear.y, 350.0f);
            vel.linear.x *= std::max(0.0f, 1.0f - (3.0f * dt));
        }

        // World collision sweep
        SweepResult sweep = world.sweepBox(trans.position, lootBox, vel.linear * dt);
        trans.position += sweep.adjustedMove;

        if (sweep.hit) {
            if (sweep.contactNormal.y < -0.5f) {
                vel.linear.y = 0.0f;
                vel.linear.x *= 0.5f; // Ground friction
            }
            if (std::abs(sweep.contactNormal.x) > 0.5f) {
                vel.linear.x = 0.0f;
            }
        }
    }

    for (auto e : toCollect) {
        if (registry.valid(e)) {
            registry.destroy(e);
        }
    }
}
