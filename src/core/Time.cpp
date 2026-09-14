#include "core/Time.hpp"
#include <algorithm>

TimeStep::TimeStep(float targetHz) {
    if (targetHz <= 0.0f) targetHz = 60.0f;
    m_fixedDelta = 1.0f / targetHz;
}

int TimeStep::update(float frameDeltaSeconds) {
    // Clamp delta time to max accumulator to avoid spiral of death
    float clampedDelta = std::min(frameDeltaSeconds, m_maxAccumulator);
    m_accumulator += clampedDelta;
    m_totalTime += clampedDelta;

    int tickCount = 0;
    while (m_accumulator >= m_fixedDelta) {
        m_accumulator -= m_fixedDelta;
        m_ticks++;
        tickCount++;
    }

    m_alpha = m_accumulator / m_fixedDelta;
    return tickCount;
}
