#include "gameplay/crafting/ModificationForge.hpp"
#include <algorithm>

ModificationForge::ModificationForge(Random& rng) : m_rng(rng) {}

int ModificationForge::getInstability(const Item& item) const {
    auto it = m_instabilityMap.find(item.id);
    if (it != m_instabilityMap.end()) {
        return it->second;
    }
    return 0;
}

void ModificationForge::setInstability(const Item& item, int val) {
    m_instabilityMap[item.id] = val;
}

bool ModificationForge::isFractured(const Item& item) const {
    auto it = m_fracturedMap.find(item.id);
    if (it != m_fracturedMap.end()) {
        return it->second;
    }
    return false;
}

bool ModificationForge::rollFracture(const Item& item) {
    int inst = getInstability(item);
    if (inst < 50) return false;

    // Chance = (instability - 50) * 1.5%
    float fractureChance = (inst - 50) * 0.015f;
    if (m_rng.chance(fractureChance)) {
        m_fracturedMap[item.id] = true;
        return true;
    }
    return false;
}

ForgeResult ModificationForge::infuseAffix(Item& item, const Affix& affix) {
    ForgeResult res;
    if (isFractured(item)) {
        res.success = false;
        res.message = "Item is fractured and cannot be modified";
        return res;
    }

    if (rollFracture(item)) {
        res.isFractured = true;
        res.success = false;
        res.message = "Item fractured during infusion!";
        return res;
    }

    item.affixes.push_back(affix);
    m_instabilityMap[item.id] += 10;
    res.success = true;
    res.message = "Affix infused successfully";
    return res;
}

ForgeResult ModificationForge::upgradeTier(Item& item) {
    ForgeResult res;
    if (isFractured(item)) {
        res.success = false;
        res.message = "Item is fractured and cannot be modified";
        return res;
    }

    if (item.tier >= 7) {
        res.success = false;
        res.message = "Item is already at maximum tier (Tier 7)";
        return res;
    }

    if (rollFracture(item)) {
        res.isFractured = true;
        res.success = false;
        res.message = "Item fractured during tier upgrade!";
        return res;
    }

    item.tier++;
    item.baseDamage *= 1.25f;
    item.baseArmor *= 1.25f;
    m_instabilityMap[item.id] += 15;

    res.success = true;
    res.message = "Item upgraded to next tier";
    return res;
}

ForgeResult ModificationForge::punchSocket(Item& item) {
    ForgeResult res;
    if (isFractured(item)) {
        res.success = false;
        res.message = "Item is fractured and cannot be modified";
        return res;
    }

    if (item.sockets >= 3) {
        res.success = false;
        res.message = "Item already has maximum 3 sockets";
        return res;
    }

    if (rollFracture(item)) {
        res.isFractured = true;
        res.success = false;
        res.message = "Item fractured while drilling socket!";
        return res;
    }

    item.sockets++;
    m_instabilityMap[item.id] += 20;

    res.success = true;
    res.message = "Socket added successfully";
    return res;
}
