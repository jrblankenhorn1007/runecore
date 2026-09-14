#include "gameplay/combat/DamageCalculator.hpp"
#include <algorithm>

DamageResult DamageCalculator::calculate(
    const DamageInstance& instance,
    float targetArmor,
    float targetResistance,
    float attackerCritChance,
    float attackerCritMultiplier
) {
    DamageResult result;
    result.rawDamage = instance.baseDamage;

    // Check critical strike
    if (instance.canCrit && attackerCritChance > 0.0f) {
        if (attackerCritChance >= 1.0f) {
            result.isCrit = true;
            result.rawDamage *= attackerCritMultiplier;
        }
    }

    // Apply armor mitigation for physical, or resistance for elemental
    if (instance.type == DamageType::Physical) {
        float effectiveArmor = std::max(0.0f, targetArmor * (1.0f - instance.armorPenetration));
        // Standard formula: Mitigated = Raw * 100 / (100 + Armor)
        float mitigationFactor = 100.0f / (100.0f + effectiveArmor);
        result.mitigatedDamage = result.rawDamage * mitigationFactor;
        result.finalDamage = result.mitigatedDamage;
    } else {
        // Elemental Resistance: Final = Raw * (1.0 - Resist)
        float clampedResist = std::clamp(targetResistance, -1.0f, 0.90f);
        result.mitigatedDamage = result.rawDamage;
        result.finalDamage = result.rawDamage * (1.0f - clampedResist);
    }

    result.finalDamage = std::max(1.0f, result.finalDamage);
    return result;
}
