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

Color SkyTransition::blend(const Color& from, const Color& to, float amount) {
    amount = std::clamp(amount, 0.0f, 1.0f);
    auto channel = [amount](unsigned char a, unsigned char b) {
        return static_cast<unsigned char>(a + (b - a) * amount);
    };
    return {channel(from.r, to.r), channel(from.g, to.g), channel(from.b, to.b), 255};
}

Color SkyTransition::colorAt(float timeOfDay, float fullCycleSeconds) {
    if (fullCycleSeconds <= 0.0f) fullCycleSeconds = 1440.0f;
    float t = std::fmod(timeOfDay, fullCycleSeconds);
    if (t < 0.0f) t += fullCycleSeconds;
    const Color midnight{9, 14, 35}, sunrise{224, 122, 74}, noon{92, 181, 238}, sunset{190, 64, 65};
    float phase = t / fullCycleSeconds;
    if (phase < 0.25f) return blend(midnight, sunrise, phase / 0.25f);
    if (phase < 0.50f) return blend(sunrise, noon, (phase - 0.25f) / 0.25f);
    if (phase < 0.75f) return blend(noon, sunset, (phase - 0.50f) / 0.25f);
    return blend(sunset, midnight, (phase - 0.75f) / 0.25f);
}
