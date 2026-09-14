#pragma once
#include <unordered_map>
#include <cstdint>

enum class BlockType : uint8_t {
    Air = 0,
    Dirt = 1,
    Stone = 2,
    WoodWall = 3,
    StoneWall = 4,
    OneWayPlatform = 5,
    WoodenDoor = 6,
    StorageChest = 7
};

class BuildingSystem {
public:
    explicit BuildingSystem(float blockSize = 16.0f);

    bool placeBlock(int x, int y, BlockType type);
    bool breakBlock(int x, int y);
    BlockType getBlock(int x, int y) const;

    bool isDoorOpen(int x, int y) const;
    void toggleDoor(int x, int y);

    float getBlockSize() const { return m_blockSize; }

private:
    static int64_t hashCoords(int x, int y) {
        return (static_cast<int64_t>(x) << 32) | (static_cast<int64_t>(y) & 0xFFFFFFFF);
    }

    float m_blockSize{16.0f};
    std::unordered_map<int64_t, BlockType> m_blocks;
    std::unordered_map<int64_t, bool> m_doorOpenStates;
};
