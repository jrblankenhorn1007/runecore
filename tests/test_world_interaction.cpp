#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include "gameplay/building/WorldInteraction.hpp"
#include "procgen/Tilemap.hpp"
#include "physics/CollisionWorld.hpp"
#include "gameplay/items/Inventory.hpp"
#include "gameplay/items/LootSystem.hpp"

using Catch::Approx;

TEST_CASE("World Mining, Tile Destruction and Block Placement", "[world][interaction]") {
    entt::registry registry;
    CollisionWorld physics(16.0f);
    Tilemap tilemap(16.0f);
    LootSystem lootSys;
    Inventory inv(40);

    // Build solid floor and stone blocks
    physics.setTile(5, 5, TileType::Solid);
    tilemap.setBlock(5, 5, BlockLayer::Foreground, 1); // 1 = Stone

    physics.setTile(6, 5, TileType::Solid);
    tilemap.setBlock(6, 5, BlockLayer::Foreground, 2); // 2 = Iron Ore

    WorldInteraction interaction(physics, tilemap, lootSys);

    Vec2 playerPos{5.0f * 16.0f, 4.0f * 16.0f}; // Directly above tile (5, 5)

    SECTION("Mining Block Within Reach Breaks Tile and Spawns Loot") {
        Vec2 targetPos{5.5f * 16.0f, 5.5f * 16.0f}; // Aiming at tile (5, 5)

        bool mined = interaction.mineTile(registry, playerPos, targetPos, 80.0f);
        REQUIRE(mined == true);

        // Tile should now be empty in both physics and tilemap
        REQUIRE(physics.isSolid(5, 5) == false);
        REQUIRE(tilemap.getBlock(5, 5, BlockLayer::Foreground) == 0);

        // Dropped loot entity should exist in registry
        auto lootView = registry.view<DroppedItemComponent>();
        REQUIRE(lootView.size() == 1);
    }

    SECTION("Mining Outside Reach Radius Fails") {
        Vec2 farTarget{500.0f, 500.0f};
        bool mined = interaction.mineTile(registry, playerPos, farTarget, 80.0f);
        REQUIRE(mined == false);
        REQUIRE(physics.isSolid(5, 5) == true);
    }

    SECTION("Placing Block from Inventory Into Empty Tile") {
        Item woodBlock;
        woodBlock.id = "blk_wood_wall";
        woodBlock.name = "Wood Wall";
        woodBlock.category = ItemCategory::Material;
        woodBlock.stackable = true;
        woodBlock.quantity = 5;
        inv.addItem(woodBlock);

        Vec2 emptyTarget{5.5f * 16.0f, 3.5f * 16.0f}; // Tile (5, 3) is air
        REQUIRE(physics.isSolid(5, 3) == false);

        bool placed = interaction.placeBlock(inv, "blk_wood_wall", playerPos, emptyTarget, 80.0f, 3);
        REQUIRE(placed == true);

        REQUIRE(physics.isSolid(5, 3) == true);
        REQUIRE(tilemap.getBlock(5, 3, BlockLayer::Foreground) == 3);
        REQUIRE(inv.getItemCount("blk_wood_wall") == 4); // Deducted 1
    }
}

TEST_CASE("Overworld to Dungeon Level Transitions", "[world][dungeon_transition]") {
    DungeonTransitionManager transitionMgr;

    SECTION("Transitioning Into Dungeon Sets Active Context") {
        REQUIRE(transitionMgr.getCurrentZone() == WorldZone::Overworld);

        transitionMgr.enterDungeon(3); // Enter Tier 3 Dungeon
        REQUIRE(transitionMgr.getCurrentZone() == WorldZone::Dungeon);
        REQUIRE(transitionMgr.getCurrentDungeonTier() == 3);
        REQUIRE(transitionMgr.isBossDefeated() == false);

        // Defeating boss unlocks exit portal
        transitionMgr.setBossDefeated(true);
        REQUIRE(transitionMgr.canExitDungeon() == true);

        transitionMgr.exitDungeon();
        REQUIRE(transitionMgr.getCurrentZone() == WorldZone::Overworld);
    }
}
