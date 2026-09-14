#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include "gameplay/stats/StatsSystem.hpp"
#include "gameplay/stats/Progression.hpp"
#include "gameplay/classes/ClassRegistry.hpp"

using Catch::Approx;

TEST_CASE("Derived Stat Calculations from Base Attributes", "[gameplay][stats]") {
    Attributes baseAttrs;
    baseAttrs.strength = 20;     // +10 above default (10)
    baseAttrs.dexterity = 25;    // +15 above default
    baseAttrs.intelligence = 15; // +5 above default
    baseAttrs.vitality = 30;     // +20 above default
    baseAttrs.wisdom = 10;
    baseAttrs.cybernetics = 18;  // +8 above default

    DerivedStats derived = StatsSystem::calculateDerivedStats(baseAttrs);

    SECTION("Health Scaling from STR and VIT") {
        // Base 100 HP + (STR * 5) + (VIT * 10) = 100 + 100 + 300 = 500
        REQUIRE(derived.maxHealth == Approx(500.0f));
    }

    SECTION("Mana Scaling from INT") {
        // Base 50 MP + (INT * 5) = 50 + 75 = 125
        REQUIRE(derived.maxMana == Approx(125.0f));
        // Base 1.0 MP/s + (INT * 0.1) = 1.0 + 1.5 = 2.5
        REQUIRE(derived.manaRegen == Approx(2.5f));
    }

    SECTION("Power Scaling from CYB") {
        // Base 50 + (CYB * 5) = 50 + 90 = 140
        REQUIRE(derived.maxPower == Approx(140.0f));
        // Cooldown reduction = CYB * 0.5% = 9.0%
        REQUIRE(derived.cooldownReduction == Approx(0.09f));
    }

    SECTION("Critical Chance and Speed from DEX") {
        // Base 5% + (DEX * 0.2%) = 0.05 + 0.05 = 0.10 (10%)
        REQUIRE(derived.critChance == Approx(0.10f));
        // Base 1.0 + (DEX * 0.005) = 1.125
        REQUIRE(derived.moveSpeedMultiplier == Approx(1.125f));
    }

    SECTION("Armor and Regeneration from VIT") {
        // Base 0 + (VIT * 1.0) = 30.0 Armor
        REQUIRE(derived.physicalArmor == Approx(30.0f));
        // Base 0.5 + (VIT * 0.1) = 3.5 HP/s
        REQUIRE(derived.healthRegen == Approx(3.5f));
    }
}

TEST_CASE("Uncapped Leveling XP Curve and Point Allocation", "[gameplay][progression]") {
    Progression progression;

    SECTION("Level 1 Initial State") {
        REQUIRE(progression.getLevel() == 1);
        REQUIRE(progression.getCurrentXP() == 0);
        REQUIRE(progression.getXPForNextLevel() == Approx(100.0f)); // 100 * 1^1.8
        REQUIRE(progression.isCrossClassUnlocked() == false);
        REQUIRE(progression.getAttributePoints() == 0);
        REQUIRE(progression.getSkillPoints() == 0);
    }

    SECTION("Level Up Thresholds and Point Awards") {
        // Level 2 threshold = 100 * 2^1.8 ~ 348 XP
        progression.addXP(400);
        REQUIRE(progression.getLevel() == 2);
        REQUIRE(progression.getAttributePoints() == 3);
        REQUIRE(progression.getSkillPoints() == 2); // 1 Class + 1 Shared
    }

    SECTION("Uncapped Progression and Level 60 Milestone") {
        progression.setLevel(59);
        REQUIRE(progression.isCrossClassUnlocked() == false);

        progression.setLevel(60);
        REQUIRE(progression.isCrossClassUnlocked() == true);

        // Can continue leveling beyond level 60
        progression.setLevel(150);
        REQUIRE(progression.getLevel() == 150);
        REQUIRE(progression.isCrossClassUnlocked() == true);
    }

    SECTION("Spending Points") {
        progression.setLevel(5); // 4 level-ups -> 12 attr points, 8 skill points
        REQUIRE(progression.getAttributePoints() == 12);

        REQUIRE(progression.spendAttributePoints(5) == true);
        REQUIRE(progression.getAttributePoints() == 7);
        REQUIRE(progression.spendAttributePoints(10) == false); // Insufficient
        REQUIRE(progression.getAttributePoints() == 7);
    }
}

TEST_CASE("9 Class Archetype Configurations and Starter Kits", "[gameplay][classes]") {
    ClassRegistry registry;

    SECTION("Juggernaut Archetype") {
        const auto& jug = registry.getClass(ClassType::Juggernaut);
        REQUIRE(jug.name == "Juggernaut");
        REQUIRE(jug.baseAttributes.strength >= 14);
        REQUIRE(jug.baseAttributes.vitality >= 12);
        REQUIRE(jug.primaryWeaponType == "Greatsword");
    }

    SECTION("Phantom Archetype") {
        const auto& pha = registry.getClass(ClassType::Phantom);
        REQUIRE(pha.name == "Phantom");
        REQUIRE(pha.baseAttributes.dexterity >= 15);
        REQUIRE(pha.primaryWeaponType == "Dagger");
    }

    SECTION("Technomancer Archetype") {
        const auto& tec = registry.getClass(ClassType::Technomancer);
        REQUIRE(tec.name == "Technomancer");
        REQUIRE(tec.baseAttributes.intelligence >= 14);
        REQUIRE(tec.baseAttributes.cybernetics >= 12);
        REQUIRE(tec.primaryWeaponType == "Wand");
    }

    SECTION("All 9 Classes Exist") {
        REQUIRE(registry.getAllClasses().size() == 9);
    }
}
