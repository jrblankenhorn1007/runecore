#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include "core/GameSimulation.hpp"
#include "ecs/Components.hpp"

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

    SECTION("Melee Selects The Nearest Enemy In Range") {
        const Vec2 playerPosition = sim.getPlayerPosition();
        const auto enemy = sim.spawnEnemy(playerPosition + Vec2{-24.0f, 0.0f}, 10.0f, 50);
        sim.playerAttack();
        REQUIRE(sim.getContext().registry.get<HealthComponent>(enemy).isDead);
    }

    SECTION("Projectiles and World Mining/Placing") {
        sim.shootProjectile(Vec2{200.0f, 100.0f});

        // Mine a nearby solid tile
        Vec2 tilePos = sim.getPlayerPosition() + Vec2{16.0f, 16.0f};
        sim.mineTileAt(tilePos);

        // Place a block into air
        sim.placeBlockAt(tilePos, "mat_wood_plank", 3);
    }

    SECTION("Mining Selects The Nearest Solid Tile When Aim Misses") {
        const Vec2 playerPosition = sim.getPlayerPosition();
        REQUIRE(sim.mineTileAt(playerPosition + Vec2{0.0f, -32.0f}));
    }

    SECTION("Farming Advances With Simulation Time") {
        sim.getFarming().tillSoil(8, 8);
        sim.getFarming().waterSoil(8, 8);
        REQUIRE(sim.getFarming().plantSeed(8, 8, "crop_wheat"));
        sim.step(ControllerInput{}, 20.0f);
        REQUIRE(sim.getFarming().getCropStage(8, 8) == CropStage::Sprout);
        sim.step(ControllerInput{}, 40.0f);
        REQUIRE(sim.getFarming().getCropStage(8, 8) == CropStage::Mature);
        const HarvestResult harvest = sim.getFarming().harvest(8, 8);
        REQUIRE(harvest.success);
        REQUIRE(harvest.yieldCount == 3);
    }

    SECTION("Active Screen Toggles") {
        REQUIRE(sim.getActiveScreen() == ActiveScreen::None);
        sim.toggleScreen(ActiveScreen::Inventory);
        REQUIRE(sim.getActiveScreen() == ActiveScreen::Inventory);
        sim.toggleScreen(ActiveScreen::Inventory);
        REQUIRE(sim.getActiveScreen() == ActiveScreen::None);
        sim.toggleScreen(ActiveScreen::Settings);
        REQUIRE(sim.getActiveScreen() == ActiveScreen::Settings);
        sim.toggleScreen(ActiveScreen::Settings);
        REQUIRE(sim.getActiveScreen() == ActiveScreen::None);
    }

    SECTION("Weather Emits Typed Environmental Particles") {
        sim.getContext().dayNight.setWeather(WeatherType::Clear);
        sim.step(ControllerInput{}, 1.0f / 60.0f);
        REQUIRE(sim.getParticles().getActiveCount() == 0);

        sim.getContext().dayNight.setWeather(WeatherType::Blizzard);
        sim.step(ControllerInput{}, 1.0f / 60.0f);
        sim.step(ControllerInput{}, 1.0f / 60.0f);
        sim.step(ControllerInput{}, 1.0f / 60.0f);
        REQUIRE(sim.getParticles().getActiveCount() > 0);
        const auto& particle = sim.getParticles().getParticles().front();
        REQUIRE(particle.active == true);
        REQUIRE(particle.color.b == 255);
    }

    SECTION("Character Sheet and Skill Allocation") {
        sim.getProgression().setLevel(2);
        int startingStrength = sim.getProgression().getAttribute(Progression::Attribute::Strength);
        REQUIRE(sim.allocateAttribute(0) == true);
        REQUIRE(sim.getProgression().getAttribute(Progression::Attribute::Strength) == startingStrength + 1);
        REQUIRE(sim.allocateSkill("mob_02") == false);
        REQUIRE(sim.allocateSkill("mob_01") == true);
        REQUIRE(sim.getSkillTree().getRank("mob_01") == 1);
        REQUIRE(sim.allocateSkill("mob_02") == true);
    }

    SECTION("Dungeon Entry and Exit") {
        REQUIRE(sim.isInsideDungeon() == false);
        REQUIRE(sim.canEnterDungeon() == false);

        // Move player to entrance at X = 400
        auto& pPos = sim.getContext().registry.get<TransformComponent>(sim.getContext().registry.view<PlayerTag>().front()).position;
        pPos.x = 400.0f;
        REQUIRE(sim.canEnterDungeon() == true);

        sim.enterDungeon();
        REQUIRE(sim.isInsideDungeon() == true);
        auto bossView = sim.getContext().registry.view<BossEncounterComponent>();
        REQUIRE(bossView.begin() != bossView.end());
        auto bossEntity = bossView.front();
        auto& bossHealth = sim.getContext().registry.get<HealthComponent>(bossEntity);
        bossHealth.current = bossHealth.max * 0.5f;
        sim.step(ControllerInput{}, 0.1f);
        REQUIRE(sim.getContext().registry.get<BossEncounterComponent>(bossEntity).controller.isEnraged());
        REQUIRE(sim.getEnemyCount() >= 3);
        sim.exitDungeon();
        REQUIRE(sim.isInsideDungeon() == false);
    }

    SECTION("Starvation and Hypothermia Damage Application") {
        auto enemyView = sim.getContext().registry.view<EnemyTag>();
        for (auto e : enemyView) {
            sim.getContext().registry.destroy(e);
        }

        ControllerInput input;
        float initialHP = sim.getPlayerHealth();
        REQUIRE(initialHP > 0.0f);

        // Step 35 seconds in cold ambient conditions to induce hypothermia damage
        sim.step(input, 35.0f);

        REQUIRE(sim.getPlayerHealth() < initialHP);
        REQUIRE(sim.getPlayerHealth() > 0.0f);
    }

    SECTION("Accessors and Skills Recast Rejections") {
        REQUIRE(sim.getPlayerFacing() != 0);
        REQUIRE(sim.getDungeonLayout().width > 0);
        REQUIRE(sim.getSkillExecutor().isOnCooldown(HotbarSlot::Q) == false);
        REQUIRE(sim.getCraftingEngine().getRecipe("rcp_iron_greatsword") != nullptr);
        REQUIRE(sim.getAugmentations().getAllInstalled().empty() == true);
        REQUIRE(sim.getProgression().getLevel() == 1);

        // Cast skills once
        sim.castSkillE();
        sim.castSkillR();
        sim.castSkillF();

        // Immediate recast should return false because on cooldown
        REQUIRE(sim.castSkillE() == false);
        REQUIRE(sim.castSkillR() == false);
        REQUIRE(sim.castSkillF() == false);
    }

    SECTION("Getters and Fallbacks When Player is Destroyed") {
        auto playerView = sim.getContext().registry.view<PlayerTag>();
        for (auto e : playerView) {
            sim.getContext().registry.destroy(e);
        }
        REQUIRE(sim.getPlayerHealth() == Approx(0.0f));
        REQUIRE(sim.getPlayerMana() == Approx(0.0f));
        REQUIRE(sim.getPlayerPower() == Approx(0.0f));
        REQUIRE(sim.getPlayerPosition().x == Approx(0.0f));
        REQUIRE(sim.canEnterDungeon() == false);

        sim.playerAttack();
        sim.shootProjectile(Vec2{100.0f, 100.0f});
        REQUIRE(sim.mineTileAt(Vec2{100.0f, 100.0f}) == false);
        REQUIRE(sim.placeBlockAt(Vec2{100.0f, 100.0f}, "mat_wood_plank", 3) == false);
        REQUIRE(sim.castSkillQ() == false);
        REQUIRE(sim.castSkillE() == false);
        REQUIRE(sim.castSkillR() == false);
        REQUIRE(sim.castSkillF() == false);
        sim.exitDungeon();
    }
}
