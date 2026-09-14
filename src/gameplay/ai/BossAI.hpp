#pragma once
#include "core/Math.hpp"

enum class BossPhase {
    Phase1,
    Phase2
};

struct BossAction {
    Vec2 moveDirection{0.0f, 0.0f};
    bool attackTriggered{false};
    bool triggerPhaseTransitionBlast{false};
};

class BossAI {
public:
    BossAI();

    BossAction update(
        const Vec2& bossPos,
        const Vec2& playerPos,
        float currentHealth,
        float maxHealth,
        float dt
    );

    BossPhase getPhase() const { return m_phase; }
    bool isEnraged() const { return m_phase == BossPhase::Phase2; }
    float getSpeedMultiplier() const { return m_speedMultiplier; }
    float getAttackCooldown() const { return m_attackCooldown; }

private:
    BossPhase m_phase{BossPhase::Phase1};
    float m_speedMultiplier{1.0f};
    float m_attackCooldown{3.0f};
    float m_cooldownTimer{0.0f};
    bool m_phaseTransitionFired{false};
};
