#pragma once
#include "core/EngineContext.hpp"
#include "physics/CharacterController.hpp"
#include "gameplay/combat/CombatSystem.hpp"
#include "gameplay/items/Inventory.hpp"
#include "gameplay/stats/Progression.hpp"
#include "gameplay/survival/Metabolism.hpp"
#include "gameplay/augmentations/AugmentationMatrix.hpp"
#include "gameplay/skills/SkillExecutor.hpp"
#include "gameplay/crafting/CraftingEngine.hpp"
#include "gameplay/crafting/ModificationForge.hpp"

class GameSimulation {
public:
    GameSimulation();

    void initialize(ClassType playerClass = ClassType::Juggernaut);
    void step(const ControllerInput& input, float dt);

    void playerAttack();
    entt::entity spawnEnemy(const Vec2& position, float health, int xpReward);

    uint64_t getTickCount() const { return m_tickCount; }
    float getSimulationTime() const { return m_simulationTime; }

    int getPlayerLevel() const { return m_progression.getLevel(); }
    uint64_t getPlayerXP() const { return m_progression.getCurrentXP(); }
    float getPlayerHealth() const;
    float getPlayerHunger() const { return m_metabolism.getHunger(); }
    Vec2 getPlayerPosition() const;
    int getPlayerFacing() const { return m_controller.getFacing(); }
    bool isAttacking() const { return m_attackVisualTimer > 0.0f; }
    const Hitbox& getLastAttackBox() const { return m_lastAttackBox; }

    size_t getEnemyCount() const;

    EngineContext& getContext() { return m_context; }
    Inventory& getInventory() { return m_inventory; }

private:
    EngineContext m_context;
    CharacterController m_controller;
    ControllerConfig m_controllerConfig;

    Inventory m_inventory{40};
    Progression m_progression;
    Metabolism m_metabolism;
    AugmentationMatrix m_augmentations;
    SkillExecutor m_skillExecutor;
    ModificationForge m_forge;
    CraftingEngine m_crafting;

    entt::entity m_playerEntity{entt::null};
    uint64_t m_tickCount{0};
    float m_simulationTime{0.0f};

    float m_attackVisualTimer{0.0f};
    Hitbox m_lastAttackBox;
};
