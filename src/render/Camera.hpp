#pragma once
#include "core/Math.hpp"

struct CanvasMetrics {
    int windowWidth{1280};
    int windowHeight{720};
    int virtualWidth{640};
    int virtualHeight{360};
    int integerScale{3};
    int viewportWidth{1920};
    int viewportHeight{1080};
    int letterboxX{0};
    int letterboxY{0};
};

class Camera {
public:
    static CanvasMetrics calculateCanvasMetrics(int windowW, int windowH);

    void setPosition(const Vec2& pos) { m_position = pos; }
    Vec2 getPosition() const { return m_position; }
    Vec2 getSnappedPosition() const;

    void addShake(float trauma, float duration);
    void update(float dt);
    bool isShaking() const { return m_shakeTimer > 0.0f; }
    float getShakeTrauma() const { return m_shakeTrauma; }

private:
    Vec2 m_position{0.0f, 0.0f};
    float m_shakeTrauma{0.0f};
    float m_shakeTimer{0.0f};
};
