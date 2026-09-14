#pragma once
#include <SDL3/SDL.h>
#include "physics/CharacterController.hpp"
#include "render/Camera.hpp"
#include "core/Math.hpp"

struct RawInputState {
    ControllerInput controller;
    bool attackPressed{false};
    bool attackHeld{false};
    bool secondaryPressed{false};
    int hotbarSelected{0}; // 0-7
    bool skillQ{false};
    bool skillE{false};
    bool skillR{false};
    bool skillF{false};
    bool toggleInventory{false};
    bool toggleCrafting{false};
    bool toggleAugmentations{false};
    bool toggleMinimap{false};
    bool toggleCharacterSheet{false};
    bool toggleSkills{false};
    bool toggleSettings{false};
    bool interactPressed{false};
    bool quitRequested{false};
    Vec2 mouseScreenPos{0.0f, 0.0f};
    Vec2 mouseWorldPos{0.0f, 0.0f};
};

class InputManager {
public:
    InputManager();

    void processEvents(const CanvasMetrics& metrics, const Camera& camera);
    const RawInputState& getState() const { return m_state; }

private:
    RawInputState m_state;
};
