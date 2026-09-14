#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include "procgen/Tilemap.hpp"
#include "procgen/DungeonGenerator.hpp"
#include "core/Random.hpp"

using Catch::Approx;

TEST_CASE("Tilemap Chunk Storage and Layer Operations", "[procgen][tilemap]") {
    Tilemap map(16.0f); // 16px tile size

    SECTION("Setting and Getting Foreground Blocks Across Chunks") {
        // Chunk (0, 0)
        map.setBlock(5, 5, BlockLayer::Foreground, 1); // Solid Stone
        REQUIRE(map.getBlock(5, 5, BlockLayer::Foreground) == 1);

        // Chunk (1, 2) -> X = 45 (chunkX = 1, localX = 13), Y = 70 (chunkY = 2, localY = 6)
        map.setBlock(45, 70, BlockLayer::Foreground, 2); // Iron Ore
        REQUIRE(map.getBlock(45, 70, BlockLayer::Foreground) == 2);

        // Background wall layer is independent
        map.setBlock(5, 5, BlockLayer::Background, 10); // Wooden Wall
        REQUIRE(map.getBlock(5, 5, BlockLayer::Background) == 10);
        REQUIRE(map.getBlock(5, 5, BlockLayer::Foreground) == 1);
    }

    SECTION("Default Unloaded / Unset Tiles Return Empty Air (0)") {
        REQUIRE(map.getBlock(999, 999, BlockLayer::Foreground) == 0);
    }
}

TEST_CASE("Hybrid BSP Procedural Dungeon Generator", "[procgen][dungeon]") {
    Random rng(12345);
    DungeonGenerator generator(rng);

    DungeonConfig config;
    config.width = 60;
    config.height = 40;
    config.minRoomSize = 6;
    config.maxRoomSize = 12;
    config.maxDepth = 4;

    DungeonLayout layout = generator.generate(config);

    SECTION("Generates Non-Empty Layout within Bounds") {
        REQUIRE(layout.width == 60);
        REQUIRE(layout.height == 40);
        REQUIRE(layout.rooms.size() >= 4);
    }

    SECTION("Start Entrance and Boss Room Exist") {
        REQUIRE(layout.startRoomIndex >= 0);
        REQUIRE(layout.bossRoomIndex >= 0);
        REQUIRE(layout.startRoomIndex != layout.bossRoomIndex);
    }

    SECTION("Carved Corridors Connect Rooms (Path Exists Between Start and Boss)") {
        bool pathExists = layout.hasPath(layout.startRoomIndex, layout.bossRoomIndex);
        REQUIRE(pathExists == true);
    }

    SECTION("Rooms Lie Strictly Inside Dungeon Bounding Box") {
        for (const auto& room : layout.rooms) {
            REQUIRE(room.x >= 1);
            REQUIRE(room.y >= 1);
            REQUIRE(room.x + room.width < config.width);
            REQUIRE(room.y + room.height < config.height);
        }
    }
}
