#pragma once

#include <string>

namespace rpg {

enum class WindowMode {
    Fullscreen,
    Borderless,
    Windowed
};

struct DisplayConfig {
    int windowWidth = 1280;
    int windowHeight = 720;
    int targetInternalHeight = 360;
    int refreshRate = 60;
    bool vsync = true;
    WindowMode mode = WindowMode::Windowed;
};

struct GameConfig {
    DisplayConfig display;
    float masterVolume = 1.0f;
    float sfxVolume = 0.8f;
    float musicVolume = 0.6f;
    std::string title = "Untitled RPG";
};

} // namespace rpg
