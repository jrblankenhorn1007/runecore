#include <catch2/catch_test_macros.hpp>
#include "gameplay/building/FarmingSystem.hpp"

TEST_CASE("FarmingSystem Tilling, Irrigation, and Growth Stages", "[gameplay][farming]") {
    FarmingSystem fs;

    SECTION("Soil Tilling and Water State") {
        REQUIRE(fs.isTilled(5, 5) == false);
        REQUIRE(fs.isHydrated(5, 5) == false);

        fs.waterSoil(5, 5); // Cannot hydrate until tilled
        REQUIRE(fs.isHydrated(5, 5) == false);

        fs.tillSoil(5, 5);
        REQUIRE(fs.isTilled(5, 5) == true);
        REQUIRE(fs.isHydrated(5, 5) == false);

        fs.waterSoil(5, 5);
        REQUIRE(fs.isHydrated(5, 5) == true);
    }

    SECTION("Crop Planting, Stages, and Premature Harvest Rejection") {
        REQUIRE(fs.plantSeed(10, 10, "crop_wheat") == false); // Not tilled

        fs.tillSoil(10, 10);
        fs.waterSoil(10, 10);
        REQUIRE(fs.plantSeed(10, 10, "crop_wheat") == true);
        REQUIRE(fs.plantSeed(10, 10, "crop_wheat") == false); // Already planted
        REQUIRE(fs.getCropStage(10, 10) == CropStage::Seed);
        REQUIRE(fs.getCropStage(99, 99) == CropStage::None);

        // Premature harvest fails
        REQUIRE(fs.harvest(10, 10).success == false);
        REQUIRE(fs.harvest(99, 99).success == false);

        // Advance to Sprout (>= 25%)
        fs.update(15.0f); // 15s * 2x speed = 30%
        REQUIRE(fs.getCropStage(10, 10) == CropStage::Sprout);

        // Advance to Vegetative (>= 50%)
        fs.update(15.0f); // 30s * 2x = 60%
        REQUIRE(fs.getCropStage(10, 10) == CropStage::Vegetative);

        // Advance to Flowering (>= 75%)
        fs.update(10.0f); // 40s * 2x = 80%
        REQUIRE(fs.getCropStage(10, 10) == CropStage::Flowering);

        // Advance to Mature (>= 100%)
        fs.update(15.0f); // 55s * 2x = 110%
        REQUIRE(fs.getCropStage(10, 10) == CropStage::Mature);

        // Update when crop is already mature (hits continue branch)
        fs.update(10.0f);
        REQUIRE(fs.getCropStage(10, 10) == CropStage::Mature);

        // Successful harvest
        HarvestResult res = fs.harvest(10, 10);
        REQUIRE(res.success == true);
        REQUIRE(res.produceItemId == "crop_wheat");
        REQUIRE(res.yieldCount >= 2);
        REQUIRE(fs.getCropStage(10, 10) == CropStage::None);
    }
}
