#pragma once

#include "core/Config.hpp"
#include <SDL3/SDL.h>
#include <spdlog/spdlog.h>

namespace rpg {

class Renderer {
public:
    Renderer() = default;
    ~Renderer() { shutdown(); }

    bool init(SDL_Window* window, const DisplayConfig& config) {
        m_window = window;
        m_config = config;

        m_renderer = SDL_CreateRenderer(window, nullptr);
        if (!m_renderer) {
            spdlog::error("Failed to create SDL renderer: {}", SDL_GetError());
            return false;
        }

        updateDimensions();
        return createRenderTarget();
    }

    void shutdown() {
        if (m_renderTarget) {
            SDL_DestroyTexture(m_renderTarget);
            m_renderTarget = nullptr;
        }
        if (m_renderer) {
            SDL_DestroyRenderer(m_renderer);
            m_renderer = nullptr;
        }
    }

    void beginScene() {
        SDL_SetRenderTarget(m_renderer, m_renderTarget);
        SDL_SetRenderDrawColor(m_renderer, 18, 18, 24, 255); // Dark pixel slate
        SDL_RenderClear(m_renderer);
    }

    void endScene() {
        // Switch to default backbuffer to upscale the internal canvas
        SDL_SetRenderTarget(m_renderer, nullptr);
        SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255); // Letterbox black bars
        SDL_RenderClear(m_renderer);

        SDL_FRect destRect = {
            static_cast<float>(m_viewportX),
            static_cast<float>(m_viewportY),
            static_cast<float>(m_internalWidth * m_integerScale),
            static_cast<float>(m_internalHeight * m_integerScale)
        };

        SDL_RenderTexture(m_renderer, m_renderTarget, nullptr, &destRect);
    }

    void present() {
        SDL_RenderPresent(m_renderer);
    }

    void drawRect(float x, float y, float w, float h, uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255) {
        SDL_SetRenderDrawColor(m_renderer, r, g, b, a);
        SDL_FRect rect = { x, y, w, h };
        SDL_RenderFillRect(m_renderer, &rect);
    }

    SDL_Renderer* getSDLRenderer() const { return m_renderer; }
    int getInternalWidth() const { return m_internalWidth; }
    int getInternalHeight() const { return m_internalHeight; }
    int getIntegerScale() const { return m_integerScale; }

private:
    void updateDimensions() {
        int windowW = 0, windowH = 0;
        SDL_GetWindowSize(m_window, &windowW, &windowH);

        m_internalHeight = m_config.targetInternalHeight;
        float aspect = static_cast<float>(windowW) / static_cast<float>(windowH > 0 ? windowH : 1);
        m_internalWidth = static_cast<int>(m_internalHeight * aspect);

        // Calculate maximum clean integer scale
        int scaleX = windowW / m_internalWidth;
        int scaleY = windowH / m_internalHeight;
        m_integerScale = std::max(1, std::min(scaleX, scaleY));

        // Center the scaled viewport with black letterboxing
        int renderedW = m_internalWidth * m_integerScale;
        int renderedH = m_internalHeight * m_integerScale;
        m_viewportX = (windowW - renderedW) / 2;
        m_viewportY = (windowH - renderedH) / 2;
    }

    bool createRenderTarget() {
        if (m_renderTarget) {
            SDL_DestroyTexture(m_renderTarget);
        }

        m_renderTarget = SDL_CreateTexture(
            m_renderer,
            SDL_PIXELFORMAT_RGBA8888,
            SDL_TEXTUREACCESS_TARGET,
            m_internalWidth,
            m_internalHeight
        );

        if (!m_renderTarget) {
            spdlog::error("Failed to create pixel render target: {}", SDL_GetError());
            return false;
        }

        SDL_SetTextureScaleMode(m_renderTarget, SDL_SCALEMODE_NEAREST);
        return true;
    }

    SDL_Window* m_window = nullptr;
    SDL_Renderer* m_renderer = nullptr;
    SDL_Texture* m_renderTarget = nullptr;
    DisplayConfig m_config;

    int m_internalWidth = 640;
    int m_internalHeight = 360;
    int m_integerScale = 1;
    int m_viewportX = 0;
    int m_viewportY = 0;
};

} // namespace rpg
