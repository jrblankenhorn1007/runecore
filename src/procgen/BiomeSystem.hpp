#pragma once
#include <string>
#include <vector>
#include "core/Math.hpp"
#include "physics/CollisionWorld.hpp"

struct BiomeData {
    std::string id;
    std::string name;
    int tier{1};
    float minX{-9999.0f};
    float maxX{9999.0f};
    float ambientTemperature{20.0f}; // Celsius
    Color skyColor{20, 25, 40, 255};
    Color groundColor{70, 75, 90, 255};
};

enum class HazardType {
    None,
    Spikes,
    Lava,
    Acid
};

struct HazardHit {
    bool hasHazard{false};
    HazardType type{HazardType::None};
    float damage{0.0f};
    bool inflictsBleed{false};
    bool inflictsBurn{false};
};

class BiomeSystem {
public:
    BiomeSystem();

    BiomeData getBiomeAt(float worldX) const;
    float getAmbientTemperature(float worldX) const;

    HazardHit checkHazard(const CollisionWorld& world, const Vec2& position, const Rect& localBox) const;

private:
    void initBiomes();

    std::vector<BiomeData> m_biomes;
};
