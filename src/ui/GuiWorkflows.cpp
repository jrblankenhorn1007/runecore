#include "ui/GuiWorkflows.hpp"
#include <algorithm>

namespace {
bool categoryMatches(CraftingCategory category, const CraftingRecipe& recipe) {
    if (category == CraftingCategory::All) return true;
    switch (category) {
    case CraftingCategory::Weapons: return recipe.category == ItemCategory::Weapon;
    case CraftingCategory::Armor: return recipe.category == ItemCategory::Armor;
    case CraftingCategory::Bionics: return recipe.category == ItemCategory::Augmentation;
    case CraftingCategory::Alchemy:
    case CraftingCategory::Cooking: return recipe.category == ItemCategory::Consumable;
    case CraftingCategory::Structures: return recipe.category == ItemCategory::Tool;
    case CraftingCategory::Materials: return recipe.category == ItemCategory::Material;
    case CraftingCategory::All: break;
    }
    return false;
}
}

bool GuiWorkflows::beginInventoryDrag(const Inventory& inventory, int slot) {
    if (slot < 0 || slot >= inventory.getSlotCount() || !inventory.getSlot(slot).has_value()) return false;
    m_draggedSlot = slot;
    return true;
}

bool GuiWorkflows::dropInventory(const Inventory&, Inventory& target, int slot) {
    if (m_draggedSlot < 0) return false;
    const bool moved = target.moveSlot(m_draggedSlot, slot);
    if (moved) m_draggedSlot = -1;
    return moved;
}

bool GuiWorkflows::dropEquipment(Inventory& inventory, EquipSlot slot) {
    if (m_draggedSlot < 0) return false;
    const bool equipped = inventory.equipItem(slot, m_draggedSlot);
    if (equipped) m_draggedSlot = -1;
    return equipped;
}

bool GuiWorkflows::useInventoryItem(Inventory& inventory, int slot) {
    return inventory.consumeSlot(slot);
}

std::optional<InventoryTooltip> GuiWorkflows::inventoryTooltip(const Inventory& inventory, int slot) const {
    const auto item = inventory.getSlot(slot);
    if (!item.has_value()) return std::nullopt;
    return InventoryTooltip{item->name, item->rarity, item->tier, item->quality,
                             item->category == ItemCategory::Consumable};
}

std::vector<std::string> GuiWorkflows::visibleRecipes(const CraftingEngine& crafting,
                                                       const Inventory& inventory,
                                                       CraftingStation station) const {
    std::vector<std::string> result;
    for (const auto& id : crafting.getRecipeIds()) {
        const auto* recipe = crafting.getRecipe(id);
        if (recipe == nullptr || !categoryMatches(m_craftingCategory, *recipe)) continue;
        const CraftingStation effectiveStation =
            station == CraftingStation::None ? recipe->station : station;
        if (m_craftableOnly && !crafting.canCraft(id, inventory, effectiveStation)) continue;
        result.push_back(id);
    }
    return result;
}

bool GuiWorkflows::craftSelected(CraftingEngine& crafting, Inventory& inventory,
                                 const std::string& recipeId, CraftingStation station) const {
    const auto visible = visibleRecipes(crafting, inventory, station);
    if (std::find(visible.begin(), visible.end(), recipeId) == visible.end()) return false;
    const auto* recipe = crafting.getRecipe(recipeId);
    const CraftingStation effectiveStation =
        station == CraftingStation::None && recipe != nullptr ? recipe->station : station;
    return crafting.craft(recipeId, inventory, effectiveStation);
}

bool GuiWorkflows::requestAugmentationInstall(AugmentSlot slot, const AugmentDef& augment) {
    if (augment.slot != slot) return false;
    m_pendingAugmentation = std::make_pair(slot, augment);
    return true;
}

bool GuiWorkflows::confirmAugmentationInstall(AugmentationMatrix& matrix) {
    if (!m_pendingAugmentation.has_value()) return false;
    const auto [slot, augment] = *m_pendingAugmentation;
    if (!matrix.install(slot, augment)) return false;
    m_pendingAugmentation.reset();
    return true;
}

float GuiWorkflows::humanityMeter(const AugmentationMatrix& matrix) const {
    return std::clamp(matrix.getTotalHumanityStrain() / 100.0f, 0.0f, 1.0f);
}

float GuiWorkflows::powerMeter(const AugmentationMatrix& matrix) const {
    return std::clamp((matrix.getNetPowerGeneration() + 100.0f) / 200.0f, 0.0f, 1.0f);
}

Attributes GuiWorkflows::characterAttributes(const Progression& progression) const {
    Attributes attrs;
    attrs.strength = progression.getAttribute(Progression::Attribute::Strength);
    attrs.dexterity = progression.getAttribute(Progression::Attribute::Dexterity);
    attrs.intelligence = progression.getAttribute(Progression::Attribute::Intelligence);
    attrs.vitality = progression.getAttribute(Progression::Attribute::Vitality);
    attrs.wisdom = progression.getAttribute(Progression::Attribute::Wisdom);
    attrs.cybernetics = progression.getAttribute(Progression::Attribute::Cybernetics);
    return attrs;
}

DerivedStats GuiWorkflows::characterDerivedStats(const Progression& progression) const {
    return StatsSystem::calculateDerivedStats(characterAttributes(progression));
}

bool GuiWorkflows::hoverSkill(const SkillTree& tree, const std::string& nodeId) {
    if (tree.getNodes().find(nodeId) == tree.getNodes().end()) return false;
    m_hoveredSkill = nodeId;
    return true;
}

const SkillNode* GuiWorkflows::hoveredSkill(const SkillTree& tree) const {
    if (m_hoveredSkill.empty()) return nullptr;
    const auto it = tree.getNodes().find(m_hoveredSkill);
    return it == tree.getNodes().end() ? nullptr : &it->second;
}

bool GuiWorkflows::requestSkillAllocation(const SkillTree& tree, const std::string& nodeId) {
    if (!tree.canAllocate(nodeId)) return false;
    m_pendingSkill = nodeId;
    return true;
}

bool GuiWorkflows::confirmSkillAllocation(SkillTree& tree, Progression& progression) {
    if (!m_pendingSkill.has_value()) return false;
    if (progression.getSkillPoints() <= 0 || !tree.canAllocate(*m_pendingSkill)) return false;
    const bool allocated = tree.allocate(*m_pendingSkill);
    if (allocated && progression.spendSkillPoints(1)) {
        m_pendingSkill.reset();
        return true;
    }
    return false;
}
