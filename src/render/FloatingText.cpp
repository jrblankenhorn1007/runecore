#include "render/FloatingText.hpp"
#include <cmath>
#include <algorithm>

FloatingTextSystem::FloatingTextSystem(size_t maxCount) {
    m_texts.resize(maxCount);
}

void FloatingTextSystem::spawnText(const Vec2& position, const std::string& text, Color color, float lifetime, bool isCrit) {
    // Find free slot or steal oldest
    FloatingText* targetSlot = nullptr;
    float lowestLifetime = 999.0f;

    for (auto& ft : m_texts) {
        if (!ft.active) {
            targetSlot = &ft;
            break;
        }
        if (ft.lifetime < lowestLifetime) {
            lowestLifetime = ft.lifetime;
            targetSlot = &ft;
        }
    }

    if (targetSlot) {
        targetSlot->position = position;
        targetSlot->velocity = Vec2{0.0f, isCrit ? -65.0f : -40.0f};
        targetSlot->text = text;
        targetSlot->color = color;
        targetSlot->lifetime = lifetime;
        targetSlot->maxLifetime = lifetime;
        targetSlot->scale = isCrit ? 1.4f : 1.0f;
        targetSlot->isCrit = isCrit;
        targetSlot->active = true;
    }
}

void FloatingTextSystem::spawnDamage(const Vec2& position, float damage, bool isCrit, DamageType type) {
    int intDmg = static_cast<int>(std::round(damage));
    std::string str = isCrit ? ("CRIT! " + std::to_string(intDmg)) : std::to_string(intDmg);
    Color col{255, 255, 255, 255};
    if (isCrit) {
        col = Color{255, 230, 40, 255};
    } else if (type == DamageType::Fire) {
        col = Color{255, 145, 45, 255};
    } else if (type == DamageType::Frost) {
        col = Color{70, 220, 255, 255};
    }
    spawnText(position, str, col, isCrit ? 1.2f : 0.9f, isCrit);
}

void FloatingTextSystem::spawnHeal(const Vec2& position, float amount) {
    int intHeal = static_cast<int>(std::round(amount));
    std::string str = "+" + std::to_string(intHeal) + " HP";
    spawnText(position, str, Color{60, 240, 90, 255}, 1.0f, false);
}

void FloatingTextSystem::spawnXP(const Vec2& position, int xp) {
    std::string str = "+" + std::to_string(xp) + " XP";
    spawnText(position, str, Color{190, 80, 255, 255}, 1.1f, false);
}

void FloatingTextSystem::update(float dt) {
    for (auto& ft : m_texts) {
        if (!ft.active) continue;

        ft.lifetime -= dt;
        if (ft.lifetime <= 0.0f) {
            ft.active = false;
            continue;
        }

        // Upward motion with gravity deceleration
        ft.velocity.y += 30.0f * dt;
        ft.position += ft.velocity * dt;

        // Fade alpha in last 60% of lifetime
        float progress = ft.lifetime / ft.maxLifetime;
        if (progress < 0.6f) {
            ft.color.a = static_cast<uint8_t>(std::clamp((progress / 0.6f) * 255.0f, 0.0f, 255.0f));
        }
    }
}

void FloatingTextSystem::clear() {
    for (auto& ft : m_texts) {
        ft.active = false;
    }
}

size_t FloatingTextSystem::getActiveCount() const {
    size_t count = 0;
    for (const auto& ft : m_texts) {
        if (ft.active) count++;
    }
    return count;
}
