#include "save/SaveManager.hpp"
#include <nlohmann/json.hpp>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <algorithm>
#include <utility>

using json = nlohmann::json;

namespace {
json serializeItem(const Item& item) {
    json result;
    result["id"] = item.id;
    result["name"] = item.name;
    result["category"] = static_cast<int>(item.category);
    result["equipSlot"] = static_cast<int>(item.equipSlot);
    result["rarity"] = static_cast<int>(item.rarity);
    result["tier"] = item.tier;
    result["quality"] = item.quality;
    result["baseDamage"] = item.baseDamage;
    result["baseArmor"] = item.baseArmor;
    result["attackSpeed"] = item.attackSpeed;
    result["weight"] = item.weight;
    result["stackable"] = item.stackable;
    result["quantity"] = item.quantity;
    result["maxStack"] = item.maxStack;
    result["sockets"] = item.sockets;
    result["usedSockets"] = item.usedSockets;
    result["uniquePerk"] = item.uniquePerk;

    json affixes = json::array();
    for (const auto& affix : item.affixes) {
        affixes.push_back({
            {"name", affix.name},
            {"isPrefix", affix.isPrefix},
            {"tier", affix.tier},
            {"flatBonus", affix.flatBonus},
            {"percentBonus", affix.percentBonus},
            {"statTarget", affix.statTarget}
        });
    }
    result["affixes"] = std::move(affixes);
    return result;
}

Item deserializeItem(const json& value) {
    Item item;
    item.id = value.value("id", "");
    item.name = value.value("name", "");
    item.tier = value.value("tier", 1);
    item.quality = value.value("quality", 0.0f);
    item.baseDamage = value.value("baseDamage", 0.0f);
    item.baseArmor = value.value("baseArmor", 0.0f);
    const ItemCategory defaultCategory = item.baseArmor > 0.0f
        ? ItemCategory::Armor
        : (item.baseDamage > 0.0f ? ItemCategory::Weapon : ItemCategory::Material);
    item.category = static_cast<ItemCategory>(
        value.value("category", static_cast<int>(defaultCategory)));
    const EquipSlot defaultEquipSlot = item.category == ItemCategory::Weapon
        ? EquipSlot::MainHand
        : EquipSlot::None;
    item.equipSlot = static_cast<EquipSlot>(
        value.value("equipSlot", static_cast<int>(defaultEquipSlot)));
    item.rarity = static_cast<ItemRarity>(
        value.value("rarity", static_cast<int>(ItemRarity::Common)));
    item.attackSpeed = value.value("attackSpeed", 1.0f);
    item.weight = value.value("weight", 0.5f);
    item.stackable = value.value("stackable", false);
    item.quantity = value.value("quantity", 1);
    item.maxStack = value.value("maxStack", 99);
    item.sockets = value.value("sockets", 0);
    item.usedSockets = value.value("usedSockets", 0);
    item.uniquePerk = value.value("uniquePerk", "");

    if (value.contains("affixes") && value["affixes"].is_array()) {
        for (const auto& affixJson : value["affixes"]) {
            Affix affix;
            affix.name = affixJson.value("name", "");
            affix.isPrefix = affixJson.value("isPrefix", true);
            affix.tier = affixJson.value("tier", 1);
            affix.flatBonus = affixJson.value("flatBonus", 0.0f);
            affix.percentBonus = affixJson.value("percentBonus", 0.0f);
            affix.statTarget = affixJson.value("statTarget", "");
            item.affixes.push_back(std::move(affix));
        }
    }
    return item;
}
}

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
    j["visorColor"] = {
        static_cast<int>(data.visorColor.r),
        static_cast<int>(data.visorColor.g),
        static_cast<int>(data.visorColor.b),
        static_cast<int>(data.visorColor.a)
    };
    j["level"] = data.level;
    j["currentXP"] = data.currentXP;
    j["attributePoints"] = data.attributePoints;
    j["skillPoints"] = data.skillPoints;
    j["health"] = data.health;
    j["mana"] = data.mana;
    j["power"] = data.power;
    j["playerX"] = data.playerX;
    j["playerY"] = data.playerY;
    j["inDungeon"] = data.inDungeon;
    j["onboardingComplete"] = data.onboardingComplete;
    j["campaignComplete"] = data.campaignComplete;
    j["endingAcknowledged"] = data.endingAcknowledged;

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
        itemsJson.push_back(serializeItem(item));
    }
    j["inventory"] = itemsJson;

    json equippedJson = json::array();
    for (const auto& equipped : data.equippedItems) {
        equippedJson.push_back({
            {"slot", static_cast<int>(equipped.slot)},
            {"item", serializeItem(equipped.item)}
        });
    }
    j["equippedItems"] = equippedJson;

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
    const auto visorColor = j.value(
        "visorColor", std::array<int, 4>{65, 115, 220, 255});
    outData.visorColor = Color{
        static_cast<unsigned char>(std::clamp(visorColor[0], 0, 255)),
        static_cast<unsigned char>(std::clamp(visorColor[1], 0, 255)),
        static_cast<unsigned char>(std::clamp(visorColor[2], 0, 255)),
        static_cast<unsigned char>(std::clamp(visorColor[3], 0, 255))
    };
    outData.level = j.value("level", 1);
    outData.currentXP = j.value("currentXP", 0ULL);
    outData.attributePoints = j.value("attributePoints", 0);
    outData.skillPoints = j.value("skillPoints", 0);
    outData.health = j.value("health", 100.0f);
    outData.mana = j.value("mana", 50.0f);
    outData.power = j.value("power", 0.0f);
    outData.playerX = j.value("playerX", 100.0f);
    outData.playerY = j.value("playerY", 160.0f);
    outData.inDungeon = j.value("inDungeon", false);
    outData.onboardingComplete = j.value("onboardingComplete", false);
    outData.campaignComplete = j.value("campaignComplete", false);
    outData.endingAcknowledged = j.value("endingAcknowledged", false);

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
            outData.inventoryItems.push_back(deserializeItem(ij));
        }
    }

    outData.equippedItems.clear();
    if (j.contains("equippedItems") && j["equippedItems"].is_array()) {
        for (const auto& equippedJson : j["equippedItems"]) {
            SaveData::EquippedItem equipped;
            equipped.slot = static_cast<EquipSlot>(
                equippedJson.value("slot", static_cast<int>(EquipSlot::None)));
            if (equippedJson.contains("item")) {
                equipped.item = deserializeItem(equippedJson["item"]);
            }
            outData.equippedItems.push_back(std::move(equipped));
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
