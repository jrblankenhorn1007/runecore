#include "gameplay/ai/BossAI.hpp"
#include <algorithm>

BossAI::BossAI() = default;

BossAction BossAI::update(
    const Vec2& bossPos,
    const Vec2& playerPos,
    float currentHealth,
    float maxHealth,
    float dt
) {
    BossAction action;
    if (m_cooldownTimer > 0.0f) {
        m_cooldownTimer = std::max(0.0f, m_cooldownTimer - dt);
    }

    float healthRatio = (maxHealth > 0.0f) ? (currentHealth / maxHealth) : 1.0f;

    // Check Phase 2 Enrage Trigger at 50% HP
    if (healthRatio <= 0.50f && m_phase == BossPhase::Phase1) {
        m_phase = BossPhase::Phase2;
        m_speedMultiplier = 1.35f;
        m_attackCooldown = 1.5f; // Faster attacks
        if (!m_phaseTransitionFired) {
            action.triggerPhaseTransitionBlast = true;
            m_phaseTransitionFired = true;
        }
    }

    action.moveDirection = (playerPos - bossPos).normalized();

    if (m_cooldownTimer > 0.0f && m_cooldownTimer <= 1.0f) {
        action.telegraphActive = true;
        action.telegraphRadius = m_phase == BossPhase::Phase2 ? 48.0f : 32.0f;
    }

    if (m_cooldownTimer <= 0.0f) {
        action.attackTriggered = true;
        m_cooldownTimer = m_attackCooldown;
    }

    return action;
}
