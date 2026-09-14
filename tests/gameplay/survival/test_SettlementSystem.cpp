#include <catch2/catch_test_macros.hpp>
#include "gameplay/survival/SettlementSystem.hpp"
#include "procgen/Tilemap.hpp"

TEST_CASE("SettlementSystem Enclosure and NPC Recruitment", "[gameplay][survival]") {
    Tilemap tm(16.0f);
    SettlementSystem ss;

    RoomBounds tooSmall{0, 0, 3, 3};
    REQUIRE(ss.checkSuitability(tm, tooSmall).isSuitable == false);

    RoomBounds room{0, 0, 5, 5};
    // Make enclosure: top & bottom walls
    for (int x = 0; x < 5; ++x) {
        tm.setBlock(x, 0, BlockLayer::Foreground, 1);
        tm.setBlock(x, 4, BlockLayer::Foreground, 1);
    }
    // Left & Right walls (with door at 4, 3)
    for (int y = 1; y < 4; ++y) {
        tm.setBlock(0, y, BlockLayer::Foreground, 1);
        if (y == 3) {
            tm.setBlock(4, y, BlockLayer::Foreground, 6); // Door
        } else {
            tm.setBlock(4, y, BlockLayer::Foreground, 1);
        }
    }

    HousingCheckResult r1 = ss.checkSuitability(tm, room);
    REQUIRE(r1.isEnclosed == true);
    REQUIRE(r1.hasDoor == true);
    REQUIRE(r1.isSuitable == false); // Missing light and furniture

    tm.setBlock(2, 2, BlockLayer::Foreground, 8); // Torch
    tm.setBlock(1, 3, BlockLayer::Foreground, 9); // Bed

    HousingCheckResult r2 = ss.checkSuitability(tm, room);
    REQUIRE(r2.hasLightSource == true);
    REQUIRE(r2.hasFurniture == true);
    REQUIRE(r2.isSuitable == true);

    REQUIRE(ss.assignNPC(NPCType::None, room) == false);
    REQUIRE(ss.assignNPC(NPCType::Doctor, room) == true);
    REQUIRE(ss.isNPCResident(NPCType::Doctor) == true);
    REQUIRE(ss.isNPCResident(NPCType::Merchant) == false);
}
