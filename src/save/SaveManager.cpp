#include "save/SaveManager.hpp"
#include <nlohmann/json.hpp>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <algorithm>

using json = nlohmann::json;

uint32_t SaveManager::computeChecksum(const std::string& content) {
    // 32-bit FNV-1a hash
    uint32_t hash = 2166136261u;
    for (char c : content) {
        hash ^= static_cast<uint8_t>(c);
        hash *= 16777619u;
    }
    return hash;
}

bool SaveManager::saveToFile(const std::string& filePath, const SaveData& data) {
    json j;
    j["playerName"] = data.playerName;
    j["className"] = data.className;
    j["level"] = data.level;
    j["currentXP"] = data.currentXP;
    j["health"] = data.health;
    j["mana"] = data.mana;
    j["power"] = data.power;

    j["attributes"] = {
        {"strength", data.attributes.strength},
        {"dexterity", data.attributes.dexterity},
        {"intelligence", data.attributes.intelligence},
        {"vitality", data.attributes.vitality},
        {"wisdom", data.attributes.wisdom},
        {"cybernetics", data.attributes.cybernetics}
    };

    j["hunger"] = data.hunger;
    j["thirst"] = data.thirst;
    j["bodyTemp"] = data.bodyTemp;
    j["settings"] = {
        {"masterVolume", data.settings.masterVolume},
        {"sfxVolume", data.settings.sfxVolume},
        {"musicVolume", data.settings.musicVolume},
        {"ambienceVolume", data.settings.ambienceVolume},
        {"fullscreen", data.settings.fullscreen},
        {"vsync", data.settings.vsync},
        {"movementKeys", data.settings.movementKeys}
    };

    json itemsJson = json::array();
    for (const auto& item : data.inventoryItems) {
        json ij;
        ij["id"] = item.id;
        ij["name"] = item.name;
        ij["tier"] = item.tier;
        ij["quantity"] = item.quantity;
        ij["baseDamage"] = item.baseDamage;
        ij["baseArmor"] = item.baseArmor;
        itemsJson.push_back(ij);
    }
    j["inventory"] = itemsJson;

    std::string serialized = j.dump(2);
    uint32_t checksum = computeChecksum(serialized);

    json root;
    root["version"] = 1;
    root["checksum"] = checksum;
    root["payload"] = serialized;

    // Atomic write to .tmp then rename
    std::string tmpPath = filePath + ".tmp";
    std::ofstream out(tmpPath);
    if (!out.is_open()) return false;

    out << root.dump(2);
    out.close();

    std::error_code ec;
    std::filesystem::rename(tmpPath, filePath, ec);
    return !ec;
}

bool SaveManager::loadFromFile(const std::string& filePath, SaveData& outData) {
    if (!std::filesystem::exists(filePath)) return false;

    std::ifstream in(filePath);
    if (!in.is_open()) return false;

    std::string fullText((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
    in.close();

    json root;
    try {
        root = json::parse(fullText);
    } catch (...) {
        return false;
    }

    if (!root.contains("checksum") || !root.contains("payload")) {
        return false;
    }

    uint32_t recordedChecksum = root["checksum"].get<uint32_t>();
    std::string payload = root["payload"].get<std::string>();

    uint32_t computed = computeChecksum(payload);
    if (computed != recordedChecksum) {
        return false; // Checksum mismatch / corrupted
    }

    json j;
    try {
        j = json::parse(payload);
    } catch (...) {
        return false;
    }

    outData.playerName = j.value("playerName", "Hero");
    outData.className = j.value("className", "Juggernaut");
    outData.level = j.value("level", 1);
    outData.currentXP = j.value("currentXP", 0ULL);
    outData.health = j.value("health", 100.0f);
    outData.mana = j.value("mana", 50.0f);
    outData.power = j.value("power", 0.0f);

    if (j.contains("attributes")) {
        const auto& aj = j["attributes"];
        outData.attributes.strength = aj.value("strength", 10);
        outData.attributes.dexterity = aj.value("dexterity", 10);
        outData.attributes.intelligence = aj.value("intelligence", 10);
        outData.attributes.vitality = aj.value("vitality", 10);
        outData.attributes.wisdom = aj.value("wisdom", 10);
        outData.attributes.cybernetics = aj.value("cybernetics", 10);
    }

    outData.hunger = j.value("hunger", 100.0f);
    outData.thirst = j.value("thirst", 100.0f);
    outData.bodyTemp = j.value("bodyTemp", 37.0f);
    if (j.contains("settings")) {
        const auto& settings = j["settings"];
        outData.settings.masterVolume = settings.value("masterVolume", 1.0f);
        outData.settings.sfxVolume = settings.value("sfxVolume", 1.0f);
        outData.settings.musicVolume = settings.value("musicVolume", 1.0f);
        outData.settings.ambienceVolume = settings.value("ambienceVolume", 1.0f);
        outData.settings.fullscreen = settings.value("fullscreen", false);
        outData.settings.vsync = settings.value("vsync", true);
        if (settings.contains("movementKeys")) {
            outData.settings.movementKeys = settings["movementKeys"].get<std::array<int, 4>>();
        }
    }

    outData.inventoryItems.clear();
    if (j.contains("inventory")) {
        for (const auto& ij : j["inventory"]) {
            Item itm;
            itm.id = ij.value("id", "");
            itm.name = ij.value("name", "");
            itm.tier = ij.value("tier", 1);
            itm.quantity = ij.value("quantity", 1);
            itm.baseDamage = ij.value("baseDamage", 0.0f);
            itm.baseArmor = ij.value("baseArmor", 0.0f);
            outData.inventoryItems.push_back(itm);
        }
    }

    return true;
}

bool SaveManager::saveSlot(const std::string& directory, int slot, const SaveData& data) {
    if (slot < 1 || slot > 3) return false;
    std::filesystem::create_directories(directory);
    return saveToFile((std::filesystem::path(directory) /
                       ("save_slot_0" + std::to_string(slot) + ".sav")).string(), data);
}

bool SaveManager::loadSlot(const std::string& directory, int slot, SaveData& outData) {
    if (slot < 1 || slot > 3) return false;
    return loadFromFile((std::filesystem::path(directory) /
                         ("save_slot_0" + std::to_string(slot) + ".sav")).string(), outData);
}

std::vector<int> SaveManager::availableSlots(const std::string& directory, int maxSlots) {
    std::vector<int> slots;
    maxSlots = std::clamp(maxSlots, 0, 3);
    for (int slot = 1; slot <= maxSlots; ++slot) {
        const auto path = std::filesystem::path(directory) /
                          ("save_slot_0" + std::to_string(slot) + ".sav");
        if (std::filesystem::exists(path)) slots.push_back(slot);
    }
    return slots;
}
