#include "core/GameSimulation.hpp"
#include "ecs/Components.hpp"
#include "gameplay/combat/CombatSystem.hpp"

GameSimulation::GameSimulation()
    : m_skillExecutor(m_context.skillRegistry),
      m_forge(m_context.rng) {}

void GameSimulation::initialize(ClassType playerClass) {
    // 1. Build tile floor & structures in physics world & tilemap
    for (int x = -100; x <= 300; ++x) {
        // Bedrock & subterranean
        for (int y = 10; y <= 15; ++y) {
            uint16_t blockType = 1; // Stone
            if ((x % 7 == 0 || x % 13 == 0) && y > 11) {
                blockType = 2; // Iron Ore
            }
            m_context.physicsWorld.setTile(x, y, TileType::Solid);
            m_context.tilemap.setBlock(x, y, BlockLayer::Foreground, blockType);
        }
    }

    // Elevated wooden platforms
    for (int x = 12; x <= 18; ++x) {
        m_context.physicsWorld.setTile(x, 7, TileType::OneWayPlatform);
        m_context.tilemap.setBlock(x, 7, BlockLayer::Foreground, 5);
    }
    for (int x = 24; x <= 32; ++x) {
        m_context.physicsWorld.setTile(x, 4, TileType::OneWayPlatform);
        m_context.tilemap.setBlock(x, 4, BlockLayer::Foreground, 5);
    }

    // Stone wall obstacle for wall-jumping
    for (int y = 6; y <= 9; ++y) {
        m_context.physicsWorld.setTile(38, y, TileType::Solid);
        m_context.tilemap.setBlock(38, y, BlockLayer::Foreground, 1);
    }

    // 2. Spawn Player
    m_playerEntity = m_context.registry.create();
    m_context.registry.emplace<PlayerTag>(m_playerEntity);
    m_context.registry.emplace<TransformComponent>(m_playerEntity, Vec2{100.0f, 160.0f});
    m_context.registry.emplace<VelocityComponent>(m_playerEntity, Vec2{0.0f, 0.0f});
    m_context.registry.emplace<ColliderComponent>(m_playerEntity, Rect{-8.0f, -16.0f, 16.0f, 16.0f});

    const auto& cls = m_context.classRegistry.getClass(playerClass);
    DerivedStats derived = StatsSystem::calculateDerivedStats(cls.baseAttributes);

    m_context.registry.emplace<HealthComponent>(m_playerEntity, derived.maxHealth, derived.maxHealth, derived.healthRegen);
    m_context.registry.emplace<ManaComponent>(m_playerEntity, derived.maxMana, derived.maxMana, derived.manaRegen);
    m_context.registry.emplace<PowerComponent>(m_playerEntity, 0.0f, derived.maxPower, derived.powerRegen);
    m_context.registry.emplace<StatsComponent>(m_playerEntity);

    // 3. Configure platformer controller
    m_controllerConfig.moveSpeed = 120.0f;
    m_controllerConfig.jumpForce = 250.0f;
    m_controllerConfig.gravity = 600.0f;

    // 4. Spawn initial patrol enemies
    spawnEnemy(Vec2{220.0f, 160.0f}, 60.0f, 100);
    spawnEnemy(Vec2{350.0f, 160.0f}, 80.0f, 150);
    spawnEnemy(Vec2{500.0f, 160.0f}, 120.0f, 250);
}

entt::entity GameSimulation::spawnEnemy(const Vec2& position, float health, int xpReward) {
    auto enemy = m_context.registry.create();
    m_context.registry.emplace<EnemyTag>(enemy, 1, xpReward);
    m_context.registry.emplace<TransformComponent>(enemy, position);
    m_context.registry.emplace<VelocityComponent>(enemy, Vec2{0.0f, 0.0f});
    m_context.registry.emplace<ColliderComponent>(enemy, Rect{-8.0f, -16.0f, 16.0f, 16.0f});
    m_context.registry.emplace<HealthComponent>(enemy, health, health, 0.0f);
    return enemy;
}

