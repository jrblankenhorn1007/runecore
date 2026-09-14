#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include "procgen/Tilemap.hpp"

enum class NPCType {
    None,
    Blacksmith,
    Doctor,
    Alchemist,
    Merchant,
    Guide
};
enum class NPCService { Repair, Heal, Transmute, Reveal };
struct ServiceResult { bool success{false}; int value{0}; };

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
    ServiceResult useService(NPCType npc, NPCService service, int resource = 0) const;

private:
    std::unordered_map<NPCType, RoomBounds> m_residents;
};
