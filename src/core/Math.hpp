#pragma once
#include <cmath>
#include <algorithm>

struct Vec2 {
    float x{0.0f};
    float y{0.0f};

    constexpr Vec2() = default;
    constexpr Vec2(float inX, float inY) : x(inX), y(inY) {}

    constexpr Vec2 operator-() const { return {-x, -y}; }
    constexpr Vec2 operator+(const Vec2& other) const { return {x + other.x, y + other.y}; }
    constexpr Vec2 operator-(const Vec2& other) const { return {x - other.x, y - other.y}; }
    constexpr Vec2 operator*(float scalar) const { return {x * scalar, y * scalar}; }
    constexpr Vec2 operator/(float scalar) const { return {x / scalar, y / scalar}; }

    Vec2& operator+=(const Vec2& other) { x += other.x; y += other.y; return *this; }
    Vec2& operator-=(const Vec2& other) { x -= other.x; y -= other.y; return *this; }
    Vec2& operator*=(float scalar) { x *= scalar; y *= scalar; return *this; }

    constexpr float dot(const Vec2& other) const { return x * other.x + y * other.y; }
    constexpr float lengthSquared() const { return x * x + y * y; }
    float length() const { return std::sqrt(lengthSquared()); }

    Vec2 normalized() const {
        float len = length();
        if (len > 0.00001f) {
            return {x / len, y / len};
        }
        return {0.0f, 0.0f};
    }

    float distanceTo(const Vec2& other) const {
        return (*this - other).length();
    }
};

struct Rect {
    float x{0.0f};
    float y{0.0f};
    float width{0.0f};
    float height{0.0f};

    constexpr Rect() = default;
    constexpr Rect(float inX, float inY, float inW, float inH)
        : x(inX), y(inY), width(inW), height(inH) {}

    constexpr Vec2 min() const { return {x, y}; }
    constexpr Vec2 max() const { return {x + width, y + height}; }
    constexpr Vec2 center() const { return {x + width * 0.5f, y + height * 0.5f}; }

    constexpr bool contains(const Vec2& p) const {
        return p.x >= x && p.x <= (x + width) && p.y >= y && p.y <= (y + height);
    }

    constexpr bool intersects(const Rect& other) const {
        return !(other.x >= x + width ||
                 other.x + other.width <= x ||
                 other.y >= y + height ||
                 other.y + other.height <= y);
    }
};

struct Color {
    unsigned char r{255};
    unsigned char g{255};
    unsigned char b{255};
    unsigned char a{255};

    constexpr Color() = default;
    constexpr Color(unsigned char inR, unsigned char inG, unsigned char inB, unsigned char inA = 255)
        : r(inR), g(inG), b(inB), a(inA) {}
};
