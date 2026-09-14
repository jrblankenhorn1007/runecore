#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include "gameplay/skills/SkillExecutor.hpp"
#include "gameplay/skills/SkillRegistry.hpp"

using Catch::Approx;

TEST_CASE("SkillExecutor Multi-Resource Casting and Cooldowns", "[gameplay][skills]") {
    SkillRegistry reg;

    SkillDefinition s1{"s_stam", "Stamina Strike", "", ResourceCostType::Stamina, 20.0f, 2.0f, 50.0f};
    SkillDefinition s2{"s_mana", "Mana Burst", "", ResourceCostType::Mana, 30.0f, 3.0f, 80.0f};
    SkillDefinition s3{"s_pwr", "Power Laser", "", ResourceCostType::Power, 15.0f, 4.0f, 100.0f};

    reg.registerSkill(s1);
    reg.registerSkill(s2);
    reg.registerSkill(s3);

    SkillExecutor exec(reg);

    SECTION("Unassigned Slot Cooldown Queries") {
        REQUIRE(exec.isOnCooldown(HotbarSlot::F) == false);
        REQUIRE(exec.getCooldownRemaining(HotbarSlot::F) == Approx(0.0f));
    }

    exec.assignHotbar(HotbarSlot::Q, "s_stam");
    exec.assignHotbar(HotbarSlot::E, "s_mana");
    exec.assignHotbar(HotbarSlot::R, "s_pwr");

    float sta = 50.0f;
    float mana = 50.0f;
    float pwr = 50.0f;

    SECTION("Empty Slot and Unregistered Skill Rejection") {
        CastResult rEmpty = exec.tryCast(HotbarSlot::F, sta, mana, pwr);
        REQUIRE(rEmpty.success == false);
        REQUIRE(rEmpty.failReason == CastFailReason::EmptySlot);

        exec.assignHotbar(HotbarSlot::F, "nonexistent");
        CastResult rNotFound = exec.tryCast(HotbarSlot::F, sta, mana, pwr);
        REQUIRE(rNotFound.success == false);
        REQUIRE(rNotFound.failReason == CastFailReason::SkillNotFound);
    }

    SECTION("Resource Deduction by Type") {
        // Stamina
        REQUIRE(exec.tryCast(HotbarSlot::Q, sta, mana, pwr).success == true);
        REQUIRE(sta == Approx(30.0f));

        // Mana
        REQUIRE(exec.tryCast(HotbarSlot::E, sta, mana, pwr).success == true);
        REQUIRE(mana == Approx(20.0f));

        // Power
        REQUIRE(exec.tryCast(HotbarSlot::R, sta, mana, pwr).success == true);
        REQUIRE(pwr == Approx(35.0f));
    }

    SECTION("Insufficient Resources Rejection") {
        float low = 5.0f;
        REQUIRE(exec.tryCast(HotbarSlot::Q, low, mana, pwr).failReason == CastFailReason::InsufficientResource);
        REQUIRE(exec.tryCast(HotbarSlot::E, sta, low, pwr).failReason == CastFailReason::InsufficientResource);
        REQUIRE(exec.tryCast(HotbarSlot::R, sta, mana, low).failReason == CastFailReason::InsufficientResource);
    }

    SECTION("Cooldown Timers and Recovery") {
        exec.tryCast(HotbarSlot::Q, sta, mana, pwr);
        REQUIRE(exec.isOnCooldown(HotbarSlot::Q) == true);
        REQUIRE(exec.getCooldownRemaining(HotbarSlot::Q) > 1.0f);

        exec.update(2.5f);
        REQUIRE(exec.isOnCooldown(HotbarSlot::Q) == false);
        REQUIRE(exec.getCooldownRemaining(HotbarSlot::Q) == Approx(0.0f));
    }
}
