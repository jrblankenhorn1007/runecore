#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include "core/BotTester.hpp"
#include "core/GameSimulation.hpp"

using Catch::Approx;

TEST_CASE("BotTester Autonomous Scenario Execution and Reporting", "[core][bot_tester]") {
    GameSimulation sim;
    sim.initialize(ClassType::Juggernaut);

    BotTester bot;
    bot.reset();

    SECTION("Inspects Initial Phase and State") {
        REQUIRE(bot.isFinished() == false);
        REQUIRE(bot.getCurrentPhaseName() == "Testing Ground Movement & Sprint");
    }

    SECTION("Runs All 12 Phases to Completion") {
        for (int i = 0; i < 600; ++i) {
            if (bot.isFinished()) break;
            RawInputState input = bot.update(sim, 1.0f / 60.0f);
            sim.step(input.controller, 1.0f / 60.0f);
        }

        REQUIRE(bot.isFinished() == true);
        const BotReport& rep = bot.getReport();
        REQUIRE(rep.passedMovement == true);
        REQUIRE(rep.passedJumpAndDoubleJump == true);
        REQUIRE(rep.passedWallSlideAndJump == true);
        REQUIRE(rep.passedMining == true);
        REQUIRE(rep.passedLootVacuum == true);
        REQUIRE(rep.passedCrafting == true);
        REQUIRE(rep.passedRangedCombat == true);
        REQUIRE(rep.passedMeleeCombat == true);
        REQUIRE(rep.passedSkillCasting == true);
        REQUIRE(rep.passedDungeonEntry == true);
        REQUIRE(rep.passedDungeonBossDefeat == true);
        REQUIRE(rep.passedLevelUp == true);
        REQUIRE(rep.allTestsPassed() == true);

        rep.printSummary();
    }
}
