#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include "gameplay/skills/SkillTree.hpp"
#include "gameplay/skills/SkillExecutor.hpp"
#include "gameplay/skills/SkillRegistry.hpp"

using Catch::Approx;

TEST_CASE("DAG Skill Tree and Prerequisite Allocation Rules", "[gameplay][skills]") {
    SkillTree tree;

    // Root node (no prereq)
    SkillNode root;
    root.id = "jug_root";
    root.name = "Iron Foundation";
    root.maxRanks = 3;
    root.requiredTier = 1;

    // Child node (requires root)
    SkillNode child;
    child.id = "jug_shield_wall";
    child.name = "Shield Wall Stance";
    child.maxRanks = 1;
    child.requiredTier = 1;
    child.prerequisites = {"jug_root"};

    // Tier 2 node (requires 3 points spent in tree)
    SkillNode tier2;
    tier2.id = "jug_seismic_slam";
    tier2.name = "Seismic Slam";
    tier2.maxRanks = 1;
    tier2.requiredTier = 2;
    tier2.requiredPointsInTree = 3;
    tier2.prerequisites = {"jug_shield_wall"};

    tree.addNode(root);
    tree.addNode(child);
    tree.addNode(tier2);

    SECTION("Cannot Unlock Child Before Prerequisite is Allocated") {
        REQUIRE(tree.canAllocate("jug_shield_wall") == false);
        REQUIRE(tree.allocate("jug_shield_wall") == false);

        // Allocate root rank 1
        REQUIRE(tree.allocate("jug_root") == true);
        REQUIRE(tree.getRank("jug_root") == 1);

        // Now child can be unlocked
        REQUIRE(tree.canAllocate("jug_shield_wall") == true);
        REQUIRE(tree.allocate("jug_shield_wall") == true);
        REQUIRE(tree.getRank("jug_shield_wall") == 1);
    }

    SECTION("Tier Requirements Enforce Point Thresholds") {
        tree.allocate("jug_root"); // 1 point
        tree.allocate("jug_shield_wall"); // 2 points total

        // Tier 2 requires 3 points in tree
        REQUIRE(tree.canAllocate("jug_seismic_slam") == false);

        // Allocate root rank 2 -> now 3 points total!
        tree.allocate("jug_root");
        REQUIRE(tree.getTotalPointsSpent() == 3);
        REQUIRE(tree.canAllocate("jug_seismic_slam") == true);
        REQUIRE(tree.allocate("jug_seismic_slam") == true);
    }

    SECTION("Respec System Refunds All Allocated Points") {
        tree.allocate("jug_root");
        tree.allocate("jug_root");
        tree.allocate("jug_shield_wall");

        int refunded = tree.respec();
        REQUIRE(refunded == 3);
        REQUIRE(tree.getTotalPointsSpent() == 0);
        REQUIRE(tree.getRank("jug_root") == 0);
        REQUIRE(tree.getRank("jug_shield_wall") == 0);
    }
}

TEST_CASE("4-Slot Hotbar and Active Skill Cast Execution Pipeline", "[gameplay][skills]") {
    SkillRegistry registry;

    SkillDefinition slam;
    slam.id = "skill_overhead_slam";
    slam.name = "Overhead Maul Slam";
    slam.resourceType = ResourceCostType::Stamina;
    slam.resourceCost = 20.0f;
    slam.baseCooldown = 4.0f;
    slam.baseDamage = 80.0f;

    registry.registerSkill(slam);

    SkillExecutor executor(registry);
    executor.assignHotbar(HotbarSlot::Q, "skill_overhead_slam");

    SECTION("Successful Cast Deducts Resource and Initiates Cooldown") {
        float playerStamina = 50.0f;
        float playerMana = 100.0f;
        float playerPower = 0.0f;

        CastResult result = executor.tryCast(HotbarSlot::Q, playerStamina, playerMana, playerPower);
        REQUIRE(result.success == true);
        REQUIRE(playerStamina == Approx(30.0f)); // 50 - 20
        REQUIRE(result.damageOutput == Approx(80.0f));

        // Immediate recast fails because on cooldown
        CastResult recast = executor.tryCast(HotbarSlot::Q, playerStamina, playerMana, playerPower);
        REQUIRE(recast.success == false);
        REQUIRE(recast.failReason == CastFailReason::OnCooldown);
    }

    SECTION("Fails When Insufficient Resource") {
        float lowStamina = 10.0f; // Needs 20
        float mana = 100.0f;
        float power = 0.0f;

        CastResult result = executor.tryCast(HotbarSlot::Q, lowStamina, mana, power);
        REQUIRE(result.success == false);
        REQUIRE(result.failReason == CastFailReason::InsufficientResource);
    }

    SECTION("Cooldown Recovers over Simulation Time") {
        float stamina = 100.0f;
        float mana = 100.0f;
        float power = 0.0f;

        executor.tryCast(HotbarSlot::Q, stamina, mana, power);

        // Advance 2 seconds (cooldown is 4s) -> still on cooldown
        executor.update(2.0f);
        REQUIRE(executor.isOnCooldown(HotbarSlot::Q) == true);

        // Advance another 2.1 seconds -> cooldown complete
        executor.update(2.1f);
        REQUIRE(executor.isOnCooldown(HotbarSlot::Q) == false);

        CastResult recast = executor.tryCast(HotbarSlot::Q, stamina, mana, power);
        REQUIRE(recast.success == true);
    }
}
