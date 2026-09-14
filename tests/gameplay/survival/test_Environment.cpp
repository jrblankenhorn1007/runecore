#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include "gameplay/survival/Environment.hpp"

using Catch::Approx;

TEST_CASE("Environment DayNightCycle and Weather Parameters", "[gameplay][survival]") {
    DayNightCycle dnc(1440.0f); // 24-minute cycle

    SECTION("Initial Noon State") {
        dnc.setTimeOfDay(720.0f); // Noon
        REQUIRE(dnc.getTimeOfDay() == Approx(720.0f));
        REQUIRE(dnc.getAmbientDarkness() == Approx(0.0f));
        REQUIRE(dnc.isNight() == false);
    }

    SECTION("Midnight Darkness") {
        dnc.setTimeOfDay(0.0f);
        REQUIRE(dnc.getAmbientDarkness() > 0.70f);
        REQUIRE(dnc.isNight() == true);
    }

    SECTION("Time Updates and Cycle Wraparound") {
        dnc.setTimeOfDay(1400.0f);
        dnc.update(100.0f); // 1500 -> wraps to 60.0f
        REQUIRE(dnc.getTimeOfDay() == Approx(60.0f));
    }

    SECTION("Weather Selection") {
        dnc.setWeather(WeatherType::Blizzard);
        REQUIRE(dnc.getWeather() == WeatherType::Blizzard);
        dnc.setWeather(WeatherType::FalloutStorm);
        REQUIRE(dnc.getWeather() == WeatherType::FalloutStorm);
    }
}
