#include "gameplay/survival/Environment.hpp"
#include <cmath>
#include <algorithm>

DayNightCycle::DayNightCycle(float fullCycleSeconds)
    : m_fullCycle(fullCycleSeconds > 0.0f ? fullCycleSeconds : 1440.0f) {}

void DayNightCycle::update(float dt) {
    m_timeOfDay += dt;
    while (m_timeOfDay >= m_fullCycle) {
        m_timeOfDay -= m_fullCycle;
    }
}

void DayNightCycle::setTimeOfDay(float seconds) {
    m_timeOfDay = std::fmod(seconds, m_fullCycle);
    if (m_timeOfDay < 0.0f) m_timeOfDay += m_fullCycle;
}

float DayNightCycle::getAmbientDarkness() const {
    // 0s and 1440s is midnight (darkness ~ 0.85)
    // 720s is noon (darkness = 0.0)
    float normalizedTime = m_timeOfDay / m_fullCycle; // 0.0 to 1.0
    // Cosine curve: 0 at noon (0.5), 1 at midnight (0.0 and 1.0)
    float factor = 0.5f * (1.0f + std::cos(normalizedTime * 2.0f * 3.14159265f));
    return factor * 0.85f;
}

bool DayNightCycle::isNight() const {
    return getAmbientDarkness() > 0.40f;
}
