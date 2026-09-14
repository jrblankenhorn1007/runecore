#pragma once
#include "gameplay/items/Inventory.hpp"
#include <string>
#include <vector>
#include <unordered_map>

enum class CraftingStation {
    None,
    Workbench,
    FoundryForge,
    CyberClinic,
    ArcaneLoom,
    KitchenStove,
    HydroponicsLab
};

struct Ingredient {
    std::string itemId;
    int quantity{1};
};

struct CraftingRecipe {
    std::string id;
    std::string name;
    CraftingStation station{CraftingStation::Workbench};
    std::vector<Ingredient> ingredients;
    std::string outputItemId;
    int outputQuantity{1};
    ItemCategory category{ItemCategory::Material};
};

class CraftingEngine {
public:
    void registerRecipe(const CraftingRecipe& recipe);
    const CraftingRecipe* getRecipe(const std::string& id) const;
    std::vector<std::string> getRecipeIds() const;

    bool canCraft(const std::string& recipeId, const Inventory& inv, CraftingStation currentStation) const;
    bool craft(const std::string& recipeId, Inventory& inv, CraftingStation currentStation);

private:
    std::unordered_map<std::string, CraftingRecipe> m_recipes;
};
