#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include "gameplay/augmentations/AugmentationMatrix.hpp"
#include "gameplay/classes/ClassRegistry.hpp"

using Catch::Approx;

TEST_CASE("11 Body Augmentation Slots Installation and Compatibility", "[gameplay][augmentations]") {
    AugmentationMatrix matrix;

    AugmentDef headAug;
    headAug.id = "aug_target_matrix_mk1";
    headAug.name = "MK-I Target Matrix";
    headAug.slot = AugmentSlot::Head;
    headAug.type = AugmentType::Bionic;
    headAug.powerUpkeep = 5.0f;
    headAug.humanityStrain = 10.0f;
    headAug.flatCritChanceBonus = 0.05f;

    AugmentDef heartAug;
    heartAug.id = "aug_tokamak_heart";
    heartAug.name = "Cold-Fusion Tokamak Heart";
    heartAug.slot = AugmentSlot::Heart;
    heartAug.type = AugmentType::Bionic;
    heartAug.powerGeneration = 150.0f;
    heartAug.humanityStrain = 25.0f;

    AugmentDef wrongSlotAug;
    wrongSlotAug.id = "aug_wrong";
    wrongSlotAug.slot = AugmentSlot::Legs;

    SECTION("Installing Augmentations in Matching Slots") {
        REQUIRE(matrix.install(AugmentSlot::Head, headAug) == true);
        REQUIRE(matrix.getAugment(AugmentSlot::Head) != nullptr);
        REQUIRE(matrix.getAugment(AugmentSlot::Head)->name == "MK-I Target Matrix");

        REQUIRE(matrix.install(AugmentSlot::Heart, heartAug) == true);
        REQUIRE(matrix.getAugment(AugmentSlot::Heart) != nullptr);
    }

    SECTION("Rejecting Installation in Mismatched Slots") {
        REQUIRE(matrix.install(AugmentSlot::Torso, wrongSlotAug) == false);
        REQUIRE(matrix.getAugment(AugmentSlot::Torso) == nullptr);
    }

    SECTION("Uninstalling Augmentations") {
        matrix.install(AugmentSlot::Head, headAug);
        REQUIRE(matrix.uninstall(AugmentSlot::Head) == true);
        REQUIRE(matrix.getAugment(AugmentSlot::Head) == nullptr);
    }
}

TEST_CASE("Dual-Energy Economy Power and Strain Calculations", "[gameplay][augmentations]") {
    AugmentationMatrix matrix;

    AugmentDef bionicHeart;
    bionicHeart.id = "bionic_heart";
    bionicHeart.slot = AugmentSlot::Heart;
    bionicHeart.type = AugmentType::Bionic;
    bionicHeart.powerGeneration = 100.0f;
    bionicHeart.humanityStrain = 20.0f;

    AugmentDef bionicArm;
    bionicArm.id = "bionic_arm";
    bionicArm.slot = AugmentSlot::RightArm;
    bionicArm.type = AugmentType::Bionic;
    bionicArm.powerUpkeep = 15.0f;
    bionicArm.humanityStrain = 30.0f;

    AugmentDef magitechGraft;
    magitechGraft.id = "magitech_graft";
    magitechGraft.slot = AugmentSlot::Skin;
    magitechGraft.type = AugmentType::Magitech;
    magitechGraft.manaUpkeep = 10.0f;
    magitechGraft.rejectionRisk = 0.15f;

    matrix.install(AugmentSlot::Heart, bionicHeart);
    matrix.install(AugmentSlot::RightArm, bionicArm);
    matrix.install(AugmentSlot::Skin, magitechGraft);

    SECTION("Net Power Balance") {
        // Generation 100 - Upkeep 15 = +85 net power
        REQUIRE(matrix.getNetPowerGeneration() == Approx(85.0f));
    }

    SECTION("Total Humanity Strain and Rejection Risk") {
        // Strain: 20 + 30 = 50
        REQUIRE(matrix.getTotalHumanityStrain() == Approx(50.0f));
        // Total mana upkeep = 10
        REQUIRE(matrix.getTotalManaUpkeep() == Approx(10.0f));
        // Total rejection risk = 0.15
        REQUIRE(matrix.getTotalRejectionRisk() == Approx(0.15f));
    }
}

TEST_CASE("Class Signature Augmentations and Cross-Class Surgery Penalties", "[gameplay][augmentations]") {
    AugmentationMatrix matrix;

    AugmentDef juggernautCore;
    juggernautCore.id = "sig_juggernaut_core";
    juggernautCore.name = "Kinetic Impact Siphon Core";
    juggernautCore.slot = AugmentSlot::Heart;
    juggernautCore.type = AugmentType::Bionic;
    juggernautCore.humanityStrain = 20.0f;
    juggernautCore.isSignature = true;
    juggernautCore.signatureClass = ClassType::Juggernaut;

    SECTION("Native Class Installation (No Penalty)") {
        bool success = matrix.installSignature(juggernautCore, ClassType::Juggernaut, 20);
        REQUIRE(success == true);
        const auto* installed = matrix.getAugment(AugmentSlot::Heart);
        REQUIRE(installed != nullptr);
        REQUIRE(installed->humanityStrain == Approx(20.0f));
    }

    SECTION("Cross-Class Exotic Surgery Adds 50% Strain Penalty") {
        bool success = matrix.installSignature(juggernautCore, ClassType::Phantom, 25);
        REQUIRE(success == true);
        const auto* installed = matrix.getAugment(AugmentSlot::Heart);
        REQUIRE(installed != nullptr);
        // Strain should have 1.5x penalty: 20 * 1.5 = 30
        REQUIRE(installed->humanityStrain == Approx(30.0f));
    }

    SECTION("Requires Minimum Level 20") {
        bool success = matrix.installSignature(juggernautCore, ClassType::Juggernaut, 15);
        REQUIRE(success == false); // Level too low
    }
}
