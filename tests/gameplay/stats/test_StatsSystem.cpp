#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include "gameplay/stats/StatsSystem.hpp"

using Catch::Approx;

TEST_CASE("StatsSystem Mathematical Attribute Scaling", "[gameplay][stats]") {
    Attributes attrs{15, 20, 25, 30, 10, 18};
    DerivedStats d = StatsSystem::calculateDerivedStats(attrs);

    // Health: 100 + (15 * 5) + (30 * 10) = 475
    REQUIRE(d.maxHealth == Approx(475.0f));
    // Mana: 50 + (25 * 5) = 175
    REQUIRE(d.maxMana == Approx(175.0f));
    // Power: 50 + (18 * 5) = 140
    REQUIRE(d.maxPower == Approx(140.0f));
    // Cooldown Reduction: 18 * 0.005 = 0.09
    REQUIRE(d.cooldownReduction == Approx(0.09f));
    // Carry Weight: 50 + (15 * 0.5) = 57.5
    REQUIRE(d.carryWeightCapacity == Approx(57.5f));
    // Damage Multipliers
    REQUIRE(d.physicalDamageMultiplier == Approx(1.15f));
    REQUIRE(d.rangedDamageMultiplier == Approx(1.20f));
    REQUIRE(d.magicDamageMultiplier == Approx(1.25f));
}
