#pragma once
#include "core/Math.hpp"
#include "core/Random.hpp"
#include <vector>
#include <queue>
#include <unordered_set>

struct DungeonRoom {
    int x{0};
    int y{0};
    int width{0};
    int height{0};
    bool isBossRoom{false};
    bool isStartRoom{false};

    Vec2 center() const {
        return {x + width * 0.5f, y + height * 0.5f};
    }
};

struct DungeonConfig {
    int width{60};
    int height{40};
    int minRoomSize{6};
    int maxRoomSize{12};
    int maxDepth{4};
};

struct DungeonLayout {
    int width{0};
    int height{0};
    std::vector<DungeonRoom> rooms;
    std::vector<std::vector<int>> grid; // 0 = air (carved), 1 = solid stone wall
    int startRoomIndex{-1};
    int bossRoomIndex{-1};

    bool hasPath(int startIdx, int endIdx) const;
};

class DungeonGenerator {
public:
    explicit DungeonGenerator(Random& rng);

    DungeonLayout generate(const DungeonConfig& config);

private:
    struct BSPNode {
        int x{0};
        int y{0};
        int width{0};
        int height{0};
        BSPNode* left{nullptr};
        BSPNode* right{nullptr};
        int roomIndex{-1};

        ~BSPNode() {
            delete left;
            delete right;
        }
    };

    void splitNode(BSPNode* node, int depth, int maxDepth, const DungeonConfig& config, std::vector<DungeonRoom>& outRooms);
    void connectRooms(DungeonLayout& layout, const DungeonRoom& r1, const DungeonRoom& r2);

    Random& m_rng;
};
