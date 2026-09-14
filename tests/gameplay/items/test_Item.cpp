#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include "gameplay/items/Item.hpp"

using Catch::Approx;

TEST_CASE("Item Struct Quality Scaling and Methods", "[gameplay][items]") {
    Item item;
    item.id = "sword_iron";
    item.baseDamage = 50.0f;
    item.baseArmor = 20.0f;
    item.quality = 0.10f; // +10% quality

    SECTION("Effective Damage and Armor Include Quality") {
        REQUIRE(item.getEffectiveDamage() == Approx(55.0f));
        REQUIRE(item.getEffectiveArmor() == Approx(22.0f));
    }
}
