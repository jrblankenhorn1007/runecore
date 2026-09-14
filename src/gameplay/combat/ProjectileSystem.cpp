#include "gameplay/combat/ProjectileSystem.hpp"
#include "ecs/Components.hpp"
#include "gameplay/combat/CombatSystem.hpp"
#include <vector>

entt::entity ProjectileSystem::spawnProjectile(
    entt::registry& registry,
    const Vec2& origin,
    const Vec2& direction,
    const ProjectileConfig& config,
    entt::entity owner
) {
    auto proj = registry.create();
    registry.emplace<TransformComponent>(proj, origin);

    Vec2 dir = direction.normalized();
    registry.emplace<VelocityComponent>(proj, dir * config.speed, config.speed);

    ProjectileComponent pComp;
    pComp.damage = config.damage;
    pComp.lifetime = config.lifetime;
    pComp.penetrates = config.penetrates;
    pComp.maxPierces = config.maxPierces;
    pComp.pierceCount = 0;
    pComp.owner = owner;
    registry.emplace<ProjectileComponent>(proj, pComp);

    registry.emplace<ColliderComponent>(proj, Rect{-3.0f, -3.0f, 6.0f, 6.0f}, true);

    return proj;
}

void ProjectileSystem::update(entt::registry& registry, const CollisionWorld& world, float dt) {
    std::vector<entt::entity> toDestroy;

    auto view = registry.view<ProjectileComponent, TransformComponent, VelocityComponent>();
    for (auto [e, proj, trans, vel] : view.each()) {
        proj.lifetime -= dt;
        if (proj.lifetime <= 0.0f) {
            toDestroy.push_back(e);
            continue;
        }

        Vec2 moveDelta = vel.linear * dt;
        Vec2 nextPos = trans.position + moveDelta;

        // 1. Raycast / sweep against solid terrain
        RaycastHit hit;
        if (world.raycast(trans.position, vel.linear, moveDelta.length(), hit)) {
            if (!proj.penetrates) {
                toDestroy.push_back(e);
                continue;
            }
        }

        // 2. Check collision with enemies if owner is not enemy
        Hitbox projHitbox;
        projHitbox.bounds = Rect{nextPos.x - 3.0f, nextPos.y - 3.0f, 6.0f, 6.0f};
        projHitbox.damage = proj.damage;
        projHitbox.knockbackForce = 80.0f;
        projHitbox.owner = proj.owner;

        bool hitEnemy = false;
        auto enemies = registry.view<EnemyTag, TransformComponent, HealthComponent, ColliderComponent>();
        for (auto [targetE, tag, eTrans, eHealth, eCol] : enemies.each()) {
            if (targetE == proj.owner) continue;

            if (CombatSystem::resolveHitbox(registry, projHitbox, targetE)) {
                hitEnemy = true;
                proj.pierceCount++;
                if (!proj.penetrates || proj.pierceCount >= proj.maxPierces) {
                    toDestroy.push_back(e);
                    break;
                }
            }
        }

        if (!hitEnemy || proj.penetrates) {
            trans.position = nextPos;
        }
    }

    for (auto e : toDestroy) {
        if (registry.valid(e)) {
            registry.destroy(e);
        }
    }
}
