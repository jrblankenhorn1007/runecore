#pragma once
#include <vector>
#include "core/Math.hpp"

struct Particle {
    Vec2 position{0.0f, 0.0f};
    Vec2 velocity{0.0f, 0.0f};
    Color color{255, 255, 255, 255};
    float lifetime{1.0f};
    float maxLifetime{1.0f};
    float size{2.0f};
    bool active{false};
};

class ParticleSystem {
public:
    explicit ParticleSystem(size_t maxParticles = 500);

    void emit(const Vec2& position, const Vec2& velocity, Color color, float lifetime = 1.0f, float size = 2.0f);
    void emitBurst(const Vec2& position, int count, Color color, float lifetime = 0.5f, float speed = 50.0f);
    void update(float dt);

    size_t getActiveCount() const;
    const std::vector<Particle>& getParticles() const { return m_particles; }

private:
    std::vector<Particle> m_particles;
};
