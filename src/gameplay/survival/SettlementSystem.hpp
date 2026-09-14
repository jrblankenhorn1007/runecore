#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include "procgen/Tilemap.hpp"

enum class NPCType {
    None,
    Blacksmith,
    Doctor,
    Merchant,
    Guide
};

struct RoomBounds {
    int x{0};
    int y{0};
    int width{0};
    int height{0};
};

struct HousingCheckResult {
    bool isEnclosed{false};
    bool hasDoor{false};
    bool hasLightSource{false};
    bool hasFurniture{false};
    bool isSuitable{false};
};

class SettlementSystem {
public:
    HousingCheckResult checkSuitability(const Tilemap& tilemap, const RoomBounds& room) const;
    bool assignNPC(NPCType npc, const RoomBounds& room);
    bool isNPCResident(NPCType npc) const;

private:
    std::unordered_map<NPCType, RoomBounds> m_residents;
};
