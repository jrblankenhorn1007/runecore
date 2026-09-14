#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include "ecs/Components.hpp"

using Catch::Approx;

TEST_CASE("ECS Components Lifecycle, Methods, and Modifiers", "[ecs][components]") {
    SECTION("TransformComponent Constructors") {
        TransformComponent t1;
        REQUIRE(t1.position.x == Approx(0.0f));

        TransformComponent t2(Vec2{5.0f, 10.0f});
        REQUIRE(t2.position.x == Approx(5.0f));

        TransformComponent t3(Vec2{1.0f, 2.0f}, Vec2{2.0f, 2.0f}, 45.0f);
        REQUIRE(t3.rotation == Approx(45.0f));
    }

    SECTION("VelocityComponent Constructors") {
        VelocityComponent v1;
        REQUIRE(v1.maxSpeed == Approx(200.0f));

        VelocityComponent v2(Vec2{10.0f, 20.0f});
        REQUIRE(v2.linear.x == Approx(10.0f));

        VelocityComponent v3(Vec2{1.0f, 2.0f}, 350.0f);
        REQUIRE(v3.maxSpeed == Approx(350.0f));
    }

    SECTION("ColliderComponent Constructors") {
        ColliderComponent c1;
        REQUIRE(c1.isTrigger == false);

        ColliderComponent c2(Rect{0.0f, 0.0f, 10.0f, 10.0f}, true);
        REQUIRE(c2.isTrigger == true);
    }

    SECTION("HealthComponent Damage, Heal, and Regen") {
        HealthComponent hc(100.0f, 100.0f, 1.0f);
        hc.takeDamage(40.0f);
        REQUIRE(hc.current == Approx(60.0f));
        REQUIRE(hc.isDead == false);

        hc.takeDamage(-10.0f); // Negative damage ignored
        REQUIRE(hc.current == Approx(60.0f));

        hc.takeDamage(100.0f);
        REQUIRE(hc.current == Approx(0.0f));
        REQUIRE(hc.isDead == true);

        hc.takeDamage(10.0f); // Damage while dead ignored
        REQUIRE(hc.current == Approx(0.0f));

        hc.heal(-5.0f); // Negative heal ignored
        REQUIRE(hc.current == Approx(0.0f));

        hc.heal(30.0f); // Revive
        REQUIRE(hc.current == Approx(30.0f));
        REQUIRE(hc.isDead == false);

        hc.invulnTimer = 0.5f;
        hc.update(0.2f);
        REQUIRE(hc.invulnTimer == Approx(0.3f));
        REQUIRE(hc.current > 30.0f); // Regenerated
    }

    SECTION("ManaComponent Operations") {
        ManaComponent mc(50.0f, 50.0f, 2.0f);
        REQUIRE(mc.consume(-10.0f) == false);
        REQUIRE(mc.consume(20.0f) == true);
        REQUIRE(mc.current == Approx(30.0f));
        REQUIRE(mc.consume(40.0f) == false); // Insufficient
        REQUIRE(mc.current == Approx(30.0f));

        mc.restore(-5.0f);
        mc.restore(10.0f);
        REQUIRE(mc.current == Approx(40.0f));

        mc.update(1.0f);
        REQUIRE(mc.current == Approx(42.0f));
    }

    SECTION("PowerComponent Operations") {
        PowerComponent pc(50.0f, 100.0f, 5.0f);
        REQUIRE(pc.consume(-5.0f) == false);
        REQUIRE(pc.consume(20.0f) == true);
        REQUIRE(pc.current == Approx(30.0f));

        pc.charge(-10.0f);
        pc.charge(30.0f);
        REQUIRE(pc.current == Approx(60.0f));

        pc.update(1.0f);
        REQUIRE(pc.current == Approx(65.0f));
    }

    SECTION("Tags and Other Components") {
        EnemyTag et(2, 200);
        REQUIRE(et.tier == 2);
        REQUIRE(et.xpReward == 200);

        ProjectileComponent pc;
        REQUIRE(pc.damage == Approx(10.0f));

        StatsComponent sc;
        REQUIRE(sc.strength == 10);
    }
}
