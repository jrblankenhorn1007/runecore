#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include "gameplay/items/Inventory.hpp"

using Catch::Approx;

TEST_CASE("Inventory Item Stacking, Equip Slots, and Encumbrance", "[gameplay][items]") {
    Inventory inv(4); // 4 slots
    inv.setCarryCapacity(30.0f); // 30 kg

    Item potion;
    potion.id = "item_potion";
    potion.name = "Health Potion";
    potion.stackable = true;
    potion.maxStack = 10;
    potion.quantity = 7;
    potion.weight = 0.5f;

    Item sword;
    sword.id = "item_sword";
    sword.name = "Iron Sword";
    sword.equipSlot = EquipSlot::MainHand;
    sword.weight = 10.0f;

    SECTION("Adding and Stacking") {
        REQUIRE(inv.addItem(potion) == true);
        REQUIRE(inv.getItemCount("item_potion") == 7);

        // Add 5 more (7 + 5 = 12 > 10 maxStack, overflows to slot 2)
        potion.quantity = 5;
        REQUIRE(inv.addItem(potion) == true);
        REQUIRE(inv.getItemCount("item_potion") == 12);

        REQUIRE(inv.getSlot(0).has_value() == true);
        REQUIRE(inv.getSlot(0)->quantity == 10);
        REQUIRE(inv.getSlot(1).has_value() == true);
        REQUIRE(inv.getSlot(1)->quantity == 2);
    }

    SECTION("Removing Items") {
        inv.addItem(potion);
        REQUIRE(inv.removeItem("item_potion", 3) == true);
        REQUIRE(inv.getItemCount("item_potion") == 4);

        REQUIRE(inv.removeItem("item_potion", 10) == false); // Not enough
        REQUIRE(inv.removeItem("nonexistent", 1) == false);
    }

    SECTION("Equip and Unequip Swapping") {
        inv.addItem(sword);
        REQUIRE(inv.equipItem(EquipSlot::MainHand, -1) == false); // Out of bounds
        REQUIRE(inv.equipItem(EquipSlot::MainHand, 99) == false);
        REQUIRE(inv.equipItem(EquipSlot::Helmet, 0) == false);   // Slot mismatch

        REQUIRE(inv.equipItem(EquipSlot::MainHand, 0) == true);
        REQUIRE(inv.getEquipped(EquipSlot::MainHand) != nullptr);
        REQUIRE(inv.getEquipped(EquipSlot::Helmet) == nullptr);

        REQUIRE(inv.unequipItem(EquipSlot::MainHand) == true);
        REQUIRE(inv.getEquipped(EquipSlot::MainHand) == nullptr);
        REQUIRE(inv.unequipItem(EquipSlot::MainHand) == false); // Already empty
    }

    SECTION("Carry Weight and Encumbrance") {
        REQUIRE(inv.getTotalWeight() == Approx(0.0f));
        REQUIRE(inv.isEncumbered() == false);

        // Add 4 swords = 40kg > 30kg capacity
        for (int i = 0; i < 4; ++i) {
            inv.addItem(sword);
        }
        REQUIRE(inv.getTotalWeight() == Approx(40.0f));
        REQUIRE(inv.isEncumbered() == true);
    }
}
