#include "physics/CharacterController.hpp"
#include <algorithm>

CharacterController::CharacterController() = default;

void CharacterController::update(
    Vec2& position,
    Vec2& velocity,
    const ControllerInput& input,
    const CollisionWorld& world,
    const ControllerConfig& config,
    float dt
) {
    if (input.moveX > 0.1f) m_facing = 1;
    else if (input.moveX < -0.1f) m_facing = -1;

    // Horizontal speed target
    float targetSpeed = config.moveSpeed * (input.sprintHeld ? config.sprintMultiplier : 1.0f);
    velocity.x = input.moveX * targetSpeed;

    // Apply gravity
    velocity.y += config.gravity * dt;
    velocity.y = std::min(velocity.y, config.maxFallSpeed);

    // Wall slide check
    m_wallSliding = false;
    m_wallSide = 0;

    if (!m_grounded && velocity.y > 0.0f) {
        // Check left wall
        SweepResult leftCheck = world.sweepBox(position, m_box, Vec2{-2.0f, 0.0f});
        if (leftCheck.hit && input.moveX < -0.1f) {
            m_wallSliding = true;
            m_wallSide = -1;
            velocity.y = std::min(velocity.y, config.wallSlideSpeed);
        }

        // Check right wall
        SweepResult rightCheck = world.sweepBox(position, m_box, Vec2{2.0f, 0.0f});
        if (rightCheck.hit && input.moveX > 0.1f) {
            m_wallSliding = true;
            m_wallSide = 1;
            velocity.y = std::min(velocity.y, config.wallSlideSpeed);
        }
    }

    // Jump handling
    if (input.jumpPressed) {
        if (m_grounded) {
            velocity.y = -config.jumpForce;
            m_grounded = false;
            m_canDoubleJump = true;
        } else if (m_wallSliding) {
            // Wall jump kicks away from wall
            velocity.x = -m_wallSide * config.wallJumpForceX;
            velocity.y = -config.wallJumpForceY;
            m_wallSliding = false;
            m_canDoubleJump = true;
        } else if (m_canDoubleJump) {
            velocity.y = -config.jumpForce * config.doubleJumpMultiplier;
            m_canDoubleJump = false;
        }
    }

    // Perform world collision sweep
    Vec2 delta = velocity * dt;
    SweepResult sweep = world.sweepBox(position, m_box, delta);

    position += sweep.adjustedMove;

    // Update grounded state
    if (sweep.hit && sweep.contactNormal.y < -0.5f) {
        m_grounded = true;
        velocity.y = 0.0f;
        m_canDoubleJump = true;
    } else {
        // Check if just above ground (within 1 pixel)
        SweepResult groundProbe = world.sweepBox(position, m_box, Vec2{0.0f, 1.0f});
        if (groundProbe.hit && groundProbe.contactNormal.y < -0.5f) {
            m_grounded = true;
            velocity.y = 0.0f;
            m_canDoubleJump = true;
        } else {
            m_grounded = false;
        }
    }

    // Ceiling collision
    if (sweep.hit && sweep.contactNormal.y > 0.5f) {
        if (velocity.y < 0.0f) {
            velocity.y = 0.0f;
        }
    }
}
