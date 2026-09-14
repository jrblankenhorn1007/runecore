#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include "save/SaveManager.hpp"
#include <filesystem>
#include <fstream>

using Catch::Approx;

TEST_CASE("Save and Load Serialization of Game State", "[save][persistence]") {
    std::string testPath = "test_save_slot_01.sav";
    std::filesystem::remove(testPath);

    SaveData outData;
    outData.playerName = "Sovereign";
    outData.className = "Juggernaut";
    outData.level = 62;
    outData.currentXP = 125000;
    outData.health = 450.0f;
    outData.mana = 120.0f;
    outData.power = 95.0f;
    outData.attributes.strength = 35;
    outData.attributes.vitality = 25;
    outData.hunger = 85.0f;
    outData.thirst = 90.0f;

    // Add inventory item
    Item item;
    item.id = "item_titanium_greatsword";
    item.name = "Titanium Greatsword";
    item.tier = 4;
    item.quantity = 1;
    item.baseDamage = 110.0f;
    outData.inventoryItems.push_back(item);

    SECTION("Atomic Save to Disk and Successful Load") {
        bool saveSuccess = SaveManager::saveToFile(testPath, outData);
        REQUIRE(saveSuccess == true);
        REQUIRE(std::filesystem::exists(testPath) == true);

        SaveData inData;
        bool loadSuccess = SaveManager::loadFromFile(testPath, inData);
        REQUIRE(loadSuccess == true);

        REQUIRE(inData.playerName == "Sovereign");
        REQUIRE(inData.className == "Juggernaut");
        REQUIRE(inData.level == 62);
        REQUIRE(inData.currentXP == 125000);
        REQUIRE(inData.health == Approx(450.0f));
        REQUIRE(inData.attributes.strength == 35);
        REQUIRE(inData.inventoryItems.size() == 1);
        REQUIRE(inData.inventoryItems[0].name == "Titanium Greatsword");
    }

    SECTION("Checksum Validation Detects Corrupted File") {
        SaveManager::saveToFile(testPath, outData);

        // Corrupt file by appending arbitrary bytes
        std::ofstream file(testPath, std::ios::app);
        file << "CORRUPTED_TAMPERED_DATA_BYTES";
        file.close();

        SaveData corruptedData;
        bool loadSuccess = SaveManager::loadFromFile(testPath, corruptedData);
        REQUIRE(loadSuccess == false); // Detected checksum mismatch / format corruption
    }

    std::filesystem::remove(testPath);
}
