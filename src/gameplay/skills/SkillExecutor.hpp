#pragma once
#include "gameplay/skills/SkillRegistry.hpp"
#include <unordered_map>
#include <string>

enum class HotbarSlot {
    Q,
    E,
    R,
    F
};

enum class CastFailReason {
    None,
    EmptySlot,
    SkillNotFound,
    OnCooldown,
    InsufficientResource
};

struct CastResult {
    bool success{false};
    CastFailReason failReason{CastFailReason::None};
    float damageOutput{0.0f};
};

class SkillExecutor {
public:
    explicit SkillExecutor(const SkillRegistry& registry);

    void assignHotbar(HotbarSlot slot, const std::string& skillId);
    void update(float dt);

    CastResult tryCast(HotbarSlot slot, float& playerStamina, float& playerMana, float& playerPower);
    bool isOnCooldown(HotbarSlot slot) const;
    float getCooldownRemaining(HotbarSlot slot) const;

private:
    const SkillRegistry& m_registry;
    std::unordered_map<HotbarSlot, std::string> m_hotbar;
    std::unordered_map<HotbarSlot, float> m_cooldownTimers;
};
