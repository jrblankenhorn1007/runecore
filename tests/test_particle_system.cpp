#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include "render/ParticleSystem.hpp"

using Catch::Approx;

TEST_CASE("Particle System Allocation, Lifecycle, and Physics", "[render][particles]") {
    ParticleSystem ps(100);

    SECTION("Initial Pool is Empty") {
        REQUIRE(ps.getActiveCount() == 0);
    }

    SECTION("Spawning Single Particle and Lifetime Decay") {
        ps.emit(Vec2{50.0f, 50.0f}, Vec2{10.0f, -20.0f}, Color{255, 100, 50, 255}, 1.0f, 4.0f);
        REQUIRE(ps.getActiveCount() == 1);

        // Update 0.5s -> still active
        ps.update(0.5f);
        REQUIRE(ps.getActiveCount() == 1);

        // Update 0.6s (total 1.1s > 1.0s lifetime) -> expired
        ps.update(0.6f);
        REQUIRE(ps.getActiveCount() == 0);
    }

    SECTION("Combat Burst Emitter (Sparks and Blood)") {
        ps.emitBurst(Vec2{100.0f, 100.0f}, 15, Color{255, 50, 50, 255}, 0.5f, 50.0f);
        REQUIRE(ps.getActiveCount() == 15);

        ps.update(0.6f);
        REQUIRE(ps.getActiveCount() == 0);
    }
}
