#include "gameplay/survival/Metabolism.hpp"
#include <algorithm>

Metabolism::Metabolism() = default;

void Metabolism::setHunger(float val) {
    m_hunger = std::clamp(val, 0.0f, 100.0f);
}

void Metabolism::setThirst(float val) {
    m_thirst = std::clamp(val, 0.0f, 100.0f);
}

void Metabolism::eat(float hungerRestore) {
    m_hunger = std::min(100.0f, m_hunger + hungerRestore);
}

void Metabolism::drink(float thirstRestore) {
    m_thirst = std::min(100.0f, m_thirst + thirstRestore);
}

float Metabolism::update(float dt, float ambientTemperature) {
    float damage = 0.0f;

    // Deplete hunger & thirst
    m_hunger = std::max(0.0f, m_hunger - m_hungerDrainRate * dt);
    m_thirst = std::max(0.0f, m_thirst - m_thirstDrainRate * dt);

    // Thermal equilibrium towards ambient
    float tempDiff = ambientTemperature - m_bodyTemp;
    // Slow heat exchange rate
    m_bodyTemp += tempDiff * (0.005f * dt);

    if (isStarving()) {
        damage += 2.0f * dt; // 2 HP/sec starvation
    }

    if (isHypothermic()) {
        damage += 3.0f * dt; // 3 HP/sec hypothermia
    } else if (isHyperthermic()) {
        damage += 3.0f * dt; // 3 HP/sec heatstroke
    }

    return damage;
}
