#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include "gameplay/items/Item.hpp"
#include "gameplay/items/ItemGenerator.hpp"
#include "gameplay/items/Inventory.hpp"
#include "core/Random.hpp"

using Catch::Approx;

TEST_CASE("Procedural Item Generation and Gaussian Stat Rolls", "[gameplay][items]") {
    Random rng(42);
    ItemGenerator generator(rng);

    BaseItemTemplate tmpl;
    tmpl.id = "tmpl_iron_greatsword";
    tmpl.name = "Iron Greatsword";
    tmpl.category = ItemCategory::Weapon;
    tmpl.tier = 2;
    tmpl.minBaseDamage = 40.0f;
    tmpl.maxBaseDamage = 60.0f;
    tmpl.meanDamage = 50.0f;
    tmpl.stdDevDamage = 4.0f;
    tmpl.baseAttackSpeed = 1.2f;
    tmpl.baseWeight = 6.0f;

    SECTION("Gaussian Stat Roll within Min/Max Bounds") {
        for (int i = 0; i < 50; ++i) {
            Item item = generator.generateItem(tmpl, ItemRarity::Common, 0.0f);
            REQUIRE(item.baseDamage >= 40.0f);
            REQUIRE(item.baseDamage <= 60.0f);
            REQUIRE(item.rarity == ItemRarity::Common);
            REQUIRE(item.affixes.empty());
        }
    }

    SECTION("Quality Modifier 0% to 20% Boosts Primary Stats") {
        Item itemStandard = generator.generateItem(tmpl, ItemRarity::Common, 0.0f);
        Item itemMasterwork = generator.generateItem(tmpl, ItemRarity::Common, 0.20f); // 20% quality

        REQUIRE(itemMasterwork.quality == Approx(0.20f));
        REQUIRE(itemMasterwork.getEffectiveDamage() > itemStandard.baseDamage);
    }
}

TEST_CASE("Dynamic Affix Generation by Rarity", "[gameplay][items]") {
    Random rng(999);
    ItemGenerator generator(rng);

    BaseItemTemplate tmpl;
    tmpl.id = "tmpl_titanium_chestplate";
    tmpl.name = "Titanium Chestplate";
    tmpl.category = ItemCategory::Armor;
    tmpl.tier = 4;
    tmpl.minBaseArmor = 30.0f;
    tmpl.maxBaseArmor = 45.0f;
    tmpl.meanArmor = 38.0f;
    tmpl.stdDevArmor = 2.5f;

    SECTION("Rare Items Receive Exactly 1 Prefix and 1 Suffix") {
        Item rareItem = generator.generateItem(tmpl, ItemRarity::Rare);
        REQUIRE(rareItem.rarity == ItemRarity::Rare);
        REQUIRE(rareItem.affixes.size() == 2);

        int prefixCount = 0;
        int suffixCount = 0;
        for (const auto& affix : rareItem.affixes) {
            if (affix.isPrefix) prefixCount++;
            else suffixCount++;
        }
        REQUIRE(prefixCount == 1);
        REQUIRE(suffixCount == 1);
    }

    SECTION("Legendary Items Receive 4 Affixes Plus Unique Perk") {
        Item legItem = generator.generateItem(tmpl, ItemRarity::Legendary);
        REQUIRE(legItem.rarity == ItemRarity::Legendary);
        REQUIRE(legItem.affixes.size() >= 4);
    }
}

TEST_CASE("Inventory Management, Stacking, Equipment Slots and Weight", "[gameplay][inventory]") {
    Inventory inv(40); // 40-slot grid inventory
    inv.setCarryCapacity(60.0f); // 60kg capacity

    Item potion;
    potion.id = "item_health_potion";
    potion.name = "Health Potion";
    potion.category = ItemCategory::Consumable;
    potion.stackable = true;
    potion.maxStack = 99;
    potion.quantity = 20;
    potion.weight = 0.2f;

    Item greatsword;
    greatsword.id = "item_iron_greatsword";
    greatsword.name = "Iron Greatsword";
    greatsword.category = ItemCategory::Weapon;
    greatsword.equipSlot = EquipSlot::MainHand;
    greatsword.stackable = false;
    greatsword.quantity = 1;
    greatsword.baseDamage = 50.0f;
    greatsword.weight = 8.0f;

    SECTION("Adding and Stacking Stackable Items") {
        REQUIRE(inv.addItem(potion) == true);
        REQUIRE(inv.getItemCount("item_health_potion") == 20);

        // Add 30 more potions -> should stack into same slot
        potion.quantity = 30;
        REQUIRE(inv.addItem(potion) == true);
        REQUIRE(inv.getItemCount("item_health_potion") == 50);
    }

    SECTION("Equipment Slot Equip and Unequip") {
        inv.addItem(greatsword);
        REQUIRE(inv.hasItem("item_iron_greatsword"));

        // Equip into MainHand
        REQUIRE(inv.equipItem(EquipSlot::MainHand, 0) == true);
        const auto* equipped = inv.getEquipped(EquipSlot::MainHand);
        REQUIRE(equipped != nullptr);
        REQUIRE(equipped->name == "Iron Greatsword");

        // Unequip back to inventory grid
        REQUIRE(inv.unequipItem(EquipSlot::MainHand) == true);
        REQUIRE(inv.getEquipped(EquipSlot::MainHand) == nullptr);
    }

    SECTION("Carry Weight Calculation and Over-Encumbrance") {
        // Base empty weight = 0
        REQUIRE(inv.getTotalWeight() == Approx(0.0f));
        REQUIRE(inv.isEncumbered() == false);

        // Add 10 heavy weapons (10 * 8kg = 80kg > 60kg capacity)
        for (int i = 0; i < 10; ++i) {
            inv.addItem(greatsword);
        }

        REQUIRE(inv.getTotalWeight() == Approx(80.0f));
        REQUIRE(inv.isEncumbered() == true);
    }
}
