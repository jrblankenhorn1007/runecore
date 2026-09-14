#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include "gameplay/items/ItemGenerator.hpp"
#include "core/Random.hpp"

using Catch::Approx;

TEST_CASE("ItemGenerator Rarity Tiers and Affix Allocation", "[gameplay][items]") {
    Random rng(42);
    ItemGenerator gen(rng);

    BaseItemTemplate tmpl;
    tmpl.id = "tmpl_sword";
    tmpl.name = "Broadsword";
    tmpl.tier = 2;
    tmpl.minBaseDamage = 30.0f;
    tmpl.maxBaseDamage = 45.0f;
    tmpl.minBaseArmor = 5.0f;
    tmpl.maxBaseArmor = 10.0f;

    SECTION("Common and Uncommon Item Generation") {
        Item common = gen.generateItem(tmpl, ItemRarity::Common);
        REQUIRE(common.rarity == ItemRarity::Common);
        REQUIRE(common.affixes.empty());

        Item uncommon = gen.generateItem(tmpl, ItemRarity::Uncommon);
        REQUIRE(uncommon.rarity == ItemRarity::Uncommon);
        REQUIRE(uncommon.affixes.size() == 1);
    }

    SECTION("Rare, Epic, Legendary, Mythic, and Prismatic") {
        Item rare = gen.generateItem(tmpl, ItemRarity::Rare);
        REQUIRE(rare.affixes.size() == 2);

        Item epic = gen.generateItem(tmpl, ItemRarity::Epic);
        REQUIRE(epic.affixes.size() == 3);

        Item leg = gen.generateItem(tmpl, ItemRarity::Legendary);
        REQUIRE(leg.affixes.size() == 4);
        REQUIRE(!leg.uniquePerk.empty());

        Item myth = gen.generateItem(tmpl, ItemRarity::Mythic);
        REQUIRE(myth.affixes.size() == 6);

        Item prism = gen.generateItem(tmpl, ItemRarity::Prismatic);
        REQUIRE(prism.affixes.size() == 8);
    }
}
