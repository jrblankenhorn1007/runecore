#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include "core/Random.hpp"

using Catch::Approx;

TEST_CASE("Random Generator Functions and Distributions", "[core][random]") {
    Random rng(12345);

    SECTION("Reseeding") {
        rng.setSeed(999);
        int v1 = rng.rangeInt(1, 100);
        rng.setSeed(999);
        int v2 = rng.rangeInt(1, 100);
        REQUIRE(v1 == v2);
    }

    SECTION("Range Int Uniformity and Bounds Inversion") {
        for (int i = 0; i < 50; ++i) {
            int val = rng.rangeInt(10, 20);
            REQUIRE(val >= 10);
            REQUIRE(val <= 20);
        }
        REQUIRE(rng.rangeInt(15, 10) == 15); // min >= max fallback
        REQUIRE(rng.rangeInt(10, 10) == 10);
    }

    SECTION("Range Float Uniformity and Bounds Inversion") {
        for (int i = 0; i < 50; ++i) {
            float f = rng.rangeFloat(5.0f, 8.0f);
            REQUIRE(f >= 5.0f);
            REQUIRE(f <= 8.0f);
        }
        REQUIRE(rng.rangeFloat(10.0f, 5.0f) == Approx(10.0f));
    }

    SECTION("Gaussian Distribution Clamping") {
        for (int i = 0; i < 100; ++i) {
            float val = rng.gaussian(50.0f, 10.0f, 30.0f, 70.0f);
            REQUIRE(val >= 30.0f);
            REQUIRE(val <= 70.0f);
        }
    }

    SECTION("Probability Chance Extremes") {
        REQUIRE(rng.chance(-0.1f) == false);
        REQUIRE(rng.chance(0.0f) == false);
        REQUIRE(rng.chance(1.0f) == true);
        REQUIRE(rng.chance(1.5f) == true);

        int hits = 0;
        for (int i = 0; i < 200; ++i) {
            if (rng.chance(0.5f)) hits++;
        }
        REQUIRE(hits > 50);
        REQUIRE(hits < 150);
    }
}
