#pragma once
#include <cstdint>

class TimeStep {
public:
    explicit TimeStep(float targetHz = 60.0f);

    int update(float frameDeltaSeconds);

    float getFixedDelta() const { return m_fixedDelta; }
    float getAlpha() const { return m_alpha; }
    uint64_t getTicks() const { return m_ticks; }
    float getTotalTime() const { return m_totalTime; }

private:
    float m_fixedDelta{1.0f / 60.0f};
    float m_accumulator{0.0f};
    float m_alpha{0.0f};
    float m_maxAccumulator{10.0f / 60.0f}; // clamps to max 10 frames
    uint64_t m_ticks{0};
    float m_totalTime{0.0f};
};
