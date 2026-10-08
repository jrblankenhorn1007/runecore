#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include <SDL3/SDL.h>
#include "core/MainRunner.hpp"
#include <atomic>
#include <chrono>
#include <cstdlib>
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
        std::atomic<bool> cancelEvents{false};
        std::atomic<bool> gameplayInputPosted{false};
        std::atomic<bool> quitEventPosted{false};
        const auto eventScheduleStart = std::chrono::steady_clock::now();
        std::thread playAndQuit([&] {
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

        REQUIRE(exitCode == 0);
        REQUIRE(gameplayInputPosted.load());
        REQUIRE(quitEventPosted.load());
        REQUIRE(elapsed >= std::chrono::milliseconds(11500));
        REQUIRE(output.str().find("Manual player control engaged.") != std::string::npos);
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
