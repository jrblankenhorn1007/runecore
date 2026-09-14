#pragma once
#include "core/GameSimulation.hpp"
#include "input/InputManager.hpp"
#include <string>

struct BotReport {
    bool passedMovement{false};
    bool passedJumpAndDoubleJump{false};
    bool passedWallSlideAndJump{false};
    bool passedMining{false};
    bool passedLootVacuum{false};
    bool passedCrafting{false};
    bool passedRangedCombat{false};
    bool passedMeleeCombat{false};
    bool passedSkillCasting{false};
    bool passedDungeonEntry{false};
    bool passedDungeonBossDefeat{false};
    bool passedLevelUp{false};

    bool allTestsPassed() const {
        return passedMovement && passedJumpAndDoubleJump && passedWallSlideAndJump &&
               passedMining && passedLootVacuum && passedCrafting &&
               passedRangedCombat && passedMeleeCombat && passedSkillCasting &&
               passedDungeonEntry && passedDungeonBossDefeat && passedLevelUp;
    }

    void printSummary() const;
};

class BotTester {
public:
    BotTester();

    void reset();
    RawInputState update(GameSimulation& sim, float dt);

    bool isFinished() const { return m_finished; }
    const BotReport& getReport() const { return m_report; }
    std::string getCurrentPhaseName() const;

private:
    int m_tick{0};
    int m_phase{0};
    bool m_finished{false};
    BotReport m_report;

    int m_initialLevel{1};
    int m_initialLootCount{0};
    float m_jumpPeakY{999.0f};
};
