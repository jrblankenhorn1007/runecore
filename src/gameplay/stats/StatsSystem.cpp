#include "gameplay/stats/StatsSystem.hpp"
#include <algorithm>

DerivedStats StatsSystem::calculateDerivedStats(const Attributes& attrs) {
    DerivedStats d;

    // Health: 100 + (STR * 5) + (VIT * 10)
    d.maxHealth = 100.0f + (attrs.strength * 5.0f) + (attrs.vitality * 10.0f);
    d.healthRegen = 0.5f + (attrs.vitality * 0.1f);

    // Mana: 50 + (INT * 5)
    d.maxMana = 50.0f + (attrs.intelligence * 5.0f);
    d.manaRegen = 1.0f + (attrs.intelligence * 0.1f);

    // Power: 50 + (CYB * 5)
    d.maxPower = 50.0f + (attrs.cybernetics * 5.0f);
    d.cooldownReduction = std::min(0.60f, attrs.cybernetics * 0.005f); // 0.5% per CYB, capped at 60%

    // Defense & Armor
    d.physicalArmor = attrs.vitality * 1.0f;
    d.energyArmor = attrs.wisdom * 1.0f;
    d.fireResistance = std::min(0.75f, 0.05f + attrs.wisdom * 0.005f);
    d.coldResistance = std::min(0.75f, 0.05f + attrs.vitality * 0.005f);
    d.shockResistance = std::min(0.75f, 0.05f + attrs.cybernetics * 0.005f);
    d.natureResistance = std::min(0.75f, 0.05f + attrs.wisdom * 0.005f);
    d.darkResistance = std::min(0.75f, 0.05f + attrs.intelligence * 0.005f);
    d.holyResistance = std::min(0.75f, 0.05f + attrs.wisdom * 0.005f);

    // Offense
    d.physicalDamageMultiplier = 1.0f + (attrs.strength * 0.01f);
    d.rangedDamageMultiplier = 1.0f + (attrs.dexterity * 0.01f);
    d.magicDamageMultiplier = 1.0f + (attrs.intelligence * 0.01f);

    // Speed & Criticals
    d.critChance = std::min(0.75f, 0.05f + (attrs.dexterity * 0.002f)); // 5% + 0.2% per DEX
    d.critMultiplier = 1.5f + (attrs.dexterity * 0.005f);
    d.moveSpeedMultiplier = 1.0f + (attrs.dexterity * 0.005f);
    d.attackSpeedMultiplier = 1.0f + (attrs.dexterity * 0.004f);

    // Carry Weight: 50kg + (STR * 0.5kg)
    d.carryWeightCapacity = 50.0f + (attrs.strength * 0.5f);

    return d;
}
