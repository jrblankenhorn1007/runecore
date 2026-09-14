#include "procgen/Tilemap.hpp"
#include <cmath>

Tilemap::Tilemap(float tileSize) : m_tileSize(tileSize) {}

void Tilemap::setBlock(int worldX, int worldY, BlockLayer layer, uint16_t blockId) {
    int cx = static_cast<int>(std::floor(static_cast<float>(worldX) / CHUNK_SIZE));
    int cy = static_cast<int>(std::floor(static_cast<float>(worldY) / CHUNK_SIZE));

    int lx = worldX % CHUNK_SIZE;
    if (lx < 0) lx += CHUNK_SIZE;
    int ly = worldY % CHUNK_SIZE;
    if (ly < 0) ly += CHUNK_SIZE;

    int64_t key = hashChunk(cx, cy);
    auto& chunk = m_chunks[key];

    if (layer == BlockLayer::Foreground) {
        chunk.foreground[ly][lx] = blockId;
    } else {
        chunk.background[ly][lx] = blockId;
    }
}

uint16_t Tilemap::getBlock(int worldX, int worldY, BlockLayer layer) const {
    int cx = static_cast<int>(std::floor(static_cast<float>(worldX) / CHUNK_SIZE));
    int cy = static_cast<int>(std::floor(static_cast<float>(worldY) / CHUNK_SIZE));

    int lx = worldX % CHUNK_SIZE;
    if (lx < 0) lx += CHUNK_SIZE;
    int ly = worldY % CHUNK_SIZE;
    if (ly < 0) ly += CHUNK_SIZE;

    int64_t key = hashChunk(cx, cy);
    auto it = m_chunks.find(key);
    if (it != m_chunks.end()) {
        if (layer == BlockLayer::Foreground) {
            return it->second.foreground[ly][lx];
        } else {
            return it->second.background[ly][lx];
        }
    }
    return 0; // Empty air
}

uint8_t Tilemap::getAutotileMask(int x, int y, BlockLayer layer) const {
    uint16_t center = getBlock(x, y, layer);
    if (center == 0) return 0;
    uint8_t mask = 0;
    if (getBlock(x, y - 1, layer) == center) mask |= 1;
    if (getBlock(x + 1, y, layer) == center) mask |= 2;
    if (getBlock(x, y + 1, layer) == center) mask |= 4;
    if (getBlock(x - 1, y, layer) == center) mask |= 8;
    return mask;
}

void Tilemap::setSlope(int x, int y, bool risingRight) {
    m_slopes[hashChunk(x, y)] = risingRight;
}

bool Tilemap::isSlope(int x, int y) const {
    return m_slopes.find(hashChunk(x, y)) != m_slopes.end();
}

bool Tilemap::slopeRisesRight(int x, int y) const {
    auto it = m_slopes.find(hashChunk(x, y));
    return it != m_slopes.end() && it->second;
}
