#include "gameplay/skills/SkillExecutor.hpp"
#include <algorithm>

SkillExecutor::SkillExecutor(const SkillRegistry& registry) : m_registry(registry) {}

void SkillExecutor::assignHotbar(HotbarSlot slot, const std::string& skillId) {
    m_hotbar[slot] = skillId;
    m_cooldownTimers[slot] = 0.0f;
}

void SkillExecutor::update(float dt) {
    for (auto& [slot, timer] : m_cooldownTimers) {
        if (timer > 0.0f) {
            timer = std::max(0.0f, timer - dt);
        }
    }
}

bool SkillExecutor::isOnCooldown(HotbarSlot slot) const {
    auto it = m_cooldownTimers.find(slot);
    if (it != m_cooldownTimers.end()) {
        return it->second > 0.0f;
    }
    return false;
}

float SkillExecutor::getCooldownRemaining(HotbarSlot slot) const {
    auto it = m_cooldownTimers.find(slot);
    if (it != m_cooldownTimers.end()) {
        return it->second;
    }
    return 0.0f;
}

CastResult SkillExecutor::tryCast(HotbarSlot slot, float& playerStamina, float& playerMana, float& playerPower) {
    CastResult res;

    auto it = m_hotbar.find(slot);
    if (it == m_hotbar.end() || it->second.empty()) {
        res.failReason = CastFailReason::EmptySlot;
        return res;
    }

    const auto* skill = m_registry.getSkill(it->second);
    if (!skill) {
        res.failReason = CastFailReason::SkillNotFound;
        return res;
    }

    if (isOnCooldown(slot)) {
        res.failReason = CastFailReason::OnCooldown;
        return res;
    }

    // Check and deduct resources
    switch (skill->resourceType) {
        case ResourceCostType::Stamina:
            if (playerStamina < skill->resourceCost) {
                res.failReason = CastFailReason::InsufficientResource;
                return res;
            }
            playerStamina -= skill->resourceCost;
            break;

        case ResourceCostType::Mana:
            if (playerMana < skill->resourceCost) {
                res.failReason = CastFailReason::InsufficientResource;
                return res;
            }
            playerMana -= skill->resourceCost;
            break;

        case ResourceCostType::Power:
            if (playerPower < skill->resourceCost) {
                res.failReason = CastFailReason::InsufficientResource;
                return res;
            }
            playerPower -= skill->resourceCost;
            break;
    }

    // Start cooldown
    m_cooldownTimers[slot] = skill->baseCooldown;

    res.success = true;
    res.damageOutput = skill->baseDamage;
    return res;
}
