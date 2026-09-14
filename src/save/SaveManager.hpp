#pragma once
#include "gameplay/stats/StatsSystem.hpp"
#include "gameplay/items/Item.hpp"
#include <string>
#include <vector>

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
};

class SaveManager {
public:
    static bool saveToFile(const std::string& filePath, const SaveData& data);
    static bool loadFromFile(const std::string& filePath, SaveData& outData);

    static uint32_t computeChecksum(const std::string& content);
};
