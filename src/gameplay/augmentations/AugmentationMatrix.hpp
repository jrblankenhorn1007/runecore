#pragma once
#include "gameplay/classes/ClassRegistry.hpp"
#include <string>
#include <unordered_map>
#include <optional>

enum class AugmentSlot {
    Head,
    Eyes,
    Nervous,
    Lungs,
    Heart,
    Torso,
    Skin,
    LeftArm,
    RightArm,
    Hands,
    Legs
};

enum class AugmentType {
    Bionic,
    Magitech,
    Chimeric
};

struct AugmentDef {
    std::string id;
    std::string name;
    AugmentSlot slot{AugmentSlot::Head};
    AugmentType type{AugmentType::Bionic};

    float powerGeneration{0.0f};
    float powerUpkeep{0.0f};
    float humanityStrain{0.0f};

    float manaUpkeep{0.0f};
    float rejectionRisk{0.0f};

    float flatCritChanceBonus{0.0f};
    float flatArmorBonus{0.0f};
    float flatHealthBonus{0.0f};

    bool isSignature{false};
    ClassType signatureClass{ClassType::Juggernaut};
};

class AugmentationMatrix {
public:
    AugmentationMatrix();

    bool install(AugmentSlot slot, const AugmentDef& def);
    bool installSignature(const AugmentDef& def, ClassType playerClass, int playerLevel);
    bool uninstall(AugmentSlot slot);

    const AugmentDef* getAugment(AugmentSlot slot) const;

    float getNetPowerGeneration() const;
    float getTotalHumanityStrain() const;
    float getTotalManaUpkeep() const;
    float getTotalRejectionRisk() const;

    const std::unordered_map<AugmentSlot, AugmentDef>& getAllInstalled() const { return m_slots; }

private:
    std::unordered_map<AugmentSlot, AugmentDef> m_slots;
};
