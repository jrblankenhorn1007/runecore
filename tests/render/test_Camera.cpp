#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include "render/Camera.hpp"

using Catch::Approx;

TEST_CASE("Camera Canvas Scaling Math, Snapping, and Shake", "[render][camera]") {
    Camera cam;

    SECTION("Canvas Metrics Calculations") {
        CanvasMetrics m1080 = Camera::calculateCanvasMetrics(1920, 1080);
        REQUIRE(m1080.virtualHeight == 360);
        REQUIRE(m1080.virtualWidth == 640);
        REQUIRE(m1080.integerScale == 3);

        CanvasMetrics m720 = Camera::calculateCanvasMetrics(1280, 720);
        REQUIRE(m720.virtualHeight == 360);
        REQUIRE(m720.virtualWidth == 640);
        REQUIRE(m720.integerScale == 2);

        CanvasMetrics native = Camera::calculateCanvasMetrics(1280, 720);
        REQUIRE(native.windowWidth == 1280);
        REQUIRE(native.windowHeight == 720);
        REQUIRE(native.viewportWidth == 1280);
        REQUIRE(native.viewportHeight == 720);
        REQUIRE(native.letterboxX == 0);
        REQUIRE(native.letterboxY == 0);
    }

    SECTION("Position Snapping") {
        cam.setPosition(Vec2{50.4f, 80.6f});
        REQUIRE(cam.getPosition().x == Approx(50.4f));
        REQUIRE(cam.getSnappedPosition().x == Approx(50.0f));
        REQUIRE(cam.getSnappedPosition().y == Approx(81.0f));
    }

    SECTION("Camera Shake Attenuation") {
        cam.addShake(8.0f, 0.4f);
        REQUIRE(cam.isShaking() == true);
        REQUIRE(cam.getShakeTrauma() == Approx(8.0f));

        cam.update(0.5f);
        REQUIRE(cam.isShaking() == false);
        REQUIRE(cam.getShakeTrauma() == Approx(0.0f));
    }
}
