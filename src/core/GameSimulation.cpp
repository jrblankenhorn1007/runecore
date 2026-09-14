#include "core/GameSimulation.hpp"
#include "ecs/Components.hpp"
#include "gameplay/combat/CombatSystem.hpp"

GameSimulation::GameSimulation()
    : m_skillExecutor(m_context.skillRegistry),
      m_forge(m_context.rng),
    m_worldInteraction(m_context.physicsWorld, m_context.tilemap, m_lootSystem),
    m_particles(500) {}

void GameSimulation::initialize(ClassType playerClass, bool headlessAudio) {
    m_character.classType = playerClass;
    m_audio.init(headlessAudio);

    // 1. Register sample crafting recipes
    CraftingRecipe ironSwordRecipe;
    ironSwordRecipe.id = "rcp_iron_greatsword";
    ironSwordRecipe.name = "Refined Iron Greatsword";
    ironSwordRecipe.station = CraftingStation::None; // Can craft anywhere
    ironSwordRecipe.ingredients = {{"mat_iron_ore", 3}, {"mat_stone_block", 2}};
    ironSwordRecipe.outputItemId = "item_iron_greatsword";
    ironSwordRecipe.outputQuantity = 1;
    ironSwordRecipe.category = ItemCategory::Weapon;
    m_crafting.registerRecipe(ironSwordRecipe);

    CraftingRecipe potionRecipe;
    potionRecipe.id = "rcp_healing_potion";
    potionRecipe.name = "Standard Healing Potion";
    potionRecipe.station = CraftingStation::None;
    potionRecipe.ingredients = {{"mat_wood_plank", 2}};
    potionRecipe.outputItemId = "item_health_potion";
    potionRecipe.outputQuantity = 2;
    potionRecipe.category = ItemCategory::Consumable;
    m_crafting.registerRecipe(potionRecipe);

    // 2. Register Active Skills in Registry
    SkillDefinition slam;
    slam.id = "skill_seismic_slam";
    slam.name = "Seismic Maul Slam";
    slam.resourceType = ResourceCostType::Stamina;
    slam.resourceCost = 15.0f;
    slam.baseCooldown = 3.0f;
    slam.baseDamage = 90.0f;
    m_context.skillRegistry.registerSkill(slam);

    SkillDefinition dash;
    dash.id = "skill_rocket_dash";
    dash.name = "Rocket Thruster Dash";
    dash.resourceType = ResourceCostType::Power;
    dash.resourceCost = 10.0f;
    dash.baseCooldown = 4.0f;
    dash.baseDamage = 40.0f;
    m_context.skillRegistry.registerSkill(dash);

    SkillDefinition arcDischarge;
    arcDischarge.id = "skill_arc_discharge";
    arcDischarge.name = "Arc Lightning Nova";
    arcDischarge.resourceType = ResourceCostType::Mana;
    arcDischarge.resourceCost = 25.0f;
    arcDischarge.baseCooldown = 5.0f;
    arcDischarge.baseDamage = 110.0f;
    m_context.skillRegistry.registerSkill(arcDischarge);

    SkillDefinition naniteHeal;
    naniteHeal.id = "skill_nanite_heal";
    naniteHeal.name = "Nanite Healing Surge";
    naniteHeal.resourceType = ResourceCostType::Mana;
    naniteHeal.resourceCost = 30.0f;
    naniteHeal.baseCooldown = 8.0f;
    naniteHeal.baseDamage = 0.0f;
    m_context.skillRegistry.registerSkill(naniteHeal);

    m_skillExecutor.assignHotbar(HotbarSlot::Q, "skill_seismic_slam");
    m_skillExecutor.assignHotbar(HotbarSlot::E, "skill_rocket_dash");
    m_skillExecutor.assignHotbar(HotbarSlot::R, "skill_arc_discharge");
    m_skillExecutor.assignHotbar(HotbarSlot::F, "skill_nanite_heal");

    m_skillTree.addNode(SkillNode{"mob_01", "SWIFTFOOT", 3, 0, 1, 0, {}});
    m_skillTree.addNode(SkillNode{"mob_02", "AGILE LEAP", 3, 0, 1, 1, {"mob_01"}});
    m_skillTree.addNode(SkillNode{"comb_01", "HONED EDGES", 3, 0, 1, 0, {}});
    m_skillTree.addNode(SkillNode{"surv_01", "HEARTY METABOLISM", 3, 0, 1, 0, {}});

    // 3. Generate Overworld Terrain
    for (int x = -100; x <= 300; ++x) {
        for (int y = 10; y <= 16; ++y) {
            uint16_t blockType = 1; // Stone
            if ((x % 5 == 0 || x % 11 == 0) && y > 11) {
                blockType = 2; // Iron Ore
            }
            m_context.physicsWorld.setTile(x, y, TileType::Solid);
            m_context.tilemap.setBlock(x, y, BlockLayer::Foreground, blockType);
        }
    }

    // Overworld platforms & obstacle structures
    for (int x = 12; x <= 18; ++x) {
        m_context.physicsWorld.setTile(x, 7, TileType::OneWayPlatform);
        m_context.tilemap.setBlock(x, 7, BlockLayer::Foreground, 5);
    }
    for (int x = 24; x <= 32; ++x) {
        m_context.physicsWorld.setTile(x, 4, TileType::OneWayPlatform);
        m_context.tilemap.setBlock(x, 4, BlockLayer::Foreground, 5);
    }

    // Dungeon Portal Archway at X = 250
    m_context.physicsWorld.setTile(250, 9, TileType::OneWayPlatform);
    m_context.tilemap.setBlock(250, 9, BlockLayer::Foreground, 3);

    // 4. Generate Precursor BSP Dungeon
    DungeonConfig dConfig{60, 40, 6, 12, 4};
    m_dungeonLayout = DungeonGenerator(m_context.rng).generate(dConfig);

    // 5. Spawn Player
    m_playerEntity = m_context.registry.create();
    m_context.registry.emplace<PlayerTag>(m_playerEntity);
    m_context.registry.emplace<TransformComponent>(m_playerEntity, m_respawnPoint);
    m_context.registry.emplace<VelocityComponent>(m_playerEntity, Vec2{0.0f, 0.0f});
    m_context.registry.emplace<ColliderComponent>(m_playerEntity, Rect{-8.0f, -16.0f, 16.0f, 16.0f});

    const auto& cls = m_context.classRegistry.getClass(playerClass);
    DerivedStats derived = StatsSystem::calculateDerivedStats(cls.baseAttributes);

    m_context.registry.emplace<HealthComponent>(m_playerEntity, derived.maxHealth, derived.maxHealth, derived.healthRegen);
    m_context.registry.emplace<ManaComponent>(m_playerEntity, derived.maxMana, derived.maxMana, derived.manaRegen);
    m_context.registry.emplace<PowerComponent>(m_playerEntity, 50.0f, derived.maxPower, 2.0f);
    m_context.registry.emplace<StatsComponent>(m_playerEntity);

    // Initial Starter Items
    Item starterSword;
    starterSword.id = "item_starter_blade";
    starterSword.name = "Forged Scrap Blade";
    starterSword.category = ItemCategory::Weapon;
    starterSword.equipSlot = EquipSlot::MainHand;
    starterSword.baseDamage = 35.0f;
    m_inventory.addItem(starterSword);

    Item starterWood;
    starterWood.id = "mat_wood_plank";
    starterWood.name = "Wood Plank";
    starterWood.category = ItemCategory::Material;
    starterWood.stackable = true;
    starterWood.quantity = 15;
    m_inventory.addItem(starterWood);

    Item starterOre;
    starterOre.id = "mat_iron_ore";
    starterOre.name = "Iron Ore";
    starterOre.category = ItemCategory::Material;
    starterOre.stackable = true;
    starterOre.quantity = 6;
    m_inventory.addItem(starterOre);

    // 6. Controller Config
    m_controllerConfig.moveSpeed = 120.0f;
    m_controllerConfig.jumpForce = 250.0f;
    m_controllerConfig.gravity = 600.0f;

    // 7. Spawn initial patrol enemies
    spawnEnemy(Vec2{220.0f, 160.0f}, 60.0f, 100);
    spawnEnemy(Vec2{350.0f, 160.0f}, 80.0f, 150);
    spawnEnemy(Vec2{500.0f, 160.0f}, 120.0f, 250);
}

