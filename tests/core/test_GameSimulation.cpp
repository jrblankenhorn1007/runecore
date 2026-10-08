#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include "core/GameSimulation.hpp"
#include "ecs/Components.hpp"
#include "save/SaveManager.hpp"

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

    SECTION("Settings screen pauses gameplay and resumes it when closed") {
        const float initialTime = sim.getSimulationTime();
        const Vec2 initialPosition = sim.getPlayerPosition();
        ControllerInput input;
        input.moveX = 1.0f;
        input.jumpPressed = true;

        sim.toggleScreen(ActiveScreen::Settings);
        sim.step(input, 1.0f / 60.0f);
        REQUIRE(sim.getSimulationTime() == Approx(initialTime));
        REQUIRE(sim.getPlayerPosition().x == Approx(initialPosition.x));
        REQUIRE(sim.getPlayerPosition().y == Approx(initialPosition.y));

        sim.toggleScreen(ActiveScreen::Settings);
        sim.step(input, 1.0f / 60.0f);
        REQUIRE(sim.getSimulationTime() == Approx(initialTime + 1.0f / 60.0f));
    }

    SECTION("Settings remains modal until explicitly closed") {
        sim.toggleScreen(ActiveScreen::Settings);
        sim.toggleScreen(ActiveScreen::Inventory);
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

    SECTION("Save data restores character, progression, inventory, and location") {
        REQUIRE(sim.createCharacter(CharacterCreation{
            "Astra", ClassType::Juggernaut, Color{65, 225, 220, 255}}));
        REQUIRE(sim.getProgression().restoreState(
            8, 123, 4, 3, Attributes{31, 16, 17, 25, 14, 12}));

        const auto player = sim.getContext().registry.view<PlayerTag>().front();
        sim.getContext().registry.get<TransformComponent>(player).position = Vec2{384.0f, 176.0f};
        sim.getContext().registry.get<HealthComponent>(player).current = 48.0f;
        sim.getContext().registry.get<ManaComponent>(player).current = 19.0f;
        sim.getContext().registry.get<PowerComponent>(player).current = 22.0f;

        Item ore;
        ore.id = "mat_test_ore";
        ore.name = "Test Ore";
        ore.category = ItemCategory::Material;
        ore.stackable = true;
        ore.quantity = 7;
        REQUIRE(sim.getInventory().addItem(ore));

        Item blade;
        blade.id = "item_test_blade";
        blade.name = "Test Blade";
        blade.category = ItemCategory::Weapon;
        blade.equipSlot = EquipSlot::MainHand;
        blade.baseDamage = 72.0f;
        REQUIRE(sim.getInventory().addItem(blade));
        int bladeSlot = -1;
        for (int index = 0; index < sim.getInventory().getSlotCount(); ++index) {
            const auto item = sim.getInventory().getSlot(index);
            if (item.has_value() && item->id == blade.id) {
                bladeSlot = index;
                break;
            }
        }
        REQUIRE(bladeSlot >= 0);
        REQUIRE(sim.getInventory().equipItem(EquipSlot::MainHand, bladeSlot));

        SaveData saved = sim.captureSaveData();
        saved.hunger = 43.0f;
        saved.thirst = 29.0f;
        saved.bodyTemp = 34.5f;

        GameSimulation resumed;
        resumed.initialize(ClassType::Juggernaut);
        REQUIRE(resumed.restoreSaveData(saved));
        const SaveData restored = resumed.captureSaveData();

        REQUIRE(restored.playerName == "Astra");
        REQUIRE(restored.visorColor.r == 65);
        REQUIRE(restored.visorColor.g == 225);
        REQUIRE(restored.level == 8);
        REQUIRE(restored.currentXP == 123);
        REQUIRE(restored.attributePoints == 4);
        REQUIRE(restored.skillPoints == 3);
        REQUIRE(restored.attributes.strength == 31);
        REQUIRE(restored.playerX == Approx(384.0f));
        REQUIRE(restored.playerY == Approx(176.0f));
        REQUIRE(restored.health == Approx(48.0f));
        REQUIRE(restored.mana == Approx(19.0f));
        REQUIRE(restored.power == Approx(22.0f));
        REQUIRE(restored.hunger == Approx(43.0f));
        REQUIRE(restored.thirst == Approx(29.0f));
        REQUIRE(restored.bodyTemp == Approx(34.5f));
        REQUIRE(resumed.getInventory().getItemCount("mat_test_ore") == 7);
        REQUIRE(resumed.getInventory().getEquipped(EquipSlot::MainHand) != nullptr);
        REQUIRE(resumed.getInventory().getEquipped(EquipSlot::MainHand)->id == "item_test_blade");
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
