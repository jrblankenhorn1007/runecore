#include <catch2/catch_test_macros.hpp>
#include "gameplay/survival/QuestSystem.hpp"
#include "gameplay/items/Inventory.hpp"
#include "gameplay/stats/Progression.hpp"

TEST_CASE("QuestSystem Registration, Progress, and Claiming", "[gameplay][survival]") {
    QuestSystem qs;
    Inventory inv;
    Progression prog;

    QuestDefinition q;
    q.id = "q_boss";
    q.title = "Slay the Titan";
    q.xpReward = 500;
    q.rewardItems = {{"item_gem", 2}};
    q.objectives = {
        QuestObjective{ObjectiveType::SlayMonster, "titan", 1, 0}
    };

    qs.registerQuest(q);

    REQUIRE(qs.getQuestState("q_boss") == QuestState::Unstarted);
    REQUIRE(qs.getQuestState("unknown") == QuestState::Unstarted);
    REQUIRE(qs.acceptQuest("unknown") == false);

    REQUIRE(qs.acceptQuest("q_boss") == true);
    REQUIRE(qs.acceptQuest("q_boss") == false); // Already active
    REQUIRE(qs.getQuestState("q_boss") == QuestState::Active);
    REQUIRE(qs.isQuestCompleted("q_boss") == false);

    // Progress wrong target
    qs.onObjectiveProgress(ObjectiveType::SlayMonster, "goblin", 1);
    REQUIRE(qs.isQuestCompleted("q_boss") == false);

    // Progress correct target
    qs.onObjectiveProgress(ObjectiveType::SlayMonster, "titan", 1);
    REQUIRE(qs.isQuestCompleted("q_boss") == true);

    // Claim
    REQUIRE(qs.claimReward("q_boss", inv, prog) == true);
    REQUIRE(qs.getQuestState("q_boss") == QuestState::Claimed);
    REQUIRE(qs.claimReward("q_boss", inv, prog) == false); // Already claimed
    REQUIRE(qs.claimReward("unknown", inv, prog) == false);

    REQUIRE(inv.getItemCount("item_gem") == 2);
}