void GameSimulation::step(const ControllerInput& input, float dt) {
    m_tickCount++;
    m_simulationTime += dt;

    if (m_attackVisualTimer > 0.0f) {
        m_attackVisualTimer = std::max(0.0f, m_attackVisualTimer - dt);
    }

    // Update Player Movement & Controller
    Vec2 playerPos{0.0f, 0.0f};
    if (m_context.registry.valid(m_playerEntity)) {
        auto& pos = m_context.registry.get<TransformComponent>(m_playerEntity).position;
        auto& vel = m_context.registry.get<VelocityComponent>(m_playerEntity).linear;
        m_controller.update(pos, vel, input, m_context.physicsWorld, m_controllerConfig, dt);
        playerPos = pos;
    }

    // Update Enemies (Simple Pursuit towards Player)
    auto enemies = m_context.registry.view<EnemyTag, TransformComponent, VelocityComponent, HealthComponent>();
    for (auto [e, tag, trans, vel, hp] : enemies.each()) {
        float dist = trans.position.distanceTo(playerPos);
        if (dist < 180.0f && dist > 15.0f) {
            float dir = (playerPos.x > trans.position.x) ? 1.0f : -1.0f;
            vel.linear.x = dir * 45.0f;
        } else {
            vel.linear.x = 0.0f;
        }

        // Apply simple gravity
        vel.linear.y += 600.0f * dt;
        SweepResult sweep = m_context.physicsWorld.sweepBox(trans.position, Rect{-8.0f, -16.0f, 16.0f, 16.0f}, vel.linear * dt);
        trans.position += sweep.adjustedMove;
        if (sweep.hit && sweep.contactNormal.y < -0.5f) {
            vel.linear.y = 0.0f;
        }

        // Enemy melee attack against player if very close
        if (dist <= 16.0f && m_context.registry.valid(m_playerEntity)) {
            Hitbox enemyHitbox;
            enemyHitbox.damage = 5.0f;
            enemyHitbox.knockbackForce = 60.0f;
            enemyHitbox.owner = e;
            enemyHitbox.bounds = Rect{trans.position.x - 8.0f, trans.position.y - 16.0f, 16.0f, 16.0f};
            CombatSystem::resolveHitbox(m_context.registry, enemyHitbox, m_playerEntity);
        }
    }

    // Update Day/Night & Metabolism
    m_context.dayNight.update(dt);
    float starveDamage = m_metabolism.update(dt, 20.0f);
    if (starveDamage > 0.0f && m_context.registry.valid(m_playerEntity)) {
        m_context.registry.get<HealthComponent>(m_playerEntity).takeDamage(starveDamage);
    }

    // Update Health Components & Invulnerability
    auto healthView = m_context.registry.view<HealthComponent>();
    for (auto [e, health] : healthView.each()) {
        health.update(dt);

        // Check defeated enemies to award XP
        if (health.isDead && m_context.registry.all_of<EnemyTag>(e)) {
            const auto& enemyTag = m_context.registry.get<EnemyTag>(e);
            m_progression.addXP(enemyTag.xpReward);
            m_context.registry.destroy(e);
        }
    }
}

void GameSimulation::playerAttack() {
    if (!m_context.registry.valid(m_playerEntity)) return;

    const auto& playerPos = m_context.registry.get<TransformComponent>(m_playerEntity).position;
    int facing = m_controller.getFacing();

    // Hitbox directly in front of player
    Hitbox attackBox;
    attackBox.damage = 50.0f;
    attackBox.knockbackForce = 120.0f;
    attackBox.owner = m_playerEntity;
    attackBox.bounds = Rect{
        playerPos.x + (facing > 0 ? 0.0f : -28.0f),
        playerPos.y - 16.0f,
        28.0f,
        18.0f
    };

    m_attackVisualTimer = 0.15f; // 150ms visual slash
    m_lastAttackBox = attackBox;

    auto enemies = m_context.registry.view<EnemyTag, TransformComponent, HealthComponent, ColliderComponent>();
    for (auto [e, tag, trans, hp, col] : enemies.each()) {
        CombatSystem::resolveHitbox(m_context.registry, attackBox, e);
    }
}

float GameSimulation::getPlayerHealth() const {
    if (m_context.registry.valid(m_playerEntity)) {
        return m_context.registry.get<HealthComponent>(m_playerEntity).current;
    }
    return 0.0f;
}

Vec2 GameSimulation::getPlayerPosition() const {
    if (m_context.registry.valid(m_playerEntity)) {
        return m_context.registry.get<TransformComponent>(m_playerEntity).position;
    }
    return {0.0f, 0.0f};
}

size_t GameSimulation::getEnemyCount() const {
    auto view = m_context.registry.view<EnemyTag>();
    return view.size();
}
