#pragma once
#include <unordered_map>
#include <vector>

enum class MapIcon { Player, Entrance, Key, Chest, Boss };
struct MapMarker { int x{0}; int y{0}; MapIcon icon{MapIcon::Chest}; };

class MapFog {
public:
    void revealRoom(int roomIndex);
    bool isRevealed(int roomIndex) const;
    void hideAll();
    void addMarker(MapMarker marker);
    const std::vector<MapMarker>& markers() const { return m_markers; }
private:
    std::unordered_map<int, bool> m_revealed;
    std::vector<MapMarker> m_markers;
};
