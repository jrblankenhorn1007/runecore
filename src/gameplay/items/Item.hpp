#pragma once
#include <string>
#include <vector>

enum class ItemCategory {
    Weapon,
    Armor,
    Accessory,
    Consumable,
    Material,
    Tool,
    Augmentation
};

enum class EquipSlot {
    None,
    MainHand,
    OffHand,
    Helmet,
    Chestplate,
    Greaves,
    Boots,
    Ring1,
    Ring2,
    Amulet,
    Relic
};

enum class ItemRarity {
    Common,
    Uncommon,
    Rare,
    Epic,
    Legendary,
    Mythic,
    Prismatic
};

struct Affix {
    std::string name;
    bool isPrefix{true};
    int tier{1};
    float flatBonus{0.0f};
    float percentBonus{0.0f};
    std::string statTarget; // "Damage", "Armor", "CritChance", "MaxHealth", etc.
};

struct Item {
    std::string id;
    std::string name;
    ItemCategory category{ItemCategory::Material};
    EquipSlot equipSlot{EquipSlot::None};
    ItemRarity rarity{ItemRarity::Common};
    int tier{1};

    float quality{0.0f}; // 0.0 to 0.20 (+0% to +20%)
    float baseDamage{0.0f};
    float baseArmor{0.0f};
    float attackSpeed{1.0f};
    float weight{0.5f};

    bool stackable{false};
    int quantity{1};
    int maxStack{99};

    int sockets{0};
    int usedSockets{0};

    std::vector<Affix> affixes;
    std::string uniquePerk;

    float getEffectiveDamage() const {
        return baseDamage * (1.0f + quality);
    }

    float getEffectiveArmor() const {
        return baseArmor * (1.0f + quality);
    }
};

struct BaseItemTemplate {
    std::string id;
    std::string name;
    ItemCategory category{ItemCategory::Weapon};
    EquipSlot equipSlot{EquipSlot::MainHand};
    int tier{1};

    float minBaseDamage{10.0f};
    float maxBaseDamage{20.0f};
    float meanDamage{15.0f};
    float stdDevDamage{2.0f};

    float minBaseArmor{0.0f};
    float maxBaseArmor{0.0f};
    float meanArmor{0.0f};
    float stdDevArmor{0.0f};

    float baseAttackSpeed{1.0f};
    float baseWeight{1.0f};
    bool stackable{false};
    int maxStack{1};
};
