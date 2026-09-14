#include "procgen/DungeonProps.hpp"

bool DungeonProps::place(int x, int y, DungeonProp prop) {
    return m_props.emplace(key(x, y), prop).second;
}
DungeonProp* DungeonProps::get(int x, int y) {
    auto it = m_props.find(key(x, y)); return it == m_props.end() ? nullptr : &it->second;
}
const DungeonProp* DungeonProps::get(int x, int y) const {
    auto it = m_props.find(key(x, y)); return it == m_props.end() ? nullptr : &it->second;
}
bool DungeonProps::interact(int x, int y, KeyColor carriedKey) {
    DungeonProp* prop = get(x, y);
    if (!prop) return false;
    if (prop->type == DungeonPropType::Chest) { if (prop->opened) return false; prop->opened = true; return true; }
    if (prop->type == DungeonPropType::Lever) { prop->active = !prop->active; return true; }
    if (prop->type == DungeonPropType::Keycard) return carriedKey == prop->key;
    return false;
}
bool DungeonProps::isTrapActive(int x, int y) const {
    const DungeonProp* prop = get(x, y);
    return prop && (prop->type == DungeonPropType::DartTrap || prop->type == DungeonPropType::PressurePlate ||
                    prop->type == DungeonPropType::SpikePit) && prop->active;
}
