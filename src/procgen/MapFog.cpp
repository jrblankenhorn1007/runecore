#include "procgen/MapFog.hpp"
void MapFog::revealRoom(int roomIndex) { m_revealed[roomIndex] = true; }
bool MapFog::isRevealed(int roomIndex) const {
    auto it = m_revealed.find(roomIndex); return it != m_revealed.end() && it->second;
}
void MapFog::hideAll() { m_revealed.clear(); }
void MapFog::addMarker(MapMarker marker) { m_markers.push_back(marker); }
