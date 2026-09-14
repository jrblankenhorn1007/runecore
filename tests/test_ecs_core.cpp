#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include <entt/entt.hpp>
#include "ecs/Components.hpp"
#include "core/Math.hpp"

using Catch::Approx;

TEST_CASE("ECS Entity Lifecycle and Component Attachment", "[ecs][lifecycle]") {
    entt::registry registry;

    entt::entity entity = registry.create();
    REQUIRE(registry.valid(entity));

    registry.emplace<TransformComponent>(entity, Vec2{100.0f, 200.0f});
    registry.emplace<VelocityComponent>(entity, Vec2{10.0f, -5.0f});
    registry.emplace<HealthComponent>(entity, 100.0f, 100.0f);

    SECTION("Retrieving Attached Components") {
        auto& transform = registry.get<TransformComponent>(entity);
        REQUIRE(transform.position.x == Approx(100.0f));
        REQUIRE(transform.position.y == Approx(200.0f));

        auto& vel = registry.get<VelocityComponent>(entity);
        REQUIRE(vel.linear.x == Approx(10.0f));
        REQUIRE(vel.linear.y == Approx(-5.0f));

        auto& health = registry.get<HealthComponent>(entity);
        REQUIRE(health.current == Approx(100.0f));
        REQUIRE(health.max == Approx(100.0f));
        REQUIRE(health.isDead == false);
    }

    SECTION("Component Removal and Checks") {
        REQUIRE(registry.all_of<VelocityComponent>(entity));
        registry.remove<VelocityComponent>(entity);
        REQUIRE_FALSE(registry.all_of<VelocityComponent>(entity));
    }

    SECTION("Entity Destruction") {
        registry.destroy(entity);
        REQUIRE_FALSE(registry.valid(entity));
    }
}

TEST_CASE("ECS Query Views and Iterations", "[ecs][views]") {
    entt::registry registry;

    // Create 10 entities with Transform
    // Half with Velocity, Half with EnemyTag
    for (int i = 0; i < 10; ++i) {
        auto e = registry.create();
        registry.emplace<TransformComponent>(e, Vec2{static_cast<float>(i * 10), 0.0f});
        if (i % 2 == 0) {
            registry.emplace<VelocityComponent>(e, Vec2{1.0f, 0.0f});
        }
        if (i >= 5) {
            registry.emplace<EnemyTag>(e, 1, 100);
        }
    }

    SECTION("Multi-Component View Iteration") {
        auto view = registry.view<TransformComponent, VelocityComponent>();
        int count = 0;
        for (auto [e, transform, velocity] : view.each()) {
            transform.position += velocity.linear;
            count++;
        }
        REQUIRE(count == 5);
    }

    SECTION("View with Tag Filters") {
        auto enemyView = registry.view<TransformComponent, EnemyTag>();
        int count = 0;
        for (auto [e, transform, enemy] : enemyView.each()) {
            REQUIRE(enemy.xpReward == 100);
            count++;
        }
        REQUIRE(count == 5);
    }
}

TEST_CASE("Core Gameplay Components Default Values and Operations", "[ecs][components]") {
    entt::registry registry;
    auto player = registry.create();

    registry.emplace<PlayerTag>(player);
    registry.emplace<StatsComponent>(player);
    registry.emplace<HealthComponent>(player, 150.0f, 150.0f, 1.5f);
    registry.emplace<ManaComponent>(player, 80.0f, 80.0f, 2.0f);
    registry.emplace<PowerComponent>(player, 50.0f, 100.0f, 0.0f);

    SECTION("Stats Component Defaults") {
        const auto& stats = registry.get<StatsComponent>(player);
        REQUIRE(stats.strength == 10);
        REQUIRE(stats.dexterity == 10);
        REQUIRE(stats.intelligence == 10);
        REQUIRE(stats.vitality == 10);
        REQUIRE(stats.wisdom == 10);
        REQUIRE(stats.cybernetics == 10);
        REQUIRE(stats.critChance == Approx(0.05f));
        REQUIRE(stats.critMultiplier == Approx(1.5f));
    }

    SECTION("Health Damage and Death State") {
        auto& health = registry.get<HealthComponent>(player);
        health.takeDamage(100.0f);
        REQUIRE(health.current == Approx(50.0f));
        REQUIRE(health.isDead == false);

        health.takeDamage(60.0f);
        REQUIRE(health.current == Approx(0.0f));
        REQUIRE(health.isDead == true);

        health.heal(50.0f);
        REQUIRE(health.current == Approx(50.0f));
        REQUIRE(health.isDead == false);
    }

    SECTION("Mana Consumption and Recovery") {
        auto& mana = registry.get<ManaComponent>(player);
        REQUIRE(mana.consume(30.0f) == true);
        REQUIRE(mana.current == Approx(50.0f));

        REQUIRE(mana.consume(60.0f) == false); // Not enough mana
        REQUIRE(mana.current == Approx(50.0f)); // Unchanged

        mana.restore(20.0f);
        REQUIRE(mana.current == Approx(70.0f));
    }
}
