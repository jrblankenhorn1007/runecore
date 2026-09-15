#include "gameplay/ai/EnemyRoster.hpp"

EnemyProfile EnemyRoster::profile(EnemyType type) {
    switch (type) {
    case EnemyType::Bat: return {type, EnemyBehavior::Swoop, 28.0f, 85.0f, 1.4f, false, false, false, false};
    case EnemyType::Raptor: return {type, EnemyBehavior::Pounce, 30.0f, 120.0f, 1.1f, false, false, false, true};
    case EnemyType::CyberGunner: return {type, EnemyBehavior::Volley, 150.0f, 45.0f, 2.0f, false, false, true, false};
    case EnemyType::Harpy: return {type, EnemyBehavior::Swoop, 36.0f, 95.0f, 1.6f, false, false, false, false};
    case EnemyType::Carapace: return {type, EnemyBehavior::Guard, 24.0f, 30.0f, 1.8f, true, false, false, false};
    case EnemyType::Slime: default: return {EnemyType::Slime, EnemyBehavior::Hop, 26.0f, 42.0f, 1.2f, false, true, false, false};
    }
}

EnemyAction EnemyRoster::update(const EnemyProfile& p, const Vec2& enemy, const Vec2& player,
                                float distance, float cooldownRemaining) {
    EnemyAction action;
    action.behavior = p.behavior;
    Vec2 toward = (player - enemy).normalized();
    if (p.behavior == EnemyBehavior::Volley && distance < p.preferredRange * 0.65f) {
        action.movement = -toward;
        action.retreat = true;
    } else if (p.behavior == EnemyBehavior::Swoop && distance <= p.preferredRange) {
        action.movement = toward * 0.25f;
        action.retreat = true;
    } else if (p.behavior == EnemyBehavior::Guard && distance < p.preferredRange) {
        action.movement = toward * 0.35f;
    } else {
        action.movement = toward;
    }
    action.attack = distance <= p.preferredRange && cooldownRemaining <= 0.0f;
    action.pin = action.attack && p.canPin;
    return action;
}
