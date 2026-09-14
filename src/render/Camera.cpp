#include "render/Camera.hpp"
#include <cmath>
#include <algorithm>

CanvasMetrics Camera::calculateCanvasMetrics(int windowW, int windowH) {
    CanvasMetrics m;
    m.windowWidth = windowW;
    m.windowHeight = windowH;
    m.virtualHeight = 360;

    float aspect = static_cast<float>(windowW) / static_cast<float>(windowH);
    // Standard virtual width: e.g. 16:9 -> 640, 16:10 -> 576
    m.virtualWidth = static_cast<int>(std::round(360.0f * aspect));

    // Calculate maximum integer scale that fits inside window
    int scaleH = windowH / m.virtualHeight;
    int scaleW = windowW / m.virtualWidth;
    m.integerScale = std::max(1, std::min(scaleH, scaleW));

    m.viewportWidth = m.virtualWidth * m.integerScale;
    m.viewportHeight = m.virtualHeight * m.integerScale;

    m.letterboxX = (windowW - m.viewportWidth) / 2;
    m.letterboxY = (windowH - m.viewportHeight) / 2;

    return m;
}

Vec2 Camera::getSnappedPosition() const {
    return Vec2{
        std::round(m_position.x),
        std::round(m_position.y)
    };
}

void Camera::addShake(float trauma, float duration) {
    m_shakeTrauma = trauma;
    m_shakeTimer = duration;
}

void Camera::update(float dt) {
    if (m_shakeTimer > 0.0f) {
        m_shakeTimer = std::max(0.0f, m_shakeTimer - dt);
        if (m_shakeTimer <= 0.0f) {
            m_shakeTrauma = 0.0f;
        }
    }
}
