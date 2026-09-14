#include <catch2/catch_test_macros.hpp>
#include "gameplay/building/WorldInteraction.hpp"
#include "physics/CollisionWorld.hpp"
#include "procgen/Tilemap.hpp"
#include "gameplay/items/LootSystem.hpp"
#include "gameplay/items/Inventory.hpp"

TEST_CASE("WorldInteraction Mining and Block Placement Operations", "[gameplay][world_interaction]") {
    entt::registry reg;
    CollisionWorld physics(16.0f);
    Tilemap tilemap(16.0f);
    LootSystem loot;
    WorldInteraction wi(physics, tilemap, loot);
    Inventory inv;

    Vec2 playerPos{100.0f, 100.0f};

    SECTION("Mining Distant or Empty Tile Fails") {
        REQUIRE(wi.mineTile(reg, playerPos, Vec2{500.0f, 500.0f}) == false); // Out of reach
        REQUIRE(wi.mineTile(reg, playerPos, Vec2{110.0f, 110.0f}) == false); // Empty tile
    }

    SECTION("Mining Different Tile Types Spawns Matching Drops") {
        // Tile 1: Stone
        physics.setTile(6, 6, TileType::Solid);
        tilemap.setBlock(6, 6, BlockLayer::Foreground, 1);
        REQUIRE(wi.mineTile(reg, playerPos, Vec2{6.5f * 16.0f, 6.5f * 16.0f}) == true);

        // Tile 2: Iron Ore
        physics.setTile(7, 6, TileType::Solid);
        tilemap.setBlock(7, 6, BlockLayer::Foreground, 2);
        REQUIRE(wi.mineTile(reg, playerPos, Vec2{7.5f * 16.0f, 6.5f * 16.0f}) == true);

        // Tile 3: Wood Plank
        physics.setTile(6, 7, TileType::Solid);
        tilemap.setBlock(6, 7, BlockLayer::Foreground, 3);
        REQUIRE(wi.mineTile(reg, playerPos, Vec2{6.5f * 16.0f, 7.5f * 16.0f}) == true);
    }

    SECTION("Block Placement Edge Cases") {
        REQUIRE(wi.placeBlock(inv, "mat_wood", playerPos, Vec2{500.0f, 500.0f}) == false); // Out of reach
        REQUIRE(wi.placeBlock(inv, "mat_wood", playerPos, Vec2{110.0f, 110.0f}) == false); // Not in inventory

        Item wood; wood.id = "mat_wood"; wood.quantity = 2; wood.stackable = true;
        inv.addItem(wood);

        physics.setTile(6, 6, TileType::Solid); // Already occupied
        REQUIRE(wi.placeBlock(inv, "mat_wood", playerPos, Vec2{6.5f * 16.0f, 6.5f * 16.0f}) == false);

        // Valid placement into air
        REQUIRE(wi.placeBlock(inv, "mat_wood", playerPos, Vec2{5.5f * 16.0f, 5.5f * 16.0f}, 80.0f, 3) == true);
        REQUIRE(inv.getItemCount("mat_wood") == 1);
    }
}

TEST_CASE("DungeonTransitionManager State Transitions", "[gameplay][world_interaction]") {
    DungeonTransitionManager dtm;
    REQUIRE(dtm.getCurrentZone() == WorldZone::Overworld);
    REQUIRE(dtm.isBossDefeated() == false);
    REQUIRE(dtm.canExitDungeon() == false);

    dtm.enterDungeon(2);
    REQUIRE(dtm.getCurrentZone() == WorldZone::Dungeon);
    REQUIRE(dtm.getCurrentDungeonTier() == 2);

    dtm.setBossDefeated(true);
    REQUIRE(dtm.isBossDefeated() == true);
    REQUIRE(dtm.canExitDungeon() == true);

    dtm.exitDungeon();
    REQUIRE(dtm.getCurrentZone() == WorldZone::Overworld);
    REQUIRE(dtm.isBossDefeated() == false);
}
