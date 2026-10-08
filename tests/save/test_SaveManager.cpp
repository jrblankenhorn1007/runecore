#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include "save/SaveManager.hpp"
#include <fstream>
#include <cstdio>
#include <iterator>

using Catch::Approx;

TEST_CASE("SaveManager Serialization, Atomic Writes, and Checksums", "[save][persistence]") {
    std::string testPath = "test_slot_save.sav";
    std::remove(testPath.c_str());

    SaveData data;
    data.playerName = "Aegis";
    data.className = "Juggernaut";
    data.level = 25;
    data.currentXP = 15000;
    data.health = 400.0f;
    data.mana = 100.0f;
    data.power = 80.0f;
    data.attributes.strength = 30;
    data.onboardingComplete = true;

    Item sword;
    sword.id = "sword_iron";
    sword.name = "Iron Sword";
    sword.tier = 2;
    sword.quantity = 1;
    data.inventoryItems.push_back(sword);

    SECTION("Successful Save and Load Roundtrip") {
        REQUIRE(SaveManager::saveToFile(testPath, data) == true);

        SaveData loaded;
        REQUIRE(SaveManager::loadFromFile(testPath, loaded) == true);
        REQUIRE(loaded.playerName == "Aegis");
        REQUIRE(loaded.level == 25);
        REQUIRE(loaded.health == Approx(400.0f));
        REQUIRE(loaded.attributes.strength == 30);
        REQUIRE(loaded.onboardingComplete);
        REQUIRE(loaded.inventoryItems.size() == 1);
        REQUIRE(loaded.inventoryItems[0].name == "Iron Sword");
    }

    SECTION("Legacy saves default to unfinished onboarding") {
        const std::string legacyPath = "test_legacy_save.sav";
        const std::string payload =
            R"({"playerName":"Legacy","className":"Juggernaut"})";
        std::ofstream file(legacyPath);
        file << "{\n  \"version\": 1,\n  \"checksum\": "
             << SaveManager::computeChecksum(payload)
             << ",\n  \"payload\": "
             << "\"{\\\"playerName\\\":\\\"Legacy\\\",\\\"className\\\":\\\"Juggernaut\\\"}\"\n}";
        file.close();

        SaveData loaded;
        REQUIRE(SaveManager::loadFromFile(legacyPath, loaded));
        REQUIRE_FALSE(loaded.onboardingComplete);
        REQUIRE_FALSE(loaded.campaignComplete);
        REQUIRE_FALSE(loaded.endingAcknowledged);
        std::remove(legacyPath.c_str());
    }

    SECTION("Nonexistent File Fails") {
        SaveData out;
        REQUIRE(SaveManager::loadFromFile("does_not_exist_99.sav", out) == false);
    }

    SECTION("Malformed JSON Fails") {
        std::ofstream file(testPath);
        file << "{ malformed: json [";
        file.close();

        SaveData out;
        REQUIRE(SaveManager::loadFromFile(testPath, out) == false);
    }

    SECTION("Missing Checksum Root Key Fails") {
        std::ofstream file(testPath);
        file << "{ \"version\": 1, \"payload\": \"{}\" }";
        file.close();

        SaveData out;
        REQUIRE(SaveManager::loadFromFile(testPath, out) == false);
    }

    SECTION("Checksum Mismatch Detection") {
        SaveManager::saveToFile(testPath, data);

        // Valid JSON root with mismatched checksum
        std::string rawJson = "{\n  \"version\": 1,\n  \"checksum\": 9999999,\n  \"payload\": \"{\\\"playerName\\\":\\\"Tampered\\\"}\"\n}";
        std::ofstream file(testPath);
        file << rawJson;
        file.close();

        SaveData out;
        REQUIRE(SaveManager::loadFromFile(testPath, out) == false);
    }

    SECTION("Payload Is Not Valid JSON Even Though Checksum Matches") {
        std::string badPayload = "not_json_payload";
        uint32_t csum = SaveManager::computeChecksum(badPayload);
        std::ofstream file(testPath);
        file << "{\n  \"version\": 1,\n  \"checksum\": " << csum << ",\n  \"payload\": \"" << badPayload << "\"\n}";
        file.close();

        SaveData out;
        REQUIRE(SaveManager::loadFromFile(testPath, out) == false);
    }

    SECTION("Three Save Slots Are Addressable") {
        const std::string directory = "test_save_slots";
        REQUIRE(SaveManager::saveSlot(directory, 2, data));
        SaveData loaded;
        REQUIRE(SaveManager::loadSlot(directory, 2, loaded));
        REQUIRE(loaded.playerName == "Aegis");
        REQUIRE(SaveManager::availableSlots(directory) == std::vector<int>{2});
        std::remove((directory + "/save_slot_02.sav").c_str());
        std::remove(directory.c_str());
    }

    std::remove(testPath.c_str());
}

