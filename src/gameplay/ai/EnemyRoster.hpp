#pragma once
#include "core/Math.hpp"
#include "ecs/Components.hpp"

enum class EnemyBehavior {
    Hop,
    Swoop,
    Pounce,
    Volley,
    Guard
};

struct EnemyProfile {
    EnemyType type{EnemyType::Slime};
    EnemyBehavior behavior{EnemyBehavior::Hop};
    float preferredRange{24.0f};
    float moveSpeed{50.0f};
    float cooldown{1.0f};
    bool frontalShield{false};
};

struct EnemyAction {
    EnemyBehavior behavior{EnemyBehavior::Hop};
    Vec2 movement{0.0f, 0.0f};
    bool attack{false};
    bool retreat{false};
};

class EnemyRoster {
public:
    static EnemyProfile profile(EnemyType type);
    static EnemyAction update(const EnemyProfile& profile, const Vec2& enemy, const Vec2& player,
                              float distance, float cooldownRemaining);
};
