#include "procgen/DungeonGenerator.hpp"
#include <algorithm>

DungeonGenerator::DungeonGenerator(Random& rng) : m_rng(rng) {}

bool DungeonLayout::hasPath(int startIdx, int endIdx) const {
    if (startIdx < 0 || startIdx >= static_cast<int>(rooms.size())) return false;
    if (endIdx < 0 || endIdx >= static_cast<int>(rooms.size())) return false;

    // BFS flood fill on grid from center of startRoom to center of bossRoom
    int startX = static_cast<int>(rooms[startIdx].center().x);
    int startY = static_cast<int>(rooms[startIdx].center().y);
    int endX = static_cast<int>(rooms[endIdx].center().x);
    int endY = static_cast<int>(rooms[endIdx].center().y);

    std::queue<std::pair<int, int>> q;
    std::vector<std::vector<bool>> visited(height, std::vector<bool>(width, false));

    q.push({startX, startY});
    visited[startY][startX] = true;

    int dx[4] = {1, -1, 0, 0};
    int dy[4] = {0, 0, 1, -1};

    while (!q.empty()) {
        auto [cx, cy] = q.front();
        q.pop();

        if (cx == endX && cy == endY) {
            return true;
        }

        for (int i = 0; i < 4; ++i) {
            int nx = cx + dx[i];
            int ny = cy + dy[i];

            if (nx >= 0 && nx < width && ny >= 0 && ny < height) {
                if (!visited[ny][nx] && grid[ny][nx] == 0) { // Air / walkable corridor
                    visited[ny][nx] = true;
                    q.push({nx, ny});
                }
            }
        }
    }

    return false;
}

DungeonLayout DungeonGenerator::generate(const DungeonConfig& config) {
    DungeonLayout layout;
    layout.width = config.width;
    layout.height = config.height;
    // Fill completely with solid wall (1)
    layout.grid.resize(config.height, std::vector<int>(config.width, 1));

    BSPNode* root = new BSPNode{1, 1, config.width - 2, config.height - 2, nullptr, nullptr, -1};
    splitNode(root, 0, config.maxDepth, config, layout.rooms);

    // Carve room rectangles into grid (0 = air)
    for (size_t i = 0; i < layout.rooms.size(); ++i) {
        const auto& r = layout.rooms[i];
        for (int y = r.y; y < r.y + r.height; ++y) {
            for (int x = r.x; x < r.x + r.width; ++x) {
                if (x >= 0 && x < config.width && y >= 0 && y < config.height) {
                    layout.grid[y][x] = 0;
                }
            }
        }
    }

    // Connect sequential rooms with L-shaped corridors
    for (size_t i = 0; i + 1 < layout.rooms.size(); ++i) {
        connectRooms(layout, layout.rooms[i], layout.rooms[i + 1]);
    }

    // Assign start room and boss room (farthest apart)
    if (!layout.rooms.empty()) {
        layout.startRoomIndex = 0;
        layout.rooms[0].isStartRoom = true;

        float maxDist = -1.0f;
        int bestBoss = 0;
        Vec2 startCenter = layout.rooms[0].center();

        for (size_t i = 1; i < layout.rooms.size(); ++i) {
            float dist = startCenter.distanceTo(layout.rooms[i].center());
            if (dist > maxDist) {
                maxDist = dist;
                bestBoss = static_cast<int>(i);
            }
        }

        layout.bossRoomIndex = bestBoss;
        layout.rooms[bestBoss].isBossRoom = true;
    }

    delete root;
    return layout;
}

void DungeonGenerator::splitNode(
    BSPNode* node,
    int depth,
    int maxDepth,
    const DungeonConfig& config,
    std::vector<DungeonRoom>& outRooms
) {
    if (depth >= maxDepth || (node->width < config.minRoomSize * 2 && node->height < config.minRoomSize * 2)) {
        // Create room inside leaf node
        int rw = m_rng.rangeInt(config.minRoomSize, std::min(config.maxRoomSize, node->width - 2));
        int rh = m_rng.rangeInt(config.minRoomSize, std::min(config.maxRoomSize, node->height - 2));

        rw = std::max(rw, config.minRoomSize);
        rh = std::max(rh, config.minRoomSize);

        int rx = node->x + m_rng.rangeInt(1, std::max(1, node->width - rw - 1));
        int ry = node->y + m_rng.rangeInt(1, std::max(1, node->height - rh - 1));

        DungeonRoom room{rx, ry, rw, rh, false, false};
        node->roomIndex = static_cast<int>(outRooms.size());
        outRooms.push_back(room);
        return;
    }

    // Decide split direction
    bool splitH = (node->width > node->height);
    if (node->width >= config.minRoomSize * 2 && node->height >= config.minRoomSize * 2) {
        splitH = m_rng.chance(0.5f);
    } else if (node->width >= config.minRoomSize * 2) {
        splitH = true;
    } else {
        splitH = false;
    }

    if (splitH) {
        int split = m_rng.rangeInt(config.minRoomSize, node->width - config.minRoomSize);
        node->left = new BSPNode{node->x, node->y, split, node->height, nullptr, nullptr, -1};
        node->right = new BSPNode{node->x + split, node->y, node->width - split, node->height, nullptr, nullptr, -1};
    } else {
        int split = m_rng.rangeInt(config.minRoomSize, node->height - config.minRoomSize);
        node->left = new BSPNode{node->x, node->y, node->width, split, nullptr, nullptr, -1};
        node->right = new BSPNode{node->x, node->y + split, node->width, node->height - split, nullptr, nullptr, -1};
    }

    splitNode(node->left, depth + 1, maxDepth, config, outRooms);
    splitNode(node->right, depth + 1, maxDepth, config, outRooms);
}

void DungeonGenerator::connectRooms(DungeonLayout& layout, const DungeonRoom& r1, const DungeonRoom& r2) {
    int x1 = static_cast<int>(r1.center().x);
    int y1 = static_cast<int>(r1.center().y);
    int x2 = static_cast<int>(r2.center().x);
    int y2 = static_cast<int>(r2.center().y);

    // Carve horizontal corridor
    int startX = std::min(x1, x2);
    int endX = std::max(x1, x2);
    for (int x = startX; x <= endX; ++x) {
        if (x >= 0 && x < layout.width && y1 >= 0 && y1 < layout.height) {
            layout.grid[y1][x] = 0;
            // 2-tile wide corridor
            if (y1 + 1 < layout.height) layout.grid[y1 + 1][x] = 0;
        }
    }

    // Carve vertical corridor
    int startY = std::min(y1, y2);
    int endY = std::max(y1, y2);
    for (int y = startY; y <= endY; ++y) {
        if (x2 >= 0 && x2 < layout.width && y >= 0 && y < layout.height) {
            layout.grid[y][x2] = 0;
            if (x2 + 1 < layout.width) layout.grid[y][x2 + 1] = 0;
        }
    }
}
