#include <iostream>
#include <iomanip>
#include <chrono>
#include <thread>
#include "core/GameSimulation.hpp"
#include "procgen/DungeonGenerator.hpp"
#include "save/SaveManager.hpp"
#include "render/Camera.hpp"

void printDashboard(const GameSimulation& sim, const CanvasMetrics& metrics) {
    std::cout << "\033[2J\033[H"; // ANSI clear screen & home cursor
    std::cout << "================================================================================\n";
    std::cout << "                         UNTITLED RPG - ENGINE RUNNER                           \n";
    std::cout << "================================================================================\n";
    std::cout << " Canvas: " << metrics.virtualWidth << "x" << metrics.virtualHeight
              << " @ " << metrics.integerScale << "x Integer Scale (Viewport: "
              << metrics.viewportWidth << "x" << metrics.viewportHeight << ")\n";
    std::cout << " Simulation Time: " << std::fixed << std::setprecision(2)
              << sim.getSimulationTime() << "s | Ticks: " << sim.getTickCount() << "\n";
    std::cout << "--------------------------------------------------------------------------------\n";

    Vec2 pos = sim.getPlayerPosition();
    std::cout << " [PLAYER VITALS]\n";
    std::cout << " Level: " << sim.getPlayerLevel() << " | XP: " << sim.getPlayerXP() << "\n";
    std::cout << " Health: " << std::setprecision(1) << sim.getPlayerHealth() << " HP\n";
    std::cout << " Hunger: " << sim.getPlayerHunger() << "%\n";
    std::cout << " Position: (" << pos.x << ", " << pos.y << ")\n";
    std::cout << " Active Enemies: " << sim.getEnemyCount() << "\n";
    std::cout << "--------------------------------------------------------------------------------\n";
    std::cout << " [SIMULATION EVENTS]\n";
    std::cout << " - Player walking through Overworld\n";
    std::cout << " - Fixed 60 Hz physics sweeps active\n";
    std::cout << " - Procedural Dungeon Generator initialized\n";
    std::cout << "================================================================================\n";
}

int main() {
    std::cout << "Initializing Untitled RPG...\n";

    GameSimulation sim;
    sim.initialize(ClassType::Juggernaut);

    CanvasMetrics metrics = Camera::calculateCanvasMetrics(1920, 1080);

    // Generate a sample procedural dungeon layout
    Random rng(42);
    DungeonGenerator dungeonGen(rng);
    DungeonConfig dConfig{60, 40, 6, 12, 4};
    DungeonLayout layout = dungeonGen.generate(dConfig);

    std::cout << "Procedural Dungeon Generated: " << layout.rooms.size() << " rooms carved.\n";
    std::cout << "Start Room: #" << layout.startRoomIndex
              << " | Boss Room: #" << layout.bossRoomIndex << "\n";

    // Run simulation loop for 60 ticks (1 second demonstration)
    ControllerInput input;
    input.moveX = 1.0f; // Walk right

    for (int tick = 0; tick < 60; ++tick) {
        sim.step(input, 1.0f / 60.0f);

        // Every 20 ticks trigger an attack swing
        if (tick % 20 == 0) {
            sim.playerAttack();
        }

        if (tick % 20 == 0) {
            printDashboard(sim, metrics);
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

    std::cout << "Untitled RPG Core Engine & Gameplay Pipeline running successfully.\n";
    return 0;
}
