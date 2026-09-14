#include <catch2/catch_test_macros.hpp>
#include "gameplay/skills/SkillTree.hpp"

TEST_CASE("SkillTree Node Hierarchies, Allocation, and Respec", "[gameplay][skills]") {
    SkillTree tree;

    SkillNode n1;
    n1.id = "node_1";
    n1.name = "Root";
    n1.maxRanks = 3;

    SkillNode n2;
    n2.id = "node_2";
    n2.name = "Child";
    n2.prerequisites = {"node_1"};
    n2.requiredPointsInTree = 2;

    tree.addNode(n1);
    tree.addNode(n2);

    REQUIRE(tree.getNodes().size() == 2);
    REQUIRE(tree.getRank("unknown") == 0);
    REQUIRE(tree.canAllocate("unknown") == false);

    // Cannot allocate child before prereq
    REQUIRE(tree.canAllocate("node_2") == false);

    // Allocate root rank 1
    REQUIRE(tree.allocate("node_1") == true);
    REQUIRE(tree.getRank("node_1") == 1);
    REQUIRE(tree.getTotalPointsSpent() == 1);

    // Still cannot allocate node_2 because requiredPointsInTree is 2
    REQUIRE(tree.canAllocate("node_2") == false);

    // Allocate root rank 2
    REQUIRE(tree.allocate("node_1") == true);
    REQUIRE(tree.getTotalPointsSpent() == 2);
    REQUIRE(tree.canAllocate("node_2") == true);
    REQUIRE(tree.allocate("node_2") == true);
    REQUIRE(tree.allocate("node_2") == false); // Max rank reached

    // Respec
    REQUIRE(tree.respec() == 3);
    REQUIRE(tree.getTotalPointsSpent() == 0);
}
