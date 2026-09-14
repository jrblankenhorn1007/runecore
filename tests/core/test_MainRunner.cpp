#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include <SDL3/SDL.h>
#include "core/MainRunner.hpp"

TEST_CASE("MainRunner Headless and CLI Argument Variations", "[core][main_runner]") {
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
        char* args[] = {const_cast<char*>("untitled_rpg")};
        int code = runGame(1, args);
        REQUIRE(code == 0);
    }
}
