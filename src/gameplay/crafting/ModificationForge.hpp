#pragma once
#include "gameplay/items/Item.hpp"
#include "core/Random.hpp"
#include <unordered_map>

struct ForgeResult {
    bool success{false};
    bool isFractured{false};
    std::string message;
};

class ModificationForge {
public:
    explicit ModificationForge(Random& rng);

    ForgeResult infuseAffix(Item& item, const Affix& affix);
    ForgeResult upgradeTier(Item& item);
    ForgeResult punchSocket(Item& item);

    int getInstability(const Item& item) const;
    void setInstability(const Item& item, int val);
    bool isFractured(const Item& item) const;

private:
    bool rollFracture(const Item& item);

    Random& m_rng;
    std::unordered_map<std::string, int> m_instabilityMap;
    std::unordered_map<std::string, bool> m_fracturedMap;
};
