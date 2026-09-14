#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include "input/InputManager.hpp"
#include "render/Camera.hpp"

using Catch::Approx;

TEST_CASE("InputManager Event Polling, Keyboard Actions, and Mouse Coordinates", "[input][events]") {
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS)) {
        return;
    }

    InputManager im;
    CanvasMetrics metrics = Camera::calculateCanvasMetrics(1280, 720);
    Camera camera;
    camera.setPosition(Vec2{100.0f, 100.0f});

    SECTION("Keyboard Keydown Events") {
        auto pushKey = [](SDL_Keycode k, bool down) {
            SDL_Event e;
            e.type = down ? SDL_EVENT_KEY_DOWN : SDL_EVENT_KEY_UP;
            e.key.key = k;
            e.key.repeat = 0;
            SDL_PushEvent(&e);
        };

        // Push Space
        pushKey(SDLK_SPACE, true);
        im.processEvents(metrics, camera);
        REQUIRE(im.getState().controller.jumpPressed == true);
        REQUIRE(im.getState().controller.jumpHeld == true);

        pushKey(SDLK_SPACE, false);
        im.processEvents(metrics, camera);
        REQUIRE(im.getState().controller.jumpHeld == false);

        // Push LSHIFT
        pushKey(SDLK_LSHIFT, true);
        im.processEvents(metrics, camera);
        REQUIRE(im.getState().controller.sprintHeld == true);
        REQUIRE(im.getState().controller.dashPressed == true);

        pushKey(SDLK_LSHIFT, false);
        im.processEvents(metrics, camera);
        REQUIRE(im.getState().controller.sprintHeld == false);

        // Push Skills Q, E, R, F
        pushKey(SDLK_Q, true);
        im.processEvents(metrics, camera);
        REQUIRE(im.getState().skillQ == true);

        pushKey(SDLK_E, true);
        im.processEvents(metrics, camera);
        REQUIRE(im.getState().skillE == true);

        pushKey(SDLK_R, true);
        im.processEvents(metrics, camera);
        REQUIRE(im.getState().skillR == true);

        pushKey(SDLK_F, true);
        im.processEvents(metrics, camera);
        REQUIRE(im.getState().skillF == true);

        // Push UI Toggles
        pushKey(SDLK_TAB, true);
        im.processEvents(metrics, camera);
        REQUIRE(im.getState().toggleInventory == true);

        pushKey(SDLK_C, true);
        im.processEvents(metrics, camera);
        REQUIRE(im.getState().toggleCrafting == true);

        pushKey(SDLK_U, true);
        im.processEvents(metrics, camera);
        REQUIRE(im.getState().toggleAugmentations == true);

        pushKey(SDLK_M, true);
        im.processEvents(metrics, camera);
        REQUIRE(im.getState().toggleMinimap == true);

        pushKey(SDLK_W, true);
        im.processEvents(metrics, camera);
        REQUIRE(im.getState().interactPressed == true);

        pushKey(SDLK_ESCAPE, true);
        im.processEvents(metrics, camera);
        REQUIRE(im.getState().quitRequested == true);

        // Hotbar keys
        pushKey(SDLK_1, true); im.processEvents(metrics, camera); REQUIRE(im.getState().hotbarSelected == 0);
        pushKey(SDLK_2, true); im.processEvents(metrics, camera); REQUIRE(im.getState().hotbarSelected == 1);
        pushKey(SDLK_3, true); im.processEvents(metrics, camera); REQUIRE(im.getState().hotbarSelected == 2);
        pushKey(SDLK_4, true); im.processEvents(metrics, camera); REQUIRE(im.getState().hotbarSelected == 3);
        pushKey(SDLK_5, true); im.processEvents(metrics, camera); REQUIRE(im.getState().hotbarSelected == 4);
        pushKey(SDLK_6, true); im.processEvents(metrics, camera); REQUIRE(im.getState().hotbarSelected == 5);
        pushKey(SDLK_7, true); im.processEvents(metrics, camera); REQUIRE(im.getState().hotbarSelected == 6);
        pushKey(SDLK_8, true); im.processEvents(metrics, camera); REQUIRE(im.getState().hotbarSelected == 7);

        // Unmapped key down & up triggers default branches
        pushKey(SDLK_Z, true);
        im.processEvents(metrics, camera);
        pushKey(SDLK_Z, false);
        im.processEvents(metrics, camera);
    }

    SECTION("Mouse Button Events") {
        auto pushMouse = [](Uint8 btn, bool down) {
            SDL_Event e;
            e.type = down ? SDL_EVENT_MOUSE_BUTTON_DOWN : SDL_EVENT_MOUSE_BUTTON_UP;
            e.button.button = btn;
            SDL_PushEvent(&e);
        };

        pushMouse(SDL_BUTTON_LEFT, true);
        im.processEvents(metrics, camera);
        REQUIRE(im.getState().attackPressed == true);
        REQUIRE(im.getState().attackHeld == true);

        pushMouse(SDL_BUTTON_LEFT, false);
        im.processEvents(metrics, camera);
        REQUIRE(im.getState().attackHeld == false);

        pushMouse(SDL_BUTTON_RIGHT, true);
        im.processEvents(metrics, camera);
        REQUIRE(im.getState().secondaryPressed == true);

        // Push quit event
        SDL_Event quitEv;
        quitEv.type = SDL_EVENT_QUIT;
        SDL_PushEvent(&quitEv);
        im.processEvents(metrics, camera);
        REQUIRE(im.getState().quitRequested == true);
    }
}
