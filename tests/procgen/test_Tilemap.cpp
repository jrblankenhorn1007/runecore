#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include "procgen/Tilemap.hpp"

using Catch::Approx;

TEST_CASE("Tilemap Multilayer Chunks and Unloaded Space", "[procgen][tilemap]") {
    Tilemap tm(16.0f);
    REQUIRE(tm.getTileSize() == Approx(16.0f));

    SECTION("Independent Layers") {
        tm.setBlock(10, 20, BlockLayer::Foreground, 1);
        tm.setBlock(10, 20, BlockLayer::Background, 5);

        REQUIRE(tm.getBlock(10, 20, BlockLayer::Foreground) == 1);
        REQUIRE(tm.getBlock(10, 20, BlockLayer::Background) == 5);
        REQUIRE(tm.getBlock(11, 20, BlockLayer::Foreground) == 0); // Empty air

        // Query background tile in chunk that exists but where background is 0
        tm.setBlock(10, 21, BlockLayer::Foreground, 2);
        REQUIRE(tm.getBlock(10, 21, BlockLayer::Background) == 0);
    }

    SECTION("Negative Coordinates and Chunk Boundaries") {
        tm.setBlock(-45, -70, BlockLayer::Foreground, 3);
        REQUIRE(tm.getBlock(-45, -70, BlockLayer::Foreground) == 3);
    }
}
