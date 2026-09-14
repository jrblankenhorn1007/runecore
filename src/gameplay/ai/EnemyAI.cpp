#include "gameplay/ai/EnemyAI.hpp"
#include <algorithm>

EnemyAI::EnemyAI() = default;

AIAction EnemyAI::update(
    const Vec2& enemyPos,
    const Vec2& playerPos,
    float currentHealth,
    float maxHealth,
    const AIConfig& config,
    float dt
) {
    AIAction action;
    if (m_attackCooldownTimer > 0.0f) {
        m_attackCooldownTimer = std::max(0.0f, m_attackCooldownTimer - dt);
    }

    float distToPlayer = enemyPos.distanceTo(playerPos);
    float healthRatio = (maxHealth > 0.0f) ? (currentHealth / maxHealth) : 1.0f;

    // Check Flee state
    if (healthRatio <= config.fleeHealthThreshold) {
        m_state = AIState::Flee;
        action.type = AIActionType::Move;
        action.moveDirection = (enemyPos - playerPos).normalized();
        return action;
    }

    // Check Attack state
    if (distToPlayer <= config.attackRange) {
        m_state = AIState::Attack;
        if (m_attackCooldownTimer <= 0.0f) {
            action.type = AIActionType::Attack;
            action.attackTriggered = true;
            m_attackCooldownTimer = config.attackCooldown;
        } else {
            action.type = AIActionType::None;
        }
        return action;
    }

    // Check Chase state
    if (distToPlayer <= config.sightRadius) {
        m_state = AIState::Chase;
        action.type = AIActionType::Move;
        action.moveDirection = (playerPos - enemyPos).normalized();
        return action;
    }

    // Default: Patrol
    m_state = AIState::Patrol;
    m_patrolTimer += dt;
    if (m_patrolTimer >= 2.0f) {
        m_patrolTimer = 0.0f;
        m_patrolDir = -m_patrolDir;
    }

    action.type = AIActionType::Move;
    action.moveDirection = Vec2{static_cast<float>(m_patrolDir), 0.0f};
    return action;
}
