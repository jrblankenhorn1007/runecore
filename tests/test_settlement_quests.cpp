#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include "gameplay/survival/SettlementSystem.hpp"
#include "gameplay/survival/QuestSystem.hpp"
#include "gameplay/items/Inventory.hpp"
#include "gameplay/stats/Progression.hpp"
#include "procgen/Tilemap.hpp"

using Catch::Approx;

TEST_CASE("Settlement Room Enclosure and NPC Housing Suitability", "[settlement][housing]") {
    Tilemap tilemap(16.0f);
    SettlementSystem settlement;

    // Construct a 6x5 enclosed room from X=10..15, Y=10..14
    // Top & Bottom walls
    for (int x = 10; x <= 15; ++x) {
        tilemap.setBlock(x, 10, BlockLayer::Foreground, 3); // Wood wall roof
        tilemap.setBlock(x, 14, BlockLayer::Foreground, 1); // Stone floor
    }
    // Left & Right walls (with door at X=15, Y=13)
    for (int y = 11; y <= 13; ++y) {
        tilemap.setBlock(10, y, BlockLayer::Foreground, 3); // Left wall
        if (y == 13) {
            tilemap.setBlock(15, y, BlockLayer::Foreground, 6); // Wooden Door
        } else {
            tilemap.setBlock(15, y, BlockLayer::Foreground, 3); // Right wall
        }
    }

    RoomBounds room{10, 10, 6, 5};

    SECTION("Incomplete Room Without Light and Furniture is Not Suitable") {
        HousingCheckResult res = settlement.checkSuitability(tilemap, room);
        REQUIRE(res.isEnclosed == true);
        REQUIRE(res.hasDoor == true);
        REQUIRE(res.hasLightSource == false);
        REQUIRE(res.hasFurniture == false);
        REQUIRE(res.isSuitable == false);
    }

    SECTION("Adding Light Source and Furniture Makes Room Suitable for NPC Move-In") {
        tilemap.setBlock(12, 11, BlockLayer::Foreground, 8); // Wall Torch (Light)
        tilemap.setBlock(11, 13, BlockLayer::Foreground, 9); // Bed (Furniture)

        HousingCheckResult res = settlement.checkSuitability(tilemap, room);
        REQUIRE(res.isSuitable == true);

        // Recruit Blacksmith NPC into the room
        bool assigned = settlement.assignNPC(NPCType::Blacksmith, room);
        REQUIRE(assigned == true);
        REQUIRE(settlement.isNPCResident(NPCType::Blacksmith) == true);
    }
}

TEST_CASE("Quest System Objective Tracking and Reward Delivery", "[settlement][quests]") {
    QuestSystem quests;
    Inventory inv(40);
    Progression progression;

    QuestDefinition ironMinerQuest;
    ironMinerQuest.id = "quest_iron_miner";
    ironMinerQuest.title = "Iron for the Forge";
    ironMinerQuest.xpReward = 200;
    ironMinerQuest.rewardItems = {{"mat_iron_ore", 5}};
    ironMinerQuest.objectives.push_back(QuestObjective{ObjectiveType::MineMaterial, "mat_iron_ore", 3, 0});

    quests.registerQuest(ironMinerQuest);

    SECTION("Accepting and Progressing Quest Objectives") {
        REQUIRE(quests.acceptQuest("quest_iron_miner") == true);
        REQUIRE(quests.getQuestState("quest_iron_miner") == QuestState::Active);

        // Mine 2 iron ore
        quests.onObjectiveProgress(ObjectiveType::MineMaterial, "mat_iron_ore", 2);
        REQUIRE(quests.isQuestCompleted("quest_iron_miner") == false);

        // Mine 1 more iron ore (total 3/3)
        quests.onObjectiveProgress(ObjectiveType::MineMaterial, "mat_iron_ore", 1);
        REQUIRE(quests.isQuestCompleted("quest_iron_miner") == true);

        // Claim Rewards (200 XP rewards: 100 XP levels up to Level 2 with 100 XP remaining)
        bool claimed = quests.claimReward("quest_iron_miner", inv, progression);
        REQUIRE(claimed == true);
        REQUIRE(quests.getQuestState("quest_iron_miner") == QuestState::Claimed);
        REQUIRE(progression.getLevel() == 2);
        REQUIRE(progression.getCurrentXP() == 100);
        REQUIRE(inv.getItemCount("mat_iron_ore") == 5);
    }
}
