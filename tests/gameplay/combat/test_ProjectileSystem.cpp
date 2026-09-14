#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include "gameplay/combat/ProjectileSystem.hpp"
#include "physics/CollisionWorld.hpp"
#include "ecs/Components.hpp"

using Catch::Approx;

TEST_CASE("ProjectileSystem Spawning, Collisions, and Lifetime", "[gameplay][combat]") {
    entt::registry reg;
    CollisionWorld world(16.0f);
    // Wall at X = 20 (320px)
    for (int y = 0; y <= 15; ++y) {
        world.setTile(20, y, TileType::Solid);
    }

    ProjectileSystem ps;

    SECTION("Spawn and Velocity Direction") {
        ProjectileConfig cfg;
        cfg.speed = 250.0f;
        cfg.damage = 30.0f;
        cfg.lifetime = 1.0f;

        auto proj = ps.spawnProjectile(reg, Vec2{100.0f, 100.0f}, Vec2{0.0f, 1.0f}, cfg, entt::null);
        REQUIRE(reg.valid(proj));
        REQUIRE(reg.get<VelocityComponent>(proj).linear.y == Approx(250.0f));
    }

    SECTION("Lifetime Decay Destroys Projectile") {
        ProjectileConfig cfg;
        cfg.lifetime = 0.5f;
        auto proj = ps.spawnProjectile(reg, Vec2{100.0f, 100.0f}, Vec2{1.0f, 0.0f}, cfg, entt::null);

        ps.update(reg, world, 0.3f);
        REQUIRE(reg.valid(proj));

        ps.update(reg, world, 0.3f); // 0.6s total > 0.5s lifetime
        REQUIRE_FALSE(reg.valid(proj));
    }

    SECTION("Collision with Solid Wall Destroys Non-Penetrating Projectile") {
        ProjectileConfig cfg;
        cfg.speed = 200.0f;
        cfg.lifetime = 5.0f;
        cfg.penetrates = false;

        auto proj = ps.spawnProjectile(reg, Vec2{300.0f, 100.0f}, Vec2{1.0f, 0.0f}, cfg, entt::null);
        // Step 0.2s: moves 40px past wall at 320px
        ps.update(reg, world, 0.2f);
        REQUIRE_FALSE(reg.valid(proj));
    }

    SECTION("Penetrating Projectile Hits Enemies and Respects Max Pierces") {
        ProjectileConfig cfg;
        cfg.speed = 100.0f;
        cfg.damage = 20.0f;
        cfg.lifetime = 5.0f;
        cfg.penetrates = true;
        cfg.maxPierces = 1;

        auto proj = ps.spawnProjectile(reg, Vec2{50.0f, 100.0f}, Vec2{1.0f, 0.0f}, cfg, entt::null);

        auto enemy = reg.create();
        reg.emplace<EnemyTag>(enemy, 1, 50);
        reg.emplace<TransformComponent>(enemy, Vec2{80.0f, 100.0f});
        reg.emplace<ColliderComponent>(enemy, Rect{-8.0f, -8.0f, 16.0f, 16.0f});
        reg.emplace<HealthComponent>(enemy, 100.0f, 100.0f);

        ps.update(reg, world, 0.3f); // travels 30px from 50 to 80, directly hitting enemy
        REQUIRE(reg.get<HealthComponent>(enemy).current == Approx(80.0f));
        REQUIRE_FALSE(reg.valid(proj)); // Expended after 1 pierce
    }

    SECTION("Penetrating Projectile Passes Through Solid Terrain") {
        ProjectileConfig cfg;
        cfg.speed = 100.0f;
        cfg.damage = 10.0f;
        cfg.lifetime = 5.0f;
        cfg.penetrates = true;
        cfg.maxPierces = 5;

        // Wall at X=20*16 = 320
        world.setTile(20, 5, TileType::Solid);
        auto proj = ps.spawnProjectile(reg, Vec2{310.0f, 5.0f * 16.0f}, Vec2{1.0f, 0.0f}, cfg, entt::null);

        // Update step moves through wall without being destroyed
        ps.update(reg, world, 0.3f);
        REQUIRE(reg.valid(proj));
    }
}
