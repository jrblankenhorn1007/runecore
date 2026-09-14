#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include "gameplay/combat/CombatSystem.hpp"
#include "ecs/Components.hpp"

using Catch::Approx;

TEST_CASE("CombatSystem Hitbox Resolution, Directional Knocks, and Edge Cases", "[gameplay][combat]") {
    entt::registry reg;

    auto target = reg.create();
    reg.emplace<TransformComponent>(target, Vec2{100.0f, 100.0f});
    reg.emplace<VelocityComponent>(target, Vec2{0.0f, 0.0f});
    reg.emplace<ColliderComponent>(target, Rect{-8.0f, -8.0f, 16.0f, 16.0f});
    reg.emplace<HealthComponent>(target, 100.0f, 100.0f);

    auto attacker = reg.create();
    reg.emplace<TransformComponent>(attacker, Vec2{80.0f, 100.0f});

    SECTION("Invalid Target Entity Returns False") {
        Hitbox box;
        box.bounds = Rect{90.0f, 90.0f, 20.0f, 20.0f};
        REQUIRE(CombatSystem::resolveHitbox(reg, box, entt::null) == false);

        auto incomplete = reg.create(); // Missing health/collider
        REQUIRE(CombatSystem::resolveHitbox(reg, box, incomplete) == false);
    }

    SECTION("Dead or Invulnerable Target Ignored") {
        Hitbox box;
        box.bounds = Rect{90.0f, 90.0f, 20.0f, 20.0f};

        auto& hp = reg.get<HealthComponent>(target);
        hp.isDead = true;
        REQUIRE(CombatSystem::resolveHitbox(reg, box, target) == false);

        hp.isDead = false;
        hp.invulnTimer = 0.5f;
        REQUIRE(CombatSystem::resolveHitbox(reg, box, target) == false);
    }

    SECTION("Non-Intersecting Hitbox Returns False") {
        Hitbox box;
        box.bounds = Rect{300.0f, 300.0f, 10.0f, 10.0f}; // Far away
        REQUIRE(CombatSystem::resolveHitbox(reg, box, target) == false);
    }

    SECTION("Valid Hit Applies Damage and Directional Knockback") {
        Hitbox box;
        box.bounds = Rect{95.0f, 95.0f, 10.0f, 10.0f};
        box.damage = 30.0f;
        box.knockbackForce = 100.0f;
        box.owner = attacker;

        REQUIRE(CombatSystem::resolveHitbox(reg, box, target) == true);
        REQUIRE(reg.get<HealthComponent>(target).current == Approx(70.0f));
        REQUIRE(reg.get<VelocityComponent>(target).linear.x > 0.0f); // Pushed right away from attacker
    }
}
