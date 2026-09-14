#include <catch2/catch_test_macros.hpp>
#include "gameplay/classes/ClassRegistry.hpp"

TEST_CASE("ClassRegistry Complete Archetypes and Exception Verification", "[gameplay][classes]") {
    ClassRegistry cr;

    SECTION("All 9 Core Archetypes Registered") {
        REQUIRE(cr.getAllClasses().size() == 9);

        const auto& jug = cr.getClass(ClassType::Juggernaut);
        REQUIRE(jug.name == "Juggernaut");
        REQUIRE(jug.primaryWeaponType == "Greatsword");

        const auto& ber = cr.getClass(ClassType::Berserker);
        REQUIRE(ber.name == "Berserker");

        const auto& gun = cr.getClass(ClassType::Gunslinger);
        REQUIRE(gun.name == "Gunslinger");

        const auto& pha = cr.getClass(ClassType::Phantom);
        REQUIRE(pha.name == "Phantom");

        const auto& tec = cr.getClass(ClassType::Technomancer);
        REQUIRE(tec.name == "Technomancer");

        const auto& med = cr.getClass(ClassType::Medic);
        REQUIRE(med.name == "Medic");

        const auto& sym = cr.getClass(ClassType::Symbiote);
        REQUIRE(sym.name == "Symbiote");

        const auto& war = cr.getClass(ClassType::Warden);
        REQUIRE(war.name == "Warden");

        const auto& rea = cr.getClass(ClassType::Reanimator);
        REQUIRE(rea.name == "Reanimator");
    }

    SECTION("Unknown Class Type Throws std::runtime_error") {
        bool threw = false;
        try {
            cr.getClass(static_cast<ClassType>(999));
        } catch (const std::runtime_error&) {
            threw = true;
        }
        REQUIRE(threw == true);
    }
}
