#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include "gameplay/combat/DamageCalculator.hpp"

using Catch::Approx;

TEST_CASE("DamageCalculator Calculations, Penetration, and Bounds", "[gameplay][combat]") {
    DamageInstance inst;
    inst.baseDamage = 100.0f;
    inst.type = DamageType::Physical;
    inst.canCrit = true;

    SECTION("Physical Zero Armor") {
        DamageResult res = DamageCalculator::calculate(inst, 0.0f, 0.0f);
        REQUIRE(res.rawDamage == Approx(100.0f));
        REQUIRE(res.finalDamage == Approx(100.0f));
        REQUIRE(res.isCrit == false);
    }

    SECTION("Physical Armor Mitigation Formula") {
        // Raw * 100 / (100 + Armor)
        DamageResult res100 = DamageCalculator::calculate(inst, 100.0f, 0.0f);
        REQUIRE(res100.finalDamage == Approx(50.0f));

        DamageResult res300 = DamageCalculator::calculate(inst, 300.0f, 0.0f);
        REQUIRE(res300.finalDamage == Approx(25.0f));
    }

    SECTION("Armor Penetration Scaling") {
        inst.armorPenetration = 0.50f; // 50% penetration of 200 armor = 100 effective armor
        DamageResult res = DamageCalculator::calculate(inst, 200.0f, 0.0f);
        REQUIRE(res.finalDamage == Approx(50.0f));
    }

    SECTION("Elemental Resistance Bounds and Clamping") {
        inst.type = DamageType::Fire;
        DamageResult res50 = DamageCalculator::calculate(inst, 0.0f, 0.50f);
        REQUIRE(res50.finalDamage == Approx(50.0f));

        // Negative resistance (vulnerability)
        DamageResult vuln = DamageCalculator::calculate(inst, 0.0f, -0.25f);
        REQUIRE(vuln.finalDamage == Approx(125.0f));

        // Resistance clamped to max 90%
        DamageResult immune = DamageCalculator::calculate(inst, 0.0f, 1.0f);
        REQUIRE(immune.finalDamage == Approx(10.0f));
    }

    SECTION("Critical Strike Multiplier") {
        DamageResult crit = DamageCalculator::calculate(inst, 0.0f, 0.0f, 1.0f, 2.5f);
        REQUIRE(crit.isCrit == true);
        REQUIRE(crit.finalDamage == Approx(250.0f));
    }
}
