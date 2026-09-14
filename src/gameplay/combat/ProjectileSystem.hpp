#pragma once
#include <entt/entt.hpp>
#include "core/Math.hpp"
#include "physics/CollisionWorld.hpp"

struct ProjectileConfig {
    float speed{300.0f};
    float damage{20.0f};
    float lifetime{3.0f};
    bool penetrates{false};
    int maxPierces{1};
    float knockback{80.0f};
    Color color{255, 220, 50, 255};
};

class ProjectileSystem {
public:
    entt::entity spawnProjectile(
        entt::registry& registry,
        const Vec2& origin,
        const Vec2& direction,
        const ProjectileConfig& config,
        entt::entity owner
    );

    void update(entt::registry& registry, const CollisionWorld& world, float dt);
};
