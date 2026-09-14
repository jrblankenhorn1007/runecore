#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include "core/Math.hpp"

using Catch::Approx;

TEST_CASE("Vec2 Complete Vector Operations", "[core][math]") {
    Vec2 v0;
    REQUIRE(v0.x == Approx(0.0f));
    REQUIRE(v0.y == Approx(0.0f));

    Vec2 v1{3.0f, 4.0f};
    Vec2 v2{1.0f, 2.0f};

    SECTION("Unary Negation") {
        Vec2 neg = -v1;
        REQUIRE(neg.x == Approx(-3.0f));
        REQUIRE(neg.y == Approx(-4.0f));
    }

    SECTION("Addition, Subtraction, Multiplication, Division") {
        Vec2 sum = v1 + v2;
        REQUIRE(sum.x == Approx(4.0f));
        REQUIRE(sum.y == Approx(6.0f));

        Vec2 diff = v1 - v2;
        REQUIRE(diff.x == Approx(2.0f));
        REQUIRE(diff.y == Approx(2.0f));

        Vec2 mult = v1 * 2.5f;
        REQUIRE(mult.x == Approx(7.5f));
        REQUIRE(mult.y == Approx(10.0f));

        Vec2 div = v1 / 2.0f;
        REQUIRE(div.x == Approx(1.5f));
        REQUIRE(div.y == Approx(2.0f));

        Vec2 mut{5.0f, 6.0f};
        mut += v2;
        REQUIRE(mut.x == Approx(6.0f));
        REQUIRE(mut.y == Approx(8.0f));

        mut -= v2;
        REQUIRE(mut.x == Approx(5.0f));
        REQUIRE(mut.y == Approx(6.0f));

        mut *= 3.0f;
        REQUIRE(mut.x == Approx(15.0f));
        REQUIRE(mut.y == Approx(18.0f));
    }

    SECTION("Dot, Length, and Distance") {
        REQUIRE(v1.dot(v2) == Approx(11.0f));
        REQUIRE(v1.lengthSquared() == Approx(25.0f));
        REQUIRE(v1.length() == Approx(5.0f));
        REQUIRE(v1.distanceTo(v2) == Approx(2.828427f));

        Vec2 norm = v1.normalized();
        REQUIRE(norm.length() == Approx(1.0f));
        REQUIRE(norm.x == Approx(0.6f));
        REQUIRE(norm.y == Approx(0.8f));

        Vec2 zeroV{0.0f, 0.0f};
        REQUIRE(zeroV.normalized().length() == Approx(0.0f));
    }
}

TEST_CASE("Rect Bounds and Containment Operations", "[core][math]") {
    Rect r0;
    REQUIRE(r0.x == Approx(0.0f));
    REQUIRE(r0.width == Approx(0.0f));

    Rect r{10.0f, 20.0f, 30.0f, 40.0f};
    REQUIRE(r.min().x == Approx(10.0f));
    REQUIRE(r.min().y == Approx(20.0f));
    REQUIRE(r.max().x == Approx(40.0f));
    REQUIRE(r.max().y == Approx(60.0f));
    REQUIRE(r.center().x == Approx(25.0f));
    REQUIRE(r.center().y == Approx(40.0f));

    SECTION("Point Containment") {
        REQUIRE(r.contains(Vec2{10.0f, 20.0f}) == true);
        REQUIRE(r.contains(Vec2{25.0f, 35.0f}) == true);
        REQUIRE(r.contains(Vec2{40.0f, 60.0f}) == true);
        REQUIRE(r.contains(Vec2{9.0f, 25.0f}) == false);
        REQUIRE(r.contains(Vec2{41.0f, 25.0f}) == false);
        REQUIRE(r.contains(Vec2{25.0f, 19.0f}) == false);
        REQUIRE(r.contains(Vec2{25.0f, 61.0f}) == false);
    }

    SECTION("Rect Intersections") {
        Rect overlapping{20.0f, 30.0f, 20.0f, 20.0f};
        Rect nonOverlapping{100.0f, 100.0f, 10.0f, 10.0f};
        REQUIRE(r.intersects(overlapping) == true);
        REQUIRE(overlapping.intersects(r) == true);
        REQUIRE(r.intersects(nonOverlapping) == false);
    }
}

TEST_CASE("Color RGBA Construction", "[core][math]") {
    Color def;
    REQUIRE(def.r == 255);
    REQUIRE(def.g == 255);
    REQUIRE(def.b == 255);
    REQUIRE(def.a == 255);

    Color custom{100, 150, 200, 128};
    REQUIRE(custom.r == 100);
    REQUIRE(custom.g == 150);
    REQUIRE(custom.b == 200);
    REQUIRE(custom.a == 128);
}