TEST_CASE("SaveManager preserves character appearance and complete item data", "[save][persistence]") {
    const std::string path = "test_character_metadata.sav";
    std::remove(path.c_str());

    SaveData data;
    data.playerName = "Astra";
    data.className = "Medic";
    data.visorColor = Color{65, 225, 220, 255};
    data.level = 12;
    data.currentXP = 33;
    data.attributePoints = 5;
    data.skillPoints = 2;
    data.playerX = 812.5f;
    data.playerY = 144.0f;
    data.inDungeon = true;

    Item blade;
    blade.id = "item_arc_blade";
    blade.name = "Arc Blade";
    blade.category = ItemCategory::Weapon;
    blade.equipSlot = EquipSlot::MainHand;
    blade.rarity = ItemRarity::Rare;
    blade.quality = 0.15f;
    blade.baseDamage = 82.0f;
    blade.attackSpeed = 1.25f;
    blade.weight = 4.0f;
    blade.sockets = 2;
    blade.usedSockets = 1;
    blade.affixes.push_back(Affix{"Charged", true, 2, 4.0f, 0.1f, "Damage"});
    blade.uniquePerk = "chain_lightning";
    data.equippedItems.push_back(SaveData::EquippedItem{EquipSlot::MainHand, blade});

    REQUIRE(SaveManager::saveToFile(path, data));
    SaveData loaded;
    REQUIRE(SaveManager::loadFromFile(path, loaded));
    REQUIRE(loaded.playerName == "Astra");
    REQUIRE(loaded.className == "Medic");
    REQUIRE(loaded.visorColor.r == 65);
    REQUIRE(loaded.visorColor.g == 225);
    REQUIRE(loaded.level == 12);
    REQUIRE(loaded.currentXP == 33);
    REQUIRE(loaded.attributePoints == 5);
    REQUIRE(loaded.skillPoints == 2);
    REQUIRE(loaded.playerX == Approx(812.5f));
    REQUIRE(loaded.playerY == Approx(144.0f));
    REQUIRE(loaded.inDungeon);
    REQUIRE(loaded.equippedItems.size() == 1);
    REQUIRE(loaded.equippedItems[0].slot == EquipSlot::MainHand);
    REQUIRE(loaded.equippedItems[0].item.id == "item_arc_blade");
    REQUIRE(loaded.equippedItems[0].item.category == ItemCategory::Weapon);
    REQUIRE(loaded.equippedItems[0].item.rarity == ItemRarity::Rare);
    REQUIRE(loaded.equippedItems[0].item.affixes.size() == 1);
    REQUIRE(loaded.equippedItems[0].item.affixes[0].name == "Charged");
    REQUIRE(loaded.equippedItems[0].item.uniquePerk == "chain_lightning");

    std::remove(path.c_str());
}

TEST_CASE("SaveManager writes campaign-ending state for safe resume", "[save][campaign]") {
    const std::string path = "test_campaign_ending.sav";
    std::remove(path.c_str());

    SaveData data;
    data.campaignComplete = true;
    REQUIRE(SaveManager::saveToFile(path, data));

    std::ifstream file(path);
    const std::string serialized(
        (std::istreambuf_iterator<char>(file)),
        std::istreambuf_iterator<char>());
    REQUIRE(serialized.find("campaignComplete") != std::string::npos);
    REQUIRE(serialized.find("endingAcknowledged") != std::string::npos);

    SaveData loaded;
    REQUIRE(SaveManager::loadFromFile(path, loaded));
    REQUIRE(loaded.campaignComplete);
    REQUIRE_FALSE(loaded.endingAcknowledged);

    data.endingAcknowledged = true;
    REQUIRE(SaveManager::saveToFile(path, data));
    REQUIRE(SaveManager::loadFromFile(path, loaded));
    REQUIRE(loaded.campaignComplete);
    REQUIRE(loaded.endingAcknowledged);

    std::remove(path.c_str());
}
