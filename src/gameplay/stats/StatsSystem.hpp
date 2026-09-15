#pragma once

struct Attributes {
    int strength{10};
    int dexterity{10};
    int intelligence{10};
    int vitality{10};
    int wisdom{10};
    int cybernetics{10};
};

struct DerivedStats {
    float maxHealth{100.0f};
    float healthRegen{0.5f};
    float maxMana{50.0f};
    float manaRegen{1.0f};
    float maxPower{50.0f};
    float powerRegen{0.0f};
    float physicalArmor{0.0f};
    float energyArmor{0.0f};
    float fireResistance{0.0f};
    float coldResistance{0.0f};
    float shockResistance{0.0f};
    float natureResistance{0.0f};
    float darkResistance{0.0f};
    float holyResistance{0.0f};
    float physicalDamageMultiplier{1.0f};
    float rangedDamageMultiplier{1.0f};
    float magicDamageMultiplier{1.0f};
    float critChance{0.05f};
    float critMultiplier{1.5f};
    float moveSpeedMultiplier{1.0f};
    float attackSpeedMultiplier{1.0f};
    float cooldownReduction{0.0f};
    float carryWeightCapacity{50.0f};
};

class StatsSystem {
public:
    static DerivedStats calculateDerivedStats(const Attributes& attrs);
};
