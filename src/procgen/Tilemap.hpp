#pragma once
#include <unordered_map>
#include <vector>
#include <cstdint>
#include "core/Math.hpp"

enum class BlockLayer {
    Foreground,
    Background
};

constexpr int CHUNK_SIZE = 32;

struct Chunk {
    uint16_t foreground[CHUNK_SIZE][CHUNK_SIZE]{{0}};
    uint16_t background[CHUNK_SIZE][CHUNK_SIZE]{{0}};
};

class Tilemap {
public:
    explicit Tilemap(float tileSize = 16.0f);

    float getTileSize() const { return m_tileSize; }

    void setBlock(int worldX, int worldY, BlockLayer layer, uint16_t blockId);
    uint16_t getBlock(int worldX, int worldY, BlockLayer layer) const;
    uint8_t getAutotileMask(int worldX, int worldY, BlockLayer layer) const;
    void setSlope(int worldX, int worldY, bool risingRight);
    bool isSlope(int worldX, int worldY) const;
    bool slopeRisesRight(int worldX, int worldY) const;

private:
    static int64_t hashChunk(int cx, int cy) {
        return (static_cast<int64_t>(cx) << 32) | (static_cast<int64_t>(cy) & 0xFFFFFFFF);
    }

    float m_tileSize{16.0f};
    mutable std::unordered_map<int64_t, Chunk> m_chunks;
    std::unordered_map<int64_t, bool> m_slopes;
};
