#include "gameplay/building/BuildingSystem.hpp"

BuildingSystem::BuildingSystem(float blockSize) : m_blockSize(blockSize) {}

bool BuildingSystem::placeBlock(int x, int y, BlockType type) {
    if (type == BlockType::Air) return false;

    int64_t key = hashCoords(x, y);
    if (m_blocks.find(key) != m_blocks.end() && m_blocks[key] != BlockType::Air) {
        return false; // Already occupied
    }

    m_blocks[key] = type;
    if (type == BlockType::WoodenDoor) {
        m_doorOpenStates[key] = false;
    }
    return true;
}

bool BuildingSystem::breakBlock(int x, int y) {
    int64_t key = hashCoords(x, y);
    auto it = m_blocks.find(key);
    if (it != m_blocks.end() && it->second != BlockType::Air) {
        m_blocks.erase(it);
        m_doorOpenStates.erase(key);
        return true;
    }
    return false;
}

BlockType BuildingSystem::getBlock(int x, int y) const {
    int64_t key = hashCoords(x, y);
    auto it = m_blocks.find(key);
    if (it != m_blocks.end()) {
        return it->second;
    }
    return BlockType::Air;
}

bool BuildingSystem::isDoorOpen(int x, int y) const {
    int64_t key = hashCoords(x, y);
    auto it = m_doorOpenStates.find(key);
    if (it != m_doorOpenStates.end()) {
        return it->second;
    }
    return false;
}

void BuildingSystem::toggleDoor(int x, int y) {
    int64_t key = hashCoords(x, y);
    auto it = m_doorOpenStates.find(key);
    if (it != m_doorOpenStates.end()) {
        it->second = !it->second;
    }
}
