#pragma once

#include "gameplay/augmentations/AugmentationMatrix.hpp"
#include "gameplay/crafting/CraftingEngine.hpp"
#include "gameplay/items/Inventory.hpp"
#include "gameplay/skills/SkillTree.hpp"
#include "gameplay/stats/Progression.hpp"
#include "gameplay/stats/StatsSystem.hpp"
#include <optional>
#include <string>
#include <vector>

enum class CraftingCategory {
    All,
    Weapons,
    Armor,
    Bionics,
    Alchemy,
    Cooking,
    Structures,
    Materials
};

struct InventoryTooltip {
    std::string name;
    ItemRarity rarity{ItemRarity::Common};
    int tier{0};
    float quality{0.0f};
    bool canUse{false};
};

class GuiWorkflows {
public:
    bool beginInventoryDrag(const Inventory& inventory, int slot);
    bool dropInventory(const Inventory& inventory, Inventory& target, int slot);
    bool dropEquipment(Inventory& inventory, EquipSlot slot);
    bool useInventoryItem(Inventory& inventory, int slot);
    int draggedInventorySlot() const { return m_draggedSlot; }
    std::optional<InventoryTooltip> inventoryTooltip(const Inventory& inventory, int slot) const;

    void setCraftingCategory(CraftingCategory category) { m_craftingCategory = category; }
    CraftingCategory getCraftingCategory() const { return m_craftingCategory; }
    void setCraftableOnly(bool enabled) { m_craftableOnly = enabled; }
    bool getCraftableOnly() const { return m_craftableOnly; }
    std::vector<std::string> visibleRecipes(const CraftingEngine& crafting,
                                            const Inventory& inventory,
                                            CraftingStation station) const;
    bool craftSelected(CraftingEngine& crafting, Inventory& inventory,
                       const std::string& recipeId, CraftingStation station) const;

    bool requestAugmentationInstall(AugmentSlot slot, const AugmentDef& augment);
    bool hasPendingAugmentation() const { return m_pendingAugmentation.has_value(); }
    bool confirmAugmentationInstall(AugmentationMatrix& matrix);
    void cancelAugmentationInstall() { m_pendingAugmentation.reset(); }
    float humanityMeter(const AugmentationMatrix& matrix) const;
    float powerMeter(const AugmentationMatrix& matrix) const;

    Attributes characterAttributes(const Progression& progression) const;
    DerivedStats characterDerivedStats(const Progression& progression) const;

    bool hoverSkill(const SkillTree& tree, const std::string& nodeId);
    const SkillNode* hoveredSkill(const SkillTree& tree) const;
    bool requestSkillAllocation(const SkillTree& tree, const std::string& nodeId);
    bool confirmSkillAllocation(SkillTree& tree, Progression& progression);
    int respecSkills(SkillTree& tree) {
        m_pendingSkill.reset();
        m_hoveredSkill.clear();
        return tree.respec();
    }

private:
    int m_draggedSlot{-1};
    CraftingCategory m_craftingCategory{CraftingCategory::All};
    bool m_craftableOnly{false};
    std::optional<std::pair<AugmentSlot, AugmentDef>> m_pendingAugmentation;
    std::string m_hoveredSkill;
    std::optional<std::string> m_pendingSkill;
};
