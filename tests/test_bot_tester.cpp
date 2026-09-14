#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include "core/BotTester.hpp"
#include "core/GameSimulation.hpp"

using Catch::Approx;

TEST_CASE("Automated Bot Tester Full 12-System Verification Run", "[core][bot_tester]") {
    GameSimulation sim;
    sim.initialize(ClassType::Juggernaut);

    BotTester bot;
    bot.reset();

    SECTION("Bot Executes Full Autonomous Gameplay Cycle and All Subsystems Pass") {
        const int maxTicks = 600;
        for (int tick = 0; tick < maxTicks; ++tick) {
            if (bot.isFinished()) break;

            RawInputState input = bot.update(sim, 1.0f / 60.0f);
            sim.step(input.controller, 1.0f / 60.0f);
        }

        const BotReport& report = bot.getReport();

        REQUIRE(report.passedMovement == true);
        REQUIRE(report.passedJumpAndDoubleJump == true);
        REQUIRE(report.passedWallSlideAndJump == true);
        REQUIRE(report.passedMining == true);
        REQUIRE(report.passedLootVacuum == true);
        REQUIRE(report.passedCrafting == true);
        REQUIRE(report.passedRangedCombat == true);
        REQUIRE(report.passedMeleeCombat == true);
        REQUIRE(report.passedSkillCasting == true);
        REQUIRE(report.passedDungeonEntry == true);
        REQUIRE(report.passedDungeonBossDefeat == true);
        REQUIRE(report.passedLevelUp == true);
        REQUIRE(report.allTestsPassed() == true);
    }
}
