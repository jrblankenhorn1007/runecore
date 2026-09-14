#pragma once
#include <string>
#include <unordered_map>

enum class ResourceCostType {
    Stamina,
    Mana,
    Power
};

struct SkillDefinition {
    std::string id;
    std::string name;
    std::string description;
    ResourceCostType resourceType{ResourceCostType::Stamina};
    float resourceCost{10.0f};
    float baseCooldown{5.0f};
    float baseDamage{50.0f};
    float range{5.0f};
    bool isAoE{false};
};

class SkillRegistry {
public:
    void registerSkill(const SkillDefinition& def);
    const SkillDefinition* getSkill(const std::string& id) const;

private:
    std::unordered_map<std::string, SkillDefinition> m_skills;
};
