#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include "gameplay/items/Inventory.hpp"
#include "gameplay/stats/Progression.hpp"

enum class QuestState {
    Unstarted,
    Active,
    Completed,
    Claimed
};

enum class ObjectiveType {
    SlayMonster,
    MineMaterial,
    CraftItem,
    ReachLevel
};

struct QuestObjective {
    ObjectiveType type{ObjectiveType::SlayMonster};
    std::string targetId;
    int requiredCount{1};
    int currentCount{0};

    bool isComplete() const {
        return currentCount >= requiredCount;
    }
};

struct QuestRewardItem {
    std::string itemId;
    int quantity{1};
};

struct QuestDefinition {
    std::string id;
    std::string title;
    std::string description;
    uint64_t xpReward{100};
    std::vector<QuestRewardItem> rewardItems;
    std::vector<QuestObjective> objectives;
};

class QuestSystem {
public:
    void registerQuest(const QuestDefinition& quest);
    bool acceptQuest(const std::string& questId);
    void onObjectiveProgress(ObjectiveType type, const std::string& targetId, int count = 1);

    QuestState getQuestState(const std::string& questId) const;
    bool isQuestCompleted(const std::string& questId) const;
    bool claimReward(const std::string& questId, Inventory& inventory, Progression& progression);

private:
    std::unordered_map<std::string, QuestDefinition> m_definitions;
    std::unordered_map<std::string, QuestState> m_states;
    std::unordered_map<std::string, std::vector<QuestObjective>> m_activeObjectives;
};
