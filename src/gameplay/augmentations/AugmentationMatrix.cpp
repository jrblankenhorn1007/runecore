#include "gameplay/augmentations/AugmentationMatrix.hpp"

AugmentationMatrix::AugmentationMatrix() = default;

bool AugmentationMatrix::install(AugmentSlot slot, const AugmentDef& def) {
    if (def.slot != slot) {
        return false; // Slot mismatch
    }
    m_slots[slot] = def;
    return true;
}

bool AugmentationMatrix::installSignature(const AugmentDef& def, ClassType playerClass, int playerLevel) {
    if (!def.isSignature || playerLevel < 20) {
        return false;
    }

    AugmentDef toInstall = def;
    // Cross-class surgery penalty: 50% more humanity strain
    if (def.signatureClass != playerClass) {
        toInstall.humanityStrain *= 1.5f;
    }

    return install(def.slot, toInstall);
}

bool AugmentationMatrix::uninstall(AugmentSlot slot) {
    auto it = m_slots.find(slot);
    if (it != m_slots.end()) {
        m_slots.erase(it);
        return true;
    }
    return false;
}

const AugmentDef* AugmentationMatrix::getAugment(AugmentSlot slot) const {
    auto it = m_slots.find(slot);
    if (it != m_slots.end()) {
        return &it->second;
    }
    return nullptr;
}

float AugmentationMatrix::getNetPowerGeneration() const {
    float net = 0.0f;
    for (const auto& [slot, aug] : m_slots) {
        net += (aug.powerGeneration - aug.powerUpkeep);
    }
    return net;
}

float AugmentationMatrix::getTotalHumanityStrain() const {
    float total = 0.0f;
    for (const auto& [slot, aug] : m_slots) {
        total += aug.humanityStrain;
    }
    return total;
}

float AugmentationMatrix::getTotalManaUpkeep() const {
    float total = 0.0f;
    for (const auto& [slot, aug] : m_slots) {
        total += aug.manaUpkeep;
    }
    return total;
}

float AugmentationMatrix::getTotalRejectionRisk() const {
    float total = 0.0f;
    for (const auto& [slot, aug] : m_slots) {
        total += aug.rejectionRisk;
    }
    return total;
}
