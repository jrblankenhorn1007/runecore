#include "render/ParticleSystem.hpp"
#include <cmath>

ParticleSystem::ParticleSystem(size_t maxParticles) {
    m_particles.resize(maxParticles);
}

void ParticleSystem::emit(const Vec2& position, const Vec2& velocity, Color color, float lifetime, float size) {
    for (auto& p : m_particles) {
        if (!p.active) {
            p.position = position;
            p.velocity = velocity;
            p.color = color;
            p.lifetime = lifetime;
            p.maxLifetime = lifetime;
            p.size = size;
            p.active = true;
            return;
        }
    }
}

void ParticleSystem::emitBurst(const Vec2& position, int count, Color color, float lifetime, float speed) {
    for (int i = 0; i < count; ++i) {
        float angle = (i * 2.0f * 3.14159265f) / count;
        Vec2 vel{std::cos(angle) * speed, std::sin(angle) * speed};
        emit(position, vel, color, lifetime, 3.0f);
    }
}

void ParticleSystem::update(float dt) {
    for (auto& p : m_particles) {
        if (!p.active) continue;

        p.lifetime -= dt;
        if (p.lifetime <= 0.0f) {
            p.active = false;
            continue;
        }

        // Apply simple velocity and gravity
        p.velocity.y += 100.0f * dt;
        p.position += p.velocity * dt;
    }
}

size_t ParticleSystem::getActiveCount() const {
    size_t count = 0;
    for (const auto& p : m_particles) {
        if (p.active) count++;
    }
    return count;
}
