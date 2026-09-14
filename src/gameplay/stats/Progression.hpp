#pragma once
#include <cstdint>

class Progression {
public:
    enum class Attribute {
        Strength,
        Dexterity,
        Intelligence,
        Vitality,
        Wisdom,
        Cybernetics,
        Count
    };

    Progression();

    int getLevel() const { return m_level; }
    uint64_t getCurrentXP() const { return m_currentXP; }
    float getXPForNextLevel() const;

    void addXP(uint64_t amount);
    void setLevel(int level);

    int getAttributePoints() const { return m_attributePoints; }
    int getSkillPoints() const { return m_skillPoints; }

    bool spendAttributePoints(int count);
    bool allocateAttribute(Attribute attribute);
    int getAttribute(Attribute attribute) const;
    bool spendSkillPoints(int count);

    bool isCrossClassUnlocked() const { return m_level >= 60; }

private:
    void checkLevelUp();

    int m_level{1};
    uint64_t m_currentXP{0};
    int m_attributePoints{0};
    int m_skillPoints{0};
    int m_attributes[static_cast<int>(Attribute::Count)]{10, 10, 10, 10, 10, 10};
};
