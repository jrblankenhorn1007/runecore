#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include "gameplay/survival/Metabolism.hpp"
#include "gameplay/survival/Environment.hpp"
#include "gameplay/building/BuildingSystem.hpp"
#include "gameplay/building/FarmingSystem.hpp"

using Catch::Approx;

TEST_CASE("Survival Metabolism Simulation Hunger, Thirst and Temperature", "[gameplay][survival]") {
    Metabolism metabolism;

    SECTION("Default Vital Parameters") {
        REQUIRE(metabolism.getHunger() == Approx(100.0f));
        REQUIRE(metabolism.getThirst() == Approx(100.0f));
        REQUIRE(metabolism.getBodyTemperature() == Approx(37.0f));
        REQUIRE(metabolism.isStarving() == false);
        REQUIRE(metabolism.isDehydrated() == false);
    }

    SECTION("Hunger and Thirst Depletion over Time") {
        // Step 60 seconds at normal rates
        metabolism.update(60.0f, 20.0f); // 20°C ambient
        REQUIRE(metabolism.getHunger() < 100.0f);
        REQUIRE(metabolism.getThirst() < 100.0f);

        // Test eating and drinking
        metabolism.eat(15.0f);
        REQUIRE(metabolism.getHunger() == Approx(100.0f));
        metabolism.drink(20.0f);
        REQUIRE(metabolism.getThirst() == Approx(100.0f));
    }

    SECTION("Starvation Damage when Hunger Reaches 0") {
        metabolism.setHunger(0.0f);
        REQUIRE(metabolism.isStarving() == true);
        float damage = metabolism.update(10.0f, 20.0f);
        REQUIRE(damage > 0.0f); // Deals starvation damage to player
    }

    SECTION("Environmental Cold Induces Hypothermia") {
        // Freeze at -20°C
        for (int i = 0; i < 10; ++i) {
            metabolism.update(30.0f, -20.0f);
        }
        REQUIRE(metabolism.getBodyTemperature() < 35.0f);
        REQUIRE(metabolism.isHypothermic() == true);
    }
}

TEST_CASE("Day-Night Cycle and Ambient Lighting Transitions", "[gameplay][survival]") {
    DayNightCycle dayNight(1440.0f); // 24 minute full cycle (1440 seconds)

    SECTION("Noon Has Minimum Darkness") {
        dayNight.setTimeOfDay(720.0f); // 12:00 PM
        REQUIRE(dayNight.getAmbientDarkness() == Approx(0.0f));
        REQUIRE(dayNight.isNight() == false);
    }

    SECTION("Midnight Has Maximum Darkness") {
        dayNight.setTimeOfDay(0.0f); // 12:00 AM
        REQUIRE(dayNight.getAmbientDarkness() > 0.70f);
        REQUIRE(dayNight.isNight() == true);
    }

    SECTION("Time Advances with Delta") {
        dayNight.setTimeOfDay(100.0f);
        dayNight.update(50.0f);
        REQUIRE(dayNight.getTimeOfDay() == Approx(150.0f));
    }
}

TEST_CASE("16x16 Grid Building System and Structural Support", "[gameplay][building]") {
    BuildingSystem building(16.0f);

    SECTION("Placing and Breaking Solid Blocks") {
        REQUIRE(building.placeBlock(5, 5, BlockType::WoodWall) == true);
        REQUIRE(building.getBlock(5, 5) == BlockType::WoodWall);

        // Cannot place over existing block
        REQUIRE(building.placeBlock(5, 5, BlockType::StoneWall) == false);

        // Break block
        REQUIRE(building.breakBlock(5, 5) == true);
        REQUIRE(building.getBlock(5, 5) == BlockType::Air);
    }

    SECTION("Placing Doors and Platforms") {
        REQUIRE(building.placeBlock(2, 4, BlockType::OneWayPlatform) == true);
        REQUIRE(building.placeBlock(2, 5, BlockType::WoodenDoor) == true);
        REQUIRE(building.isDoorOpen(2, 5) == false);

        building.toggleDoor(2, 5);
        REQUIRE(building.isDoorOpen(2, 5) == true);
    }
}

TEST_CASE("Agriculture Soil Tilling, Hydration and Crop Growth", "[gameplay][farming]") {
    FarmingSystem farming;

    SECTION("Tilling and Hydrating Soil Plot") {
        farming.tillSoil(10, 10);
        REQUIRE(farming.isTilled(10, 10) == true);
        REQUIRE(farming.isHydrated(10, 10) == false);

        farming.waterSoil(10, 10);
        REQUIRE(farming.isHydrated(10, 10) == true);
    }

    SECTION("Planting and Crop Growth Cycle") {
        farming.tillSoil(10, 10);
        farming.waterSoil(10, 10);

        REQUIRE(farming.plantSeed(10, 10, "crop_rust_wheat") == true);
        REQUIRE(farming.getCropStage(10, 10) == CropStage::Seed);

        // Advance growth time
        farming.update(50.0f); // 50s with water
        REQUIRE(farming.getCropStage(10, 10) >= CropStage::Sprout);

        farming.update(250.0f); // Total 300s -> fully mature
        REQUIRE(farming.getCropStage(10, 10) == CropStage::Mature);

        // Harvest yields produce
        HarvestResult harvest = farming.harvest(10, 10);
        REQUIRE(harvest.success == true);
        REQUIRE(harvest.produceItemId == "crop_rust_wheat");
        REQUIRE(harvest.yieldCount >= 2);
        REQUIRE(farming.getCropStage(10, 10) == CropStage::None);
    }
}
