#include "input/InputManager.hpp"
#include <algorithm>

InputManager::InputManager() = default;

void InputManager::processEvents(const CanvasMetrics& metrics, const Camera& camera) {
    // Reset one-frame pulses
    m_state.controller.jumpPressed = false;
    m_state.controller.dashPressed = false;
    m_state.attackPressed = false;
    m_state.secondaryPressed = false;
    m_state.skillQ = false;
    m_state.skillE = false;
    m_state.skillR = false;
    m_state.skillF = false;
    m_state.toggleInventory = false;
    m_state.toggleCrafting = false;
    m_state.toggleAugmentations = false;
    m_state.toggleMinimap = false;
    m_state.interactPressed = false;

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_EVENT_QUIT) {
            m_state.quitRequested = true;
        } else if (event.type == SDL_EVENT_KEY_DOWN) {
            if (event.key.repeat == 0) {
                switch (event.key.key) {
                    case SDLK_SPACE:
                        m_state.controller.jumpPressed = true;
                        m_state.controller.jumpHeld = true;
                        break;
                    case SDLK_LSHIFT:
                        m_state.controller.sprintHeld = true;
                        m_state.controller.dashPressed = true;
                        break;
                    case SDLK_Q:
                        m_state.skillQ = true;
                        break;
                    case SDLK_E:
                        m_state.skillE = true;
                        break;
                    case SDLK_R:
                        m_state.skillR = true;
                        break;
                    case SDLK_F:
                        m_state.skillF = true;
                        break;
                    case SDLK_TAB:
                        m_state.toggleInventory = true;
                        break;
                    case SDLK_C:
                        m_state.toggleCrafting = true;
                        break;
                    case SDLK_U:
                        m_state.toggleAugmentations = true;
                        break;
                    case SDLK_M:
                        m_state.toggleMinimap = true;
                        break;
                    case SDLK_W:
                        m_state.interactPressed = true;
                        break;
                    case SDLK_ESCAPE:
                        m_state.quitRequested = true;
                        break;
                    case SDLK_1: m_state.hotbarSelected = 0; break;
                    case SDLK_2: m_state.hotbarSelected = 1; break;
                    case SDLK_3: m_state.hotbarSelected = 2; break;
                    case SDLK_4: m_state.hotbarSelected = 3; break;
                    case SDLK_5: m_state.hotbarSelected = 4; break;
                    case SDLK_6: m_state.hotbarSelected = 5; break;
                    case SDLK_7: m_state.hotbarSelected = 6; break;
                    case SDLK_8: m_state.hotbarSelected = 7; break;
                    default: break;
                }
            }
        } else if (event.type == SDL_EVENT_KEY_UP) {
            switch (event.key.key) {
                case SDLK_SPACE:
                    m_state.controller.jumpHeld = false;
                    break;
                case SDLK_LSHIFT:
                    m_state.controller.sprintHeld = false;
                    break;
                default: break;
            }
        } else if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
            if (event.button.button == SDL_BUTTON_LEFT) {
                m_state.attackPressed = true;
                m_state.attackHeld = true;
            } else if (event.button.button == SDL_BUTTON_RIGHT) {
                m_state.secondaryPressed = true;
            }
        } else if (event.type == SDL_EVENT_MOUSE_BUTTON_UP) {
            if (event.button.button == SDL_BUTTON_LEFT) {
                m_state.attackHeld = false;
            }
        }
    }

    // Continuous key polling for movement
    const bool* keyboard = SDL_GetKeyboardState(nullptr);
    float mx = 0.0f;
    float my = 0.0f;

    if (keyboard[SDL_SCANCODE_A] || keyboard[SDL_SCANCODE_LEFT]) mx -= 1.0f;
    if (keyboard[SDL_SCANCODE_D] || keyboard[SDL_SCANCODE_RIGHT]) mx += 1.0f;
    if (keyboard[SDL_SCANCODE_W] || keyboard[SDL_SCANCODE_UP]) my -= 1.0f;
    if (keyboard[SDL_SCANCODE_S] || keyboard[SDL_SCANCODE_DOWN]) my += 1.0f;

    m_state.controller.moveX = mx;
    m_state.controller.moveY = my;

    // Mouse coordinates
    float mouseX = 0.0f;
    float mouseY = 0.0f;
    SDL_GetMouseState(&mouseX, &mouseY);
    m_state.mouseScreenPos = Vec2{mouseX, mouseY};

    // Calculate canvas and world positions
    float scale = std::max(1.0f, static_cast<float>(metrics.integerScale));
    float canvasX = (mouseX - metrics.letterboxX) / scale;
    float canvasY = (mouseY - metrics.letterboxY) / scale;

    Vec2 camPos = camera.getSnappedPosition();
    m_state.mouseWorldPos = Vec2{
        camPos.x + (canvasX - metrics.virtualWidth * 0.5f),
        camPos.y + (canvasY - metrics.virtualHeight * 0.5f)
    };
}
