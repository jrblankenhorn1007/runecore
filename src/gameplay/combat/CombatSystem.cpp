#include "gameplay/combat/CombatSystem.hpp"
#include "ecs/Components.hpp"

bool CombatSystem::resolveHitbox(entt::registry& registry, const Hitbox& hitbox, entt::entity target) {
    if (!registry.valid(target)) return false;
    if (!registry.all_of<TransformComponent, HealthComponent, ColliderComponent>(target)) return false;

    auto& health = registry.get<HealthComponent>(target);
    if (health.isDead || health.invulnTimer > 0.0f) {
        return false; // Target is invulnerable or dead
    }

    const auto& targetTransform = registry.get<TransformComponent>(target);
    const auto& targetCollider = registry.get<ColliderComponent>(target);

    // Calculate world AABB of target
    Rect targetWorldBounds{
        targetTransform.position.x + targetCollider.aabb.x,
        targetTransform.position.y + targetCollider.aabb.y,
        targetCollider.aabb.width,
        targetCollider.aabb.height
    };

    if (!hitbox.bounds.intersects(targetWorldBounds)) {
        return false;
    }

    // Apply damage
    health.takeDamage(hitbox.damage);
    if (hitbox.triggersIFrames) {
        health.invulnTimer = hitbox.iFrameDuration;
    }

    // Apply knockback impulse if target has velocity
    if (registry.all_of<VelocityComponent>(target)) {
        auto& velocity = registry.get<VelocityComponent>(target);
        Vec2 knockDir{1.0f, 0.0f};

        if (registry.valid(hitbox.owner) && registry.all_of<TransformComponent>(hitbox.owner)) {
            const auto& ownerTransform = registry.get<TransformComponent>(hitbox.owner);
            knockDir = (targetTransform.position - ownerTransform.position).normalized();
            if (knockDir.lengthSquared() < 0.001f) {
                knockDir = Vec2{1.0f, 0.0f};
            }
        }
        velocity.linear += knockDir * hitbox.knockbackForce;
    }

    return true;
}
