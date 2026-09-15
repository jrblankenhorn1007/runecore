#pragma once
#include "core/EngineContext.hpp"
#include "ecs/Components.hpp"
#include "physics/CharacterController.hpp"
#include "gameplay/combat/CombatSystem.hpp"
#include "gameplay/combat/ProjectileSystem.hpp"
#include "gameplay/items/Inventory.hpp"
#include "gameplay/items/LootSystem.hpp"
#include "gameplay/stats/Progression.hpp"
#include "gameplay/survival/Metabolism.hpp"
#include "gameplay/augmentations/AugmentationMatrix.hpp"
#include "gameplay/skills/SkillExecutor.hpp"
#include "gameplay/skills/SkillTree.hpp"
#include "gameplay/crafting/CraftingEngine.hpp"
#include "gameplay/crafting/ModificationForge.hpp"
#include "gameplay/building/WorldInteraction.hpp"
#include "gameplay/building/FarmingSystem.hpp"
#include "procgen/DungeonGenerator.hpp"
#include "render/FloatingText.hpp"
#include "render/ParticleSystem.hpp"
#include "audio/AudioEngine.hpp"
#include "ui/GuiWorkflows.hpp"

enum class ActiveScreen {
    None,
    Inventory,
    Crafting,
    Augmentations,
    CharacterSheet,
    Skills,
    Minimap,
    Settings
};

struct CharacterCreation {
    std::string name{"Vanguard"};
    ClassType classType{ClassType::Juggernaut};
    Color visorColor{65, 115, 220, 255};
};

class GameSimulation {
public:
    GameSimulation();

    void initialize(ClassType playerClass = ClassType::Juggernaut, bool headlessAudio = true);
    void step(const ControllerInput& input, float dt);

    void playerAttack();
    void shootProjectile(const Vec2& targetWorldPos);
    bool mineTileAt(const Vec2& targetWorldPos);
    bool placeBlockAt(const Vec2& targetWorldPos, const std::string& itemId, uint16_t blockType);

    bool castSkillQ();
    bool castSkillE();
    bool castSkillR();
    bool castSkillF();
    bool respawnPlayer();
    bool isPlayerDead() const;
    void setRespawnPoint(const Vec2& point);
    Vec2 getRespawnPoint() const { return m_respawnPoint; }
    bool createCharacter(const CharacterCreation& character);
    const CharacterCreation& getCharacter() const { return m_character; }
    bool allocateAttribute(int attributeIndex);
    bool allocateSkill(const std::string& nodeId);

    void toggleScreen(ActiveScreen screen);
    ActiveScreen getActiveScreen() const { return m_activeScreen; }

    bool canEnterDungeon() const;
    void enterDungeon();
    void exitDungeon();
    bool isInsideDungeon() const { return m_dungeonManager.getCurrentZone() == WorldZone::Dungeon; }

    entt::entity spawnEnemy(const Vec2& position, float health, int xpReward, EnemyType type = EnemyType::Slime);

    uint64_t getTickCount() const { return m_tickCount; }
    float getSimulationTime() const { return m_simulationTime; }

    int getPlayerLevel() const { return m_progression.getLevel(); }
    uint64_t getPlayerXP() const { return m_progression.getCurrentXP(); }
    float getPlayerHealth() const;
    float getPlayerMana() const;
    float getPlayerPower() const;
    float getPlayerHunger() const { return m_metabolism.getHunger(); }
    Vec2 getPlayerPosition() const;
    int getPlayerFacing() const { return m_controller.getFacing(); }
    bool isAttacking() const { return m_attackVisualTimer > 0.0f; }
    float getHitstopRemaining() const { return m_hitstopTimer; }
    const Hitbox& getLastAttackBox() const { return m_lastAttackBox; }

    size_t getEnemyCount() const;

    EngineContext& getContext() { return m_context; }
    const EngineContext& getContext() const { return m_context; }
    Inventory& getInventory() { return m_inventory; }
    const DungeonLayout& getDungeonLayout() const { return m_dungeonLayout; }
    SkillExecutor& getSkillExecutor() { return m_skillExecutor; }
    CraftingEngine& getCraftingEngine() { return m_crafting; }
    AugmentationMatrix& getAugmentations() { return m_augmentations; }
    Progression& getProgression() { return m_progression; }
    const Progression& getProgression() const { return m_progression; }
    SkillTree& getSkillTree() { return m_skillTree; }
    const SkillTree& getSkillTree() const { return m_skillTree; }
    GuiWorkflows& getGuiWorkflows() { return m_guiWorkflows; }
    const GuiWorkflows& getGuiWorkflows() const { return m_guiWorkflows; }
    FarmingSystem& getFarming() { return m_farming; }
    const FarmingSystem& getFarming() const { return m_farming; }
    FloatingTextSystem& getFloatingText() { return m_floatingText; }
    const FloatingTextSystem& getFloatingText() const { return m_floatingText; }
    AudioEngine& getAudio() { return m_audio; }
    const AudioEngine& getAudio() const { return m_audio; }
    ParticleSystem& getParticles() { return m_particles; }
    const ParticleSystem& getParticles() const { return m_particles; }

private:
    EngineContext m_context;
    CharacterController m_controller;
    ControllerConfig m_controllerConfig;

    Inventory m_inventory{40};
    Progression m_progression;
    SkillTree m_skillTree;
    Metabolism m_metabolism;
    AugmentationMatrix m_augmentations;
    SkillExecutor m_skillExecutor;
    ModificationForge m_forge;
    CraftingEngine m_crafting;
    LootSystem m_lootSystem;
    ProjectileSystem m_projectileSystem;
    WorldInteraction m_worldInteraction;
    DungeonTransitionManager m_dungeonManager;
    DungeonLayout m_dungeonLayout;
    FloatingTextSystem m_floatingText;
    ParticleSystem m_particles;
    AudioEngine m_audio;
    GuiWorkflows m_guiWorkflows;
    FarmingSystem m_farming;

    entt::entity m_playerEntity{entt::null};
    uint64_t m_tickCount{0};
    float m_simulationTime{0.0f};

    float m_attackVisualTimer{0.0f};
    float m_hitstopTimer{0.0f};
    Hitbox m_lastAttackBox;
    ActiveScreen m_activeScreen{ActiveScreen::None};
    CharacterCreation m_character;
    Vec2 m_respawnPoint{100.0f, 160.0f};
};
