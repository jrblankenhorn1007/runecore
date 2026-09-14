#include "gameplay/stats/Progression.hpp"
#include <cmath>

Progression::Progression() = default;

float Progression::getXPForNextLevel() const {
    // XP(L) = 100 * L^1.8
    return 100.0f * std::pow(static_cast<float>(m_level), 1.8f);
}

void Progression::addXP(uint64_t amount) {
    m_currentXP += amount;
    checkLevelUp();
}

void Progression::checkLevelUp() {
    while (true) {
        float req = getXPForNextLevel();
        if (m_currentXP >= static_cast<uint64_t>(req)) {
            m_currentXP -= static_cast<uint64_t>(req);
            m_level++;
            m_attributePoints += 3;
            m_skillPoints += 2; // 1 Class + 1 Shared Point
        } else {
            break;
        }
    }
}

void Progression::setLevel(int level) {
    if (level <= m_level) return;
    int diff = level - m_level;
    m_level = level;
    m_attributePoints += diff * 3;
    m_skillPoints += diff * 2;
}

bool Progression::spendAttributePoints(int count) {
    if (count <= 0 || m_attributePoints < count) return false;
    m_attributePoints -= count;
    return true;
}

bool Progression::spendSkillPoints(int count) {
    if (count <= 0 || m_skillPoints < count) return false;
    m_skillPoints -= count;
    return true;
}
