#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include "gameplay/crafting/CraftingEngine.hpp"
#include "gameplay/crafting/ModificationForge.hpp"
#include "gameplay/items/Inventory.hpp"
#include "core/Random.hpp"

using Catch::Approx;

TEST_CASE("Crafting Recipe Lookups and Material Consumption", "[gameplay][crafting]") {
    CraftingEngine engine;

    CraftingRecipe ironSwordRecipe;
    ironSwordRecipe.id = "rcp_iron_sword";
    ironSwordRecipe.name = "Iron Greatsword";
    ironSwordRecipe.station = CraftingStation::FoundryForge;
    ironSwordRecipe.ingredients = {
        {"mat_iron_ingot", 8},
        {"mat_wood_plank", 2}
    };
    ironSwordRecipe.outputItemId = "item_iron_greatsword";
    ironSwordRecipe.outputQuantity = 1;

    engine.registerRecipe(ironSwordRecipe);

    Inventory inv;
    inv.addItem(Item{"mat_iron_ingot", "Iron Ingot", ItemCategory::Material, EquipSlot::None, ItemRarity::Common, 1, 0.0f, 0.0f, 0.0f, 1.0f, 0.5f, true, 10, 99});
    inv.addItem(Item{"mat_wood_plank", "Wood Plank", ItemCategory::Material, EquipSlot::None, ItemRarity::Common, 1, 0.0f, 0.0f, 0.0f, 1.0f, 0.5f, true, 5, 99});

    SECTION("Can Craft when Materials and Station Match") {
        REQUIRE(engine.canCraft("rcp_iron_sword", inv, CraftingStation::FoundryForge) == true);
        REQUIRE(engine.canCraft("rcp_iron_sword", inv, CraftingStation::Workbench) == false); // Wrong station

        bool success = engine.craft("rcp_iron_sword", inv, CraftingStation::FoundryForge);
        REQUIRE(success == true);

        // Materials deducted: 10 - 8 = 2 iron, 5 - 2 = 3 wood
        REQUIRE(inv.getItemCount("mat_iron_ingot") == 2);
        REQUIRE(inv.getItemCount("mat_wood_plank") == 3);
        REQUIRE(inv.hasItem("item_iron_greatsword") == true);
    }

    SECTION("Fails when Materials are Insufficient") {
        inv.removeItem("mat_iron_ingot", 5); // Now only 5 iron remaining (needs 8)
        REQUIRE(engine.canCraft("rcp_iron_sword", inv, CraftingStation::FoundryForge) == false);
        REQUIRE(engine.craft("rcp_iron_sword", inv, CraftingStation::FoundryForge) == false);
    }
}

TEST_CASE("Modification Forge Deterministic Stat Modification and Fracture Risk", "[gameplay][forge]") {
    Random rng(777);
    ModificationForge forge(rng);

    Item sword;
    sword.id = "test_greatsword";
    sword.name = "Titanium Greatsword";
    sword.category = ItemCategory::Weapon;
    sword.tier = 3;
    sword.baseDamage = 80.0f;
    sword.sockets = 1;

    SECTION("Affix Infusion Adds Affix and Accumulates Instability") {
        Affix fireAffix{"Blazing", true, 3, 0.0f, 0.15f, "Damage"};
        ForgeResult res = forge.infuseAffix(sword, fireAffix);

        REQUIRE(res.success == true);
        REQUIRE(res.isFractured == false);
        REQUIRE(sword.affixes.size() == 1);
        REQUIRE(sword.affixes[0].name == "Blazing");
        REQUIRE(forge.getInstability(sword) == 10);
    }

    SECTION("Tier Upgrading Increases Stats and Tier") {
        ForgeResult res = forge.upgradeTier(sword);
        REQUIRE(res.success == true);
        REQUIRE(sword.tier == 4);
        REQUIRE(sword.baseDamage > 80.0f);
        REQUIRE(forge.getInstability(sword) == 15);
    }

    SECTION("Socket Punching Up to Max 3 Sockets") {
        REQUIRE(sword.sockets == 1);

        forge.punchSocket(sword);
        REQUIRE(sword.sockets == 2);

        forge.punchSocket(sword);
        REQUIRE(sword.sockets == 3);

        ForgeResult maxed = forge.punchSocket(sword);
        REQUIRE(maxed.success == false); // Cannot exceed 3 sockets
        REQUIRE(sword.sockets == 3);
    }

    SECTION("High Instability Triggers Fracture") {
        forge.setInstability(sword, 85); // High risk

        // Try several modifications until fracture occurs or risk evaluated
        bool sawFracture = false;
        for (int i = 0; i < 20; ++i) {
            Affix af{"Sharp", true, 3, 5.0f, 0.0f, "Damage"};
            ForgeResult r = forge.infuseAffix(sword, af);
            if (r.isFractured) {
                sawFracture = true;
                break;
            }
        }
        REQUIRE(sawFracture == true);
        REQUIRE(forge.isFractured(sword) == true);

        // Fractured items reject further forge modifications
        Affix failAffix{"Icy", true, 3, 0.0f, 0.10f, "Damage"};
        ForgeResult rejected = forge.infuseAffix(sword, failAffix);
        REQUIRE(rejected.success == false);
    }
}
