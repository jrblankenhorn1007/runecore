#pragma once
#include <SDL3/SDL.h>
#include <unordered_map>
#include <string>
#include <vector>
#include "core/Math.hpp"
#include "render/Camera.hpp"
#include "gameplay/combat/CombatSystem.hpp"
#include "gameplay/items/Inventory.hpp"
#include "gameplay/crafting/CraftingEngine.hpp"
#include "gameplay/augmentations/AugmentationMatrix.hpp"
#include "gameplay/building/FarmingSystem.hpp"
#include "gameplay/skills/SkillTree.hpp"
#include "gameplay/stats/Progression.hpp"
#include "procgen/DungeonGenerator.hpp"
#include "render/FloatingText.hpp"
#include "render/ParticleSystem.hpp"
#include "audio/AudioEngine.hpp"

class GameSimulation;
struct RawInputState;

class Renderer {
public:
    Renderer();
    ~Renderer();

    bool init(const std::string& title, int windowWidth = 1280, int windowHeight = 720, int virtualWidth = 640, int virtualHeight = 360, uint32_t extraFlags = 0);
    void shutdown();

    void beginFrame();
    void endFrame(const CanvasMetrics& metrics);

    void drawParallaxBackground(float worldX, int biomeTier, const CanvasMetrics& metrics);
    void drawTile(int tileX, int tileY, uint16_t blockId, const Camera& camera, const CanvasMetrics& metrics);
        void drawEntity(const Vec2& worldPos, const Vec2& size, Color color, const Camera& camera, const CanvasMetrics& metrics, int facing = 1, bool isPlayer = false, float healthRatio = 1.0f, bool hitFlash = false, bool showHealthBar = false);
        void drawBossTelegraph(const Vec2& worldPos, float radius, const Camera& camera, const CanvasMetrics& metrics, bool enraged = false);
    void drawWeapon(const Vec2& playerPos, const Vec2& aimTarget, bool attacking, const Camera& camera, const CanvasMetrics& metrics);
    void drawSlashArc(const Hitbox& hitbox, const Camera& camera, const CanvasMetrics& metrics, int facing);
    void drawProjectile(const Vec2& worldPos, const Vec2& vel, Color color, const Camera& camera, const CanvasMetrics& metrics);
    void drawLoot(const Vec2& worldPos, const std::string& name, const Camera& camera, const CanvasMetrics& metrics);
    void drawFloatingText(const FloatingText& text, const Camera& camera, const CanvasMetrics& metrics);
    void drawParticle(const Particle& particle, const Camera& camera, const CanvasMetrics& metrics);
    void drawFarmingPlot(int tileX, int tileY, CropStage stage, const Camera& camera, const CanvasMetrics& metrics);
    void drawGeneratedSlimeEnemy(const Vec2& worldPos, const Vec2& size,
                                 const Camera& camera, const CanvasMetrics& metrics,
                                 float healthRatio, bool showHealthBar, bool hitFlash,
                                 int animationFrame);
    bool drawGeneratedEntity(const std::string& assetPath, const Vec2& worldPos, const Vec2& size,
                             const Camera& camera, const CanvasMetrics& metrics, float healthRatio,
                             bool showHealthBar, bool hitFlash);

    void drawHUD(const GameSimulation& sim, const CanvasMetrics& metrics, const RawInputState& input);
    void drawBossHUD(const GameSimulation& sim, const CanvasMetrics& metrics);
    void drawMinimap(const DungeonLayout& layout, const Vec2& playerPos, const CanvasMetrics& metrics);
    void drawInventoryScreen(const Inventory& inv, const CanvasMetrics& metrics, Vec2 mouseVirtualPos = Vec2{-1.0f, -1.0f}, int draggedSlot = -1);
    void drawCraftingScreen(const CraftingEngine& crafting, const Inventory& inv, const CanvasMetrics& metrics);
    void drawAugmentationScreen(const AugmentationMatrix& augs, const CanvasMetrics& metrics);
    void drawCharacterSheet(const Progression& progression, const CanvasMetrics& metrics);
    void drawSkillTreeScreen(const SkillTree& skillTree, int skillPoints, const CanvasMetrics& metrics);
    void drawSettingsScreen(const AudioEngine& audio, const CanvasMetrics& metrics);
    void drawVisualQaOverlay(const std::string& scenario, float progress, const CanvasMetrics& metrics);
    void drawLightingOverlay(const Vec2& playerPos, float ambientDarkness, const Camera& camera, const CanvasMetrics& metrics);
    static int pixelGlyphIndex(char character);
    static int pixelGlyphRow(int pixel);

    SDL_Window* getWindow() const { return m_window; }
    SDL_Renderer* getSDLRenderer() const { return m_renderer; }
    static const std::vector<std::string>& getRequiredGeneratedAssets();
    std::vector<std::string> getMissingGeneratedAssets() const;
    int getGeneratedDrawCount(const std::string& assetPath) const;

private:
    SDL_Window* m_window{nullptr};
    SDL_Renderer* m_renderer{nullptr};
    SDL_Texture* m_virtualTexture{nullptr};
    SDL_Texture* m_generatedSlimeTexture{nullptr};
    std::unordered_map<std::string, SDL_Texture*> m_generatedTextures;
    std::unordered_map<std::string, int> m_generatedDrawCounts;
    std::vector<std::string> m_missingGeneratedAssets;
    int m_virtualWidth{640};
    int m_virtualHeight{360};
    static constexpr int m_internalRenderScale = 2;

    void drawPixelText(const std::string& text, float x, float y, float scale, Color color);
    SDL_Texture* loadGeneratedTexture(const std::string& assetPath);
};
