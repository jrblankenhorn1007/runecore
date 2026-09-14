#pragma once
#include "core/Math.hpp"
#include <unordered_map>
#include <cstdint>

enum class TileType : uint8_t {
    Empty = 0,
    Solid = 1,
    OneWayPlatform = 2,
    SlopeLeft = 3,
    SlopeRight = 4,
    HazardSpike = 5,
    HazardLava = 6
};

struct RaycastHit {
    Vec2 point{0.0f, 0.0f};
    Vec2 normal{0.0f, 0.0f};
    float distance{0.0f};
    int tileX{0};
    int tileY{0};
    TileType tileType{TileType::Empty};
};

struct SweepResult {
    bool hit{false};
    Vec2 adjustedMove{0.0f, 0.0f};
    Vec2 contactNormal{0.0f, 0.0f};
    float hitDistance{0.0f};
};

class CollisionWorld {
public:
    explicit CollisionWorld(float tileSize = 16.0f);

    float getTileSize() const { return m_tileSize; }

    void setTile(int x, int y, TileType type);
    TileType getTile(int x, int y) const;
    bool isSolid(int x, int y) const;

    bool raycast(const Vec2& origin, const Vec2& direction, float maxDist, RaycastHit& outHit) const;
    SweepResult sweepBox(const Vec2& startPos, const Rect& localBox, const Vec2& moveDelta) const;

private:
    static int64_t hashCoords(int x, int y) {
        return (static_cast<int64_t>(x) << 32) | (static_cast<int64_t>(y) & 0xFFFFFFFF);
    }

    float m_tileSize{16.0f};
    std::unordered_map<int64_t, TileType> m_tiles;
};
