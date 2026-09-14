#include "gameplay/skills/SkillRegistry.hpp"

void SkillRegistry::registerSkill(const SkillDefinition& def) {
    m_skills[def.id] = def;
}

const SkillDefinition* SkillRegistry::getSkill(const std::string& id) const {
    auto it = m_skills.find(id);
    if (it != m_skills.end()) {
        return &it->second;
    }
    return nullptr;
}
