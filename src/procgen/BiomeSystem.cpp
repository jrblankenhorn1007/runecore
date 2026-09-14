#include "procgen/BiomeSystem.hpp"
#include <cmath>
#include <algorithm>

BiomeSystem::BiomeSystem() {
    initBiomes();
}

void BiomeSystem::initBiomes() {
    // Haven (Hub Valley, Temperate)
    BiomeData haven;
    haven.id = "bio_haven";
    haven.name = "The Haven Valley";
    haven.tier = 1;
    haven.minX = -2000.0f;
    haven.maxX = 200.0f;
    haven.ambientTemperature = 22.0f;
    haven.skyColor = Color{30, 40, 60, 255};
    haven.groundColor = Color{65, 125, 60, 255};
    m_biomes.push_back(haven);

    // Rustwood Forest (Temperate / Cool)
    BiomeData rustwood;
    rustwood.id = "bio_rustwood";
    rustwood.name = "Rustwood Forest";
    rustwood.tier = 1;
    rustwood.minX = 200.0f;
    rustwood.maxX = 600.0f;
    rustwood.ambientTemperature = 16.0f;
    rustwood.skyColor = Color{25, 35, 45, 255};
    rustwood.groundColor = Color{90, 75, 45, 255};
    m_biomes.push_back(rustwood);

    // Ashen Foundry (Extreme Heat)
    BiomeData foundry;
    foundry.id = "bio_foundry";
    foundry.name = "Ashen Foundry";
    foundry.tier = 2;
    foundry.minX = 600.0f;
    foundry.maxX = 1000.0f;
    foundry.ambientTemperature = 85.0f;
    foundry.skyColor = Color{45, 20, 15, 255};
    foundry.groundColor = Color{55, 40, 35, 255};
    m_biomes.push_back(foundry);

    // Cryo-Glacier (Extreme Cold)
    BiomeData glacier;
    glacier.id = "bio_glacier";
    glacier.name = "Cryo-Glacier Peaks";
    glacier.tier = 2;
    glacier.minX = 1000.0f;
    glacier.maxX = 1400.0f;
    glacier.ambientTemperature = -18.0f;
    glacier.skyColor = Color{20, 45, 70, 255};
    glacier.groundColor = Color{180, 210, 240, 255};
    m_biomes.push_back(glacier);

    // Bioluminescent Bog (Humid / Toxic)
    BiomeData bog;
    bog.id = "bio_bog";
    bog.name = "Bioluminescent Bog";
    bog.tier = 3;
    bog.minX = 1400.0f;
    bog.maxX = 2500.0f;
    bog.ambientTemperature = 20.0f;
    bog.skyColor = Color{15, 25, 30, 255};
    bog.groundColor = Color{40, 65, 55, 255};
    m_biomes.push_back(bog);
}

BiomeData BiomeSystem::getBiomeAt(float worldX) const {
    for (const auto& b : m_biomes) {
        if (worldX >= b.minX && worldX < b.maxX) {
            return b;
        }
    }
    // Default fallback to Haven
    if (!m_biomes.empty()) {
        return m_biomes[0];
    }
    return BiomeData{};
}

float BiomeSystem::getAmbientTemperature(float worldX) const {
    BiomeData current = getBiomeAt(worldX);

    // Check if within 50px blend distance to neighbor
    float blendDist = 50.0f;
    for (const auto& b : m_biomes) {
        if (std::abs(worldX - b.minX) < blendDist) {
            // Find left neighbor
            BiomeData left = getBiomeAt(b.minX - 1.0f);
            float t = (worldX - (b.minX - blendDist * 0.5f)) / blendDist;
            t = std::clamp(t, 0.0f, 1.0f);
            return left.ambientTemperature * (1.0f - t) + b.ambientTemperature * t;
        }
    }

    return current.ambientTemperature;
}

HazardHit BiomeSystem::checkHazard(const CollisionWorld& world, const Vec2& position, const Rect& localBox) const {
    HazardHit hit;
    float tileSize = world.getTileSize();

    Rect worldBox{
        position.x + localBox.x,
        position.y + localBox.y,
        localBox.width,
        localBox.height
    };

    int minTx = static_cast<int>(std::floor(worldBox.x / tileSize));
    int maxTx = static_cast<int>(std::floor((worldBox.x + worldBox.width) / tileSize));
    int minTy = static_cast<int>(std::floor(worldBox.y / tileSize));
    int maxTy = static_cast<int>(std::floor((worldBox.y + worldBox.height) / tileSize));

    for (int ty = minTy; ty <= maxTy; ++ty) {
        for (int tx = minTx; tx <= maxTx; ++tx) {
            TileType t = world.getTile(tx, ty);
            if (t == TileType::HazardSpike) {
                hit.hasHazard = true;
                hit.type = HazardType::Spikes;
                hit.damage = std::max(hit.damage, 25.0f);
                hit.inflictsBleed = true;
            } else if (t == TileType::HazardLava) {
                hit.hasHazard = true;
                hit.type = HazardType::Lava;
                hit.damage = std::max(hit.damage, 60.0f);
                hit.inflictsBurn = true;
            }
        }
    }

    return hit;
}
