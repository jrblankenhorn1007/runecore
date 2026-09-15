#include <catch2/catch_test_macros.hpp>
#include "gameplay/ai/EnemyRoster.hpp"
#include "gameplay/survival/Environment.hpp"
#include "procgen/Tilemap.hpp"
#include "procgen/DungeonProps.hpp"
#include "procgen/MapFog.hpp"
#include "gameplay/building/BuildingSystem.hpp"
#include "gameplay/survival/SettlementSystem.hpp"

TEST_CASE("Enemy roster exposes family-specific behaviors") {
    auto slime = EnemyRoster::profile(EnemyType::Slime);
    auto raptor = EnemyRoster::profile(EnemyType::Raptor);
    auto harpy = EnemyRoster::profile(EnemyType::Harpy);
    auto gunner = EnemyRoster::profile(EnemyType::CyberGunner);
    auto carapace = EnemyRoster::profile(EnemyType::Carapace);
    REQUIRE(slime.splitsOnDeath);
    REQUIRE(raptor.canPin);
    REQUIRE(harpy.behavior == EnemyBehavior::Swoop);
    REQUIRE(gunner.behavior == EnemyBehavior::Volley);
    REQUIRE(gunner.usesCover);
    REQUIRE(carapace.frontalShield);
    REQUIRE(EnemyRoster::update(gunner, {0, 0}, {20, 0}, 20, 0).retreat);
    REQUIRE(EnemyRoster::update(raptor, {0, 0}, {20, 0}, 20, 0).pin);
    REQUIRE(EnemyRoster::update(harpy, {0, 0}, {20, 0}, 20, 0).retreat);
}

TEST_CASE("Sky transitions cover sunrise noon sunset and midnight") {
    REQUIRE(SkyTransition::colorAt(0).b < SkyTransition::colorAt(720).b);
    REQUIRE(SkyTransition::colorAt(360).r > SkyTransition::colorAt(720).r);
    REQUIRE(SkyTransition::colorAt(1080).r > SkyTransition::colorAt(720).r);
}

TEST_CASE("Tile palette autotiling and slopes") {
    Tilemap map;
    for (int x = 0; x < 3; ++x) map.setBlock(x, 0, BlockLayer::Foreground, 2);
    REQUIRE((map.getAutotileMask(1, 0, BlockLayer::Foreground) & 10) == 10);
    map.setSlope(1, 1, true);
    REQUIRE(map.isSlope(1, 1));
    REQUIRE(map.slopeRisesRight(1, 1));
}

TEST_CASE("Dungeon props and map fog support discovery interactions") {
    DungeonProps props;
    REQUIRE(props.place(1, 1, {DungeonPropType::Chest}));
    REQUIRE(props.interact(1, 1));
    REQUIRE_FALSE(props.interact(1, 1));
    props.place(2, 2, {DungeonPropType::Keycard, KeyColor::Red});
    REQUIRE(props.interact(2, 2, KeyColor::Red));
    REQUIRE_FALSE(props.interact(2, 2, KeyColor::Blue));
    MapFog fog;
    fog.addMarker({3, 4, MapIcon::Boss});
    REQUIRE_FALSE(fog.isRevealed(7));
    fog.revealRoom(7);
    REQUIRE(fog.isRevealed(7));
    REQUIRE(fog.markers().size() == 1);
}

TEST_CASE("Building tools enforce material specialization and placement ghosts") {
    BuildingSystem building;
    REQUIRE(building.placeBlock(1, 1, BlockType::Stone));
    REQUIRE_FALSE(building.breakBlock(1, 1, BuildingTool::Axe));
    REQUIRE(building.breakBlock(1, 1, BuildingTool::Pickaxe));
    REQUIRE(building.getPlacementGhost(1, 1, BlockType::WoodWall).valid);
}

TEST_CASE("Recruited NPCs provide their services") {
    SettlementSystem settlement;
    RoomBounds room{0, 0, 6, 6};
    REQUIRE(settlement.assignNPC(NPCType::Blacksmith, room));
    REQUIRE(settlement.assignNPC(NPCType::Doctor, room));
    REQUIRE(settlement.assignNPC(NPCType::Alchemist, room));
    REQUIRE(settlement.assignNPC(NPCType::Guide, room));
    REQUIRE(settlement.useService(NPCType::Blacksmith, NPCService::Repair, 10).success);
    REQUIRE(settlement.useService(NPCType::Doctor, NPCService::Heal).value == 25);
    REQUIRE(settlement.useService(NPCType::Guide, NPCService::Reveal).success);
}
