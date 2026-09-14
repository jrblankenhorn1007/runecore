#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include "gameplay/building/BuildingSystem.hpp"

using Catch::Approx;

TEST_CASE("BuildingSystem Block Placement, Breaking, and Door Operations", "[gameplay][building]") {
    BuildingSystem bs(16.0f);
    REQUIRE(bs.getBlockSize() == Approx(16.0f));

    SECTION("Placing and Breaking Blocks") {
        REQUIRE(bs.placeBlock(5, 5, BlockType::Air) == false); // Cannot place air
        REQUIRE(bs.placeBlock(5, 5, BlockType::WoodWall) == true);
        REQUIRE(bs.getBlock(5, 5) == BlockType::WoodWall);
        REQUIRE(bs.placeBlock(5, 5, BlockType::StoneWall) == false); // Occupied

        REQUIRE(bs.breakBlock(5, 5) == true);
        REQUIRE(bs.breakBlock(5, 5) == false); // Already empty
        REQUIRE(bs.getBlock(5, 5) == BlockType::Air);
        REQUIRE(bs.getBlock(100, 100) == BlockType::Air);
    }

    SECTION("Door Toggling and State") {
        REQUIRE(bs.placeBlock(10, 10, BlockType::WoodenDoor) == true);
        REQUIRE(bs.isDoorOpen(10, 10) == false);

        bs.toggleDoor(10, 10);
        REQUIRE(bs.isDoorOpen(10, 10) == true);

        bs.toggleDoor(10, 10);
        REQUIRE(bs.isDoorOpen(10, 10) == false);

        REQUIRE(bs.isDoorOpen(99, 99) == false); // Nonexistent door
        bs.toggleDoor(99, 99); // Does not crash
    }
}
