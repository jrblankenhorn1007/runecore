#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include "gameplay/combat/ProjectileSystem.hpp"
#include "gameplay/items/LootSystem.hpp"
#include "ecs/Components.hpp"
#include "physics/CollisionWorld.hpp"

using Catch::Approx;

TEST_CASE("Dynamic Projectiles Spawning and 360-Degree Aim Trajectory", "[combat][projectiles]") {
    entt::registry registry;
    CollisionWorld world(16.0f);
    // Ground floor at Y = 10 (160px), wall at X = 20 (320px)
    for (int x = 0; x <= 30; ++x) {
        world.setTile(x, 10, TileType::Solid);
    }
    world.setTile(20, 5, TileType::Solid);
    world.setTile(20, 6, TileType::Solid);
    world.setTile(20, 7, TileType::Solid);

    ProjectileSystem projSys;

    SECTION("Fires in Direction of Aim Vector at Specified Speed") {
        Vec2 origin{100.0f, 100.0f};
        Vec2 target{200.0f, 100.0f}; // Directly right
        Vec2 aimDir = (target - origin).normalized();

        ProjectileConfig config;
        config.speed = 300.0f;
        config.damage = 25.0f;
        config.lifetime = 2.0f;
        config.penetrates = false;

        entt::entity proj = projSys.spawnProjectile(registry, origin, aimDir, config, entt::null);
        REQUIRE(registry.valid(proj));

        const auto& vel = registry.get<VelocityComponent>(proj);
        REQUIRE(vel.linear.x == Approx(300.0f));
        REQUIRE(vel.linear.y == Approx(0.0f));

        const auto& pComp = registry.get<ProjectileComponent>(proj);
        REQUIRE(pComp.damage == Approx(25.0f));
        REQUIRE(pComp.lifetime == Approx(2.0f));
    }

    SECTION("Projectile Steps, Hits Enemies and Deals Damage") {
        Vec2 origin{100.0f, 100.0f};
        Vec2 dir{1.0f, 0.0f};
        ProjectileConfig config;
        config.speed = 200.0f;
        config.damage = 40.0f;
        config.lifetime = 2.0f;

        projSys.spawnProjectile(registry, origin, dir, config, entt::null);

        // Spawn target enemy at X = 150
        auto enemy = registry.create();
        registry.emplace<EnemyTag>(enemy, 1, 50);
        registry.emplace<TransformComponent>(enemy, Vec2{150.0f, 100.0f});
        registry.emplace<ColliderComponent>(enemy, Rect{-8.0f, -8.0f, 16.0f, 16.0f});
        registry.emplace<HealthComponent>(enemy, 100.0f, 100.0f);

        // Step simulation for 0.3s (travels 60px: 100 -> 160, passing through 150)
        projSys.update(registry, world, 0.3f);

        const auto& enemyHealth = registry.get<HealthComponent>(enemy);
        REQUIRE(enemyHealth.current == Approx(60.0f)); // 100 - 40 damage
    }

    SECTION("Projectile Hits Solid Wall and Destroys Self If Non-Penetrating") {
        Vec2 origin{300.0f, 100.0f}; // Wall is at X=20*16 = 320
        Vec2 dir{1.0f, 0.0f};
        ProjectileConfig config;
        config.speed = 200.0f;
        config.penetrates = false;

        entt::entity proj = projSys.spawnProjectile(registry, origin, dir, config, entt::null);
        REQUIRE(registry.valid(proj));

        // Step 0.2s -> moves 40px to 340, hitting wall at 320
        projSys.update(registry, world, 0.2f);
        REQUIRE_FALSE(registry.valid(proj)); // Destroyed on impact
    }
}

TEST_CASE("Dropped World Loot and Magnetic Attraction to Player", "[items][loot]") {
    entt::registry registry;
    CollisionWorld world(16.0f);
    for (int x = -10; x <= 20; ++x) {
        world.setTile(x, 10, TileType::Solid); // Y=160px
    }

    LootSystem lootSys;
    Inventory playerInv(40);

    auto player = registry.create();
    registry.emplace<PlayerTag>(player);
    registry.emplace<TransformComponent>(player, Vec2{100.0f, 144.0f});

    Item dropItem;
    dropItem.id = "mat_iron_ore";
    dropItem.name = "Iron Ore";
    dropItem.category = ItemCategory::Material;
    dropItem.stackable = true;
    dropItem.quantity = 3;

    SECTION("Spawning Dropped Item Falls Under Gravity") {
        Vec2 spawnPos{150.0f, 80.0f};
        entt::entity loot = lootSys.spawnLoot(registry, spawnPos, dropItem);
        REQUIRE(registry.valid(loot));

        // Update 0.5s -> should fall towards ground
        lootSys.update(registry, world, playerInv, Vec2{100.0f, 144.0f}, 0.5f);

        const auto& trans = registry.get<TransformComponent>(loot);
        REQUIRE(trans.position.y > 80.0f);
    }

    SECTION("Magnetic Attraction Pulls Nearby Loot into Inventory") {
        // Drop loot within 30px of player (magnetic radius = 64px)
        Vec2 nearPos{120.0f, 144.0f};
        entt::entity loot = lootSys.spawnLoot(registry, nearPos, dropItem);

        REQUIRE(playerInv.getItemCount("mat_iron_ore") == 0);

        // Step simulation: loot gets magnetically attracted and collected
        for (int i = 0; i < 30; ++i) {
            lootSys.update(registry, world, playerInv, Vec2{100.0f, 144.0f}, 1.0f / 60.0f);
        }

        REQUIRE(playerInv.getItemCount("mat_iron_ore") == 3);
        REQUIRE_FALSE(registry.valid(loot)); // Loot entity consumed and destroyed
    }
}
