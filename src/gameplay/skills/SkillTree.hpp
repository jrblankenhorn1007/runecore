#pragma once
#include <string>
#include <vector>
#include <unordered_map>

struct SkillNode {
    std::string id;
    std::string name;
    int maxRanks{1};
    int currentRank{0};
    int requiredTier{1};
    int requiredPointsInTree{0};
    std::vector<std::string> prerequisites;
};

class SkillTree {
public:
    void addNode(const SkillNode& node);
    bool canAllocate(const std::string& nodeId) const;
    bool allocate(const std::string& nodeId);
    int getRank(const std::string& nodeId) const;
    int getTotalPointsSpent() const;
    int respec();

    const std::unordered_map<std::string, SkillNode>& getNodes() const { return m_nodes; }

private:
    std::unordered_map<std::string, SkillNode> m_nodes;
};
