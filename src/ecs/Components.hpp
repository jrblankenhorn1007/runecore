#pragma once
#include "core/Math.hpp"
#include <entt/entt.hpp>
#include <vector>
#include <string>
#include <algorithm>

struct TransformComponent {
    Vec2 position{0.0f, 0.0f};
    Vec2 scale{1.0f, 1.0f};
    float rotation{0.0f};

    TransformComponent() = default;
    TransformComponent(const Vec2& pos) : position(pos) {}
    TransformComponent(const Vec2& pos, const Vec2& scl, float rot)
        : position(pos), scale(scl), rotation(rot) {}
};

struct VelocityComponent {
    Vec2 linear{0.0f, 0.0f};
    float maxSpeed{200.0f};

    VelocityComponent() = default;
    VelocityComponent(const Vec2& lin) : linear(lin) {}
    VelocityComponent(const Vec2& lin, float maxSpd) : linear(lin), maxSpeed(maxSpd) {}
};

struct ColliderComponent {
    Rect aabb{-8.0f, -8.0f, 16.0f, 16.0f}; // relative to transform
    bool isTrigger{false};
    uint16_t categoryBits{1};
    uint16_t maskBits{0xFFFF};

    ColliderComponent() = default;
    ColliderComponent(const Rect& box, bool trigger = false)
        : aabb(box), isTrigger(trigger) {}
};

struct HealthComponent {
    float current{100.0f};
    float max{100.0f};
    float regenRate{0.5f}; // HP per second
    bool isDead{false};
    float invulnTimer{0.0f};

    HealthComponent() = default;
    HealthComponent(float cur, float maxHp, float regen = 0.5f)
        : current(cur), max(maxHp), regenRate(regen), isDead(cur <= 0.0f) {}

    void takeDamage(float amount) {
        if (amount <= 0.0f || isDead) return;
        current = std::max(0.0f, current - amount);
        if (current <= 0.0f) {
            isDead = true;
        }
    }

    void heal(float amount) {
        if (amount <= 0.0f) return;
        current = std::min(max, current + amount);
        if (current > 0.0f) {
            isDead = false;
        }
    }

    void update(float dt) {
        if (invulnTimer > 0.0f) {
            invulnTimer = std::max(0.0f, invulnTimer - dt);
        }
        if (!isDead && regenRate > 0.0f && current < max) {
            heal(regenRate * dt);
        }
    }
};

struct ManaComponent {
    float current{50.0f};
    float max{50.0f};
    float regenRate{1.0f}; // MP per second

    ManaComponent() = default;
    ManaComponent(float cur, float maxMp, float regen = 1.0f)
        : current(cur), max(maxMp), regenRate(regen) {}

    bool consume(float amount) {
        if (amount < 0.0f) return false;
        if (current >= amount) {
            current -= amount;
            return true;
        }
        return false;
    }

    void restore(float amount) {
        if (amount <= 0.0f) return;
        current = std::min(max, current + amount);
    }

    void update(float dt) {
        if (regenRate > 0.0f && current < max) {
            restore(regenRate * dt);
        }
    }
};

struct PowerComponent {
    float current{0.0f};
    float max{100.0f};
    float regenRate{0.0f}; // Passive bionic power regen

    PowerComponent() = default;
    PowerComponent(float cur, float maxPwr, float regen = 0.0f)
        : current(cur), max(maxPwr), regenRate(regen) {}

    bool consume(float amount) {
        if (amount < 0.0f) return false;
        if (current >= amount) {
            current -= amount;
            return true;
        }
        return false;
    }

    void charge(float amount) {
        if (amount <= 0.0f) return;
        current = std::min(max, current + amount);
    }

    void update(float dt) {
        if (regenRate > 0.0f && current < max) {
            charge(regenRate * dt);
        }
    }
};

struct StatsComponent {
    int strength{10};
    int dexterity{10};
    int intelligence{10};
    int vitality{10};
    int wisdom{10};
    int cybernetics{10};

    float physicalArmor{0.0f};
    float energyArmor{0.0f};
    float moveSpeedMultiplier{1.0f};
    float attackSpeedMultiplier{1.0f};
    float critChance{0.05f};
    float critMultiplier{1.5f};
};

struct PlayerTag {};

struct EnemyTag {
    int tier{1};
    int xpReward{50};

    EnemyTag() = default;
    EnemyTag(int t, int xp) : tier(t), xpReward(xp) {}
};

struct ProjectileComponent {
    float damage{10.0f};
    float lifetime{3.0f};
    bool penetrates{false};
    int maxPierces{0};
    int pierceCount{0};
    entt::entity owner{entt::null};
};

struct ActiveStatusEffect {
    int type{0}; // Enum for Bleed, Poison, Burn, etc.
    float duration{0.0f};
    float tickTimer{0.0f};
    float tickInterval{1.0f};
    float damagePerTick{0.0f};
    float potency{1.0f};
};

struct StatusEffectsComponent {
    std::vector<ActiveStatusEffect> effects;
};
