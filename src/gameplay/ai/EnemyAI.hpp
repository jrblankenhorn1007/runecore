#pragma once
#include "core/Math.hpp"

enum class AIState {
    Idle,
    Patrol,
    Chase,
    Attack,
    Flee
};

enum class AIActionType {
    None,
    Move,
    Attack
};

struct AIConfig {
    float sightRadius{150.0f};
    float attackRange{25.0f};
    float attackCooldown{1.5f};
    float patrolDistance{60.0f};
    float fleeHealthThreshold{0.20f};
};

struct AIAction {
    AIActionType type{AIActionType::None};
    Vec2 moveDirection{0.0f, 0.0f};
    bool attackTriggered{false};
};

class EnemyAI {
public:
    EnemyAI();

    AIAction update(
        const Vec2& enemyPos,
        const Vec2& playerPos,
        float currentHealth,
        float maxHealth,
        const AIConfig& config,
        float dt
    );

    AIState getState() const { return m_state; }

private:
    AIState m_state{AIState::Patrol};
    float m_patrolTimer{0.0f};
    int m_patrolDir{1};
    float m_attackCooldownTimer{0.0f};
};
