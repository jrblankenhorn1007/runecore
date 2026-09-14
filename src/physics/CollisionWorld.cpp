#include "physics/CollisionWorld.hpp"
#include <cmath>
#include <algorithm>

CollisionWorld::CollisionWorld(float tileSize) : m_tileSize(tileSize) {}

void CollisionWorld::setTile(int x, int y, TileType type) {
    int64_t key = hashCoords(x, y);
    if (type == TileType::Empty) {
        m_tiles.erase(key);
    } else {
        m_tiles[key] = type;
    }
}

TileType CollisionWorld::getTile(int x, int y) const {
    auto it = m_tiles.find(hashCoords(x, y));
    if (it != m_tiles.end()) {
        return it->second;
    }
    return TileType::Empty;
}

bool CollisionWorld::isSolid(int x, int y) const {
    TileType t = getTile(x, y);
    return t == TileType::Solid;
}

bool CollisionWorld::raycast(const Vec2& origin, const Vec2& direction, float maxDist, RaycastHit& outHit) const {
    Vec2 dir = direction.normalized();
    if (dir.lengthSquared() < 0.001f) return false;

    // Fast DDA grid traversal
    float step = 1.0f; // pixel step
    float traveled = 0.0f;

    while (traveled < maxDist) {
        Vec2 curr = origin + dir * traveled;
        int tx = static_cast<int>(std::floor(curr.x / m_tileSize));
        int ty = static_cast<int>(std::floor(curr.y / m_tileSize));

        if (isSolid(tx, ty)) {
            outHit.point = curr;
            outHit.distance = traveled;
            outHit.tileX = tx;
            outHit.tileY = ty;
            outHit.tileType = getTile(tx, ty);
            outHit.normal = -dir;
            return true;
        }
        traveled += step;
    }

    return false;
}

SweepResult CollisionWorld::sweepBox(const Vec2& startPos, const Rect& localBox, const Vec2& moveDelta) const {
    SweepResult result;
    result.adjustedMove = moveDelta;

    Vec2 currentPos = startPos;
    Rect targetBox{
        currentPos.x + localBox.x + moveDelta.x,
        currentPos.y + localBox.y + moveDelta.y,
        localBox.width,
        localBox.height
    };

    // Calculate tile search bounding box
    float minX = std::min(startPos.x + localBox.x, targetBox.x);
    float maxX = std::max(startPos.x + localBox.x + localBox.width, targetBox.x + targetBox.width);
    float minY = std::min(startPos.y + localBox.y, targetBox.y);
    float maxY = std::max(startPos.y + localBox.y + localBox.height, targetBox.y + targetBox.height);

    int startTileX = static_cast<int>(std::floor(minX / m_tileSize)) - 1;
    int endTileX = static_cast<int>(std::floor(maxX / m_tileSize)) + 1;
    int startTileY = static_cast<int>(std::floor(minY / m_tileSize)) - 1;
    int endTileY = static_cast<int>(std::floor(maxY / m_tileSize)) + 1;

    // First sweep horizontal (inset vertically by skin to avoid catching on floor)
    Vec2 hMove{moveDelta.x, 0.0f};
    Rect hBox{
        currentPos.x + localBox.x + hMove.x,
        currentPos.y + localBox.y + 0.1f,
        localBox.width,
        localBox.height - 0.2f
    };

    for (int ty = startTileY; ty <= endTileY; ++ty) {
        for (int tx = startTileX; tx <= endTileX; ++tx) {
            if (isSolid(tx, ty)) {
                Rect tileRect{tx * m_tileSize, ty * m_tileSize, m_tileSize, m_tileSize};
                if (hBox.intersects(tileRect)) {
                    result.hit = true;
                    if (hMove.x > 0.0f) {
                        float allowed = tileRect.x - (startPos.x + localBox.x + localBox.width) - 0.01f;
                        result.adjustedMove.x = std::min(result.adjustedMove.x, allowed);
                        result.contactNormal.x = -1.0f;
                    } else if (hMove.x < 0.0f) {
                        float allowed = (tileRect.x + tileRect.width) - (startPos.x + localBox.x) + 0.01f;
                        result.adjustedMove.x = std::max(result.adjustedMove.x, allowed);
                        result.contactNormal.x = 1.0f;
                    }
                }
            }
        }
    }

    // Then sweep vertical (inset horizontally by skin to avoid catching on walls)
    currentPos.x += result.adjustedMove.x;
    Vec2 vMove{0.0f, moveDelta.y};
    Rect vBox{
        currentPos.x + localBox.x + 0.1f,
        currentPos.y + localBox.y + vMove.y,
        localBox.width - 0.2f,
        localBox.height
    };

    for (int ty = startTileY; ty <= endTileY; ++ty) {
        for (int tx = startTileX; tx <= endTileX; ++tx) {
            if (isSolid(tx, ty)) {
                Rect tileRect{tx * m_tileSize, ty * m_tileSize, m_tileSize, m_tileSize};
                if (vBox.intersects(tileRect)) {
                    result.hit = true;
                    if (vMove.y > 0.0f) {
                        float allowed = tileRect.y - (startPos.y + localBox.y + localBox.height) - 0.01f;
                        result.adjustedMove.y = std::min(result.adjustedMove.y, allowed);
                        result.contactNormal.y = -1.0f;
                    } else if (vMove.y < 0.0f) {
                        float allowed = (tileRect.y + tileRect.height) - (startPos.y + localBox.y) + 0.01f;
                        result.adjustedMove.y = std::max(result.adjustedMove.y, allowed);
                        result.contactNormal.y = 1.0f;
                    }
                }
            }
        }
    }

    return result;
}
