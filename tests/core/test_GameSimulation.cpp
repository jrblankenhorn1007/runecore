#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include "core/GameSimulation.hpp"

using Catch::Approx;

TEST_CASE("GameSimulation Integration and Player Controls", "[core][simulation]") {
    GameSimulation sim;
    sim.initialize(ClassType::Juggernaut);

    SECTION("Initial Vitals and Attributes") {
        REQUIRE(sim.getPlayerLevel() == 1);
        REQUIRE(sim.getPlayerXP() == 0);
        REQUIRE(sim.getPlayerHealth() > 0.0f);
        REQUIRE(sim.getPlayerMana() > 0.0f);
        REQUIRE(sim.getPlayerPower() >= 0.0f);
        REQUIRE(sim.getPlayerHunger() == Approx(100.0f));
        REQUIRE(sim.getPlayerPosition().x == Approx(100.0f));
        REQUIRE(sim.getEnemyCount() > 0);
    }

    SECTION("Player Melee Attack and Skill Invocations") {
        sim.playerAttack();
        REQUIRE(sim.isAttacking() == true);
        REQUIRE(sim.getLastAttackBox().damage > 0.0f);

        // Cast all 4 skills
        REQUIRE(sim.castSkillQ() == true); // Seismic slam
        REQUIRE(sim.castSkillE() == true); // Rocket dash
        REQUIRE(sim.castSkillR() == true); // Arc lightning nova
        REQUIRE(sim.castSkillF() == true); // Nanite heal

        // Immediate recast fails because on cooldown
        REQUIRE(sim.castSkillQ() == false);
    }

    SECTION("Projectiles and World Mining/Placing") {
        sim.shootProjectile(Vec2{200.0f, 100.0f});

        // Mine a nearby solid tile
        Vec2 tilePos = sim.getPlayerPosition() + Vec2{16.0f, 16.0f};
        sim.mineTileAt(tilePos);

        // Place a block into air
        sim.placeBlockAt(tilePos, "mat_wood_plank", 3);
    }

    SECTION("Active Screen Toggles") {
        REQUIRE(sim.getActiveScreen() == ActiveScreen::None);
        sim.toggleScreen(ActiveScreen::Inventory);
        REQUIRE(sim.getActiveScreen() == ActiveScreen::Inventory);
        sim.toggleScreen(ActiveScreen::Inventory);
        REQUIRE(sim.getActiveScreen() == ActiveScreen::None);
    }

    SECTION("Dungeon Entry and Exit") {
        REQUIRE(sim.isInsideDungeon() == false);
        sim.enterDungeon();
        REQUIRE(sim.isInsideDungeon() == true);
        sim.exitDungeon();
        REQUIRE(sim.isInsideDungeon() == false);
    }
}
