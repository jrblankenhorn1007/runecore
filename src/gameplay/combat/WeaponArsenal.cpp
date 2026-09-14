#include "gameplay/combat/WeaponArsenal.hpp"
#include <cmath>

WeaponArsenal::WeaponArsenal(ProjectileSystem& projSystem)
    : m_projSystem(projSystem) {}

int WeaponArsenal::fireShotgun(
    entt::registry& registry,
    const Vec2& origin,
    const Vec2& direction,
    int pelletCount,
    float spreadAngleDegrees,
    float pelletDamage,
    entt::entity owner
) {
    if (pelletCount <= 0) return 0;

    Vec2 baseDir = direction.normalized();
    float baseAngle = std::atan2(baseDir.y, baseDir.x);
    float spreadRad = spreadAngleDegrees * (3.14159265f / 180.0f);

    float halfSpread = spreadRad * 0.5f;
    float step = (pelletCount > 1) ? (spreadRad / (pelletCount - 1)) : 0.0f;

    for (int i = 0; i < pelletCount; ++i) {
        float angle = baseAngle - halfSpread + (i * step);
        Vec2 pelletDir{std::cos(angle), std::sin(angle)};

        ProjectileConfig cfg;
        cfg.speed = 320.0f;
        cfg.damage = pelletDamage;
        cfg.lifetime = 0.8f;
        cfg.knockback = 50.0f;
        cfg.color = Color{255, 180, 50, 255};

        m_projSystem.spawnProjectile(registry, origin, pelletDir, cfg, owner);
    }

    return pelletCount;
}
