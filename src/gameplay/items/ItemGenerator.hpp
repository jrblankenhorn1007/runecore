#pragma once
#include "gameplay/items/Item.hpp"
#include "core/Random.hpp"

class ItemGenerator {
public:
    explicit ItemGenerator(Random& rng);

    Item generateItem(const BaseItemTemplate& tmpl, ItemRarity rarity = ItemRarity::Common, float quality = 0.0f);

private:
    void generateAffixes(Item& item);

    Random& m_rng;
};
