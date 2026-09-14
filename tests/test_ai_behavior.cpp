#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include "gameplay/ai/EnemyAI.hpp"
#include "gameplay/ai/BossAI.hpp"

using Catch::Approx;

TEST_CASE("Enemy FSM State Transitions and Sensory Perception", "[gameplay][ai]") {
    EnemyAI ai;
    AIConfig config;
    config.sightRadius = 150.0f;
    config.attackRange = 25.0f;
    config.fleeHealthThreshold = 0.20f; // Flee when < 20% HP

    Vec2 enemyPos{100.0f, 100.0f};
    Vec2 playerPos{500.0f, 100.0f}; // Too far away initially (400px > 150px sight)
    float currentHealth = 100.0f;
    float maxHealth = 100.0f;

    SECTION("Idle/Patrol when Player is Out of Sight") {
        AIAction action = ai.update(enemyPos, playerPos, currentHealth, maxHealth, config, 0.1f);
        REQUIRE(ai.getState() == AIState::Patrol);
        REQUIRE(action.type == AIActionType::Move);
    }

    SECTION("Transitions to Chase when Player Enters Sight Radius") {
        playerPos = Vec2{200.0f, 100.0f}; // Distance = 100px < 150px sight
        AIAction action = ai.update(enemyPos, playerPos, currentHealth, maxHealth, config, 0.1f);

        REQUIRE(ai.getState() == AIState::Chase);
        REQUIRE(action.type == AIActionType::Move);
        REQUIRE(action.moveDirection.x > 0.0f); // Move right towards player at 200
    }

    SECTION("Transitions to Attack when within Attack Range") {
        playerPos = Vec2{115.0f, 100.0f}; // Distance = 15px < 25px range
        AIAction action = ai.update(enemyPos, playerPos, currentHealth, maxHealth, config, 0.1f);

        REQUIRE(ai.getState() == AIState::Attack);
        REQUIRE(action.type == AIActionType::Attack);
    }

    SECTION("Transitions to Flee when Health Drops Below Threshold") {
        playerPos = Vec2{150.0f, 100.0f};
        currentHealth = 15.0f; // 15% < 20%

        AIAction action = ai.update(enemyPos, playerPos, currentHealth, maxHealth, config, 0.1f);
        REQUIRE(ai.getState() == AIState::Flee);
        REQUIRE(action.type == AIActionType::Move);
        REQUIRE(action.moveDirection.x < 0.0f); // Run away from player (left)
    }
}

TEST_CASE("Multi-Phase Boss AI Transitions and Enrage State", "[gameplay][ai]") {
    BossAI boss;
    Vec2 bossPos{200.0f, 100.0f};
    Vec2 playerPos{250.0f, 100.0f};

    SECTION("Phase 1 at Full Health") {
        boss.update(bossPos, playerPos, 1000.0f, 1000.0f, 0.1f);
        REQUIRE(boss.getPhase() == BossPhase::Phase1);
        REQUIRE(boss.isEnraged() == false);
    }

    SECTION("Phase 2 Transition Trigger at 50% Health") {
        // Drop health to 490 (49% < 50%)
        BossAction act = boss.update(bossPos, playerPos, 490.0f, 1000.0f, 0.1f);
        REQUIRE(boss.getPhase() == BossPhase::Phase2);
        REQUIRE(boss.isEnraged() == true);
        REQUIRE(act.triggerPhaseTransitionBlast == true); // Invulnerable burst
    }

    SECTION("Enraged Boss Moves and Attacks Faster") {
        boss.update(bossPos, playerPos, 400.0f, 1000.0f, 0.1f);
        REQUIRE(boss.getSpeedMultiplier() > 1.25f);
        REQUIRE(boss.getAttackCooldown() < 2.0f);
    }
}
