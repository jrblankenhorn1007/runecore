#include "core/MainRunner.hpp"
#include <iostream>
#include <iomanip>
#include <chrono>
#include <thread>
#include <string>
#include <vector>
#include <filesystem>
#include <fstream>

#include "core/GameSimulation.hpp"
#include "core/BotTester.hpp"
#include "ecs/Components.hpp"
#include "gameplay/items/LootSystem.hpp"
#include "procgen/DungeonGenerator.hpp"
#include "save/SaveManager.hpp"
#include "render/Renderer.hpp"
#include "render/Camera.hpp"
#include "input/InputManager.hpp"
#include "core/Time.hpp"

void runHeadlessBenchmark(GameSimulation& sim, const CanvasMetrics& metrics, int totalTicks = 600) {
    std::cout << "Running headless simulation benchmark (" << totalTicks << " ticks @ 60 Hz)...\n";
    ControllerInput input;
    input.moveX = 1.0f; // Walk right

    for (int tick = 0; tick < totalTicks; ++tick) {
        sim.step(input, 1.0f / 60.0f);

        // Every 30 ticks trigger an attack swing
        if (tick % 30 == 0) {
            sim.playerAttack();
        }

        if (tick % 120 == 0 || tick == totalTicks - 1) {
            Vec2 pos = sim.getPlayerPosition();
            std::cout << "[Tick " << std::setw(3) << tick << "] Time: "
                      << std::fixed << std::setprecision(2) << sim.getSimulationTime()
                      << "s | Level: " << sim.getPlayerLevel()
                      << " | HP: " << std::setprecision(1) << sim.getPlayerHealth()
                      << " | Hunger: " << sim.getPlayerHunger()
                      << "% | Pos: (" << pos.x << ", " << pos.y
                      << ") | Enemies: " << sim.getEnemyCount() << "\n";
        }
    }
}

void runHeadlessBotTest(GameSimulation& sim, int totalTicks = 550) {
    std::cout << "Starting Autonomous Bot Gameplay Test Suite...\n";
    BotTester bot;
    bot.reset();

    std::string lastPhase = "";
    for (int tick = 0; tick < totalTicks; ++tick) {
        if (bot.isFinished()) break;

        std::string currentPhase = bot.getCurrentPhaseName();
        if (currentPhase != lastPhase) {
            std::cout << " -> " << currentPhase << " (Tick " << tick << ")...\n";
            lastPhase = currentPhase;
        }

        RawInputState input = bot.update(sim, 1.0f / 60.0f);
        sim.step(input.controller, 1.0f / 60.0f);
    }

    bot.getReport().printSummary();
}

