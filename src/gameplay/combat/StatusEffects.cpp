#include "gameplay/combat/StatusEffects.hpp"
#include <algorithm>

void StatusEffectsManager::applyEffect(
    StatusEffectsComponent& comp,
    StatusType type,
    float duration,
    float tickInterval,
    float damagePerTick
) {
    int typeInt = static_cast<int>(type);

    // Refresh if already present
    for (auto& effect : comp.effects) {
        if (effect.type == typeInt) {
            effect.duration = std::max(effect.duration, duration);
            effect.damagePerTick = std::max(effect.damagePerTick, damagePerTick);
            return;
        }
    }

    ActiveStatusEffect newEff;
    newEff.type = typeInt;
    newEff.duration = duration;
    newEff.tickInterval = tickInterval;
    newEff.tickTimer = 0.0f;
    newEff.damagePerTick = damagePerTick;

    comp.effects.push_back(newEff);
}

float StatusEffectsManager::update(StatusEffectsComponent& comp, float dt) {
    float totalTickDamage = 0.0f;

    for (auto it = comp.effects.begin(); it != comp.effects.end(); ) {
        it->duration -= dt;
        it->tickTimer += dt;

        while (it->tickTimer >= it->tickInterval && it->tickInterval > 0.0f) {
            it->tickTimer -= it->tickInterval;
            totalTickDamage += it->damagePerTick;
        }

        if (it->duration <= 0.0f) {
            it = comp.effects.erase(it);
        } else {
            ++it;
        }
    }

    return totalTickDamage;
}

void StatusEffectsManager::cleanseAll(StatusEffectsComponent& comp) {
    comp.effects.clear();
}

bool StatusEffectsManager::hasEffect(const StatusEffectsComponent& comp, StatusType type) const {
    int typeInt = static_cast<int>(type);
    for (const auto& effect : comp.effects) {
        if (effect.type == typeInt) {
            return true;
        }
    }
    return false;
}
