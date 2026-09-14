#pragma once
#include <SDL3/SDL.h>
#include <string>
#include "core/Math.hpp"
#include "render/Camera.hpp"
#include "gameplay/combat/CombatSystem.hpp"

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
    void drawHUD(const GameSimulation& sim, const CanvasMetrics& metrics, const RawInputState& input);

    SDL_Window* getWindow() const { return m_window; }
    SDL_Renderer* getSDLRenderer() const { return m_renderer; }

private:
    SDL_Window* m_window{nullptr};
    SDL_Renderer* m_renderer{nullptr};
    SDL_Texture* m_virtualTexture{nullptr};
    int m_virtualWidth{640};
    int m_virtualHeight{360};
};
