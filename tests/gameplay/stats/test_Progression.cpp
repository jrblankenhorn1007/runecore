#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include "gameplay/stats/Progression.hpp"

using Catch::Approx;

TEST_CASE("Progression Uncapped Level Curve and Point Spending", "[gameplay][stats]") {
    Progression p;

    REQUIRE(p.getLevel() == 1);
    REQUIRE(p.getCurrentXP() == 0);
    REQUIRE(p.getXPForNextLevel() == Approx(100.0f));
    REQUIRE(p.isCrossClassUnlocked() == false);

    SECTION("XP Accumulation and Level Ups") {
        p.addXP(400); // Level 1 -> 2 (100 XP), Level 2 -> 3 (348 XP)
        REQUIRE(p.getLevel() >= 2);
        REQUIRE(p.getAttributePoints() >= 3);
        REQUIRE(p.getSkillPoints() >= 2);
    }

    SECTION("Set Level Directly") {
        p.setLevel(60);
        REQUIRE(p.getLevel() == 60);
        REQUIRE(p.isCrossClassUnlocked() == true);

        p.setLevel(50); // Lower level ignored
        REQUIRE(p.getLevel() == 60);
    }

    SECTION("Spending Points Boundary Cases") {
        p.setLevel(5); // 12 attr, 8 skill
        REQUIRE(p.spendAttributePoints(0) == false);
        REQUIRE(p.spendAttributePoints(-5) == false);
        REQUIRE(p.spendAttributePoints(20) == false); // Too much
        REQUIRE(p.spendAttributePoints(6) == true);
        REQUIRE(p.getAttributePoints() == 6);

        REQUIRE(p.spendSkillPoints(0) == false);
        REQUIRE(p.spendSkillPoints(-2) == false);
        REQUIRE(p.spendSkillPoints(20) == false);
        REQUIRE(p.spendSkillPoints(4) == true);
        REQUIRE(p.getSkillPoints() == 4);
    }
}