bool GameSimulation::isPlayerDead() const {
    return m_context.registry.valid(m_playerEntity) &&
           m_context.registry.all_of<HealthComponent>(m_playerEntity) &&
           m_context.registry.get<HealthComponent>(m_playerEntity).isDead;
}

void GameSimulation::setRespawnPoint(const Vec2& point) {
    m_respawnPoint = point;
}

bool GameSimulation::respawnPlayer() {
    if (!isPlayerDead()) return false;

    auto& health = m_context.registry.get<HealthComponent>(m_playerEntity);
    auto& position = m_context.registry.get<TransformComponent>(m_playerEntity).position;
    auto& velocity = m_context.registry.get<VelocityComponent>(m_playerEntity).linear;
    position = m_respawnPoint;
    velocity = Vec2{0.0f, 0.0f};
    health.current = health.max;
    health.isDead = false;
    health.invulnTimer = 2.0f;
    m_metabolism.eat(100.0f);
    m_metabolism.drink(100.0f);
    m_audio.playSound(SoundEffect::LevelUp, 0.35f);
    m_particles.emitBurst(position, 18, Color{90, 220, 255, 255}, 0.6f, 70.0f);
    return true;
}

bool GameSimulation::createCharacter(const CharacterCreation& character) {
    if (character.name.empty()) return false;
    m_character = character;
    return true;
}

