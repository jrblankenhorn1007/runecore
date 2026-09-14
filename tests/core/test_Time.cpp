#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include "core/Time.hpp"

using Catch::Approx;

TEST_CASE("TimeStep Fixed Accumulator and Delta Timers", "[core][time]") {
    SECTION("Default Construction and Target Hz") {
        TimeStep ts60(60.0f);
        REQUIRE(ts60.getFixedDelta() == Approx(1.0f / 60.0f));
        REQUIRE(ts60.getTicks() == 0);
        REQUIRE(ts60.getTotalTime() == Approx(0.0f));
        REQUIRE(ts60.getAlpha() == Approx(0.0f));

        TimeStep tsInvalid(-5.0f); // Fallback to 60.0f
        REQUIRE(tsInvalid.getFixedDelta() == Approx(1.0f / 60.0f));
    }

    SECTION("Stepping and Accumulation") {
        TimeStep ts(60.0f);
        // 0.034s is slightly more than 2 frames (2/60 = 0.033333s)
        int ticks = ts.update(0.034f);
        REQUIRE(ticks == 2);
        REQUIRE(ts.getTicks() == 2);
        REQUIRE(ts.getTotalTime() == Approx(0.034f));
        REQUIRE(ts.getAlpha() >= 0.0f);
        REQUIRE(ts.getAlpha() <= 1.0f);
    }

    SECTION("Spiral of Death Clamping") {
        TimeStep ts(60.0f);
        // Massive lag frame (2.0 seconds) clamped to max 10 frames
        int ticks = ts.update(2.0f);
        REQUIRE(ticks <= 10);
    }
}
