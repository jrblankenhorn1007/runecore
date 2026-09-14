#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include "render/ParticleSystem.hpp"

using Catch::Approx;

TEST_CASE("ParticleSystem Pooling, Burst Emitters, and Decay", "[render][particles]") {
    ParticleSystem ps(50);
    REQUIRE(ps.getActiveCount() == 0);
    REQUIRE(ps.getParticles().size() == 50);

    SECTION("Single Particle Emission") {
        ps.emit(Vec2{0.0f, 0.0f}, Vec2{10.0f, -10.0f}, Color{255, 0, 0, 255}, 1.0f, 2.0f);
        REQUIRE(ps.getActiveCount() == 1);

        ps.update(0.5f);
        REQUIRE(ps.getActiveCount() == 1);

        ps.update(0.6f);
        REQUIRE(ps.getActiveCount() == 0);
    }

    SECTION("Burst Emission") {
        ps.emitBurst(Vec2{50.0f, 50.0f}, 10, Color{0, 255, 0, 255}, 0.5f, 25.0f);
        REQUIRE(ps.getActiveCount() == 10);

        ps.update(0.6f);
        REQUIRE(ps.getActiveCount() == 0);
    }
}
