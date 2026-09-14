#pragma once
#include <string>
#include <vector>
#include "core/Math.hpp"

struct FloatingText {
    Vec2 position{0.0f, 0.0f};
    Vec2 velocity{0.0f, -40.0f};
    std::string text;
    Color color{255, 255, 255, 255};
    float lifetime{1.0f};
    float maxLifetime{1.0f};
    float scale{1.0f};
    bool isCrit{false};
    bool active{false};
};

enum class DamageType {
    Physical,
    Fire,
    Frost
};

class FloatingTextSystem {
public:
    explicit FloatingTextSystem(size_t maxCount = 100);

    void spawnText(const Vec2& position, const std::string& text, Color color, float lifetime = 1.0f, bool isCrit = false);
    void spawnDamage(const Vec2& position, float damage, bool isCrit = false, DamageType type = DamageType::Physical);
    void spawnHeal(const Vec2& position, float amount);
    void spawnXP(const Vec2& position, int xp);

    void update(float dt);
    void clear();

    size_t getActiveCount() const;
    const std::vector<FloatingText>& getTexts() const { return m_texts; }

private:
    std::vector<FloatingText> m_texts;
};
