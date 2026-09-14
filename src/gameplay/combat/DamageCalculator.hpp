#pragma once

enum class DamageType {
    Physical,
    Fire,
    Cold,
    Shock,
    Nature,
    Holy,
    Dark,
    Chaos
};

struct DamageInstance {
    float baseDamage{10.0f};
    DamageType type{DamageType::Physical};
    bool canCrit{true};
    float armorPenetration{0.0f};
};

struct DamageResult {
    float rawDamage{0.0f};
    float mitigatedDamage{0.0f};
    float finalDamage{0.0f};
    bool isCrit{false};
};

class DamageCalculator {
public:
    static DamageResult calculate(
        const DamageInstance& instance,
        float targetArmor,
        float targetResistance,
        float attackerCritChance = 0.05f,
        float attackerCritMultiplier = 1.5f
    );
};
