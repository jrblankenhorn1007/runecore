#pragma once
#include <SDL3/SDL.h>
#include <string>
#include "core/Math.hpp"
#include "render/Camera.hpp"
#include "gameplay/combat/CombatSystem.hpp"
#include "gameplay/items/Inventory.hpp"
#include "gameplay/crafting/CraftingEngine.hpp"
#include "gameplay/augmentations/AugmentationMatrix.hpp"
#include "procgen/DungeonGenerator.hpp"

class GameSimulation;
struct RawInputState;

class Renderer {
public:
    Renderer();
    ~Renderer();

    bool init(const std::string& title, int windowWidth, int windowHeight, int virtualWidth = 640, int virtualHeight = 360);
    void shutdown();

    void beginFrame();
    void endFrame(const CanvasMetrics& metrics);

    void drawTile(int tileX, int tileY, uint16_t blockId, const Camera& camera, const CanvasMetrics& metrics);
    void drawEntity(const Vec2& worldPos, const Vec2& size, Color color, const Camera& camera, const CanvasMetrics& metrics, int facing = 1, bool isPlayer = false, float healthRatio = 1.0f);
    void drawSlashArc(const Hitbox& hitbox, const Camera& camera, const CanvasMetrics& metrics, int facing);
    void drawProjectile(const Vec2& worldPos, const Vec2& vel, Color color, const Camera& camera, const CanvasMetrics& metrics);
    void drawLoot(const Vec2& worldPos, const std::string& name, const Camera& camera, const CanvasMetrics& metrics);

    void drawHUD(const GameSimulation& sim, const CanvasMetrics& metrics, const RawInputState& input);
    void drawMinimap(const DungeonLayout& layout, const Vec2& playerPos, const CanvasMetrics& metrics);
    void drawInventoryScreen(const Inventory& inv, const CanvasMetrics& metrics);
    void drawCraftingScreen(const CraftingEngine& crafting, const Inventory& inv, const CanvasMetrics& metrics);
    void drawAugmentationScreen(const AugmentationMatrix& augs, const CanvasMetrics& metrics);
    void drawLightingOverlay(const Vec2& playerPos, float ambientDarkness, const Camera& camera, const CanvasMetrics& metrics);

    SDL_Window* getWindow() const { return m_window; }
    SDL_Renderer* getSDLRenderer() const { return m_renderer; }

private:
    SDL_Window* m_window{nullptr};
    SDL_Renderer* m_renderer{nullptr};
    SDL_Texture* m_virtualTexture{nullptr};
    int m_virtualWidth{640};
    int m_virtualHeight{360};
};
