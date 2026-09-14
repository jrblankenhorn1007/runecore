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
