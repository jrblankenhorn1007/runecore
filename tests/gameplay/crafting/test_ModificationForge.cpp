#include <catch2/catch_test_macros.hpp>
#include "gameplay/crafting/ModificationForge.hpp"
#include "core/Random.hpp"

TEST_CASE("ModificationForge Affix Infusion, Tier Upgrading, and Fracture State", "[gameplay][crafting]") {
    Random rng(12345);
    ModificationForge forge(rng);

    Item item;
    item.id = "sword_1";
    item.name = "Steel Blade";
    item.tier = 2;
    item.baseDamage = 50.0f;
    item.sockets = 0;

    SECTION("Affix Infusion Accumulates Instability") {
        Affix af;
        af.name = "Sharp";
        af.isPrefix = true;
        af.flatBonus = 10.0f;

        ForgeResult res = forge.infuseAffix(item, af);
        REQUIRE(res.success == true);
        REQUIRE(item.affixes.size() == 1);
        REQUIRE(forge.getInstability(item) == 10);
    }

    SECTION("Tier Upgrading and Tier 7 Cap") {
        ForgeResult r1 = forge.upgradeTier(item);
        REQUIRE(r1.success == true);
        REQUIRE(item.tier == 3);

        item.tier = 7; // Max tier
        ForgeResult rMax = forge.upgradeTier(item);
        REQUIRE(rMax.success == false);
    }

    SECTION("Socket Punching and Max 3 Sockets Cap") {
        REQUIRE(forge.punchSocket(item).success == true);
        REQUIRE(item.sockets == 1);
        REQUIRE(forge.punchSocket(item).success == true);
        REQUIRE(item.sockets == 2);
        REQUIRE(forge.punchSocket(item).success == true);
        REQUIRE(item.sockets == 3);

        // Cannot exceed 3 sockets
        REQUIRE(forge.punchSocket(item).success == false);
    }

    SECTION("Fractured State Rejects All Modifications") {
        forge.setInstability(item, 95); // Extremely high instability

        bool fractured = false;
        for (int i = 0; i < 30; ++i) {
            Affix af{"Fiery", true, 1, 5.0f, 0.0f, "Damage"};
            ForgeResult r = forge.infuseAffix(item, af);
            if (r.isFractured) {
                fractured = true;
                break;
            }
        }
        REQUIRE(fractured == true);
        REQUIRE(forge.isFractured(item) == true);

        // All forge operations reject fractured items
        Affix af{"Icy", true, 1, 5.0f, 0.0f, "Damage"};
        REQUIRE(forge.infuseAffix(item, af).success == false);
        REQUIRE(forge.upgradeTier(item).success == false);
        REQUIRE(forge.punchSocket(item).success == false);
    }
}