bool GameSimulation::allocateAttribute(int attributeIndex) {
    if (attributeIndex < 0 || attributeIndex >= static_cast<int>(Progression::Attribute::Count)) return false;
    return m_progression.allocateAttribute(static_cast<Progression::Attribute>(attributeIndex));
}

bool GameSimulation::allocateSkill(const std::string& nodeId) {
    if (!m_skillTree.canAllocate(nodeId) || !m_progression.spendSkillPoints(1)) return false;
    return m_skillTree.allocate(nodeId);
}

entt::entity GameSimulation::spawnEnemy(const Vec2& position, float health, int xpReward, EnemyType type) {
    auto enemy = m_context.registry.create();
    m_context.registry.emplace<EnemyTag>(enemy, 1, xpReward, type);
    m_context.registry.emplace<TransformComponent>(enemy, position);
    m_context.registry.emplace<VelocityComponent>(enemy, Vec2{0.0f, 0.0f});
    m_context.registry.emplace<ColliderComponent>(enemy, Rect{-8.0f, -16.0f, 16.0f, 16.0f});
    m_context.registry.emplace<HealthComponent>(enemy, health, health, 0.0f);
    return enemy;
}

void GameSimulation::step(const ControllerInput& input, float dt) {
    if (m_hitstopTimer > 0.0f) {
        m_hitstopTimer = std::max(0.0f, m_hitstopTimer - dt);
        return;
    }

    m_tickCount++;
    m_simulationTime += dt;

    if (m_attackVisualTimer > 0.0f) {
        m_attackVisualTimer = std::max(0.0f, m_attackVisualTimer - dt);
    }

    // Update Skill Cooldowns
    m_skillExecutor.update(dt);
    m_floatingText.update(dt);
    m_particles.update(dt);
    m_audio.update(dt);

    if (input.jumpPressed) {
        m_audio.playSound(SoundEffect::Jump);
    }

    // Update Player Movement & Controller
    Vec2 playerPos{0.0f, 0.0f};
    if (m_context.registry.valid(m_playerEntity)) {
        auto& pos = m_context.registry.get<TransformComponent>(m_playerEntity).position;
        auto& vel = m_context.registry.get<VelocityComponent>(m_playerEntity).linear;
        m_controller.update(pos, vel, input, m_context.physicsWorld, m_controllerConfig, dt);
        playerPos = pos;
    }

    if (m_context.dayNight.getWeather() != WeatherType::Clear && m_tickCount % 3 == 0) {
        Color weatherColor{110, 190, 235, 180};
        Vec2 weatherVelocity{0.0f, 150.0f};
        float particleSize = 1.5f;
        switch (m_context.dayNight.getWeather()) {
            case WeatherType::Blizzard:
                weatherColor = Color{235, 245, 255, 210};
                weatherVelocity = Vec2{-35.0f, 80.0f};
                particleSize = 2.5f;
                break;
            case WeatherType::FalloutStorm:
                weatherColor = Color{125, 220, 100, 175};
                weatherVelocity = Vec2{20.0f, 95.0f};
                particleSize = 2.0f;
                break;
            case WeatherType::Rain:
            case WeatherType::Clear:
                break;
        }
        Vec2 offset{static_cast<float>((m_tickCount * 37) % 160) - 80.0f, -120.0f};
        m_particles.emit(playerPos + offset, weatherVelocity, weatherColor, 1.0f, particleSize);
    }

    // Update Projectile Physics & Collisions
    m_projectileSystem.update(m_context.registry, m_context.physicsWorld, dt);

    // Update Loot Physics, Magnetic Attraction & Auto-Pickup
    m_lootSystem.update(m_context.registry, m_context.physicsWorld, m_inventory, playerPos, dt, 80.0f);

    // Update Enemies (Pursuit AI towards Player)
    auto enemies = m_context.registry.view<EnemyTag, TransformComponent, VelocityComponent, HealthComponent>();
    bool nearbyCombat = false;
    bool bossCombat = false;
    for (auto [e, tag, trans, vel, hp] : enemies.each()) {
        hp.hitFlashTimer = std::max(0.0f, hp.hitFlashTimer - dt);
        hp.healthBarTimer = std::max(0.0f, hp.healthBarTimer - dt);
        float dist = trans.position.distanceTo(playerPos);
        if (!hp.isDead && dist < 220.0f) {
            nearbyCombat = true;
            bossCombat = bossCombat || m_context.registry.all_of<BossEncounterComponent>(e);
        }
        if (m_context.registry.all_of<BossEncounterComponent>(e)) {
            auto& encounter = m_context.registry.get<BossEncounterComponent>(e);
            encounter.action = encounter.controller.update(trans.position, playerPos, hp.current, hp.max, dt);
            if (encounter.action.triggerPhaseTransitionBlast) {
                m_particles.emitBurst(trans.position, 24, Color{255, 75, 45, 255}, 0.8f, 140.0f);
                if (!encounter.summonsSpawned) {
                    spawnEnemy(trans.position + Vec2{-32.0f, 0.0f}, 80.0f, 120, EnemyType::Bat);
                    spawnEnemy(trans.position + Vec2{32.0f, 0.0f}, 80.0f, 120, EnemyType::Bat);
                    encounter.summonsSpawned = true;
                }
                if (bossCombat) {
                    m_audio.setMusicScene(MusicScene::Boss);
                } else if (nearbyCombat) {
                    m_audio.setMusicScene(MusicScene::Combat);
                } else if (m_context.dayNight.getWeather() != WeatherType::Clear) {
                    m_audio.setMusicScene(MusicScene::Environment);
                } else {
                    m_audio.setMusicScene(MusicScene::Exploration);
                }
            }
        }
        if (dist < 220.0f && dist > 15.0f) {
            float dir = (playerPos.x > trans.position.x) ? 1.0f : -1.0f;
            vel.linear.x = dir * 50.0f;
        } else {
            vel.linear.x = 0.0f;
        }

        vel.linear.y += 600.0f * dt;
        SweepResult sweep = m_context.physicsWorld.sweepBox(trans.position, Rect{-8.0f, -16.0f, 16.0f, 16.0f}, vel.linear * dt);
        trans.position += sweep.adjustedMove;
        if (sweep.hit && sweep.contactNormal.y < -0.5f) {
            vel.linear.y = 0.0f;
        }

        // Enemy melee damage against player
        if (dist <= 16.0f && m_context.registry.valid(m_playerEntity)) {
            Hitbox enemyHitbox;
            enemyHitbox.damage = 4.0f;
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

    // Passive regeneration of Health, Mana, Power
    if (m_context.registry.valid(m_playerEntity)) {
        m_context.registry.get<HealthComponent>(m_playerEntity).update(dt);
        m_context.registry.get<ManaComponent>(m_playerEntity).update(dt);
        m_context.registry.get<PowerComponent>(m_playerEntity).update(dt);
    }

    auto deathAnimationView = m_context.registry.view<DeathAnimationComponent>();
    std::vector<entt::entity> finishedDeaths;
    for (auto [e, death] : deathAnimationView.each()) {
        death.remaining -= dt;
        if (death.remaining <= 0.0f) {
            finishedDeaths.push_back(e);
        }
    }
    for (auto e : finishedDeaths) {
        if (m_context.registry.valid(e)) {
            m_context.registry.destroy(e);
        }
    }

    // Check defeated enemies to award XP and spawn loot drops
    auto healthView = m_context.registry.view<HealthComponent, EnemyTag, TransformComponent>();
    std::vector<entt::entity> defeated;
    for (auto [e, health, enemyTag, trans] : healthView.each()) {
        if (health.isDead && !m_context.registry.all_of<DeathAnimationComponent>(e)) {
            defeated.push_back(e);
        }
    }

    for (auto e : defeated) {
        if (m_context.registry.valid(e)) {
            const auto& enemyTag = m_context.registry.get<EnemyTag>(e);
            const auto& trans = m_context.registry.get<TransformComponent>(e);

            m_progression.addXP(enemyTag.xpReward);
            m_floatingText.spawnXP(trans.position, enemyTag.xpReward);
            bool isBoss = m_context.registry.all_of<BossEncounterComponent>(e);
            Color deathColor = isBoss ? Color{255, 55, 80, 255} : Color{255, 120, 45, 255};
            switch (enemyTag.type) {
                case EnemyType::Bat:
                    deathColor = Color{180, 90, 240, 255};
                    break;
                case EnemyType::CyberGunner:
                    deathColor = Color{80, 220, 240, 255};
                    break;
                case EnemyType::Raptor:
                    deathColor = Color{230, 150, 50, 255};
                    break;
                case EnemyType::Slime:
                default:
                    break;
            }
            m_particles.emitBurst(trans.position, isBoss ? 40 : 18, deathColor, isBoss ? 1.0f : 0.65f, 95.0f);
            m_audio.playSound(SoundEffect::EnemyDeath);
            m_audio.playSound(SoundEffect::XPPickup);

            // Spawn monster loot drop
            Item drop;
            drop.id = isBoss ? "boss_architect_core" : "mat_monster_trophy";
            drop.name = isBoss ? "Architect Core" : "Mutant Chitin";
            drop.category = ItemCategory::Material;
            drop.stackable = true;
            drop.quantity = 1;
            m_lootSystem.spawnLoot(m_context.registry, trans.position, drop);
            m_context.registry.emplace<DeathAnimationComponent>(e, 0.25f, 0.25f, enemyTag.type);
        }
    }
}

void GameSimulation::playerAttack() {
    if (!m_context.registry.valid(m_playerEntity)) return;

    m_audio.playSound(SoundEffect::SwordSlash);

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
        float previousHealth = hp.current;
        CombatSystem::resolveHitbox(m_context.registry, attackBox, e);
        if (hp.current < previousHealth) {
            hp.hitFlashTimer = 2.0f / 60.0f;
            hp.healthBarTimer = 3.0f;
            float damage = previousHealth - hp.current;
            m_floatingText.spawnDamage(trans.position, damage);
            m_particles.emitBurst(trans.position, 5, Color{255, 210, 90, 255}, 0.25f, 45.0f);
            m_audio.playSound(SoundEffect::HitImpact);
            m_hitstopTimer = std::max(m_hitstopTimer, 0.04f);
        }
    }
}

void GameSimulation::shootProjectile(const Vec2& targetWorldPos) {
    if (!m_context.registry.valid(m_playerEntity)) return;

    const auto& playerPos = m_context.registry.get<TransformComponent>(m_playerEntity).position;
    Vec2 origin = playerPos + Vec2{0.0f, -8.0f};
    Vec2 aimDir = (targetWorldPos - origin).normalized();

    ProjectileConfig config;
    config.speed = 350.0f;
    config.damage = 30.0f;
    config.lifetime = 2.5f;
    config.color = Color{255, 230, 80, 255};

    m_projectileSystem.spawnProjectile(m_context.registry, origin, aimDir, config, m_playerEntity);
}

bool GameSimulation::mineTileAt(const Vec2& targetWorldPos) {
    if (!m_context.registry.valid(m_playerEntity)) return false;
    const auto& playerPos = m_context.registry.get<TransformComponent>(m_playerEntity).position;
    bool mined = m_worldInteraction.mineTile(m_context.registry, playerPos, targetWorldPos, 96.0f);
    if (mined) {
        m_audio.playSound(SoundEffect::MiningClink);
        m_audio.setMusicScene(MusicScene::Mining);
    }
    return mined;
}

bool GameSimulation::placeBlockAt(const Vec2& targetWorldPos, const std::string& itemId, uint16_t blockType) {
    if (!m_context.registry.valid(m_playerEntity)) return false;
    const auto& playerPos = m_context.registry.get<TransformComponent>(m_playerEntity).position;
    return m_worldInteraction.placeBlock(m_inventory, itemId, playerPos, targetWorldPos, 96.0f, blockType);
}

bool GameSimulation::castSkillQ() {
    if (!m_context.registry.valid(m_playerEntity)) return false;
    float sta = 100.0f;
    float mana = m_context.registry.get<ManaComponent>(m_playerEntity).current;
    float pwr = m_context.registry.get<PowerComponent>(m_playerEntity).current;

    CastResult res = m_skillExecutor.tryCast(HotbarSlot::Q, sta, mana, pwr);
    if (res.success) {
        // Seismic Shockwave: hits all enemies within 8 tiles
        const auto& pPos = m_context.registry.get<TransformComponent>(m_playerEntity).position;
        Hitbox wave;
        wave.bounds = Rect{pPos.x - 64.0f, pPos.y - 32.0f, 128.0f, 48.0f};
        wave.damage = res.damageOutput;
        wave.knockbackForce = 200.0f;
        wave.owner = m_playerEntity;

        auto enemies = m_context.registry.view<EnemyTag, TransformComponent, HealthComponent, ColliderComponent>();
        for (auto [e, tag, trans, hp, col] : enemies.each()) {
            CombatSystem::resolveHitbox(m_context.registry, wave, e);
        }
        return true;
    }
    return false;
}

bool GameSimulation::castSkillE() {
    if (!m_context.registry.valid(m_playerEntity)) return false;
    auto& pwr = m_context.registry.get<PowerComponent>(m_playerEntity);
    float sta = 100.0f;
    float mana = 100.0f;
    float curPwr = pwr.current;

    CastResult res = m_skillExecutor.tryCast(HotbarSlot::E, sta, mana, curPwr);
    if (res.success) {
        pwr.current = curPwr;
        auto& vel = m_context.registry.get<VelocityComponent>(m_playerEntity).linear;
        vel.x = m_controller.getFacing() * 300.0f; // Rapid horizontal dash burst
        m_context.registry.get<HealthComponent>(m_playerEntity).invulnTimer = 0.4f; // i-frames
        return true;
    }
    return false;
}

bool GameSimulation::castSkillR() {
    if (!m_context.registry.valid(m_playerEntity)) return false;
    auto& mana = m_context.registry.get<ManaComponent>(m_playerEntity);
    float sta = 100.0f;
    float curMana = mana.current;
    float pwr = 100.0f;

    CastResult res = m_skillExecutor.tryCast(HotbarSlot::R, sta, curMana, pwr);
    if (res.success) {
        mana.current = curMana;
        // Radial 360-degree projectile lightning discharge (8 projectiles)
        const auto& pPos = m_context.registry.get<TransformComponent>(m_playerEntity).position;
        for (int i = 0; i < 8; ++i) {
            float angle = i * (3.14159265f / 4.0f);
            Vec2 dir{std::cos(angle), std::sin(angle)};
            ProjectileConfig cfg;
            cfg.speed = 280.0f;
            cfg.damage = 45.0f;
            cfg.lifetime = 1.5f;
            cfg.color = Color{50, 180, 255, 255};
            m_projectileSystem.spawnProjectile(m_context.registry, pPos + Vec2{0.0f, -8.0f}, dir, cfg, m_playerEntity);
        }
        return true;
    }
    return false;
}

bool GameSimulation::castSkillF() {
    if (!m_context.registry.valid(m_playerEntity)) return false;
    auto& mana = m_context.registry.get<ManaComponent>(m_playerEntity);
    float sta = 100.0f;
    float curMana = mana.current;
    float pwr = 100.0f;

    CastResult res = m_skillExecutor.tryCast(HotbarSlot::F, sta, curMana, pwr);
    if (res.success) {
        mana.current = curMana;
        m_context.registry.get<HealthComponent>(m_playerEntity).heal(80.0f);
        return true;
    }
    return false;
}

void GameSimulation::toggleScreen(ActiveScreen screen) {
    if (m_activeScreen == screen) {
        m_activeScreen = ActiveScreen::None;
    } else {
        m_activeScreen = screen;
    }
}

bool GameSimulation::canEnterDungeon() const {
    if (!m_context.registry.valid(m_playerEntity)) return false;
    const auto& pos = m_context.registry.get<TransformComponent>(m_playerEntity).position;
    // Entrance is around X = 250*16 = 4000
    return std::abs(pos.x - 400.0f) < 48.0f;
}

void GameSimulation::enterDungeon() {
    m_dungeonManager.enterDungeon(1);
    if (!m_dungeonLayout.rooms.empty()) {
        const auto& startRoom = m_dungeonLayout.rooms[m_dungeonLayout.startRoomIndex];
        auto& pPos = m_context.registry.get<TransformComponent>(m_playerEntity).position;
        pPos = Vec2{startRoom.center().x * 16.0f, startRoom.center().y * 16.0f};

        // Populate dungeon tiles in world
        for (int y = 0; y < m_dungeonLayout.height; ++y) {
            for (int x = 0; x < m_dungeonLayout.width; ++x) {
                if (m_dungeonLayout.grid[y][x] == 1) {
                    m_context.physicsWorld.setTile(x, y, TileType::Solid);
                    m_context.tilemap.setBlock(x, y, BlockLayer::Foreground, 1);
                } else {
                    m_context.physicsWorld.setTile(x, y, TileType::Empty);
                    m_context.tilemap.setBlock(x, y, BlockLayer::Foreground, 0);
                }
            }
        }

        // Spawn Dungeon Boss in Boss Room
        const auto& bossRoom = m_dungeonLayout.rooms[m_dungeonLayout.bossRoomIndex];
        entt::entity boss = spawnEnemy(Vec2{bossRoom.center().x * 16.0f, bossRoom.center().y * 16.0f}, 400.0f, 1000);
        m_context.registry.emplace<BossEncounterComponent>(boss);
    }
}

void GameSimulation::exitDungeon() {
    m_dungeonManager.exitDungeon();
    // Return to Overworld settlement
    if (m_context.registry.valid(m_playerEntity)) {
        auto& pPos = m_context.registry.get<TransformComponent>(m_playerEntity).position;
        pPos = Vec2{100.0f, 160.0f};
    }
}

float GameSimulation::getPlayerHealth() const {
    if (m_context.registry.valid(m_playerEntity)) {
        return m_context.registry.get<HealthComponent>(m_playerEntity).current;
    }
    return 0.0f;
}

float GameSimulation::getPlayerMana() const {
    if (m_context.registry.valid(m_playerEntity)) {
        return m_context.registry.get<ManaComponent>(m_playerEntity).current;
    }
    return 0.0f;
}

float GameSimulation::getPlayerPower() const {
    if (m_context.registry.valid(m_playerEntity)) {
        return m_context.registry.get<PowerComponent>(m_playerEntity).current;
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
