#include <iostream>
#include <iomanip>
#include <chrono>
#include <thread>
#include <string>

#include "core/GameSimulation.hpp"
#include "ecs/Components.hpp"
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

int main(int argc, char* argv[]) {
    bool headless = false;
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "--headless" || arg == "-h" || arg == "--benchmark") {
            headless = true;
        }
    }

    std::cout << "================================================================================\n";
    std::cout << "                         UNTITLED RPG - ENGINE RUNNER                           \n";
    std::cout << "                   C++20 / SDL3 / Box2D v3 / EnTT Architecture                  \n";
    std::cout << "================================================================================\n";

    GameSimulation sim;
    sim.initialize(ClassType::Juggernaut);

    // Generate Procedural Dungeon
    Random rng(1337);
    DungeonGenerator dungeonGen(rng);
    DungeonConfig dConfig{60, 40, 6, 12, 4};
    DungeonLayout layout = dungeonGen.generate(dConfig);
    std::cout << "Procedural Dungeon Generated: " << layout.rooms.size() << " rooms carved.\n";
    std::cout << "Start Room: #" << layout.startRoomIndex
              << " | Boss Room: #" << layout.bossRoomIndex << "\n\n";

    CanvasMetrics metrics = Camera::calculateCanvasMetrics(1280, 720);

    if (headless) {
        runHeadlessBenchmark(sim, metrics, 600);
    } else {
        std::cout << "Initializing SDL3 Graphical Window (1280x720, Virtual Canvas 640x360)...\n";
        Renderer renderer;
        bool ok = renderer.init("Untitled RPG [Pre-Alpha] - 2D Action Platformer", 1280, 720, 640, 360);

        if (!ok) {
            std::cout << "Display server not available. Falling back to headless simulation.\n";
            runHeadlessBenchmark(sim, metrics, 600);
        } else {
            std::cout << "Window created successfully! Controls:\n";
            std::cout << " [A] / [D] : Move Left / Right\n";
            std::cout << " [Space]   : Jump / Double Jump\n";
            std::cout << " [L-Shift] : Sprint / Dash\n";
            std::cout << " [L-Click] : Swing Greatsword / Attack\n";
            std::cout << " [1] - [8] : Select Hotbar Item\n";
            std::cout << " [Esc]     : Quit\n";

            InputManager inputMgr;
            Camera camera;
            TimeStep timeStep(60.0f);
            auto lastTime = std::chrono::high_resolution_clock::now();
            bool running = true;

            while (running) {
                auto currentTime = std::chrono::high_resolution_clock::now();
                float frameDelta = std::chrono::duration<float>(currentTime - lastTime).count();
                lastTime = currentTime;

                // Process SDL Window & Input Events
                inputMgr.processEvents(metrics, camera);
                const auto& inputState = inputMgr.getState();

                if (inputState.quitRequested) {
                    running = false;
                    break;
                }

                // Handle UI Screen toggles
                if (inputState.toggleInventory) sim.toggleScreen(ActiveScreen::Inventory);
                if (inputState.toggleCrafting) sim.toggleScreen(ActiveScreen::Crafting);
                if (inputState.toggleAugmentations) sim.toggleScreen(ActiveScreen::Augmentations);
                if (inputState.toggleMinimap) sim.toggleScreen(ActiveScreen::Minimap);

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
                    if (inputState.attackPressed) {
                        bool mined = sim.mineTileAt(inputState.mouseWorldPos);
                        if (!mined) {
                            sim.playerAttack();
                        }
                    }

                    // Right Click: Try placing block or shoot projectile
                    if (inputState.secondaryPressed) {
                        bool placed = sim.placeBlockAt(inputState.mouseWorldPos, "mat_wood_plank", 3);
                        if (!placed) {
                            sim.shootProjectile(inputState.mouseWorldPos);
                        }
                    }

                    sim.step(inputState.controller, 1.0f / 60.0f);
                }

                // Camera follows player
                Vec2 playerPos = sim.getPlayerPosition();
                camera.setPosition(playerPos);

                // Render Virtual Frame
                renderer.beginFrame();

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
                    renderer.drawEntity(trans.position, Vec2{16.0f, 16.0f}, Color{200, 45, 55, 255}, camera, metrics, -1, false, ratio);
                }

                // Draw player
                renderer.drawEntity(playerPos, Vec2{16.0f, 24.0f}, Color{65, 115, 220, 255}, camera, metrics, sim.getPlayerFacing(), true, 1.0f);

                // Draw attack slash
                if (sim.isAttacking()) {
                    renderer.drawSlashArc(sim.getLastAttackBox(), camera, metrics, sim.getPlayerFacing());
                }

                // Dynamic 2D Lighting overlay
                float darkness = sim.getContext().dayNight.getAmbientDarkness();
                renderer.drawLightingOverlay(playerPos, darkness, camera, metrics);

                // Draw HUD & Crosshair
                renderer.drawHUD(sim, metrics, inputState);

                // Draw Active Overlay UI Screen
                switch (sim.getActiveScreen()) {
                    case ActiveScreen::Inventory:
                        renderer.drawInventoryScreen(sim.getInventory(), metrics);
                        break;
                    case ActiveScreen::Crafting:
                        renderer.drawCraftingScreen(sim.getCraftingEngine(), sim.getInventory(), metrics);
                        break;
                    case ActiveScreen::Augmentations:
                        renderer.drawAugmentationScreen(sim.getAugmentations(), metrics);
                        break;
                    case ActiveScreen::Minimap:
                        renderer.drawMinimap(sim.getDungeonLayout(), playerPos, metrics);
                        break;
                    default:
                        break;
                }

                // Blit to screen
                renderer.endFrame(metrics);

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

    // Save game state to file
    SaveData save;
    save.playerName = "Vanguard";
    save.className = "Juggernaut";
    save.level = sim.getPlayerLevel();
    save.currentXP = sim.getPlayerXP();
    save.health = sim.getPlayerHealth();
    save.hunger = sim.getPlayerHunger();

    std::string saveFile = "save_slot_01.sav";
    bool saved = SaveManager::saveToFile(saveFile, save);
    std::cout << "\nGame session saved to '" << saveFile << "': " << (saved ? "SUCCESS" : "FAILED") << "\n";
    std::cout << "Untitled RPG execution completed cleanly.\n";

    return 0;
}
