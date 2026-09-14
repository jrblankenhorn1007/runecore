#pragma once
#include "core/Math.hpp"
#include "physics/CollisionWorld.hpp"

struct ControllerConfig {
    float moveSpeed{120.0f};
    float sprintMultiplier{1.5f};
    float jumpForce{250.0f};
    float doubleJumpMultiplier{0.85f};
    float gravity{600.0f};
    float maxFallSpeed{400.0f};
    float wallSlideSpeed{50.0f};
    float wallJumpForceX{180.0f};
    float wallJumpForceY{220.0f};
};

struct ControllerInput {
    float moveX{0.0f};
    float moveY{0.0f};
    bool jumpPressed{false};
    bool jumpHeld{false};
    bool sprintHeld{false};
    bool dashPressed{false};
};

class CharacterController {
public:
    CharacterController();

    void update(
        Vec2& position,
        Vec2& velocity,
        const ControllerInput& input,
        const CollisionWorld& world,
        const ControllerConfig& config,
        float dt
    );

    bool isGrounded() const { return m_grounded; }
    bool isWallSliding() const { return m_wallSliding; }
    bool canDoubleJump() const { return m_canDoubleJump; }
    int getFacing() const { return m_facing; }

private:
    Rect m_box{-8.0f, -16.0f, 16.0f, 16.0f}; // Feet origin at (0, 0)
    bool m_grounded{false};
    bool m_wallSliding{false};
    bool m_canDoubleJump{true};
    int m_wallSide{0}; // -1 left, 1 right
    int m_facing{1};
};
