#pragma once
#include "gameplay/stats/StatsSystem.hpp"
#include <string>
#include <vector>
#include <unordered_map>

enum class ClassType {
    Juggernaut,
    Berserker,
    Gunslinger,
    Phantom,
    Technomancer,
    Medic,
    Symbiote,
    Warden,
    Reanimator
};

struct ClassDefinition {
    ClassType type;
    std::string name;
    std::string description;
    Attributes baseAttributes;
    std::string primaryWeaponType;
    std::string signatureAugmentName;
    std::string resourceName; // e.g. "Kinetic Impact Charge", "Rage", "Focus", etc.
};

class ClassRegistry {
public:
    ClassRegistry();

    const ClassDefinition& getClass(ClassType type) const;
    const std::vector<ClassDefinition>& getAllClasses() const { return m_classList; }

private:
    void registerClasses();

    std::unordered_map<ClassType, ClassDefinition> m_classes;
    std::vector<ClassDefinition> m_classList;
};
