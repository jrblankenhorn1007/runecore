#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include <SDL3/SDL.h>
#include "core/MainRunner.hpp"
#include "save/SaveManager.hpp"
#include <atomic>
#include <chrono>
#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <sstream>
#include <string>
#include <string_view>
#include <thread>

TEST_CASE("MainRunner Headless and CLI Argument Variations", "[core][main_runner]") {
    SECTION("CTest SDL video and audio backends are headless") {
        const char* videoDriver = std::getenv("SDL_VIDEODRIVER");
        const char* audioDriver = std::getenv("SDL_AUDIODRIVER");
        REQUIRE(videoDriver != nullptr);
        REQUIRE(audioDriver != nullptr);
        REQUIRE(std::string_view(videoDriver) == "dummy");
        REQUIRE(std::string_view(audioDriver) == "dummy");
    }

    SECTION("Melee visual QA verifies the generated slime asset") {
        char* args[] = {
            const_cast<char*>("untitled_rpg"),
            const_cast<char*>("--visual-qa"),
            const_cast<char*>("melee")
        };
        REQUIRE(runGame(3, args) == 0);
    }

    SECTION("Jump visual QA completes its scripted action") {
        char* args[] = {
            const_cast<char*>("untitled_rpg"),
            const_cast<char*>("--visual-qa"),
            const_cast<char*>("jump")
        };
        REQUIRE(runGame(3, args) == 0);
    }

    SECTION("Default launch remains playable until the player quits") {
        const std::string saveDirectory =
            (std::filesystem::temp_directory_path() /
             ("runecore-default-launch-" +
              std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()))).string();
        const char* previousSaveDirectory = std::getenv("RUNECORE_SAVE_DIR");
        const bool hadPreviousSaveDirectory = previousSaveDirectory != nullptr;
        const std::string previousSaveDirectoryValue =
            hadPreviousSaveDirectory ? previousSaveDirectory : "";
        REQUIRE(setenv("RUNECORE_SAVE_DIR", saveDirectory.c_str(), 1) == 0);

        std::atomic<bool> cancelEvents{false};
        std::atomic<bool> gameplayInputPosted{false};
        std::atomic<bool> quitEventPosted{false};
        const auto eventScheduleStart = std::chrono::steady_clock::now();
        std::thread playAndQuit([&] {
            const auto postKey = [&](std::chrono::milliseconds offset, SDL_Keycode key) {
                const auto deadline = eventScheduleStart + offset;
                while (std::chrono::steady_clock::now() < deadline && !cancelEvents.load()) {
                    std::this_thread::sleep_for(std::chrono::milliseconds(5));
                }
                if (cancelEvents.load()) return;

                SDL_Event event{};
                event.type = SDL_EVENT_KEY_DOWN;
                event.key.key = key;
                event.key.repeat = 0;
                while (!SDL_PushEvent(&event) && !cancelEvents.load()) {
                    std::this_thread::sleep_for(std::chrono::milliseconds(10));
                }
            };
            postKey(std::chrono::milliseconds(400), SDLK_RETURN);
            postKey(std::chrono::milliseconds(650), SDLK_RETURN);
            postKey(std::chrono::milliseconds(900), SDLK_RETURN);

            const auto movementDeadline = eventScheduleStart + std::chrono::milliseconds(10500);
            while (std::chrono::steady_clock::now() < movementDeadline && !cancelEvents.load()) {
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
            }
            if (cancelEvents.load()) return;

            SDL_Event jump{};
            jump.type = SDL_EVENT_KEY_DOWN;
            jump.key.key = SDLK_SPACE;
            gameplayInputPosted.store(SDL_PushEvent(&jump));

            const auto quitDeadline = eventScheduleStart + std::chrono::seconds(12);
            while (std::chrono::steady_clock::now() < quitDeadline && !cancelEvents.load()) {
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
            }
            if (cancelEvents.load()) return;

            SDL_Event quit{};
            quit.type = SDL_EVENT_QUIT;
            quitEventPosted.store(SDL_PushEvent(&quit));
        });

        char* args[] = {const_cast<char*>("untitled_rpg")};
        const auto startTime = std::chrono::steady_clock::now();
        std::ostringstream output;
        std::streambuf* previousOutput = std::cout.rdbuf(output.rdbuf());
        const int exitCode = runGame(1, args);
        const auto elapsed = std::chrono::steady_clock::now() - startTime;
        std::cout.rdbuf(previousOutput);
        cancelEvents.store(true);
        playAndQuit.join();

        SaveData savedCharacter;
        const bool slotSaved = SaveManager::loadSlot(saveDirectory, 1, savedCharacter);
        const int environmentRestoreResult = hadPreviousSaveDirectory
            ? setenv("RUNECORE_SAVE_DIR", previousSaveDirectoryValue.c_str(), 1)
            : unsetenv("RUNECORE_SAVE_DIR");
        std::error_code cleanupError;
        std::filesystem::remove_all(saveDirectory, cleanupError);

        REQUIRE(environmentRestoreResult == 0);
        REQUIRE_FALSE(cleanupError);
        REQUIRE(exitCode == 0);
        REQUIRE(gameplayInputPosted.load());
        REQUIRE(quitEventPosted.load());
        REQUIRE(elapsed >= std::chrono::milliseconds(11500));
        REQUIRE(output.str().find("Manual player control engaged.") != std::string::npos);
        REQUIRE(slotSaved);
        REQUIRE(savedCharacter.playerName == "Vanguard");
        REQUIRE(savedCharacter.onboardingComplete);
    }

    SECTION("Interactive title flow creates and saves the selected character") {
        const std::string saveDirectory =
            (std::filesystem::temp_directory_path() /
             ("runecore-title-flow-" +
              std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()))).string();
        const char* previousSaveDirectory = std::getenv("RUNECORE_SAVE_DIR");
        const bool hadPreviousSaveDirectory = previousSaveDirectory != nullptr;
        const std::string previousSaveDirectoryValue =
            hadPreviousSaveDirectory ? previousSaveDirectory : "";
        REQUIRE(setenv("RUNECORE_SAVE_DIR", saveDirectory.c_str(), 1) == 0);

        std::atomic<bool> cancelEvents{false};
        std::atomic<bool> quitEventPosted{false};
        const auto eventScheduleStart = std::chrono::steady_clock::now();
        std::thread chooseCharacter([&] {
            const auto postKey = [&](std::chrono::milliseconds offset, SDL_Keycode key) {
                const auto deadline = eventScheduleStart + offset;
                while (std::chrono::steady_clock::now() < deadline && !cancelEvents.load()) {
                    std::this_thread::sleep_for(std::chrono::milliseconds(5));
                }
                if (cancelEvents.load()) return;

                SDL_Event event{};
                event.type = SDL_EVENT_KEY_DOWN;
                event.key.key = key;
                event.key.repeat = 0;
                while (!SDL_PushEvent(&event) && !cancelEvents.load()) {
                    std::this_thread::sleep_for(std::chrono::milliseconds(10));
                }
            };

            postKey(std::chrono::milliseconds(400), SDLK_RETURN);
            postKey(std::chrono::milliseconds(600), SDLK_RIGHT);
            postKey(std::chrono::milliseconds(800), SDLK_V);
            postKey(std::chrono::milliseconds(1000), SDLK_RETURN);
            postKey(std::chrono::milliseconds(1300), SDLK_SPACE);

            const auto quitDeadline = eventScheduleStart + std::chrono::milliseconds(1800);
            while (std::chrono::steady_clock::now() < quitDeadline && !cancelEvents.load()) {
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
            }
            if (cancelEvents.load()) return;

            SDL_Event quit{};
            quit.type = SDL_EVENT_QUIT;
            quitEventPosted.store(SDL_PushEvent(&quit));
        });

        char* args[] = {
            const_cast<char*>("untitled_rpg"),
            const_cast<char*>("--duration"),
            const_cast<char*>("2.0")
        };
        std::ostringstream output;
        std::streambuf* previousOutput = std::cout.rdbuf(output.rdbuf());
        const int exitCode = runGame(3, args);
        std::cout.rdbuf(previousOutput);
        cancelEvents.store(true);
        chooseCharacter.join();

        SaveData savedCharacter;
        const bool slotSaved = SaveManager::loadSlot(saveDirectory, 1, savedCharacter);
        const int environmentRestoreResult = hadPreviousSaveDirectory
            ? setenv("RUNECORE_SAVE_DIR", previousSaveDirectoryValue.c_str(), 1)
            : unsetenv("RUNECORE_SAVE_DIR");
        std::error_code cleanupError;
        std::filesystem::remove_all(saveDirectory, cleanupError);

        REQUIRE(environmentRestoreResult == 0);
        REQUIRE_FALSE(cleanupError);
        REQUIRE(exitCode == 0);
        REQUIRE(quitEventPosted.load());
        REQUIRE(slotSaved);
        REQUIRE(savedCharacter.className == "Berserker");
        REQUIRE(savedCharacter.onboardingComplete);
        REQUIRE(savedCharacter.playerY > 130.0f);
        REQUIRE(output.str().find("RUNECORE") != std::string::npos);
    }

    SECTION("Interactive title flow resumes progress from the selected save slot") {
        const std::string saveDirectory =
            (std::filesystem::temp_directory_path() /
             ("runecore-resume-flow-" +
              std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()))).string();
        const char* previousSaveDirectory = std::getenv("RUNECORE_SAVE_DIR");
        const bool hadPreviousSaveDirectory = previousSaveDirectory != nullptr;
        const std::string previousSaveDirectoryValue =
            hadPreviousSaveDirectory ? previousSaveDirectory : "";
        REQUIRE(setenv("RUNECORE_SAVE_DIR", saveDirectory.c_str(), 1) == 0);

        SaveData startingSave;
        startingSave.playerName = "Returning Hero";
        startingSave.className = "Medic";
        startingSave.visorColor = Color{245, 105, 145, 255};
        startingSave.level = 8;
        startingSave.currentXP = 123;
        startingSave.attributePoints = 4;
        startingSave.skillPoints = 3;
        startingSave.health = 75.0f;
        startingSave.mana = 25.0f;
        startingSave.power = 12.0f;
        startingSave.playerX = 640.0f;
        startingSave.playerY = 160.0f;
        startingSave.attributes.strength = 24;
        startingSave.hunger = 62.0f;
        startingSave.thirst = 48.0f;
        startingSave.bodyTemp = 36.0f;

        Item ore;
        ore.id = "mat_resume_ore";
        ore.name = "Resume Ore";
        ore.category = ItemCategory::Material;
        ore.stackable = true;
        ore.quantity = 7;
        startingSave.inventoryItems.push_back(ore);

        Item blade;
        blade.id = "item_resume_blade";
        blade.name = "Resume Blade";
        blade.category = ItemCategory::Weapon;
        blade.equipSlot = EquipSlot::MainHand;
        blade.baseDamage = 55.0f;
        startingSave.equippedItems.push_back(
            SaveData::EquippedItem{EquipSlot::MainHand, blade});
        REQUIRE(SaveManager::saveSlot(saveDirectory, 2, startingSave));

        std::atomic<bool> cancelEvents{false};
        const auto eventScheduleStart = std::chrono::steady_clock::now();
        std::thread resumeCharacter([&] {
            const auto postKey = [&](std::chrono::milliseconds offset, SDL_Keycode key) {
                const auto deadline = eventScheduleStart + offset;
                while (std::chrono::steady_clock::now() < deadline && !cancelEvents.load()) {
                    std::this_thread::sleep_for(std::chrono::milliseconds(5));
                }
                if (cancelEvents.load()) return;

                SDL_Event event{};
                event.type = SDL_EVENT_KEY_DOWN;
                event.key.key = key;
                event.key.repeat = 0;
                while (!SDL_PushEvent(&event) && !cancelEvents.load()) {
                    std::this_thread::sleep_for(std::chrono::milliseconds(10));
                }
            };

            postKey(std::chrono::milliseconds(400), SDLK_DOWN);
            postKey(std::chrono::milliseconds(650), SDLK_RETURN);
            postKey(std::chrono::milliseconds(950), SDLK_RETURN);
        });

        char* args[] = {
            const_cast<char*>("untitled_rpg"),
            const_cast<char*>("--duration"),
            const_cast<char*>("2.0")
        };
        std::ostringstream output;
        std::streambuf* previousOutput = std::cout.rdbuf(output.rdbuf());
        const int exitCode = runGame(3, args);
        std::cout.rdbuf(previousOutput);
        cancelEvents.store(true);
        resumeCharacter.join();

        SaveData resumedSave;
        const bool slotSaved = SaveManager::loadSlot(saveDirectory, 2, resumedSave);
        const int environmentRestoreResult = hadPreviousSaveDirectory
            ? setenv("RUNECORE_SAVE_DIR", previousSaveDirectoryValue.c_str(), 1)
            : unsetenv("RUNECORE_SAVE_DIR");
        std::error_code cleanupError;
        std::filesystem::remove_all(saveDirectory, cleanupError);

        REQUIRE(environmentRestoreResult == 0);
        REQUIRE_FALSE(cleanupError);
        REQUIRE(exitCode == 0);
        REQUIRE(slotSaved);
        REQUIRE(output.str().find("Resumed RUNECORE save slot 2 for Returning Hero at level 8.")
                != std::string::npos);
        REQUIRE(resumedSave.playerName == startingSave.playerName);
        REQUIRE(resumedSave.onboardingComplete);
        REQUIRE(resumedSave.className == startingSave.className);
        REQUIRE(resumedSave.visorColor.r == startingSave.visorColor.r);
        REQUIRE(resumedSave.visorColor.g == startingSave.visorColor.g);
        REQUIRE(resumedSave.level == startingSave.level);
        REQUIRE(resumedSave.currentXP == startingSave.currentXP);
        REQUIRE(resumedSave.attributes.strength == startingSave.attributes.strength);
        REQUIRE(resumedSave.playerX > 500.0f);
        REQUIRE(resumedSave.inventoryItems.size() == 1);
        REQUIRE(resumedSave.inventoryItems.front().id == ore.id);
        REQUIRE(resumedSave.inventoryItems.front().quantity == ore.quantity);
        REQUIRE(resumedSave.equippedItems.size() == 1);
        REQUIRE(resumedSave.equippedItems.front().slot == EquipSlot::MainHand);
        REQUIRE(resumedSave.equippedItems.front().item.id == blade.id);
    }

    SECTION("Interactive resume acknowledges and saves the campaign ending") {
        const std::string saveDirectory =
            (std::filesystem::temp_directory_path() /
             ("runecore-campaign-ending-" +
              std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()))).string();
        const char* previousSaveDirectory = std::getenv("RUNECORE_SAVE_DIR");
        const bool hadPreviousSaveDirectory = previousSaveDirectory != nullptr;
        const std::string previousSaveDirectoryValue =
            hadPreviousSaveDirectory ? previousSaveDirectory : "";
        REQUIRE(setenv("RUNECORE_SAVE_DIR", saveDirectory.c_str(), 1) == 0);

        SaveData completedRun;
        completedRun.playerName = "Completed Hero";
        completedRun.inDungeon = true;
        completedRun.onboardingComplete = true;
        completedRun.campaignComplete = true;
        REQUIRE(SaveManager::saveSlot(saveDirectory, 1, completedRun));

        std::atomic<bool> cancelEvents{false};
        std::atomic<bool> quitEventPosted{false};
        const auto eventScheduleStart = std::chrono::steady_clock::now();
        std::thread acknowledgeEnding([&] {
            const auto postKey = [&](std::chrono::milliseconds offset, SDL_Keycode key) {
                const auto deadline = eventScheduleStart + offset;
                while (std::chrono::steady_clock::now() < deadline && !cancelEvents.load()) {
                    std::this_thread::sleep_for(std::chrono::milliseconds(5));
                }
                if (cancelEvents.load()) return;

                SDL_Event event{};
                event.type = SDL_EVENT_KEY_DOWN;
                event.key.key = key;
                event.key.repeat = 0;
                while (!SDL_PushEvent(&event) && !cancelEvents.load()) {
                    std::this_thread::sleep_for(std::chrono::milliseconds(10));
                }
            };

            postKey(std::chrono::milliseconds(400), SDLK_RETURN);
            postKey(std::chrono::milliseconds(800), SDLK_SPACE);

            const auto quitDeadline = eventScheduleStart + std::chrono::milliseconds(1300);
            while (std::chrono::steady_clock::now() < quitDeadline && !cancelEvents.load()) {
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
            }
            if (cancelEvents.load()) return;

            SDL_Event quit{};
            quit.type = SDL_EVENT_QUIT;
            quitEventPosted.store(SDL_PushEvent(&quit));
        });

        char* args[] = {
            const_cast<char*>("untitled_rpg"),
            const_cast<char*>("--duration"),
            const_cast<char*>("2.0")
        };
        std::ostringstream output;
        std::streambuf* previousOutput = std::cout.rdbuf(output.rdbuf());
        const int exitCode = runGame(3, args);
        std::cout.rdbuf(previousOutput);
        cancelEvents.store(true);
        acknowledgeEnding.join();

        SaveData savedRun;
        const bool slotSaved = SaveManager::loadSlot(saveDirectory, 1, savedRun);
        const int environmentRestoreResult = hadPreviousSaveDirectory
            ? setenv("RUNECORE_SAVE_DIR", previousSaveDirectoryValue.c_str(), 1)
            : unsetenv("RUNECORE_SAVE_DIR");
        std::error_code cleanupError;
        std::filesystem::remove_all(saveDirectory, cleanupError);

        REQUIRE(environmentRestoreResult == 0);
        REQUIRE_FALSE(cleanupError);
        REQUIRE(exitCode == 0);
        REQUIRE(quitEventPosted.load());
        REQUIRE(slotSaved);
        INFO(output.str());
        REQUIRE(output.str().find(
                    "Resumed RUNECORE save slot 1 for Completed Hero at level 1.") !=
                std::string::npos);
        REQUIRE(savedRun.campaignComplete);
        REQUIRE(savedRun.endingAcknowledged);
    }

    SECTION("Headless Benchmark Argument") {
        char* args[] = {const_cast<char*>("untitled_rpg"), const_cast<char*>("--headless")};
        int code = runGame(2, args);
        REQUIRE(code == 0);
    }

    SECTION("Headless Bot Mode Argument") {
        char* args[] = {const_cast<char*>("untitled_rpg"), const_cast<char*>("--headless"), const_cast<char*>("--bot")};
        int code = runGame(3, args);
        REQUIRE(code == 0);
    }

    SECTION("Short Flags -h and -b") {
        char* args[] = {const_cast<char*>("untitled_rpg"), const_cast<char*>("-h"), const_cast<char*>("-b")};
        int code = runGame(3, args);
        REQUIRE(code == 0);
    }

    SECTION("Benchmark Flag") {
        char* args[] = {const_cast<char*>("untitled_rpg"), const_cast<char*>("--benchmark")};
        int code = runGame(2, args);
        REQUIRE(code == 0);
    }

    SECTION("Auto Test Flag") {
        char* args[] = {const_cast<char*>("untitled_rpg"), const_cast<char*>("--headless"), const_cast<char*>("--auto-test")};
        int code = runGame(3, args);
        REQUIRE(code == 0);
    }

    SECTION("Manual Mode Arguments") {
        char* args1[] = {const_cast<char*>("untitled_rpg"), const_cast<char*>("--headless"), const_cast<char*>("--manual")};
        REQUIRE(runGame(3, args1) == 0);

        char* args2[] = {const_cast<char*>("untitled_rpg"), const_cast<char*>("--headless"), const_cast<char*>("-m")};
        REQUIRE(runGame(3, args2) == 0);
    }

    SECTION("Duration Argument") {
        char* args[] = {const_cast<char*>("untitled_rpg"), const_cast<char*>("--duration"), const_cast<char*>("0.05")};
        REQUIRE(runGame(3, args) == 0);
    }

    SECTION("Quit Event in Windowed Mode") {
        SDL_Event quitEv;
        quitEv.type = SDL_EVENT_QUIT;
        SDL_PushEvent(&quitEv);

        char* args[] = {const_cast<char*>("untitled_rpg"), const_cast<char*>("--duration"), const_cast<char*>("2.0")};
        REQUIRE(runGame(3, args) == 0);
    }

    SECTION("Human Control Takeover in Windowed Mode") {
        SDL_Event keyEv;
        keyEv.type = SDL_EVENT_KEY_DOWN;
        keyEv.key.key = SDLK_A;
        keyEv.key.repeat = 0;
        SDL_PushEvent(&keyEv);

        char* args[] = {const_cast<char*>("untitled_rpg"), const_cast<char*>("--duration"), const_cast<char*>("0.05")};
        REQUIRE(runGame(3, args) == 0);
    }

    SECTION("Fallback to Headless when Window Display Unavailable") {
        const char* previousVideoDriver = SDL_GetHint(SDL_HINT_VIDEO_DRIVER);
        const bool hadPreviousVideoDriver = previousVideoDriver != nullptr;
        const std::string previousVideoDriverValue = hadPreviousVideoDriver ? previousVideoDriver : "";
        REQUIRE(SDL_SetHintWithPriority(
            SDL_HINT_VIDEO_DRIVER, "runecore-test-unavailable-driver", SDL_HINT_OVERRIDE));

        char* args[] = {
            const_cast<char*>("untitled_rpg"),
            const_cast<char*>("--duration"),
            const_cast<char*>("0.05")
        };
        std::ostringstream output;
        std::streambuf* previousOutput = std::cout.rdbuf(output.rdbuf());
        int code = runGame(3, args);
        std::cout.rdbuf(previousOutput);
        const bool hintRestored = hadPreviousVideoDriver
            ? SDL_SetHintWithPriority(
                SDL_HINT_VIDEO_DRIVER, previousVideoDriverValue.c_str(), SDL_HINT_OVERRIDE)
            : SDL_ResetHint(SDL_HINT_VIDEO_DRIVER);

        REQUIRE(hintRestored);
        REQUIRE(code == 0);
        REQUIRE(output.str().find("Display server not available. Falling back to headless simulation.") != std::string::npos);
    }
}
