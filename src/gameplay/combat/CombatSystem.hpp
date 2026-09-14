#pragma once
#include "core/Math.hpp"
#include <entt/entt.hpp>

struct Hitbox {
    Rect bounds;
    float damage{10.0f};
    float knockbackForce{100.0f};
    entt::entity owner{entt::null};
    bool triggersIFrames{true};
    float iFrameDuration{0.25f};
};

class CombatSystem {
public:
    static bool resolveHitbox(entt::registry& registry, const Hitbox& hitbox, entt::entity target);
};