int runGame(int argc, char* argv[]) {
    bool headless = false;
    bool botMode = false;
    bool manualMode = false;
    bool qaMode = false;
    bool visualQaMode = false;
    bool qaList = false;
    std::string qaScenario;
    float maxDuration = 10.0f; // Default 10s demo runtime if unattended
    const std::vector<std::string> visualQaScenarios{
        "movement", "jump", "mining", "projectile", "melee", "feedback",
        "dungeon", "inventory_drag", "crafting_gui", "augmentations_gui",
        "character_sheet", "skill_tree", "farming", "asset_pipeline"
    };

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "--headless" || arg == "-h" || arg == "--benchmark") {
            headless = true;
        } else if (arg == "--manual" || arg == "-m") {
            manualMode = true;
            botMode = false;
            maxDuration = 0.0f; // Manual mode runs indefinitely
        } else if (arg == "--bot" || arg == "--auto-test" || arg == "-b") {
            botMode = true;
            manualMode = false;
        } else if (arg == "--duration" && i + 1 < argc) {
            maxDuration = std::stof(argv[++i]);
        } else if (arg == "--qa" && i + 1 < argc) {
            qaMode = true;
            headless = true;
            botMode = false;
            qaScenario = argv[++i];
        } else if (arg == "--visual-qa" && i + 1 < argc) {
            visualQaMode = true;
            headless = false;
            botMode = false;
            manualMode = false;
            maxDuration = 5.0f;
            qaScenario = argv[++i];
            if (qaScenario == "all") {
                maxDuration = 5.0f * static_cast<float>(visualQaScenarios.size());
            }
        } else if (arg == "--qa-list") {
            qaList = true;
            headless = true;
            botMode = false;
        }
    }

    std::cout << "================================================================================\n";
    std::cout << "                         UNTITLED RPG - ENGINE RUNNER                           \n";
    std::cout << "                   C++20 / SDL3 / Box2D v3 / EnTT Architecture                  \n";
    std::cout << "================================================================================\n";

    GameSimulation sim;
    sim.initialize(ClassType::Juggernaut, headless || qaMode);

    if (qaList) {
        std::cout << "Focused QA scenarios:\n";
        for (const auto& scenario : getFocusedScenarioNames()) {
            std::cout << "  " << scenario << "\n";
        }
        std::cout << "  all\n";
        return 0;
    }

    if (qaMode) {
        FocusedScenarioResult result = runFocusedScenario(qaScenario);
        printFocusedScenarioResult(result);
        return result.passed ? 0 : 1;
    }

    // Generate Procedural Dungeon
    Random rng(1337);
    DungeonGenerator dungeonGen(rng);
    DungeonConfig dConfig{60, 40, 6, 12, 4};
    DungeonLayout layout = dungeonGen.generate(dConfig);
    std::cout << "Procedural Dungeon Generated: " << layout.rooms.size() << " rooms carved.\n";
    std::cout << "Start Room: #" << layout.startRoomIndex
              << " | Boss Room: #" << layout.bossRoomIndex << "\n\n";

    CanvasMetrics metrics = Camera::calculateCanvasMetrics(1280, 720);
    bool visualQaPassed = true;
    bool visualActionDone = false;

    if (visualQaMode) {
        std::filesystem::create_directories("build/visual_qa");
        if (qaScenario == "all") {
            for (const auto& scenario : visualQaScenarios) {
                std::filesystem::remove("build/visual_qa/" + scenario + ".bmp");
                std::filesystem::remove("build/visual_qa/" + scenario + ".json");
            }
        } else {
            std::filesystem::remove("build/visual_qa/" + qaScenario + ".bmp");
            std::filesystem::remove("build/visual_qa/" + qaScenario + ".json");
        }
    }

    if (headless && !manualMode) {
        runHeadlessBotTest(sim, 550);
    } else if (headless) {
        runHeadlessBenchmark(sim, metrics, 600);
    } else {
        std::cout << "Initializing SDL3 Graphical Window (1280x720, Native Render 1280x720)...\n";
        if (botMode) {
            std::cout << "MODE: Autonomous Bot Controller Active (Playing the game automatically!)\n";
        }

        Renderer renderer;
        bool ok = renderer.init("Untitled RPG [Pre-Alpha] - 2D Action Platformer");

        if (!ok) {
            if (visualQaMode) {
                std::cout << "Visual QA requires an available SDL display.\n";
                return 1;
            }
            std::cout << "Display server not available. Falling back to headless simulation.\n";
            if (botMode) {
                runHeadlessBotTest(sim, 550);
            } else {
                runHeadlessBenchmark(sim, metrics, 600);
            }
        } else {
            const auto missingAssets = renderer.getMissingGeneratedAssets();
            if (visualQaMode && !missingAssets.empty()) {
                std::cerr << "[VISUAL QA] required generated assets failed to load:\n";
                for (const auto& asset : missingAssets) std::cerr << "  " << asset << '\n';
                renderer.shutdown();
                return 1;
            }
            int windowWidth = 1280;
            int windowHeight = 720;
            SDL_GetWindowSize(renderer.getWindow(), &windowWidth, &windowHeight);
            metrics = Camera::calculateCanvasMetrics(windowWidth, windowHeight);
            std::cout << "Window created successfully! Controls:\n";
            std::cout << " [A] / [D] : Move Left / Right\n";
            std::cout << " [Space]   : Jump / Double Jump\n";
            std::cout << " [L-Shift] : Sprint / Dash\n";
            std::cout << " [L-Click] : Swing Greatsword / Attack / Mine Tile\n";
            std::cout << " [R-Click] : Shoot Projectile / Place Block\n";
            std::cout << " [Q,E,R,F] : Active Skills\n";
            std::cout << " [Tab]     : Inventory | [C] Crafting | [U] Augments | [M] Minimap\n";
            std::cout << " [Esc]     : Quit\n\n";

            InputManager inputMgr;
            Camera camera;
            TimeStep timeStep(60.0f);
            BotTester bot;
            if (botMode) bot.reset();
            std::string activeVisualScenario = qaScenario;
            int visualScenarioIndex = 0;
            if (visualQaMode && qaScenario == "all") {
                activeVisualScenario = visualQaScenarios.front();
            }
            Vec2 visualScenarioStartPosition = sim.getPlayerPosition();

            auto lastTime = std::chrono::high_resolution_clock::now();
            auto startTime = lastTime;
            bool running = true;
            std::string lastPhase = "";
            int displayedLevel = sim.getPlayerLevel();
            int draggedInventorySlot = -1;
            int visualInventorySourceSlot = -1;
            int visualInventoryStep = 0;
            bool visualScreenshotSaved = false;
            size_t visualProjectileCountBefore = 0;
            bool visualProjectileSpawned = false;
            bool visualAssetRosterSpawned = false;

            auto countProjectiles = [&sim]() {
                size_t count = 0;
                for (auto entity : sim.getContext().registry.view<ProjectileComponent>()) {
                    (void)entity;
                    ++count;
                }
                return count;
            };

            while (running) {
                auto currentTime = std::chrono::high_resolution_clock::now();
                float frameDelta = std::chrono::duration<float>(currentTime - lastTime).count();
                lastTime = currentTime;

                // Duration timeout check if set
                if (maxDuration > 0.0f) {
                    float totalElapsed = std::chrono::duration<float>(currentTime - startTime).count();
                    if (totalElapsed >= maxDuration) {
                        if (visualQaMode && !visualActionDone) {
                            std::cerr << "[VISUAL QA] timed out before scripted action completed: "
                                      << activeVisualScenario << " at simulation time "
                                      << sim.getSimulationTime() << "\n";
                        }
                        running = false;
                        break;
                    }
                }

                RawInputState inputState;

                if (visualQaMode && qaScenario == "all") {
                    const int nextScenarioIndex = std::min(
                        static_cast<int>(visualQaScenarios.size()) - 1,
                        static_cast<int>(sim.getSimulationTime() / 5.0f));
                    if (nextScenarioIndex != visualScenarioIndex) {
                        if (!visualActionDone) visualQaPassed = false;
                        visualScenarioIndex = nextScenarioIndex;
                        activeVisualScenario = visualQaScenarios[visualScenarioIndex];
                        visualActionDone = false;
                        visualScreenshotSaved = false;
                        visualScenarioStartPosition = sim.getPlayerPosition();
                        visualInventorySourceSlot = -1;
                        visualInventoryStep = 0;
                        visualProjectileSpawned = false;
                        visualAssetRosterSpawned = false;
                    }
                }

                // Process human input events first
                inputMgr.processEvents(metrics, camera);
                RawInputState humanInput = inputMgr.getState();

                if (humanInput.quitRequested) {
                    running = false;
                    break;
                }

                // Check if human acted to override bot
                bool humanInteracted = (humanInput.controller.moveX != 0.0f || humanInput.controller.moveY != 0.0f ||
                                        humanInput.controller.jumpPressed || humanInput.attackPressed ||
                                        humanInput.secondaryPressed || humanInput.skillQ || humanInput.skillE ||
                                        humanInput.skillR || humanInput.skillF || humanInput.toggleInventory ||
                                        humanInput.toggleCharacterSheet || humanInput.toggleSkills || humanInput.toggleSettings);

                if (humanInteracted && !manualMode && !visualQaMode) {
                    manualMode = true;
                    botMode = false;
                    maxDuration = 0.0f; // Human is playing, do not auto-close
                    std::cout << " [INPUT] Manual player control engaged.\n";
                }

                if (visualQaMode) {
                    inputState = RawInputState{};
                    const float visualTime = sim.getSimulationTime() - static_cast<float>(visualScenarioIndex) * 5.0f;
                    if (visualTime >= 0.2f && !visualAssetRosterSpawned) {
                        const Vec2 origin = sim.getPlayerPosition();
                        sim.spawnEnemy(origin + Vec2{72.0f, 0.0f}, 40.0f, 50, EnemyType::Slime);
                        sim.spawnEnemy(origin + Vec2{120.0f, 0.0f}, 40.0f, 50, EnemyType::Bat);
                        sim.spawnEnemy(origin + Vec2{168.0f, 0.0f}, 40.0f, 50, EnemyType::Raptor);
                        sim.spawnEnemy(origin + Vec2{216.0f, 0.0f}, 40.0f, 50, EnemyType::CyberGunner);
                        const auto spawnLoot = [&sim, &origin](const Vec2& offset, const char* id,
                                                               const char* name, ItemCategory category) {
                            Item item;
                            item.id = id;
                            item.name = name;
                            item.category = category;
                            const auto entity = sim.getContext().registry.create();
                            sim.getContext().registry.emplace<DroppedItemComponent>(entity, item);
                            sim.getContext().registry.emplace<TransformComponent>(entity, origin + offset);
                        };
                        spawnLoot(Vec2{220.0f, -20.0f}, "item_starter_blade", "Forged Scrap Blade", ItemCategory::Weapon);
                        spawnLoot(Vec2{250.0f, -20.0f}, "mat_iron_ore", "Iron Ore", ItemCategory::Material);
                        spawnLoot(Vec2{280.0f, -20.0f}, "mat_wood_plank", "Wood Plank", ItemCategory::Material);
                        visualAssetRosterSpawned = true;
                    }
                    if (activeVisualScenario == "movement") {
                        inputState.controller.moveX = visualTime < 2.0f ? 1.0f : 0.0f;
                        visualActionDone = visualTime >= 2.0f &&
                                           sim.getPlayerPosition().distanceTo(visualScenarioStartPosition) > 4.0f;
                    } else if (activeVisualScenario == "jump") {
                        inputState.controller.jumpPressed = visualTime >= 0.5f && visualTime < 0.55f;
                        visualActionDone = visualTime >= 0.8f &&
                                           visualScenarioStartPosition.y - sim.getPlayerPosition().y > 4.0f;
                    } else if (activeVisualScenario == "mining" && visualTime >= 0.8f && !visualActionDone) {
                        visualActionDone = sim.mineTileAt(sim.getPlayerPosition() + Vec2{0.0f, 16.0f});
                    } else if (activeVisualScenario == "projectile" && visualTime >= 0.8f && !visualActionDone) {
                        visualProjectileCountBefore = countProjectiles();
                        sim.shootProjectile(sim.getPlayerPosition() + Vec2{120.0f, -30.0f});
                        visualProjectileSpawned = countProjectiles() > visualProjectileCountBefore;
                        visualActionDone = visualProjectileSpawned;
                    } else if (activeVisualScenario == "melee" && visualTime >= 0.8f && !visualActionDone) {
                        sim.spawnEnemy(sim.getPlayerPosition() + Vec2{28.0f, 0.0f}, 40.0f, 50);
                        sim.playerAttack();
                        visualActionDone = true;
                    } else if (activeVisualScenario == "feedback" && visualTime >= 0.8f && !visualActionDone) {
                        sim.getFloatingText().spawnDamage(sim.getPlayerPosition(), 25.0f);
                        sim.getFloatingText().spawnDamage(sim.getPlayerPosition() + Vec2{10.0f, 0.0f}, 40.0f, true);
                        sim.getFloatingText().spawnHeal(sim.getPlayerPosition() + Vec2{20.0f, 0.0f}, 15.0f);
                        sim.getParticles().emitBurst(sim.getPlayerPosition(), 18, Color{255, 180, 70, 255}, 0.8f, 90.0f);
                        sim.getAudio().playSound(SoundEffect::CritHit);
                        visualActionDone = true;
                    } else if (activeVisualScenario == "dungeon" && visualTime >= 0.8f && !visualActionDone) {
                        sim.enterDungeon();
                        visualActionDone = true;
                    } else if (activeVisualScenario == "inventory_drag" && visualInventoryStep == 0 && visualTime >= 0.2f) {
                        Item scrap;
                        scrap.id = "mat_scrap";
                        scrap.name = "Scrap";
                        scrap.category = ItemCategory::Material;
                        scrap.quantity = 2;
                        sim.getInventory().addItem(scrap);
                        for (int index = 0; index < sim.getInventory().getSlotCount(); ++index) {
                            const auto slot = sim.getInventory().getSlot(index);
                            if (slot.has_value() && slot->id == scrap.id) {
                                visualInventorySourceSlot = index;
                                break;
                            }
                        }
                        sim.toggleScreen(ActiveScreen::Inventory);
                        visualInventoryStep = 1;
                    } else if (activeVisualScenario == "inventory_drag" && visualInventoryStep == 1 && visualTime >= 0.8f && visualInventorySourceSlot >= 0) {
                        const int column = visualInventorySourceSlot % 8;
                        const int row = visualInventorySourceSlot / 8;
                        inputState.mouseScreenPos = Vec2{
                            (60.0f + static_cast<float>(column) * 26.0f + 8.0f) * metrics.integerScale,
                            (60.0f + static_cast<float>(row) * 26.0f + 8.0f) * metrics.integerScale
                        };
                        inputState.attackPressed = true;
                        visualInventoryStep = 2;
                    } else if (activeVisualScenario == "inventory_drag" && visualInventoryStep == 2 && visualTime >= 1.1f) {
                        inputState.mouseScreenPos = Vec2{
                            (60.0f + 7.0f * 26.0f + 8.0f) * metrics.integerScale,
                            (60.0f + 8.0f) * metrics.integerScale
                        };
                        inputState.attackPressed = true;
                        visualInventoryStep = 3;
                        visualActionDone = true;
                    } else if (activeVisualScenario == "crafting_gui" && visualTime >= 0.2f && !visualActionDone) {
                        sim.toggleScreen(ActiveScreen::Crafting);
                        visualActionDone = true;
                    } else if (activeVisualScenario == "augmentations_gui" && visualTime >= 0.2f && !visualActionDone) {
                        sim.toggleScreen(ActiveScreen::Augmentations);
                        visualActionDone = true;
                    } else if (activeVisualScenario == "character_sheet" && visualTime >= 0.2f && !visualActionDone) {
                        sim.toggleScreen(ActiveScreen::CharacterSheet);
                        visualActionDone = true;
                    } else if (activeVisualScenario == "skill_tree" && visualTime >= 0.2f && !visualActionDone) {
                        sim.toggleScreen(ActiveScreen::Skills);
                        visualActionDone = true;
                    } else if (activeVisualScenario == "farming" && visualTime >= 0.2f && !visualActionDone) {
                        sim.getFarming().tillSoil(8, 8);
                        sim.getFarming().waterSoil(8, 8);
                        sim.getFarming().plantSeed(8, 8, "crop_wheat");
                        visualActionDone = true;
                    } else if (activeVisualScenario == "asset_pipeline" && visualTime >= 0.8f && !visualActionDone) {
                        sim.toggleScreen(ActiveScreen::Inventory);
                        visualActionDone = true;
                    }
                }

                if (botMode) {
                    // Bot controls the game
                    inputState = bot.update(sim, 1.0f / 60.0f);

                    std::string currentPhase = bot.getCurrentPhaseName();
                    if (currentPhase != lastPhase) {
                        std::cout << " [BOT] -> " << currentPhase << "\n";
                        lastPhase = currentPhase;
                    }

                    if (bot.isFinished()) {
                        bot.getReport().printSummary();
                        running = false;
                        break;
                    }
                } else if (!visualQaMode) {
                    inputState = humanInput;
                }

                // Handle UI Screen toggles
                if (inputState.toggleInventory) sim.toggleScreen(ActiveScreen::Inventory);
                if (inputState.toggleCrafting) sim.toggleScreen(ActiveScreen::Crafting);
                if (inputState.toggleAugmentations) sim.toggleScreen(ActiveScreen::Augmentations);
                if (inputState.toggleMinimap) sim.toggleScreen(ActiveScreen::Minimap);
                if (inputState.toggleCharacterSheet) sim.toggleScreen(ActiveScreen::CharacterSheet);
                if (inputState.toggleSkills) sim.toggleScreen(ActiveScreen::Skills);
                if (inputState.toggleSettings) sim.toggleScreen(ActiveScreen::Settings);

                bool handledUiClick = false;
                bool handledUiSecondary = false;
                if (sim.getActiveScreen() == ActiveScreen::Inventory &&
                    (inputState.attackPressed || inputState.secondaryPressed || draggedInventorySlot >= 0)) {
                    float virtualX = (inputState.mouseScreenPos.x - metrics.letterboxX) / metrics.integerScale;
                    float virtualY = (inputState.mouseScreenPos.y - metrics.letterboxY) / metrics.integerScale;
                    int column = static_cast<int>((virtualX - 60.0f) / 26.0f);
                    int row = static_cast<int>((virtualY - 60.0f) / 26.0f);
                    int slot = row * 8 + column;
                    bool validSlot = column >= 0 && column < 8 && row >= 0 && row < 5;
                    if (validSlot && inputState.attackPressed) {
                        if (draggedInventorySlot < 0) {
                            if (sim.getInventory().getSlot(slot).has_value()) {
                                draggedInventorySlot = slot;
                                handledUiClick = true;
                            }
                        } else {
                            handledUiClick = sim.getInventory().moveSlot(draggedInventorySlot, slot);
                            draggedInventorySlot = -1;
                        }
                    } else if (inputState.attackPressed && draggedInventorySlot >= 0 &&
                               virtualX >= 310.0f && virtualX < 406.0f && virtualY >= 60.0f && virtualY < 210.0f) {
                        int paperColumn = static_cast<int>((virtualX - 310.0f) / 48.0f);
                        int paperRow = static_cast<int>((virtualY - 60.0f) / 30.0f);
                        int equipmentIndex = paperRow * 2 + paperColumn;
                        static constexpr EquipSlot equipmentSlots[] = {
                            EquipSlot::MainHand, EquipSlot::OffHand, EquipSlot::Helmet, EquipSlot::Chestplate,
                            EquipSlot::Greaves, EquipSlot::Boots, EquipSlot::Ring1, EquipSlot::Ring2,
                            EquipSlot::Amulet, EquipSlot::Relic
                        };
                        if (equipmentIndex >= 0 && equipmentIndex < 10) {
                            handledUiClick = sim.getInventory().equipItem(equipmentSlots[equipmentIndex], draggedInventorySlot);
                            draggedInventorySlot = -1;
                        }
                    } else if (draggedInventorySlot >= 0 && !inputState.attackHeld &&
                               virtualX >= 310.0f && virtualX < 406.0f && virtualY >= 60.0f && virtualY < 210.0f) {
                        int paperColumn = static_cast<int>((virtualX - 310.0f) / 48.0f);
                        int paperRow = static_cast<int>((virtualY - 60.0f) / 30.0f);
                        int equipmentIndex = paperRow * 2 + paperColumn;
                        static constexpr EquipSlot equipmentSlots[] = {
                            EquipSlot::MainHand, EquipSlot::OffHand, EquipSlot::Helmet, EquipSlot::Chestplate,
                            EquipSlot::Greaves, EquipSlot::Boots, EquipSlot::Ring1, EquipSlot::Ring2,
                            EquipSlot::Amulet, EquipSlot::Relic
                        };
                        if (equipmentIndex >= 0 && equipmentIndex < 10) {
                            handledUiClick = sim.getInventory().equipItem(equipmentSlots[equipmentIndex], draggedInventorySlot);
                        }
                        draggedInventorySlot = -1;
                    } else if (draggedInventorySlot >= 0 && !inputState.attackHeld && validSlot) {
                        handledUiClick = sim.getInventory().moveSlot(draggedInventorySlot, slot);
                        draggedInventorySlot = -1;
                    } else if (validSlot && inputState.secondaryPressed) {
                        handledUiSecondary = sim.getInventory().consumeSlot(slot);
                    }
                } else if (inputState.attackPressed && sim.getActiveScreen() == ActiveScreen::Crafting) {
                    float virtualX = (inputState.mouseScreenPos.x - metrics.letterboxX) / metrics.integerScale;
                    float virtualY = (inputState.mouseScreenPos.y - metrics.letterboxY) / metrics.integerScale;
                    if (virtualX >= 65.0f && virtualX <= 530.0f && virtualY >= 55.0f && virtualY < 175.0f) {
                        int recipeIndex = static_cast<int>((virtualY - 55.0f) / 30.0f);
                        const auto recipeIds = sim.getCraftingEngine().getRecipeIds();
                        if (recipeIndex >= 0 && recipeIndex < static_cast<int>(recipeIds.size())) {
                            handledUiClick = sim.getCraftingEngine().craft(
                                recipeIds[static_cast<size_t>(recipeIndex)], sim.getInventory(), CraftingStation::None);
                        }
                    }
                }
                if (inputState.attackPressed && sim.getActiveScreen() == ActiveScreen::CharacterSheet) {
                    float virtualX = (inputState.mouseScreenPos.x - metrics.letterboxX) / metrics.integerScale;
                    float virtualY = (inputState.mouseScreenPos.y - metrics.letterboxY) / metrics.integerScale;
                    if (virtualX >= 540.0f && virtualX <= 585.0f && virtualY >= 74.0f && virtualY <= 235.0f) {
                        int attributeIndex = static_cast<int>((virtualY - 78.0f) / 28.0f);
                        handledUiClick = sim.allocateAttribute(attributeIndex);
                    }
                } else if (inputState.attackPressed && sim.getActiveScreen() == ActiveScreen::Skills) {
                    float virtualX = (inputState.mouseScreenPos.x - metrics.letterboxX) / metrics.integerScale;
                    float virtualY = (inputState.mouseScreenPos.y - metrics.letterboxY) / metrics.integerScale;
                    const char* nodeIds[] = {"mob_01", "comb_01", "mob_02", "surv_01"};
                    for (int nodeIndex = 0; nodeIndex < 4; ++nodeIndex) {
                        float nodeX = 54.0f + (nodeIndex % 2) * 250.0f;
                        float nodeY = 75.0f + (static_cast<float>(nodeIndex) / 2.0f) * 92.0f;
                        if (virtualX >= nodeX && virtualX <= nodeX + 210.0f && virtualY >= nodeY && virtualY <= nodeY + 58.0f) {
                            handledUiClick = sim.allocateSkill(nodeIds[nodeIndex]);
                            break;
                        }
                    }
                } else if (inputState.attackPressed && sim.getActiveScreen() == ActiveScreen::Settings) {
                    float virtualX = (inputState.mouseScreenPos.x - metrics.letterboxX) / metrics.integerScale;
                    float virtualY = (inputState.mouseScreenPos.y - metrics.letterboxY) / metrics.integerScale;
                    if (virtualY >= 92.0f && virtualY <= 116.0f) {
                        sim.getAudio().setMasterVolume(std::clamp((virtualX - 170.0f) / 300.0f, 0.0f, 1.0f));
                        handledUiClick = true;
                    } else if (virtualY >= 138.0f && virtualY <= 162.0f) {
                        sim.getAudio().setSFXVolume(std::clamp((virtualX - 170.0f) / 300.0f, 0.0f, 1.0f));
                        handledUiClick = true;
                    } else if (virtualY >= 184.0f && virtualY <= 208.0f) {
                        sim.getAudio().setMusicVolume(std::clamp((virtualX - 170.0f) / 300.0f, 0.0f, 1.0f));
                        handledUiClick = true;
                    } else if (virtualY >= 230.0f && virtualY <= 254.0f) {
                        sim.getAudio().setAmbienceVolume(std::clamp((virtualX - 170.0f) / 300.0f, 0.0f, 1.0f));
                        handledUiClick = true;
                    }
                }

                // Handle Dungeon Entrance / Exit Interaction
                if (inputState.interactPressed) {
                    if (sim.isInsideDungeon()) {
                        sim.exitDungeon();
                    } else if (sim.canEnterDungeon()) {
                        sim.enterDungeon();
                    }
                }

                // Handle Active Skills Q, E, R, F
                if (inputState.skillQ) sim.castSkillQ();
                if (inputState.skillE) sim.castSkillE();
                if (inputState.skillR) sim.castSkillR();
                if (inputState.skillF) sim.castSkillF();

                // Fixed 60 Hz simulation updates
                int ticks = timeStep.update(frameDelta);
                for (int t = 0; t < ticks; ++t) {
                    // Left Click: Try mining first; if not mining a solid tile, swing weapon
                    if (inputState.attackPressed && !handledUiClick) {
                        bool mined = sim.mineTileAt(inputState.mouseWorldPos);
                        if (!mined) {
                            sim.playerAttack();
                            camera.addShake(2.5f, 0.08f);
                        }
                    }

                    // Right Click: Try placing block or shoot projectile
                    if (inputState.secondaryPressed && !handledUiSecondary) {
                        bool placed = sim.placeBlockAt(inputState.mouseWorldPos, "mat_wood_plank", 3);
                        if (!placed) {
                            sim.shootProjectile(inputState.mouseWorldPos);
                        }
                    }

                    sim.step(inputState.controller, 1.0f / 60.0f);
                    if (sim.getPlayerLevel() > displayedLevel) {
                        displayedLevel = sim.getPlayerLevel();
                        sim.getFloatingText().spawnText(
                            sim.getPlayerPosition(),
                            "LEVEL " + std::to_string(displayedLevel),
                            Color{255, 220, 60, 255}, 1.5f, true);
                        sim.getParticles().emitBurst(
                            sim.getPlayerPosition(), 24, Color{255, 210, 50, 255}, 0.8f, 95.0f);
                        sim.getAudio().playSound(SoundEffect::LevelUp);
                        camera.addShake(3.0f, 0.12f);
                    }
                }

                // Camera follows player
                Vec2 playerPos = sim.getPlayerPosition();
                camera.setPosition(playerPos);
                camera.update(frameDelta);

                // Render Virtual Frame
                renderer.beginFrame();
                renderer.drawParallaxBackground(playerPos.x, static_cast<int>(playerPos.x / 2048.0f) % 3, metrics);

                // Draw tilemap around camera
                int camTileX = static_cast<int>(playerPos.x / 16.0f);
                int camTileY = static_cast<int>(playerPos.y / 16.0f);
                for (int ty = camTileY - 14; ty <= camTileY + 14; ++ty) {
                    for (int tx = camTileX - 22; tx <= camTileX + 22; ++tx) {
                        uint16_t block = sim.getContext().tilemap.getBlock(tx, ty, BlockLayer::Foreground);
                        if (block != 0) {
                            renderer.drawTile(tx, ty, block, camera, metrics);
                        }
                    }
                }

                // Draw dropped world loot items
                auto lootView = sim.getContext().registry.view<DroppedItemComponent, TransformComponent>();
                for (auto [lootE, drop, trans] : lootView.each()) {
                    renderer.drawLoot(trans.position, drop.item.name, camera, metrics);
                }

                // Draw active flying projectiles
                auto projView = sim.getContext().registry.view<ProjectileComponent, TransformComponent, VelocityComponent>();
                for (auto [projE, pComp, trans, vel] : projView.each()) {
                    renderer.drawProjectile(trans.position, vel.linear, Color{255, 220, 50, 255}, camera, metrics);
                }

                // Draw enemies
                auto enemyView = sim.getContext().registry.view<EnemyTag, TransformComponent, HealthComponent>();
                for (auto [e, tag, trans, hp] : enemyView.each()) {
                    float ratio = hp.max > 0.0f ? (hp.current / hp.max) : 1.0f;
                    Vec2 size{16.0f, 16.0f};
                    Color color{200, 45, 55, 255};
                    switch (tag.type) {
                        case EnemyType::Bat:
                            size = Vec2{20.0f, 12.0f};
                            color = Color{150, 75, 200, 255};
                            break;
                        case EnemyType::Raptor:
                            size = Vec2{22.0f, 18.0f};
                            color = Color{220, 125, 45, 255};
                            break;
                        case EnemyType::CyberGunner:
                            size = Vec2{14.0f, 20.0f};
                            color = Color{65, 180, 195, 255};
                            break;
                        case EnemyType::Slime:
                        default:
                            break;
                    }
                    if (hp.hitFlashTimer > 0.0f) {
                        color = Color{255, 255, 255, 255};
                    }
                    if (sim.getContext().registry.all_of<DeathAnimationComponent>(e)) {
                        const auto& death = sim.getContext().registry.get<DeathAnimationComponent>(e);
                        float progress = 1.0f - (death.remaining / death.duration);
                        float squash = 1.0f + progress * 0.8f;
                        float stretch = 1.0f - progress * 0.55f;
                        if (death.type == EnemyType::Bat) {
                            stretch = 1.0f + progress * 0.35f;
                            squash = 1.0f - progress * 0.25f;
                        }
                        size.x *= squash;
                        size.y *= stretch;
                    }
                    if (sim.getContext().registry.all_of<BossEncounterComponent>(e)) {
                        size = Vec2{28.0f, 34.0f};
                        color = Color{185, 45, 70, 255};
                        const auto& encounter = sim.getContext().registry.get<BossEncounterComponent>(e);
                        if (encounter.action.telegraphActive) {
                            renderer.drawBossTelegraph(trans.position, encounter.action.telegraphRadius, camera, metrics,
                                                       encounter.controller.isEnraged());
                        }
                    }
                    const bool hitFlash = hp.hitFlashTimer > 0.0f;
                    const bool showHealthBar = true;
                    if (tag.type == EnemyType::Slime) {
                        const int animationFrame = static_cast<int>(sim.getSimulationTime() * 8.0f) % 4;
                        renderer.drawGeneratedSlimeEnemy(trans.position, size, camera, metrics, ratio,
                                                        showHealthBar, hitFlash, animationFrame);
                    } else {
                        const char* assetPath = nullptr;
                        switch (tag.type) {
                            case EnemyType::Bat: assetPath = "assets/generated/enemies/bat/sprite/source.png"; break;
                            case EnemyType::Raptor: assetPath = "assets/generated/enemies/raptor/sprite/source.png"; break;
                            case EnemyType::CyberGunner: assetPath = "assets/generated/enemies/cyber_gunner/sprite/source.png"; break;
                            default: break;
                        }
                        if (!assetPath || !renderer.drawGeneratedEntity(assetPath, trans.position, size, camera, metrics,
                                                                        ratio, showHealthBar, hitFlash)) {
                            renderer.drawEntity(trans.position, size, color, camera, metrics, -1, false, ratio,
                                                hitFlash, showHealthBar);
                        }
                    }
                }

                // Draw player
                if (!renderer.drawGeneratedEntity("assets/generated/classes/berserker/sprite/source.png",
                                                  playerPos, Vec2{16.0f, 24.0f}, camera, metrics, 1.0f, false, false)) {
                    renderer.drawEntity(playerPos, Vec2{16.0f, 24.0f}, Color{65, 115, 220, 255}, camera, metrics,
                                        sim.getPlayerFacing(), true, 1.0f);
                }
                if (activeVisualScenario == "farming") {
                    renderer.drawFarmingPlot(8, 8, sim.getFarming().getCropStage(8, 8), camera, metrics);
                }
                renderer.drawWeapon(playerPos, inputState.mouseWorldPos, sim.isAttacking(), camera, metrics);

                // Draw attack slash
                if (sim.isAttacking()) {
                    renderer.drawSlashArc(sim.getLastAttackBox(), camera, metrics, sim.getPlayerFacing());
                }

                for (const auto& particle : sim.getParticles().getParticles()) {
                    if (particle.active) {
                        renderer.drawParticle(particle, camera, metrics);
                    }
                }

                for (const auto& text : sim.getFloatingText().getTexts()) {
                    if (text.active) {
                        renderer.drawFloatingText(text, camera, metrics);
                    }
                }

                // Dynamic 2D Lighting overlay
                float darkness = sim.getContext().dayNight.getAmbientDarkness();
                renderer.drawLightingOverlay(playerPos, darkness, camera, metrics);

                // Draw HUD & Crosshair
                renderer.drawHUD(sim, metrics, inputState);
                renderer.drawBossHUD(sim, metrics);

                // Draw Active Overlay UI Screen
                switch (sim.getActiveScreen()) {
                    case ActiveScreen::Inventory:
                        renderer.drawInventoryScreen(
                            sim.getInventory(), metrics,
                            Vec2{
                                (inputState.mouseScreenPos.x - metrics.letterboxX) / metrics.integerScale,
                                (inputState.mouseScreenPos.y - metrics.letterboxY) / metrics.integerScale
                            }, draggedInventorySlot);
                        break;
                    case ActiveScreen::Crafting:
                        renderer.drawCraftingScreen(sim.getCraftingEngine(), sim.getInventory(), metrics);
                        break;
                    case ActiveScreen::Augmentations:
                        renderer.drawAugmentationScreen(sim.getAugmentations(), metrics);
                        break;
                    case ActiveScreen::CharacterSheet:
                        renderer.drawCharacterSheet(sim.getProgression(), metrics);
                        break;
                    case ActiveScreen::Skills:
                        renderer.drawSkillTreeScreen(sim.getSkillTree(), sim.getProgression().getSkillPoints(), metrics);
                        break;
                    case ActiveScreen::Settings:
                        renderer.drawSettingsScreen(sim.getAudio(), metrics);
                        break;
                    case ActiveScreen::Minimap:
                        renderer.drawMinimap(sim.getDungeonLayout(), playerPos, metrics);
                        break;
                    default:
                        break;
                }

                if (visualQaMode) {
                    const float progress = qaScenario == "all"
                        ? std::clamp((sim.getSimulationTime() - static_cast<float>(visualScenarioIndex) * 5.0f) / 5.0f, 0.0f, 1.0f)
                        : std::clamp(sim.getSimulationTime() / maxDuration, 0.0f, 1.0f);
                    renderer.drawVisualQaOverlay(activeVisualScenario, progress, metrics);
                }

                // Blit to screen
                renderer.endFrame(metrics);

                if (visualQaMode && visualActionDone && !visualScreenshotSaved) {
                    const std::string screenshotPath = "build/visual_qa/" + activeVisualScenario + ".bmp";
                    const std::string reportPath = "build/visual_qa/" + activeVisualScenario + ".json";
                    const auto assetPath = [](const char* category, const char* entity, const char* label) {
                        return std::string("assets/generated/") + category + "/" + entity + "/" + label + "/source.png";
                    };
                    bool assetsRendered = true;
                    if (activeVisualScenario == "melee") {
                        assetsRendered = renderer.getGeneratedDrawCount(assetPath("classes", "berserker", "sprite")) > 0 &&
                                         renderer.getGeneratedDrawCount(assetPath("enemies", "slime_01", "sprite")) > 0;
                    } else if (activeVisualScenario == "inventory_drag" || activeVisualScenario == "asset_pipeline") {
                        assetsRendered = renderer.getGeneratedDrawCount(assetPath("items", "forged_scrap_blade", "icon")) > 0 &&
                                         renderer.getGeneratedDrawCount(assetPath("items", "iron_ore", "icon")) > 0 &&
                                         renderer.getGeneratedDrawCount(assetPath("items", "wood_plank", "icon")) > 0;
                    }
                    if (activeVisualScenario == "asset_pipeline") {
                        assetsRendered = assetsRendered &&
                            renderer.getGeneratedDrawCount(assetPath("classes", "berserker", "sprite")) > 0 &&
                            renderer.getGeneratedDrawCount(assetPath("enemies", "slime_01", "sprite")) > 0 &&
                            renderer.getGeneratedDrawCount(assetPath("enemies", "bat", "sprite")) > 0 &&
                            renderer.getGeneratedDrawCount(assetPath("enemies", "raptor", "sprite")) > 0 &&
                            renderer.getGeneratedDrawCount(assetPath("enemies", "cyber_gunner", "sprite")) > 0;
                    }
                    for (const auto& requiredAsset : Renderer::getRequiredGeneratedAssets()) {
                        if (requiredAsset == "assets/generated/classes/gunslinger/sprite/source.png") {
                            continue;
                        }
                        assetsRendered = assetsRendered && renderer.getGeneratedDrawCount(requiredAsset) > 0;
                    }
                    SDL_Surface* screenshot = SDL_RenderReadPixels(renderer.getSDLRenderer(), nullptr);
                    if (screenshot != nullptr) {
                        const bool saved = SDL_SaveBMP(screenshot, screenshotPath.c_str());
                        SDL_DestroySurface(screenshot);
                        std::ofstream report(reportPath);
                        report << "{\n  \"scenario\": \"" << activeVisualScenario
                               << "\",\n  \"assets_loaded\": true,\n  \"assets_rendered\": "
                               << (assetsRendered ? "true" : "false") << ",\n  \"screenshot\": \""
                               << screenshotPath << "\"\n}\n";
                        const bool reportSaved = report.good();
                        visualQaPassed = visualQaPassed && saved && reportSaved && assetsRendered;
                        std::cout << (saved && reportSaved && assetsRendered ? " [VISUAL QA] captured " : " [VISUAL QA] asset proof failed ")
                                  << screenshotPath << "\n";
                    } else {
                        std::cout << " [VISUAL QA] screenshot failed: " << SDL_GetError() << "\n";
                        visualQaPassed = false;
                    }
                    visualScreenshotSaved = true;
                }

                // Target 60 FPS frame pacing (~16.6ms)
                auto frameEndTime = std::chrono::high_resolution_clock::now();
                auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(frameEndTime - currentTime);
                if (elapsed.count() < 16) {
                    std::this_thread::sleep_for(std::chrono::milliseconds(16 - elapsed.count()));
                }
            }

            renderer.shutdown();
        }
    }

    if (visualQaMode) {
        return visualQaPassed && visualActionDone ? 0 : 1;
    }

    // Save game state to file
    SaveData save;
    save.playerName = "Vanguard";
    save.className = "Juggernaut";
    save.level = sim.getPlayerLevel();
    save.currentXP = sim.getPlayerXP();
    save.health = sim.getPlayerHealth();
    save.hunger = sim.getPlayerHunger();
    save.settings.masterVolume = sim.getAudio().getMasterVolume();
    save.settings.sfxVolume = sim.getAudio().getSFXVolume();
    save.settings.musicVolume = sim.getAudio().getMusicVolume();
    save.settings.ambienceVolume = sim.getAudio().getAmbienceVolume();

    const std::string saveDirectory = ".";
    bool saved = SaveManager::saveSlot(saveDirectory, 1, save);
    std::cout << "\nGame session saved to 'save_slot_01.sav': " << (saved ? "SUCCESS" : "FAILED") << "\n";
    std::cout << "Untitled RPG execution completed cleanly.\n";

    return 0;
}
