#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include "physics/CollisionWorld.hpp"

using Catch::Approx;

TEST_CASE("CollisionWorld Grid Storage, Raycasting, and AABB Sweeps", "[physics][world]") {
    CollisionWorld cw(16.0f);
    REQUIRE(cw.getTileSize() == Approx(16.0f));

    SECTION("Tile Setting and Clear") {
        cw.setTile(5, 5, TileType::Solid);
        REQUIRE(cw.isSolid(5, 5) == true);
        REQUIRE(cw.getTile(5, 5) == TileType::Solid);

        cw.setTile(5, 5, TileType::Empty);
        REQUIRE(cw.isSolid(5, 5) == false);
        REQUIRE(cw.getTile(5, 5) == TileType::Empty);
        REQUIRE(cw.getTile(99, 99) == TileType::Empty);
    }

    SECTION("Raycast Traversal and Miss") {
        cw.setTile(10, 5, TileType::Solid); // X = 160px
        RaycastHit hit;

        // Hit
        bool didHit = cw.raycast(Vec2{0.0f, 80.0f}, Vec2{1.0f, 0.0f}, 300.0f, hit);
        REQUIRE(didHit == true);
        REQUIRE(hit.tileX == 10);
        REQUIRE(hit.tileY == 5);

        // Miss (opposite direction)
        bool didMiss = cw.raycast(Vec2{0.0f, 80.0f}, Vec2{-1.0f, 0.0f}, 100.0f, hit);
        REQUIRE(didMiss == false);

        // Zero direction
        REQUIRE(cw.raycast(Vec2{0.0f, 0.0f}, Vec2{0.0f, 0.0f}, 100.0f, hit) == false);
    }

    SECTION("AABB Sweeps Against Left and Right Walls") {
        // Wall to the left at X = 0 (tx = 0)
        cw.setTile(0, 5, TileType::Solid);
        // Wall to the right at X = 80 (tx = 5)
        cw.setTile(5, 5, TileType::Solid);

        Rect box{-8.0f, -8.0f, 16.0f, 16.0f};
        Vec2 startPos{40.0f, 5.5f * 16.0f};

        // Sweep left
        SweepResult leftSweep = cw.sweepBox(startPos, box, Vec2{-40.0f, 0.0f});
        REQUIRE(leftSweep.hit == true);
        REQUIRE(leftSweep.contactNormal.x == Approx(1.0f));

        // Sweep right
        SweepResult rightSweep = cw.sweepBox(startPos, box, Vec2{50.0f, 0.0f});
        REQUIRE(rightSweep.hit == true);
        REQUIRE(rightSweep.contactNormal.x == Approx(-1.0f));
    }
}
