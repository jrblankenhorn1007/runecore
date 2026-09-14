#pragma once
#include <string>
#include <unordered_map>
#include <cstdint>

enum class CropStage : uint8_t {
    None = 0,
    Seed = 1,
    Sprout = 2,
    Vegetative = 3,
    Flowering = 4,
    Mature = 5
};

struct CropData {
    std::string seedId;
    CropStage stage{CropStage::None};
    float growthProgress{0.0f}; // 0 to 100
    float growthSpeed{1.0f};
};

struct HarvestResult {
    bool success{false};
    std::string produceItemId;
    int yieldCount{0};
    int seedRefundCount{0};
};

class FarmingSystem {
public:
    void tillSoil(int x, int y);
    void waterSoil(int x, int y);
    bool isTilled(int x, int y) const;
    bool isHydrated(int x, int y) const;

    bool plantSeed(int x, int y, const std::string& seedId);
    CropStage getCropStage(int x, int y) const;
    HarvestResult harvest(int x, int y);

    void update(float dt);

private:
    static int64_t hashCoords(int x, int y) {
        return (static_cast<int64_t>(x) << 32) | (static_cast<int64_t>(y) & 0xFFFFFFFF);
    }

    std::unordered_map<int64_t, bool> m_tilledSoil;
    std::unordered_map<int64_t, bool> m_hydratedSoil;
    std::unordered_map<int64_t, CropData> m_crops;
};
