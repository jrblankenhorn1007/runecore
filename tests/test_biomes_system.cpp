#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include "procgen/BiomeSystem.hpp"
#include "physics/CollisionWorld.hpp"

using Catch::Approx;

TEST_CASE("Overworld Biome Engine and Ambient Climate Transitions", "[procgen][biomes]") {
    BiomeSystem biomeSys;

    SECTION("Resolves Biomes Along Horizontal World X Axis") {
        // X = 50 -> The Haven (Hub Valley, Temperate)
        BiomeData haven = biomeSys.getBiomeAt(50.0f);
        REQUIRE(haven.id == "bio_haven");
        REQUIRE(haven.tier == 1);
        REQUIRE(haven.ambientTemperature == Approx(22.0f));

        // X = 350 -> Rustwood Forest
        BiomeData rustwood = biomeSys.getBiomeAt(350.0f);
        REQUIRE(rustwood.id == "bio_rustwood");
        REQUIRE(rustwood.ambientTemperature == Approx(16.0f));

        // X = 750 -> Ashen Foundry (Extreme Heat)
        BiomeData foundry = biomeSys.getBiomeAt(750.0f);
        REQUIRE(foundry.id == "bio_foundry");
        REQUIRE(foundry.tier == 2);
        REQUIRE(foundry.ambientTemperature == Approx(85.0f));

        // X = 1200 -> Cryo-Glacier (Extreme Cold)
        BiomeData glacier = biomeSys.getBiomeAt(1200.0f);
        REQUIRE(glacier.id == "bio_glacier");
        REQUIRE(glacier.ambientTemperature == Approx(-18.0f));

        // X = 1600 -> Bioluminescent Bog
        BiomeData bog = biomeSys.getBiomeAt(1600.0f);
        REQUIRE(bog.id == "bio_bog");
        REQUIRE(bog.tier == 3);
    }

    SECTION("Smooth Ambient Temperature Interpolation Near Biome Borders") {
        // Border between Haven (22°C) and Rustwood (16°C) around X = 200
        float tempAtBorder = biomeSys.getAmbientTemperature(200.0f);
        REQUIRE(tempAtBorder >= 16.0f);
        REQUIRE(tempAtBorder <= 22.0f);
    }
}

TEST_CASE("Environmental Hazard Tiles Contact and Ailment Infliction", "[physics][hazards]") {
    CollisionWorld world(16.0f);
    BiomeSystem biomeSys;

    // Place hazard tiles at Y = 10 (160px)
    world.setTile(5, 10, TileType::HazardSpike);
    world.setTile(6, 10, TileType::HazardLava);

    Rect entityBox{-6.0f, -14.0f, 12.0f, 14.0f};

    SECTION("Contact with Hazard Spikes Deals Piercing Damage and Bleed") {
        Vec2 posOnSpikes{5.5f * 16.0f, 160.0f};
        HazardHit hit = biomeSys.checkHazard(world, posOnSpikes, entityBox);

        REQUIRE(hit.hasHazard == true);
        REQUIRE(hit.type == HazardType::Spikes);
        REQUIRE(hit.damage > 0.0f);
        REQUIRE(hit.inflictsBleed == true);
    }

    SECTION("Contact with Lava Deals Thermal Damage and Burn") {
        Vec2 posInLava{6.5f * 16.0f, 160.0f};
        HazardHit hit = biomeSys.checkHazard(world, posInLava, entityBox);

        REQUIRE(hit.hasHazard == true);
        REQUIRE(hit.type == HazardType::Lava);
        REQUIRE(hit.damage >= 50.0f);
        REQUIRE(hit.inflictsBurn == true);
    }

    SECTION("Safe Ground Has Zero Hazards") {
        world.setTile(10, 10, TileType::Solid); // Normal stone
        Vec2 posOnStone{10.5f * 16.0f, 160.0f};
        HazardHit hit = biomeSys.checkHazard(world, posOnStone, entityBox);

        REQUIRE(hit.hasHazard == false);
        REQUIRE(hit.damage == Approx(0.0f));
    }
}
