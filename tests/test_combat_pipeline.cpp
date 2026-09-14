#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include "gameplay/combat/DamageCalculator.hpp"
#include "gameplay/combat/CombatSystem.hpp"
#include "gameplay/combat/StatusEffects.hpp"
#include "ecs/Components.hpp"

using Catch::Approx;

TEST_CASE("Damage Calculator Formulas and Mitigation", "[gameplay][combat]") {
    DamageInstance inst;
    inst.baseDamage = 100.0f;
    inst.type = DamageType::Physical;
    inst.canCrit = true;

    SECTION("Non-Critical Hit with Zero Armor") {
        float armor = 0.0f;
        float resist = 0.0f;
        DamageResult res = DamageCalculator::calculate(inst, armor, resist, 0.0f, 1.5f);
        REQUIRE(res.isCrit == false);
        REQUIRE(res.finalDamage == Approx(100.0f));
    }

    SECTION("Armor Mitigation Formula: Raw * 100 / (100 + Armor)") {
        float armor = 100.0f; // Exactly 50% reduction: 100 / (100 + 100) = 0.5
        float resist = 0.0f;
        DamageResult res = DamageCalculator::calculate(inst, armor, resist, 0.0f, 1.5f);
        REQUIRE(res.finalDamage == Approx(50.0f));

        armor = 300.0f; // 100 / 400 = 0.25 -> 25 damage
        res = DamageCalculator::calculate(inst, armor, resist, 0.0f, 1.5f);
        REQUIRE(res.finalDamage == Approx(25.0f));
    }

    SECTION("Elemental Resistance Scaling") {
        inst.type = DamageType::Fire;
        float armor = 0.0f;
        float resist = 0.40f; // 40% fire resistance
        DamageResult res = DamageCalculator::calculate(inst, armor, resist, 0.0f, 1.5f);
        REQUIRE(res.finalDamage == Approx(60.0f));
    }

    SECTION("Guaranteed Critical Strike") {
        DamageResult res = DamageCalculator::calculate(inst, 0.0f, 0.0f, 1.0f, 2.0f);
        REQUIRE(res.isCrit == true);
        REQUIRE(res.finalDamage == Approx(200.0f)); // 100 * 2.0
    }
}

TEST_CASE("Combat Hitbox and Knockback Resolution", "[gameplay][combat]") {
    entt::registry registry;

    auto attacker = registry.create();
    registry.emplace<TransformComponent>(attacker, Vec2{100.0f, 100.0f});

    auto target = registry.create();
    registry.emplace<TransformComponent>(target, Vec2{120.0f, 100.0f});
    registry.emplace<VelocityComponent>(target, Vec2{0.0f, 0.0f});
    registry.emplace<HealthComponent>(target, 100.0f, 100.0f);
    registry.emplace<ColliderComponent>(target, Rect{-8.0f, -8.0f, 16.0f, 16.0f});

    SECTION("Hitbox Overlap Detection and Damage Application") {
        Hitbox attackBox;
        attackBox.bounds = Rect{115.0f, 95.0f, 10.0f, 10.0f}; // Overlaps target at 120, 100
        attackBox.damage = 30.0f;
        attackBox.knockbackForce = 150.0f;
        attackBox.owner = attacker;

        bool hit = CombatSystem::resolveHitbox(registry, attackBox, target);
        REQUIRE(hit == true);

        const auto& targetHealth = registry.get<HealthComponent>(target);
        REQUIRE(targetHealth.current == Approx(70.0f));

        const auto& targetVel = registry.get<VelocityComponent>(target);
        // Target should be knocked back horizontally to the right (+X)
        REQUIRE(targetVel.linear.x > 50.0f);
    }

    SECTION("Invulnerability Frames Block Hits") {
        auto& health = registry.get<HealthComponent>(target);
        health.invulnTimer = 0.5f; // Active i-frames

        Hitbox attackBox;
        attackBox.bounds = Rect{115.0f, 95.0f, 10.0f, 10.0f};
        attackBox.damage = 30.0f;
        attackBox.owner = attacker;

        bool hit = CombatSystem::resolveHitbox(registry, attackBox, target);
        REQUIRE(hit == false); // Blocked by i-frames
        REQUIRE(health.current == Approx(100.0f));
    }
}

TEST_CASE("Status Effects Duration and Periodic Ticks", "[gameplay][status]") {
    StatusEffectsManager manager;
    StatusEffectsComponent comp;

    SECTION("Applying Poison Status Effect") {
        manager.applyEffect(comp, StatusType::Poison, 4.0f, 1.0f, 10.0f); // 4s, 1s tick, 10 dmg/tick
        REQUIRE(comp.effects.size() == 1);
        REQUIRE(comp.effects[0].duration == Approx(4.0f));
    }

    SECTION("Stepping Status Effects Generates Damage Ticks") {
        manager.applyEffect(comp, StatusType::Burn, 3.0f, 1.0f, 15.0f);

        // Advance 0.5s: no tick yet
        float dmg = manager.update(comp, 0.5f);
        REQUIRE(dmg == Approx(0.0f));

        // Advance another 0.6s (total 1.1s): 1st tick fires
        dmg = manager.update(comp, 0.6f);
        REQUIRE(dmg == Approx(15.0f));

        // Advance another 1.0s: 2nd tick fires
        dmg = manager.update(comp, 1.0f);
        REQUIRE(dmg == Approx(15.0f));

        // Advance 1.0s: 3rd tick fires and effect expires
        dmg = manager.update(comp, 1.0f);
        REQUIRE(dmg == Approx(15.0f));
        REQUIRE(comp.effects.empty() == true);
    }

    SECTION("Cleansing Negative Status Effects") {
        manager.applyEffect(comp, StatusType::Bleed, 5.0f, 1.0f, 5.0f);
        manager.applyEffect(comp, StatusType::Rot, 5.0f, 1.0f, 8.0f);
        REQUIRE(comp.effects.size() == 2);

        manager.cleanseAll(comp);
        REQUIRE(comp.effects.empty() == true);
    }
}
