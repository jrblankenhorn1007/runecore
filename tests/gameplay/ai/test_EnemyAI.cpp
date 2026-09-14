#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include "gameplay/ai/EnemyAI.hpp"

using Catch::Approx;

TEST_CASE("EnemyAI Sensory Logic and State Transitions", "[gameplay][ai]") {
    EnemyAI ai;
    AIConfig config;
    config.sightRadius = 100.0f;
    config.attackRange = 20.0f;
    config.attackCooldown = 1.0f;
    config.fleeHealthThreshold = 0.20f;

    Vec2 enemyPos{100.0f, 100.0f};

    SECTION("Patrol State and Direction Flipping") {
        Vec2 farPlayer{500.0f, 500.0f};
        AIAction act1 = ai.update(enemyPos, farPlayer, 100.0f, 100.0f, config, 0.5f);
        REQUIRE(ai.getState() == AIState::Patrol);
        REQUIRE(act1.type == AIActionType::Move);

        // Advance 2.5s -> patrol timer flips direction
        AIAction act2 = ai.update(enemyPos, farPlayer, 100.0f, 100.0f, config, 2.5f);
        REQUIRE(ai.getState() == AIState::Patrol);
        REQUIRE(act2.type == AIActionType::Move);
    }

    SECTION("Chase State when Player is Spotted") {
        Vec2 nearPlayer{150.0f, 100.0f}; // 50px distance <= 100px sight
        AIAction act = ai.update(enemyPos, nearPlayer, 100.0f, 100.0f, config, 0.1f);
        REQUIRE(ai.getState() == AIState::Chase);
        REQUIRE(act.type == AIActionType::Move);
        REQUIRE(act.moveDirection.x > 0.0f);
    }

    SECTION("Attack State and Cooldown Countdown") {
        Vec2 closePlayer{110.0f, 100.0f}; // 10px distance <= 20px range
        AIAction act1 = ai.update(enemyPos, closePlayer, 100.0f, 100.0f, config, 0.1f);
        REQUIRE(ai.getState() == AIState::Attack);
        REQUIRE(act1.attackTriggered == true);

        // Immediate next tick is on cooldown
        AIAction act2 = ai.update(enemyPos, closePlayer, 100.0f, 100.0f, config, 0.1f);
        REQUIRE(act2.type == AIActionType::None);

        // Cooldown expires after 1.1s and triggers attack
        AIAction act3 = ai.update(enemyPos, closePlayer, 100.0f, 100.0f, config, 1.1f);
        REQUIRE(act3.attackTriggered == true);
    }

    SECTION("Flee State when Health is Low") {
        Vec2 nearPlayer{130.0f, 100.0f};
        AIAction act = ai.update(enemyPos, nearPlayer, 10.0f, 100.0f, config, 0.1f); // 10% <= 20%
        REQUIRE(ai.getState() == AIState::Flee);
        REQUIRE(act.type == AIActionType::Move);
        REQUIRE(act.moveDirection.x < 0.0f); // Running away (left)
    }
}
