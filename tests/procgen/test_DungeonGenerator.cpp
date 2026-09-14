#include <catch2/catch_test_macros.hpp>
#include "procgen/DungeonGenerator.hpp"
#include "core/Random.hpp"

TEST_CASE("DungeonGenerator BSP Splitting and Corridors", "[procgen][dungeon]") {
    Random rng(1337);
    DungeonGenerator dg(rng);

    DungeonConfig cfg{60, 40, 6, 12, 4};
    DungeonLayout layout = dg.generate(cfg);

    REQUIRE(layout.width == 60);
    REQUIRE(layout.height == 40);
    REQUIRE(layout.rooms.size() >= 4);
    REQUIRE(layout.startRoomIndex != layout.bossRoomIndex);
    REQUIRE(layout.hasPath(layout.startRoomIndex, layout.bossRoomIndex) == true);

    // Invalid path bounds
    REQUIRE(layout.hasPath(-1, 0) == false);
    REQUIRE(layout.hasPath(0, 999) == false);

    // Wall off half the dungeon to verify hasPath returns false
    for (int y = 0; y < layout.height; ++y) {
        layout.grid[y][layout.width / 2] = 1;
    }
    REQUIRE(layout.hasPath(layout.startRoomIndex, layout.bossRoomIndex) == false);
}
