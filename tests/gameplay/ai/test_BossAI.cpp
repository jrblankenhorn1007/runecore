#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include "gameplay/ai/BossAI.hpp"

using Catch::Approx;

TEST_CASE("BossAI Multi-Phase Progression and Enrage Dynamics", "[gameplay][ai]") {
    BossAI boss;
    Vec2 bossPos{100.0f, 100.0f};
    Vec2 playerPos{150.0f, 100.0f};

    SECTION("Phase 1 Normal Attacks") {
        BossAction act = boss.update(bossPos, playerPos, 1000.0f, 1000.0f, 0.1f);
        REQUIRE(boss.getPhase() == BossPhase::Phase1);
        REQUIRE(boss.isEnraged() == false);
        REQUIRE(boss.getSpeedMultiplier() == Approx(1.0f));
        REQUIRE(act.attackTriggered == true);

        // Immediate next tick: on cooldown
        BossAction act2 = boss.update(bossPos, playerPos, 1000.0f, 1000.0f, 0.1f);
        REQUIRE(act2.attackTriggered == false);
        BossAction warning = boss.update(bossPos, playerPos, 1000.0f, 1000.0f, 2.0f);
        REQUIRE(warning.telegraphActive == true);
        REQUIRE(warning.telegraphRadius == Approx(32.0f));

        // Cooldown expires during 3.5s update and triggers attack
        BossAction act3 = boss.update(bossPos, playerPos, 1000.0f, 1000.0f, 3.5f);
        REQUIRE(act3.attackTriggered == true);
    }

    SECTION("Phase 2 Trigger at <= 50% HP") {
        BossAction act = boss.update(bossPos, playerPos, 450.0f, 1000.0f, 0.1f);
        REQUIRE(boss.getPhase() == BossPhase::Phase2);
        REQUIRE(boss.isEnraged() == true);
        REQUIRE(boss.getSpeedMultiplier() > 1.2f);
        REQUIRE(act.triggerPhaseTransitionBlast == true);

        // Transition blast only triggers once
        BossAction act2 = boss.update(bossPos, playerPos, 400.0f, 1000.0f, 0.1f);
        REQUIRE(act2.triggerPhaseTransitionBlast == false);
    }
}
