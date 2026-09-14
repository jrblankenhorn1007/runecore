#include <catch2/catch_test_macros.hpp>
#include "gameplay/crafting/CraftingEngine.hpp"
#include "gameplay/items/Inventory.hpp"

TEST_CASE("CraftingEngine Recipes, Lookups, and Item Fabrication", "[gameplay][crafting]") {
    CraftingEngine ce;

    CraftingRecipe rcp;
    rcp.id = "rcp_pickaxe";
    rcp.name = "Iron Pickaxe";
    rcp.station = CraftingStation::Workbench;
    rcp.ingredients = {{"mat_iron", 4}, {"mat_wood", 2}};
    rcp.outputItemId = "tool_iron_pickaxe";
    rcp.outputQuantity = 1;

    ce.registerRecipe(rcp);

    SECTION("Recipe Lookups") {
        REQUIRE(ce.getRecipe("rcp_pickaxe") != nullptr);
        REQUIRE(ce.getRecipe("unknown") == nullptr);
    }

    SECTION("Crafting Preconditions and Execution") {
        Inventory inv;
        REQUIRE(ce.canCraft("unknown", inv, CraftingStation::Workbench) == false);
        REQUIRE(ce.canCraft("rcp_pickaxe", inv, CraftingStation::FoundryForge) == false); // Wrong station

        // Insufficient materials
        REQUIRE(ce.canCraft("rcp_pickaxe", inv, CraftingStation::Workbench) == false);
        REQUIRE(ce.craft("rcp_pickaxe", inv, CraftingStation::Workbench) == false);

        // Add ingredients
        Item iron; iron.id = "mat_iron"; iron.quantity = 5; iron.stackable = true;
        Item wood; wood.id = "mat_wood"; wood.quantity = 3; wood.stackable = true;
        inv.addItem(iron);
        inv.addItem(wood);

        REQUIRE(ce.canCraft("rcp_pickaxe", inv, CraftingStation::Workbench) == true);
        REQUIRE(ce.craft("rcp_pickaxe", inv, CraftingStation::Workbench) == true);

        REQUIRE(inv.getItemCount("mat_iron") == 1); // 5 - 4
        REQUIRE(inv.getItemCount("mat_wood") == 1); // 3 - 2
        REQUIRE(inv.hasItem("tool_iron_pickaxe") == true);
    }
}
