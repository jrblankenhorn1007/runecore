#pragma once
#include "gameplay/stats/StatsSystem.hpp"
#include "gameplay/items/Item.hpp"
#include <string>
#include <vector>
#include <array>
#include <SDL3/SDL.h>

struct SettingsData {
    float masterVolume{1.0f};
    float sfxVolume{1.0f};
    float musicVolume{1.0f};
    float ambienceVolume{1.0f};
    bool fullscreen{false};
    bool vsync{true};
    std::array<int, 4> movementKeys{{SDLK_A, SDLK_D, SDLK_SPACE, SDLK_LSHIFT}};
};

struct SaveData {
    std::string playerName{"Hero"};
    std::string className{"Juggernaut"};
    int level{1};
    uint64_t currentXP{0};

    float health{100.0f};
    float mana{50.0f};
    float power{0.0f};

    Attributes attributes;

    float hunger{100.0f};
    float thirst{100.0f};
    float bodyTemp{37.0f};

    std::vector<Item> inventoryItems;
    SettingsData settings;
};

class SaveManager {
public:
    static bool saveToFile(const std::string& filePath, const SaveData& data);
    static bool loadFromFile(const std::string& filePath, SaveData& outData);
    static bool saveSlot(const std::string& directory, int slot, const SaveData& data);
    static bool loadSlot(const std::string& directory, int slot, SaveData& outData);
    static std::vector<int> availableSlots(const std::string& directory, int maxSlots = 3);

    static uint32_t computeChecksum(const std::string& content);
};
