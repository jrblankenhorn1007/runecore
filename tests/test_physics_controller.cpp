#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include "physics/CollisionLayers.hpp"
#include "physics/CollisionWorld.hpp"
#include "physics/CharacterController.hpp"

using Catch::Approx;

TEST_CASE("Collision Filtering Matrix and Layer Masks", "[physics][layers]") {
    SECTION("Player Collides with Terrain and Enemy Projectiles") {
        uint16_t playerCategory = CollisionLayer::Player;
        uint16_t playerMask = CollisionLayer::PlayerMask;

        REQUIRE(playerCategory == 0x0002);
        REQUIRE((playerMask & CollisionLayer::Terrain) != 0);
        REQUIRE((playerMask & CollisionLayer::EnemyProjectile) != 0);
        REQUIRE((playerMask & CollisionLayer::DroppedItem) != 0);
        REQUIRE((playerMask & CollisionLayer::PlayerProjectile) == 0); // No friendly fire
    }

    SECTION("Projectiles Collide with Opposing Factions and Terrain") {
        uint16_t projMask = CollisionLayer::PlayerProjectileMask;
        REQUIRE((projMask & CollisionLayer::Enemy) != 0);
        REQUIRE((projMask & CollisionLayer::Terrain) != 0);
        REQUIRE((projMask & CollisionLayer::Player) == 0);
    }
}

TEST_CASE("2D Tilemap Collision Sweeps and Solid Obstacles", "[physics][sweeps]") {
    CollisionWorld world(16.0f); // 16x16 pixel tiles

    // Create a horizontal floor at Y = 2 (Y-down coordinates: rows 0, 1 empty, row 2 is solid)
    // Floor spans X = 0 to 10
    for (int x = 0; x <= 10; ++x) {
        world.setTile(x, 2, TileType::Solid);
    }
    // Vertical wall at X = 5, Y = 0 to 1
    world.setTile(5, 0, TileType::Solid);
    world.setTile(5, 1, TileType::Solid);

    SECTION("Raycast Downwards Hits Solid Floor") {
        RaycastHit hit;
        bool didHit = world.raycast(Vec2{16.0f, 0.0f}, Vec2{0.0f, 1.0f}, 64.0f, hit);
        REQUIRE(didHit == true);
        REQUIRE(hit.tileX == 1);
        REQUIRE(hit.tileY == 2);
        REQUIRE(hit.point.y == Approx(32.0f)); // Y = 2 * 16
    }

    SECTION("AABB Box Sweep Against Solid Floor") {
        Rect playerBox{-8.0f, -16.0f, 16.0f, 16.0f}; // 16x16 player
        Vec2 startPos{16.0f, 8.0f};
        Vec2 moveDelta{0.0f, 30.0f}; // Moving down towards floor at Y=32

        SweepResult result = world.sweepBox(startPos, playerBox, moveDelta);
        REQUIRE(result.hit == true);
        REQUIRE(result.adjustedMove.y < 30.0f); // Movement stopped before penetrating floor
        REQUIRE(result.contactNormal.y == Approx(-1.0f)); // Pushed upward
    }

    SECTION("AABB Box Sweep Against Vertical Wall") {
        Rect playerBox{-8.0f, -16.0f, 16.0f, 16.0f};
        Vec2 startPos{40.0f, 8.0f}; // X=40, Wall is at X=5*16 = 80
        Vec2 moveDelta{60.0f, 0.0f}; // Moving right past wall

        SweepResult result = world.sweepBox(startPos, playerBox, moveDelta);
        REQUIRE(result.hit == true);
        REQUIRE(result.adjustedMove.x < 60.0f);
        REQUIRE(result.contactNormal.x == Approx(-1.0f));
    }
}

TEST_CASE("Character Controller Platformer Dynamics", "[physics][controller]") {
    CollisionWorld world(16.0f);
    // Create ground floor at Y = 10 (Y=160px)
    for (int x = -10; x <= 20; ++x) {
        world.setTile(x, 10, TileType::Solid);
    }
    // Create wall at X = 8, Y = 6 to 9 (Wall jump obstacle)
    for (int y = 6; y <= 9; ++y) {
        world.setTile(8, y, TileType::Solid);
    }

    CharacterController controller;
    ControllerConfig config;
    config.moveSpeed = 120.0f;
    config.jumpForce = 250.0f;
    config.gravity = 600.0f;

    SECTION("Gravity Pulls Character to Ground") {
        Vec2 pos{32.0f, 60.0f}; // In the air
        Vec2 vel{0.0f, 0.0f};
        ControllerInput input;

        // Step simulation for 1.0s (60 ticks of dt=1/60)
        for (int i = 0; i < 60; ++i) {
            controller.update(pos, vel, input, world, config, 1.0f / 60.0f);
        }

        REQUIRE(controller.isGrounded() == true);
        REQUIRE(vel.y == Approx(0.0f)); // Vertical velocity zeroed on landing
        // Y position should be sitting on top of the floor at Y = 160
        REQUIRE(pos.y == Approx(160.0f).margin(0.1f));
    }

    SECTION("Horizontal Movement on Ground") {
        Vec2 pos{32.0f, 160.0f};
        Vec2 vel{0.0f, 0.0f};
        ControllerInput input;
        input.moveX = 1.0f; // Moving right

        for (int i = 0; i < 10; ++i) {
            controller.update(pos, vel, input, world, config, 1.0f / 60.0f);
        }

        REQUIRE(pos.x > 32.0f);
        REQUIRE(vel.x > 50.0f);
        REQUIRE(controller.isGrounded() == true);
    }

    SECTION("Jump and Double Jump") {
        Vec2 pos{32.0f, 160.0f};
        Vec2 vel{0.0f, 0.0f};
        ControllerInput input;

        // Jump 1
        input.jumpPressed = true;
        controller.update(pos, vel, input, world, config, 1.0f / 60.0f);

        REQUIRE(controller.isGrounded() == false);
        REQUIRE(vel.y < -100.0f); // Upwards velocity (negative Y)

        // Mid-air double jump
        input.jumpPressed = false;
        controller.update(pos, vel, input, world, config, 1.0f / 60.0f);

        input.jumpPressed = true; // Double jump
        controller.update(pos, vel, input, world, config, 1.0f / 60.0f);
        REQUIRE(vel.y < -150.0f);
        REQUIRE(controller.canDoubleJump() == false); // Already spent
    }

    SECTION("Wall Slide and Wall Jump") {
        Vec2 pos{119.0f, 110.0f}; // Right next to wall at X = 8*16 = 128 (right edge = 119 + 8 = 127)
        Vec2 vel{0.0f, 100.0f};  // Falling downwards
        ControllerInput input;
        input.moveX = 1.0f; // Pressing against wall

        controller.update(pos, vel, input, world, config, 1.0f / 60.0f);

        REQUIRE(controller.isWallSliding() == true);
        REQUIRE(vel.y < 80.0f); // Wall friction slows fall speed

        // Wall jump kicks away from wall (towards left)
        input.jumpPressed = true;
        controller.update(pos, vel, input, world, config, 1.0f / 60.0f);

        REQUIRE(controller.isWallSliding() == false);
        REQUIRE(vel.x < 0.0f); // Kicked left away from wall
        REQUIRE(vel.y < 0.0f); // Kicked upward
    }
}
