#include "gameplay/crafting/CraftingEngine.hpp"

void CraftingEngine::registerRecipe(const CraftingRecipe& recipe) {
    m_recipes[recipe.id] = recipe;
}

const CraftingRecipe* CraftingEngine::getRecipe(const std::string& id) const {
    auto it = m_recipes.find(id);
    if (it != m_recipes.end()) {
        return &it->second;
    }
    return nullptr;
}

bool CraftingEngine::canCraft(const std::string& recipeId, const Inventory& inv, CraftingStation currentStation) const {
    const auto* rcp = getRecipe(recipeId);
    if (!rcp) return false;
    if (rcp->station != currentStation && rcp->station != CraftingStation::None) {
        return false;
    }

    for (const auto& ing : rcp->ingredients) {
        if (!inv.hasItem(ing.itemId, ing.quantity)) {
            return false;
        }
    }
    return true;
}

bool CraftingEngine::craft(const std::string& recipeId, Inventory& inv, CraftingStation currentStation) {
    if (!canCraft(recipeId, inv, currentStation)) return false;

    const auto* rcp = getRecipe(recipeId);

    // Deduct ingredients
    for (const auto& ing : rcp->ingredients) {
        inv.removeItem(ing.itemId, ing.quantity);
    }

    // Add crafted output
    Item output;
    output.id = rcp->outputItemId;
    output.name = rcp->name;
    output.quantity = rcp->outputQuantity;
    output.stackable = false;

    return inv.addItem(output);
}
