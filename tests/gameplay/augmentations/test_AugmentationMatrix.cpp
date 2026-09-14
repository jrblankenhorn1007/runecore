#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include "gameplay/augmentations/AugmentationMatrix.hpp"

using Catch::Approx;

TEST_CASE("AugmentationMatrix Installation, Strain, and Signatures", "[gameplay][augmentations]") {
    AugmentationMatrix matrix;

    AugmentDef headAug;
    headAug.id = "head_1";
    headAug.slot = AugmentSlot::Head;
    headAug.type = AugmentType::Bionic;
    headAug.powerUpkeep = 10.0f;
    headAug.humanityStrain = 15.0f;
    headAug.flatCritChanceBonus = 0.05f;

    AugmentDef heartAug;
    heartAug.id = "heart_1";
    heartAug.slot = AugmentSlot::Heart;
    heartAug.type = AugmentType::Bionic;
    heartAug.powerGeneration = 100.0f;
    heartAug.humanityStrain = 20.0f;

    AugmentDef magitechSkin;
    magitechSkin.id = "skin_1";
    magitechSkin.slot = AugmentSlot::Skin;
    magitechSkin.type = AugmentType::Magitech;
    magitechSkin.manaUpkeep = 15.0f;
    magitechSkin.rejectionRisk = 0.20f;

    SECTION("Slot Mismatch Rejection") {
        REQUIRE(matrix.install(AugmentSlot::Torso, headAug) == false);
        REQUIRE(matrix.getAugment(AugmentSlot::Torso) == nullptr);
    }

    SECTION("Successful Installation and Uninstallation") {
        REQUIRE(matrix.install(AugmentSlot::Head, headAug) == true);
        REQUIRE(matrix.install(AugmentSlot::Heart, heartAug) == true);
        REQUIRE(matrix.install(AugmentSlot::Skin, magitechSkin) == true);

        REQUIRE(matrix.getAugment(AugmentSlot::Head) != nullptr);
        REQUIRE(matrix.getAugment(AugmentSlot::Hands) == nullptr);
        REQUIRE(matrix.getAllInstalled().size() == 3);

        REQUIRE(matrix.getNetPowerGeneration() == Approx(90.0f)); // 100 - 10
        REQUIRE(matrix.getTotalHumanityStrain() == Approx(35.0f)); // 15 + 20
        REQUIRE(matrix.getTotalManaUpkeep() == Approx(15.0f));
        REQUIRE(matrix.getTotalRejectionRisk() == Approx(0.20f));

        REQUIRE(matrix.uninstall(AugmentSlot::Head) == true);
        REQUIRE(matrix.uninstall(AugmentSlot::Head) == false); // Already uninstalled
        REQUIRE(matrix.getAugment(AugmentSlot::Head) == nullptr);
    }

    SECTION("Class Signature Installation Rules") {
        AugmentDef sigCore;
        sigCore.id = "sig_jug";
        sigCore.slot = AugmentSlot::Heart;
        sigCore.isSignature = true;
        sigCore.signatureClass = ClassType::Juggernaut;
        sigCore.humanityStrain = 20.0f;

        // Level too low
        REQUIRE(matrix.installSignature(sigCore, ClassType::Juggernaut, 18) == false);

        // Native class install
        REQUIRE(matrix.installSignature(sigCore, ClassType::Juggernaut, 20) == true);
        REQUIRE(matrix.getAugment(AugmentSlot::Heart)->humanityStrain == Approx(20.0f));

        // Cross-class surgery penalty (50% penalty)
        REQUIRE(matrix.installSignature(sigCore, ClassType::Phantom, 25) == true);
        REQUIRE(matrix.getAugment(AugmentSlot::Heart)->humanityStrain == Approx(30.0f));

        // Non-signature argument rejected by installSignature
        AugmentDef normal;
        normal.slot = AugmentSlot::Lungs;
        normal.isSignature = false;
        REQUIRE(matrix.installSignature(normal, ClassType::Juggernaut, 50) == false);
    }
}
