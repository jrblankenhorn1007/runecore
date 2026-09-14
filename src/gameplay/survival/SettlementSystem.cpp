#include "gameplay/survival/SettlementSystem.hpp"

HousingCheckResult SettlementSystem::checkSuitability(const Tilemap& tilemap, const RoomBounds& room) const {
    HousingCheckResult res;
    if (room.width < 4 || room.height < 4) {
        return res;
    }

    bool topClosed = true;
    bool bottomClosed = true;
    bool leftClosed = true;
    bool rightClosed = true;

    // Check top and bottom boundaries
    for (int x = room.x; x < room.x + room.width; ++x) {
        if (tilemap.getBlock(x, room.y, BlockLayer::Foreground) == 0) topClosed = false;
        if (tilemap.getBlock(x, room.y + room.height - 1, BlockLayer::Foreground) == 0) bottomClosed = false;
    }

    // Check left and right walls (or doors)
    for (int y = room.y + 1; y < room.y + room.height - 1; ++y) {
        uint16_t leftBlk = tilemap.getBlock(room.x, y, BlockLayer::Foreground);
        uint16_t rightBlk = tilemap.getBlock(room.x + room.width - 1, y, BlockLayer::Foreground);

        if (leftBlk == 6 || rightBlk == 6) {
            res.hasDoor = true;
        }

        if (leftBlk == 0) leftClosed = false;
        if (rightBlk == 0) rightClosed = false;
    }

    res.isEnclosed = (topClosed && bottomClosed && leftClosed && rightClosed);

    // Scan interior for Light (block 8 = Torch) and Furniture (block 7 = Chest, 9 = Bed)
    for (int y = room.y + 1; y < room.y + room.height - 1; ++y) {
        for (int x = room.x + 1; x < room.x + room.width - 1; ++x) {
            uint16_t b = tilemap.getBlock(x, y, BlockLayer::Foreground);
            if (b == 8) {
                res.hasLightSource = true;
            }
            if (b == 7 || b == 9) {
                res.hasFurniture = true;
            }
        }
    }

    res.isSuitable = (res.isEnclosed && res.hasDoor && res.hasLightSource && res.hasFurniture);
    return res;
}

bool SettlementSystem::assignNPC(NPCType npc, const RoomBounds& room) {
    if (npc == NPCType::None) return false;
    m_residents[npc] = room;
    return true;
}

bool SettlementSystem::isNPCResident(NPCType npc) const {
    return m_residents.find(npc) != m_residents.end();
}
