#pragma once

#include "Config.hpp"
#include <SDL3/SDL.h>
#include <spdlog/spdlog.h>

namespace rpg {

class DisplayManager {
public:
    static DisplayConfig detectOptimalDisplay() {
        DisplayConfig config;

        SDL_DisplayID primaryDisplay = SDL_GetPrimaryDisplay();
        if (primaryDisplay == 0) {
            spdlog::warn("Could not get primary display, falling back to 1280x720");
            return config;
        }

        const SDL_DisplayMode* mode = SDL_GetCurrentDisplayMode(primaryDisplay);
        if (mode) {
            spdlog::info("Detected display: {}x{} @ {}Hz", mode->w, mode->h, mode->refresh_rate);
            config.windowWidth = mode->w;
            config.windowHeight = mode->h;
            config.refreshRate = static_cast<int>(mode->refresh_rate);
            config.mode = WindowMode::Borderless;
        }

        return config;
    }
};

} // namespace rpg
