#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include "core/BotTester.hpp"
#include "core/GameSimulation.hpp"

TEST_CASE("BotTester Autonomous Scenario Execution and Reporting", "[core][bot_tester]") {
    GameSimulation sim;
    sim.initialize(ClassType::Juggernaut);

    BotTester bot;
    bot.reset();

    SECTION("Inspects Initial Phase and State") {
        REQUIRE(bot.isFinished() == false);
        REQUIRE(bot.getCurrentPhaseName() == "Testing Ground Movement & Sprint");

        // Step through and query all phase names
        std::vector<std::string> phaseNames;
        for (int i = 0; i < 500; ++i) {
            std::string name = bot.getCurrentPhaseName();
            if (phaseNames.empty() || phaseNames.back() != name) {
                phaseNames.push_back(name);
            }
            RawInputState input = bot.update(sim, 1.0f / 60.0f);
            sim.step(input.controller, 1.0f / 60.0f);
            if (bot.isFinished()) break;
        }

        REQUIRE(phaseNames.size() >= 8);

        BotReport incomplete;
        REQUIRE(incomplete.allTestsPassed() == false);
        incomplete.printSummary(); // Prints failed report branches
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

TEST_CASE("Focused QA Scenarios Start Fresh and Pass Independently", "[core][qa]") {
    const auto scenarios = getFocusedScenarioNames();
    REQUIRE(scenarios.size() == 35);
    for (const auto& scenario : scenarios) {
        const FocusedScenarioResult result = runFocusedScenario(scenario);
        INFO("scenario=" << scenario << " detail=" << result.detail);
        REQUIRE(result.passed);
    }

    const FocusedScenarioResult aggregate = runFocusedScenario("all");
    REQUIRE(aggregate.passed);
}
