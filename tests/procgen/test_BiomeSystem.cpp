#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include "procgen/BiomeSystem.hpp"
#include "physics/CollisionWorld.hpp"

using Catch::Approx;

TEST_CASE("BiomeSystem Horizontal Progression and Hazard Intersections", "[procgen][biomes]") {
    BiomeSystem bs;
    CollisionWorld world(16.0f);

    SECTION("Resolves All Horizontal Biome Zones") {
        REQUIRE(bs.getBiomeAt(-100.0f).id == "bio_haven");
        REQUIRE(bs.getBiomeAt(300.0f).id == "bio_rustwood");
        REQUIRE(bs.getBiomeAt(700.0f).id == "bio_foundry");
        REQUIRE(bs.getBiomeAt(1100.0f).id == "bio_glacier");
        REQUIRE(bs.getBiomeAt(1500.0f).id == "bio_bog");
        REQUIRE(bs.getBiomeAt(99999.0f).id == "bio_haven"); // Fallback
    }

    SECTION("Ambient Temperature Blending") {
        float tempHaven = bs.getAmbientTemperature(50.0f);
        REQUIRE(tempHaven == Approx(22.0f));

        float tempRustwood = bs.getAmbientTemperature(400.0f);
        REQUIRE(tempRustwood == Approx(16.0f));

        // Blended boundary around X = 200
        float tempBlend = bs.getAmbientTemperature(200.0f);
        REQUIRE(tempBlend >= 16.0f);
        REQUIRE(tempBlend <= 22.0f);
    }

    SECTION("Hazard Spikes and Lava Detection") {
        world.setTile(10, 10, TileType::HazardSpike);
        world.setTile(12, 10, TileType::HazardLava);

        Rect box{-6.0f, -6.0f, 12.0f, 12.0f};

        HazardHit hSpike = bs.checkHazard(world, Vec2{10.5f * 16.0f, 10.5f * 16.0f}, box);
        REQUIRE(hSpike.hasHazard == true);
        REQUIRE(hSpike.type == HazardType::Spikes);
        REQUIRE(hSpike.inflictsBleed == true);

        HazardHit hLava = bs.checkHazard(world, Vec2{12.5f * 16.0f, 10.5f * 16.0f}, box);
        REQUIRE(hLava.hasHazard == true);
        REQUIRE(hLava.type == HazardType::Lava);
        REQUIRE(hLava.inflictsBurn == true);

        HazardHit hSafe = bs.checkHazard(world, Vec2{0.0f, 0.0f}, box);
        REQUIRE(hSafe.hasHazard == false);
    }
}
