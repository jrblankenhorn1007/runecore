#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include "core/EngineContext.hpp"
#include "core/GameSimulation.hpp"
#include "render/Camera.hpp"

using Catch::Approx;

TEST_CASE("Virtual Canvas Integer Upscaling and Camera Snapping Math", "[render][camera]") {
    Camera camera;

    SECTION("360px Base Virtual Canvas Aspect Ratio Calculations") {
        // 16:9 1080p Window: 1920x1080
        CanvasMetrics m1080 = Camera::calculateCanvasMetrics(1920, 1080);
        REQUIRE(m1080.virtualHeight == 360);
        REQUIRE(m1080.virtualWidth == 640);
        REQUIRE(m1080.integerScale == 3); // 1080 / 360 = 3
        REQUIRE(m1080.viewportWidth == 1920);
        REQUIRE(m1080.viewportHeight == 1080);
        REQUIRE(m1080.letterboxX == 0);
        REQUIRE(m1080.letterboxY == 0);

        // 16:10 MacBook 2560x1600 Display
        CanvasMetrics mMacBook = Camera::calculateCanvasMetrics(2560, 1600);
        REQUIRE(mMacBook.virtualHeight == 360);
        REQUIRE(mMacBook.virtualWidth == 576); // 360 * (16/10) = 576
        REQUIRE(mMacBook.integerScale == 4); // 1600 / 360 = 4 (scaled height = 1440)
        REQUIRE(mMacBook.letterboxY == 80); // (1600 - 1440) / 2 = 80px pillarbox
    }

    SECTION("Pixel Snapped Camera Tracking and Deadzone") {
        camera.setPosition(Vec2{100.4f, 200.7f});
        Vec2 snapped = camera.getSnappedPosition();
        REQUIRE(snapped.x == Approx(100.0f));
        REQUIRE(snapped.y == Approx(201.0f));
    }

    SECTION("Screen Shake Attenuation over Time") {
        camera.addShake(10.0f, 0.5f); // 10px trauma, 0.5s duration
        REQUIRE(camera.isShaking() == true);

        camera.update(0.6f);
        REQUIRE(camera.isShaking() == false);
    }
}

TEST_CASE("Integrated Engine Context and Game Simulation 600-Tick Run", "[core][simulation]") {
    GameSimulation sim;
    sim.initialize(ClassType::Juggernaut);

    SECTION("Initial World and Player Setup") {
        REQUIRE(sim.getPlayerLevel() == 1);
        REQUIRE(sim.getPlayerHealth() > 0.0f);
        REQUIRE(sim.getPlayerPosition().x == Approx(100.0f));
        REQUIRE(sim.getEnemyCount() > 0);
    }

    SECTION("Stepping 600 Ticks (10 Seconds of Simulation)") {
        // Run 600 ticks of simulation (10.0 seconds at 60 Hz)
        ControllerInput input;
        input.moveX = 1.0f; // Move player towards enemies on right

        for (int i = 0; i < 600; ++i) {
            sim.step(input, 1.0f / 60.0f);
        }

        REQUIRE(sim.getTickCount() == 600);
        REQUIRE(sim.getSimulationTime() == Approx(10.0f));
        // Player should have advanced horizontally across the ground
        REQUIRE(sim.getPlayerPosition().x > 100.0f);
        // Player metabolism should have processed normally
        REQUIRE(sim.getPlayerHunger() < 100.0f);
    }

    SECTION("Player Attacks and Defeats Enemy Awarding XP") {
        REQUIRE(sim.getPlayerLevel() == 1);
        REQUIRE(sim.getPlayerXP() == 0);

        // Spawn a target dummy enemy directly in front of the player
        Vec2 dummyPos = sim.getPlayerPosition() + Vec2{15.0f, 0.0f};
        sim.spawnEnemy(dummyPos, 10.0f, 150); // 10 HP, 150 XP

        // Player attacks with Primary Strike
        sim.playerAttack();

        // Enemy should be damaged or defeated, awarding XP (100 XP levels up to Level 2, leaving 50 XP)
        sim.step(ControllerInput{}, 1.0f / 60.0f);

        REQUIRE(sim.getPlayerLevel() == 2);
        REQUIRE(sim.getPlayerXP() == 50);
    }
}
