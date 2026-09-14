#pragma once
#include "ecs/Components.hpp"

enum class StatusType {
    Bleed,
    Poison,
    Burn,
    Freeze,
    Shock,
    Rot,
    Petrification,
    Stun,
    EMP
};

class StatusEffectsManager {
public:
    void applyEffect(StatusEffectsComponent& comp, StatusType type, float duration, float tickInterval, float damagePerTick);
    float update(StatusEffectsComponent& comp, float dt);
    void cleanseAll(StatusEffectsComponent& comp);
    bool hasEffect(const StatusEffectsComponent& comp, StatusType type) const;
};
