#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>
#include "ui/GuiWorkflows.hpp"

TEST_CASE("GUI inventory workflow supports drag, equipment, tooltips, and use", "[ui][inventory]") {
    Inventory inventory(3);
    Item weapon;
    weapon.id = "blade";
    weapon.name = "Blade";
    weapon.category = ItemCategory::Weapon;
    weapon.equipSlot = EquipSlot::MainHand;
    weapon.rarity = ItemRarity::Rare;
    weapon.tier = 3;
    REQUIRE(inventory.addItem(weapon));

    GuiWorkflows gui;
    REQUIRE(gui.beginInventoryDrag(inventory, 0));
    REQUIRE(gui.dropEquipment(inventory, EquipSlot::MainHand));
    REQUIRE(inventory.getEquipped(EquipSlot::MainHand) != nullptr);

    Item potion;
    potion.id = "potion";
    potion.name = "Potion";
    potion.category = ItemCategory::Consumable;
    potion.stackable = true;
    potion.quantity = 2;
    REQUIRE(inventory.addItem(potion));
    const auto tooltip = gui.inventoryTooltip(inventory, 0);
    REQUIRE(tooltip.has_value());
    REQUIRE(tooltip->canUse);
    REQUIRE(gui.useInventoryItem(inventory, 0));
    REQUIRE(inventory.getLastAction() == "ITEM USED");
}

TEST_CASE("GUI crafting filters recipes and only crafts visible entries", "[ui][crafting]") {
    Inventory inventory;
    Item ore;
    ore.id = "ore";
    ore.stackable = true;
    ore.quantity = 2;
    REQUIRE(inventory.addItem(ore));

    CraftingEngine crafting;
    CraftingRecipe recipe;
    recipe.id = "sword";
    recipe.name = "Sword";
    recipe.ingredients = {{"ore", 1}};
    recipe.outputItemId = "sword_item";
    recipe.category = ItemCategory::Weapon;
    crafting.registerRecipe(recipe);

    GuiWorkflows gui;
    gui.setCraftingCategory(CraftingCategory::Weapons);
    gui.setCraftableOnly(true);
    REQUIRE(gui.visibleRecipes(crafting, inventory, CraftingStation::None) == std::vector<std::string>{"sword"});
    REQUIRE(gui.craftSelected(crafting, inventory, "sword", CraftingStation::None));
    REQUIRE_FALSE(gui.craftSelected(crafting, inventory, "missing", CraftingStation::None));
}

TEST_CASE("GUI augmentation confirmation exposes body meters", "[ui][augmentations]") {
    AugmentDef augment;
    augment.id = "optic";
    augment.name = "Optic";
    augment.slot = AugmentSlot::Eyes;
    augment.humanityStrain = 25.0f;
    augment.powerGeneration = 10.0f;

    GuiWorkflows gui;
    AugmentationMatrix matrix;
    REQUIRE(gui.requestAugmentationInstall(AugmentSlot::Eyes, augment));
    REQUIRE(gui.hasPendingAugmentation());
    REQUIRE(gui.confirmAugmentationInstall(matrix));
    REQUIRE_FALSE(gui.hasPendingAugmentation());
    REQUIRE(matrix.getAugment(AugmentSlot::Eyes) != nullptr);
    REQUIRE(gui.humanityMeter(matrix) == Catch::Approx(0.25f));
}

TEST_CASE("GUI character sheet derives stats and skill tree confirms or respecs", "[ui][character][skills]") {
    Progression progression;
    progression.setLevel(2);
    GuiWorkflows gui;
    const auto stats = gui.characterDerivedStats(progression);
    REQUIRE(stats.maxHealth == Catch::Approx(250.0f));
    REQUIRE(gui.characterAttributes(progression).strength == 10);

    SkillTree tree;
    tree.addNode(SkillNode{"root", "Root", 1, 0, 1, 0, {}});
    REQUIRE(gui.hoverSkill(tree, "root"));
    REQUIRE(gui.hoveredSkill(tree)->name == "Root");
    REQUIRE(gui.requestSkillAllocation(tree, "root"));
    REQUIRE(gui.confirmSkillAllocation(tree, progression));
    REQUIRE(tree.getRank("root") == 1);
    REQUIRE(tree.getTotalPointsSpent() == 1);
    REQUIRE(gui.respecSkills(tree) == 1);
    REQUIRE(tree.getRank("root") == 0);
}
