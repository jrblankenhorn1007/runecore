#include "gameplay/skills/SkillTree.hpp"

void SkillTree::addNode(const SkillNode& node) {
    m_nodes[node.id] = node;
}

int SkillTree::getTotalPointsSpent() const {
    int total = 0;
    for (const auto& [id, node] : m_nodes) {
        total += node.currentRank;
    }
    return total;
}

int SkillTree::getRank(const std::string& nodeId) const {
    auto it = m_nodes.find(nodeId);
    if (it != m_nodes.end()) {
        return it->second.currentRank;
    }
    return 0;
}

bool SkillTree::canAllocate(const std::string& nodeId) const {
    auto it = m_nodes.find(nodeId);
    if (it == m_nodes.end()) return false;

    const auto& node = it->second;
    if (node.currentRank >= node.maxRanks) return false;

    // Check points spent in tree
    if (getTotalPointsSpent() < node.requiredPointsInTree) {
        return false;
    }

    // Check prerequisites
    for (const auto& reqId : node.prerequisites) {
        if (getRank(reqId) < 1) {
            return false;
        }
    }

    return true;
}

bool SkillTree::allocate(const std::string& nodeId) {
    if (!canAllocate(nodeId)) return false;
    m_nodes[nodeId].currentRank++;
    return true;
}

int SkillTree::respec() {
    int refunded = getTotalPointsSpent();
    for (auto& [id, node] : m_nodes) {
        node.currentRank = 0;
    }
    return refunded;
}
