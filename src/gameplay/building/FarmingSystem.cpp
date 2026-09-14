#include "gameplay/building/FarmingSystem.hpp"
#include <algorithm>

void FarmingSystem::tillSoil(int x, int y) {
    m_tilledSoil[hashCoords(x, y)] = true;
}

void FarmingSystem::waterSoil(int x, int y) {
    if (isTilled(x, y)) {
        m_hydratedSoil[hashCoords(x, y)] = true;
    }
}

bool FarmingSystem::isTilled(int x, int y) const {
    auto it = m_tilledSoil.find(hashCoords(x, y));
    return (it != m_tilledSoil.end() && it->second);
}

bool FarmingSystem::isHydrated(int x, int y) const {
    auto it = m_hydratedSoil.find(hashCoords(x, y));
    return (it != m_hydratedSoil.end() && it->second);
}

bool FarmingSystem::plantSeed(int x, int y, const std::string& seedId) {
    if (!isTilled(x, y)) return false;

    int64_t key = hashCoords(x, y);
    if (m_crops.find(key) != m_crops.end() && m_crops[key].stage != CropStage::None) {
        return false; // Crop already planted
    }

    CropData crop;
    crop.seedId = seedId;
    crop.stage = CropStage::Seed;
    crop.growthProgress = 0.0f;
    crop.growthSpeed = 1.0f;

    m_crops[key] = crop;
    return true;
}

CropStage FarmingSystem::getCropStage(int x, int y) const {
    auto it = m_crops.find(hashCoords(x, y));
    if (it != m_crops.end()) {
        return it->second.stage;
    }
    return CropStage::None;
}

void FarmingSystem::update(float dt) {
    for (auto& [key, crop] : m_crops) {
        if (crop.stage == CropStage::None || crop.stage == CropStage::Mature) {
            continue;
        }

        // Hydrated soil grows 2x faster
        float waterMultiplier = 1.0f;
        auto hydroIt = m_hydratedSoil.find(key);
        if (hydroIt != m_hydratedSoil.end() && hydroIt->second) {
            waterMultiplier = 2.0f;
        }

        crop.growthProgress += (dt * crop.growthSpeed * waterMultiplier);

        if (crop.growthProgress >= 100.0f) {
            crop.stage = CropStage::Mature;
        } else if (crop.growthProgress >= 75.0f) {
            crop.stage = CropStage::Flowering;
        } else if (crop.growthProgress >= 50.0f) {
            crop.stage = CropStage::Vegetative;
        } else if (crop.growthProgress >= 25.0f) {
            crop.stage = CropStage::Sprout;
        }
    }
}

HarvestResult FarmingSystem::harvest(int x, int y) {
    HarvestResult result;
    int64_t key = hashCoords(x, y);

    auto it = m_crops.find(key);
    if (it == m_crops.end() || it->second.stage != CropStage::Mature) {
        result.success = false;
        return result;
    }

    result.success = true;
    result.produceItemId = it->second.seedId;
    result.yieldCount = 3;
    result.seedRefundCount = 1;

    m_crops.erase(it);
    return result;
}
