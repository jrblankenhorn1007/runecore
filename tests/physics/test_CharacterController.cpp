#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include "physics/CharacterController.hpp"
#include "physics/CollisionWorld.hpp"

using Catch::Approx;

TEST_CASE("CharacterController Jump, Double Jump, Ceiling, and Wall Sliders", "[physics][controller]") {
    CollisionWorld world(16.0f);
    // Floor at Y = 10 (160px)
    for (int x = -10; x <= 20; ++x) {
        world.setTile(x, 10, TileType::Solid);
    }
    // Ceiling at Y = 2 (32px)
    for (int x = 0; x <= 5; ++x) {
        world.setTile(x, 2, TileType::Solid);
    }
    // Wall on left at X = 0 (Y = 4..9)
    for (int y = 4; y <= 9; ++y) {
        world.setTile(0, y, TileType::Solid);
    }
    // Wall on right at X = 6 (Y = 4..9)
    for (int y = 4; y <= 9; ++y) {
        world.setTile(6, y, TileType::Solid);
    }

    CharacterController cc;
    ControllerConfig cfg;
    cfg.moveSpeed = 100.0f;
    cfg.jumpForce = 200.0f;
    cfg.gravity = 500.0f;

    SECTION("Facing Direction Updates on Input") {
        Vec2 pos{50.0f, 150.0f};
        Vec2 vel{0.0f, 0.0f};
        ControllerInput inLeft; inLeft.moveX = -1.0f;
        cc.update(pos, vel, inLeft, world, cfg, 0.016f);
        REQUIRE(cc.getFacing() == -1);

        ControllerInput inRight; inRight.moveX = 1.0f;
        cc.update(pos, vel, inRight, world, cfg, 0.016f);
        REQUIRE(cc.getFacing() == 1);
    }

    SECTION("Ceiling Collision Zeroes Upward Velocity") {
        Vec2 pos{32.0f, 50.0f}; // Directly below ceiling at 32px
        Vec2 vel{0.0f, -200.0f}; // Jumping up
        ControllerInput in;

        cc.update(pos, vel, in, world, cfg, 0.1f);
        REQUIRE(vel.y >= 0.0f); // Stopped by ceiling
    }

    SECTION("Wall Sliding and Wall Jump Left Wall") {
        Vec2 pos{9.0f, 100.0f}; // Against left wall (X = 0..16)
        Vec2 vel{0.0f, 100.0f}; // Falling down
        ControllerInput inLeft;
        inLeft.moveX = -1.0f;

        cc.update(pos, vel, inLeft, world, cfg, 0.016f);
        REQUIRE(cc.isWallSliding() == true);

        // Wall jump kicks away to the right (+X)
        inLeft.jumpPressed = true;
        cc.update(pos, vel, inLeft, world, cfg, 0.016f);
        REQUIRE(vel.x > 0.0f);
        REQUIRE(vel.y < 0.0f);
    }

    SECTION("Wall Sliding and Wall Jump Right Wall") {
        world.setTile(10, 5, TileType::Solid);
        world.setTile(10, 6, TileType::Solid);
        world.setTile(10, 7, TileType::Solid);

        Vec2 pos{151.0f, 100.0f}; // Against right wall at X=160 (pos.x + 8 = 159)
        Vec2 vel{0.0f, 100.0f};   // Falling down
        ControllerInput inRight;
        inRight.moveX = 1.0f; // Pushing right against wall

        cc.update(pos, vel, inRight, world, cfg, 0.016f);
        REQUIRE(cc.isWallSliding() == true);

        // Wall jump kicks away to the left (-X)
        inRight.jumpPressed = true;
        cc.update(pos, vel, inRight, world, cfg, 0.016f);
        REQUIRE(vel.x < 0.0f);
        REQUIRE(vel.y < 0.0f);
    }
}
