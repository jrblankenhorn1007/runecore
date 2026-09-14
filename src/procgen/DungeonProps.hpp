#pragma once
#include <unordered_map>
#include <string>

enum class DungeonPropType { Chest, Keycard, Lever, PressurePlate, DartTrap, SpikePit };
enum class KeyColor { None, Red, Blue, Gold };

struct DungeonProp {
    DungeonPropType type{DungeonPropType::Chest};
    KeyColor key{KeyColor::None};
    bool active{true};
    bool opened{false};
};

class DungeonProps {
public:
    bool place(int x, int y, DungeonProp prop);
    DungeonProp* get(int x, int y);
    const DungeonProp* get(int x, int y) const;
    bool interact(int x, int y, KeyColor carriedKey = KeyColor::None);
    bool isTrapActive(int x, int y) const;
private:
    static long long key(int x, int y) { return (static_cast<long long>(x) << 32) ^ static_cast<unsigned int>(y); }
    std::unordered_map<long long, DungeonProp> m_props;
};
