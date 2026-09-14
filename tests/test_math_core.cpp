#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include "core/Math.hpp"
#include "core/Random.hpp"
#include "core/Time.hpp"
#include "core/EventBus.hpp"

using Catch::Approx;

TEST_CASE("Vec2 Basic Operations", "[core][math]") {
    Vec2 v1{3.0f, 4.0f};
    Vec2 v2{1.0f, 2.0f};

    SECTION("Addition and Subtraction") {
        Vec2 sum = v1 + v2;
        REQUIRE(sum.x == Approx(4.0f));
        REQUIRE(sum.y == Approx(6.0f));

        Vec2 diff = v1 - v2;
        REQUIRE(diff.x == Approx(2.0f));
        REQUIRE(diff.y == Approx(2.0f));
    }

    SECTION("Scalar Multiplication and Division") {
        Vec2 scaled = v1 * 2.0f;
        REQUIRE(scaled.x == Approx(6.0f));
        REQUIRE(scaled.y == Approx(8.0f));

        Vec2 divided = v1 / 2.0f;
        REQUIRE(divided.x == Approx(1.5f));
        REQUIRE(divided.y == Approx(2.0f));
    }

    SECTION("Length and Normalization") {
        REQUIRE(v1.lengthSquared() == Approx(25.0f));
        REQUIRE(v1.length() == Approx(5.0f));

        Vec2 norm = v1.normalized();
        REQUIRE(norm.length() == Approx(1.0f));
        REQUIRE(norm.x == Approx(0.6f));
        REQUIRE(norm.y == Approx(0.8f));

        Vec2 zero{0.0f, 0.0f};
        REQUIRE(zero.normalized().length() == Approx(0.0f));
    }

    SECTION("Dot Product and Distance") {
        float dot = v1.dot(v2); // 3*1 + 4*2 = 11
        REQUIRE(dot == Approx(11.0f));

        float dist = v1.distanceTo(v2); // sqrt((3-1)^2 + (4-2)^2) = sqrt(4 + 4) = sqrt(8)
        REQUIRE(dist == Approx(2.828427f));
    }
}

TEST_CASE("Rect Operations and Intersections", "[core][math]") {
    Rect r1{0.0f, 0.0f, 10.0f, 10.0f};
    Rect r2{5.0f, 5.0f, 10.0f, 10.0f};
    Rect r3{20.0f, 20.0f, 5.0f, 5.0f};

    SECTION("Contains Point") {
        REQUIRE(r1.contains({5.0f, 5.0f}) == true);
        REQUIRE(r1.contains({10.0f, 10.0f}) == true);
        REQUIRE(r1.contains({-1.0f, 5.0f}) == false);
        REQUIRE(r1.contains({11.0f, 5.0f}) == false);
    }

    SECTION("Intersects Other Rect") {
        REQUIRE(r1.intersects(r2) == true);
        REQUIRE(r2.intersects(r1) == true);
        REQUIRE(r1.intersects(r3) == false);
    }

    SECTION("Min and Max Bounds") {
        REQUIRE(r1.min().x == Approx(0.0f));
        REQUIRE(r1.min().y == Approx(0.0f));
        REQUIRE(r1.max().x == Approx(10.0f));
        REQUIRE(r1.max().y == Approx(10.0f));
    }
}

TEST_CASE("Random Number Generator and Gaussian Distribution", "[core][random]") {
    Random rng(1337);

    SECTION("Uniform Range") {
        for (int i = 0; i < 50; ++i) {
            int val = rng.rangeInt(5, 15);
            REQUIRE(val >= 5);
            REQUIRE(val <= 15);
        }

        for (int i = 0; i < 50; ++i) {
            float f = rng.rangeFloat(1.0f, 2.0f);
            REQUIRE(f >= 1.0f);
            REQUIRE(f <= 2.0f);
        }
    }

    SECTION("Gaussian Stat Roll Clamping") {
        float mean = 50.0f;
        float stddev = 10.0f;
        float minVal = 30.0f;
        float maxVal = 70.0f;

        float sum = 0.0f;
        const int samples = 500;
        for (int i = 0; i < samples; ++i) {
            float roll = rng.gaussian(mean, stddev, minVal, maxVal);
            REQUIRE(roll >= minVal);
            REQUIRE(roll <= maxVal);
            sum += roll;
        }

        float sampleMean = sum / samples;
        REQUIRE(sampleMean > 45.0f);
        REQUIRE(sampleMean < 55.0f);
    }
}

TEST_CASE("Fixed Timestep Accumulator", "[core][time]") {
    TimeStep timer(60.0f); // 60 Hz -> dt = 0.0166667s

    SECTION("Initial State") {
        REQUIRE(timer.getFixedDelta() == Approx(1.0f / 60.0f));
        REQUIRE(timer.getTicks() == 0);
    }

    SECTION("Accumulator Stepping") {
        // Advance time by 0.035s (slightly more than 2 frames: 2 * 0.0166667 = 0.0333333)
        int ticks = timer.update(0.035f);
        REQUIRE(ticks == 2);
        REQUIRE(timer.getTicks() == 2);
        REQUIRE(timer.getAlpha() >= 0.0f);
        REQUIRE(timer.getAlpha() <= 1.0f);
    }

    SECTION("Spiral of Death Prevention") {
        // Massive lag spike (1.0s) should be clamped to max accumulator limit (e.g. 0.2s or 5-10 frames)
        int ticks = timer.update(1.0f);
        REQUIRE(ticks <= 10);
    }
}

struct TestDamageEvent {
    int targetId;
    float damage;
};

TEST_CASE("EventBus Publish and Subscribe", "[core][eventbus]") {
    EventBus bus;
    int receivedTarget = -1;
    float receivedDmg = 0.0f;
    int callCount = 0;

    auto subId = bus.subscribe<TestDamageEvent>([&](const TestDamageEvent& ev) {
        receivedTarget = ev.targetId;
        receivedDmg = ev.damage;
        callCount++;
    });

    SECTION("Dispatches to Subscriber") {
        bus.publish(TestDamageEvent{42, 85.5f});
        REQUIRE(callCount == 1);
        REQUIRE(receivedTarget == 42);
        REQUIRE(receivedDmg == Approx(85.5f));
    }

    SECTION("Unsubscribe Stops Delivery") {
        bus.unsubscribe<TestDamageEvent>(subId);
        bus.publish(TestDamageEvent{99, 100.0f});
        REQUIRE(callCount == 0);
    }
}
