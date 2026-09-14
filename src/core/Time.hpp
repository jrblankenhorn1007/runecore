#pragma once

#include <chrono>

namespace rpg {

class Time {
public:
    static constexpr float FIXED_TIMESTEP = 1.0f / 60.0f;

    void update() {
        auto now = std::chrono::steady_clock::now();
        std::chrono::duration<float> elapsed = now - m_lastFrameTime;
        m_lastFrameTime = now;

        m_deltaTime = elapsed.count();
        if (m_deltaTime > 0.25f) {
            m_deltaTime = 0.25f; // Clamp spiral of death
        }

        m_accumulator += m_deltaTime;
        m_totalTime += m_deltaTime;
        m_frameCount++;
    }

    bool checkFixedStep() {
        if (m_accumulator >= FIXED_TIMESTEP) {
            m_accumulator -= FIXED_TIMESTEP;
            return true;
        }
        return false;
    }

    float getAlpha() const {
        return m_accumulator / FIXED_TIMESTEP;
    }

    float getDeltaTime() const { return m_deltaTime; }
    float getTotalTime() const { return m_totalTime; }
    uint64_t getFrameCount() const { return m_frameCount; }

private:
    std::chrono::steady_clock::time_point m_lastFrameTime = std::chrono::steady_clock::now();
    float m_deltaTime = 0.0f;
    float m_accumulator = 0.0f;
    float m_totalTime = 0.0f;
    uint64_t m_frameCount = 0;
};

} // namespace rpg
