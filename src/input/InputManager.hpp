#pragma once

#include <SDL3/SDL.h>
#include <unordered_map>

namespace rpg {

enum class Action {
    MoveLeft,
    MoveRight,
    MoveUp,
    MoveDown,
    Jump,
    Dash,
    AttackPrimary,
    AttackSecondary,
    SkillQ,
    SkillE,
    SkillR,
    SkillF,
    Interact,
    Inventory,
    Pause
};

class InputManager {
public:
    void update() {
        m_prevActions = m_actions;
        m_mouseDeltaX = 0.0f;
        m_mouseDeltaY = 0.0f;
    }

    void handleEvent(const SDL_Event& event) {
        if (event.type == SDL_EVENT_KEY_DOWN || event.type == SDL_EVENT_KEY_UP) {
            bool isDown = (event.type == SDL_EVENT_KEY_DOWN);
            SDL_Keycode key = event.key.key;

            if (key == SDLK_A || key == SDLK_LEFT) m_actions[Action::MoveLeft] = isDown;
            if (key == SDLK_D || key == SDLK_RIGHT) m_actions[Action::MoveRight] = isDown;
            if (key == SDLK_W || key == SDLK_UP) m_actions[Action::MoveUp] = isDown;
            if (key == SDLK_S || key == SDLK_DOWN) m_actions[Action::MoveDown] = isDown;
            if (key == SDLK_SPACE) m_actions[Action::Jump] = isDown;
            if (key == SDLK_LSHIFT) m_actions[Action::Dash] = isDown;
            if (key == SDLK_Q) m_actions[Action::SkillQ] = isDown;
            if (key == SDLK_E) m_actions[Action::SkillE] = isDown;
            if (key == SDLK_R) m_actions[Action::SkillR] = isDown;
            if (key == SDLK_F) m_actions[Action::SkillF] = isDown;
            if (key == SDLK_TAB) m_actions[Action::Inventory] = isDown;
            if (key == SDLK_ESCAPE) m_actions[Action::Pause] = isDown;
        }

        if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN || event.type == SDL_EVENT_MOUSE_BUTTON_UP) {
            bool isDown = (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN);
            if (event.button.button == SDL_BUTTON_LEFT) m_actions[Action::AttackPrimary] = isDown;
            if (event.button.button == SDL_BUTTON_RIGHT) m_actions[Action::AttackSecondary] = isDown;
        }

        if (event.type == SDL_EVENT_MOUSE_MOTION) {
            m_mouseX = event.motion.x;
            m_mouseY = event.motion.y;
            m_mouseDeltaX = event.motion.xrel;
            m_mouseDeltaY = event.motion.yrel;
        }
    }

    bool isActionDown(Action action) const {
        auto it = m_actions.find(action);
        return it != m_actions.end() && it->second;
    }

    bool isActionPressed(Action action) const {
        return isActionDown(action) && !wasActionDown(action);
    }

    bool isActionReleased(Action action) const {
        return !isActionDown(action) && wasActionDown(action);
    }

    float getMouseX() const { return m_mouseX; }
    float getMouseY() const { return m_mouseY; }

private:
    bool wasActionDown(Action action) const {
        auto it = m_prevActions.find(action);
        return it != m_prevActions.end() && it->second;
    }

    std::unordered_map<Action, bool> m_actions;
    std::unordered_map<Action, bool> m_prevActions;
    float m_mouseX = 0.0f;
    float m_mouseY = 0.0f;
    float m_mouseDeltaX = 0.0f;
    float m_mouseDeltaY = 0.0f;
};

} // namespace rpg
