#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include "gameplay/survival/Metabolism.hpp"

using Catch::Approx;

TEST_CASE("Metabolism Hunger, Thirst, and Thermal Dynamics", "[gameplay][survival]") {
    Metabolism met;

    SECTION("Default Parameter Verification") {
        REQUIRE(met.getHunger() == Approx(100.0f));
        REQUIRE(met.getThirst() == Approx(100.0f));
        REQUIRE(met.getBodyTemperature() == Approx(37.0f));
        REQUIRE(met.isStarving() == false);
        REQUIRE(met.isDehydrated() == false);
        REQUIRE(met.isHypothermic() == false);
        REQUIRE(met.isHyperthermic() == false);
    }

    SECTION("Depletion and Ingestion") {
        met.setHunger(50.0f);
        met.eat(30.0f);
        REQUIRE(met.getHunger() == Approx(80.0f));

        met.setThirst(40.0f);
        met.drink(40.0f);
        REQUIRE(met.getThirst() == Approx(80.0f));
    }

    SECTION("Starvation Damage") {
        met.setHunger(0.0f);
        REQUIRE(met.isStarving() == true);
        float dmg = met.update(1.0f, 20.0f);
        REQUIRE(dmg > 0.0f);
    }

    SECTION("Temperature Extremes: Hypothermia and Hyperthermia") {
        // Hypothermia
        for (int i = 0; i < 50; ++i) {
            met.update(20.0f, -40.0f);
        }
        REQUIRE(met.isHypothermic() == true);

        // Hyperthermia
        for (int i = 0; i < 100; ++i) {
            met.update(20.0f, 90.0f);
        }
        REQUIRE(met.isHyperthermic() == true);
    }
}
