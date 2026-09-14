#include "gameplay/items/ItemGenerator.hpp"
#include <algorithm>

ItemGenerator::ItemGenerator(Random& rng) : m_rng(rng) {}

Item ItemGenerator::generateItem(const BaseItemTemplate& tmpl, ItemRarity rarity, float quality) {
    Item item;
    item.id = tmpl.id;
    item.name = tmpl.name;
    item.category = tmpl.category;
    item.equipSlot = tmpl.equipSlot;
    item.tier = tmpl.tier;
    item.rarity = rarity;
    item.quality = std::clamp(quality, 0.0f, 0.20f);
    item.attackSpeed = tmpl.baseAttackSpeed;
    item.weight = tmpl.baseWeight;
    item.stackable = tmpl.stackable;
    item.maxStack = tmpl.maxStack;
    item.quantity = 1;

    // Roll base damage with Gaussian distribution
    if (tmpl.maxBaseDamage > 0.0f) {
        item.baseDamage = m_rng.gaussian(tmpl.meanDamage, tmpl.stdDevDamage, tmpl.minBaseDamage, tmpl.maxBaseDamage);
    }

    // Roll base armor with Gaussian distribution
    if (tmpl.maxBaseArmor > 0.0f) {
        item.baseArmor = m_rng.gaussian(tmpl.meanArmor, tmpl.stdDevArmor, tmpl.minBaseArmor, tmpl.maxBaseArmor);
    }

    // Roll sockets: 0 to 3 based on rarity
    if (rarity >= ItemRarity::Rare) {
        item.sockets = m_rng.rangeInt(1, 3);
    }

    generateAffixes(item);
    return item;
}

void ItemGenerator::generateAffixes(Item& item) {
    int prefixCount = 0;
    int suffixCount = 0;

    switch (item.rarity) {
        case ItemRarity::Common:
            prefixCount = 0;
            suffixCount = 0;
            break;
        case ItemRarity::Uncommon:
            prefixCount = m_rng.chance(0.5f) ? 1 : 0;
            suffixCount = (prefixCount == 0) ? 1 : 0;
            break;
        case ItemRarity::Rare:
            prefixCount = 1;
            suffixCount = 1;
            break;
        case ItemRarity::Epic:
            prefixCount = 2;
            suffixCount = 1;
            break;
        case ItemRarity::Legendary:
            prefixCount = 2;
            suffixCount = 2;
            item.uniquePerk = "Ancient Precursor Resonance";
            break;
        case ItemRarity::Mythic:
            prefixCount = 3;
            suffixCount = 3;
            item.uniquePerk = "Singularity Harmonic Overdrive";
            break;
        case ItemRarity::Prismatic:
            prefixCount = 4;
            suffixCount = 4;
            item.uniquePerk = "Cosmic Transmutation Horizon";
            break;
    }

    // Generate prefixes
    for (int i = 0; i < prefixCount; ++i) {
        Affix af;
        af.isPrefix = true;
        af.tier = item.tier;
        af.name = "Serrated";
        af.statTarget = "Damage";
        af.percentBonus = 0.10f * item.tier;
        item.affixes.push_back(af);
    }

    // Generate suffixes
    for (int i = 0; i < suffixCount; ++i) {
        Affix af;
        af.isPrefix = false;
        af.tier = item.tier;
        af.name = "of the Titan";
        af.statTarget = "Health";
        af.flatBonus = 25.0f * item.tier;
        item.affixes.push_back(af);
    }
}
