#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include "save/SaveManager.hpp"
#include <fstream>
#include <cstdio>

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
        REQUIRE(loaded.inventoryItems.size() == 1);
        REQUIRE(loaded.inventoryItems[0].name == "Iron Sword");
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

    std::remove(testPath.c_str());
}
