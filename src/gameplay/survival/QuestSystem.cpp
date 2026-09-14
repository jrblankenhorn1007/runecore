#include "gameplay/survival/QuestSystem.hpp"

void QuestSystem::registerQuest(const QuestDefinition& quest) {
    m_definitions[quest.id] = quest;
    m_states[quest.id] = QuestState::Unstarted;
}

bool QuestSystem::acceptQuest(const std::string& questId) {
    auto it = m_definitions.find(questId);
    if (it == m_definitions.end()) return false;
    if (m_states[questId] != QuestState::Unstarted) return false;

    m_states[questId] = QuestState::Active;
    m_activeObjectives[questId] = it->second.objectives;
    return true;
}

void QuestSystem::onObjectiveProgress(ObjectiveType type, const std::string& targetId, int count) {
    for (auto& [questId, objectives] : m_activeObjectives) {
        if (m_states[questId] != QuestState::Active) continue;

        bool allDone = true;
        for (auto& obj : objectives) {
            if (obj.type == type && (obj.targetId.empty() || obj.targetId == targetId)) {
                obj.currentCount += count;
            }
            if (!obj.isComplete()) {
                allDone = false;
            }
        }

        if (allDone) {
            m_states[questId] = QuestState::Completed;
        }
    }
}

QuestState QuestSystem::getQuestState(const std::string& questId) const {
    auto it = m_states.find(questId);
    if (it != m_states.end()) {
        return it->second;
    }
    return QuestState::Unstarted;
}

bool QuestSystem::isQuestCompleted(const std::string& questId) const {
    return getQuestState(questId) == QuestState::Completed;
}

bool QuestSystem::claimReward(const std::string& questId, Inventory& inventory, Progression& progression) {
    if (!isQuestCompleted(questId)) return false;

    auto it = m_definitions.find(questId);
    if (it == m_definitions.end()) return false;

    const auto& def = it->second;
    progression.addXP(def.xpReward);

    for (const auto& rItem : def.rewardItems) {
        Item item;
        item.id = rItem.itemId;
        item.name = rItem.itemId;
        item.category = ItemCategory::Material;
        item.stackable = true;
        item.quantity = rItem.quantity;
        inventory.addItem(item);
    }

    m_states[questId] = QuestState::Claimed;
    return true;
}
