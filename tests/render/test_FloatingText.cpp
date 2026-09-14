#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include "render/FloatingText.hpp"

using Catch::Approx;

TEST_CASE("FloatingText System Lifecycle, Physics, and Decay", "[render][fct]") {
    FloatingTextSystem fts(50); // Pool of 50 text instances

    SECTION("Initial Pool is Empty") {
        REQUIRE(fts.getActiveCount() == 0);
    }

    SECTION("Spawning Damage Numbers and Upward Pop") {
        fts.spawnText(Vec2{100.0f, 150.0f}, "-45", Color{255, 80, 80, 255}, 1.0f, false);
        REQUIRE(fts.getActiveCount() == 1);

        const auto& texts = fts.getTexts();
        REQUIRE(texts[0].active == true);
        REQUIRE(texts[0].text == "-45");
        REQUIRE(texts[0].velocity.y < 0.0f); // Popped upward (negative Y)
        REQUIRE(texts[0].scale == Approx(1.0f));

        // Step simulation for 0.5s
        fts.update(0.5f);
        REQUIRE(fts.getActiveCount() == 1);
        // Position should have moved upward
        REQUIRE(texts[0].position.y < 150.0f);
        // Alpha should be fading
        REQUIRE(texts[0].color.a < 255);

        // Step another 0.6s (total 1.1s > 1.0s lifetime)
        fts.update(0.6f);
        REQUIRE(fts.getActiveCount() == 0);
        REQUIRE(texts[0].active == false);
    }

    SECTION("Critical Hit Styling and Formatting") {
        fts.spawnText(Vec2{200.0f, 200.0f}, "CRIT! 120", Color{255, 230, 40, 255}, 1.2f, true);
        REQUIRE(fts.getActiveCount() == 1);
        const auto& texts = fts.getTexts();
        REQUIRE(texts[0].isCrit == true);
        REQUIRE(texts[0].scale > 1.2f); // Criticals are enlarged
    }

    SECTION("XP and Health Restoration Floating Text Helpers") {
        fts.spawnDamage(Vec2{50.0f, 50.0f}, 65.0f, false);
        fts.spawnDamage(Vec2{60.0f, 50.0f}, 130.0f, true); // Crit
        fts.spawnHeal(Vec2{70.0f, 50.0f}, 40.0f);
        fts.spawnXP(Vec2{80.0f, 50.0f}, 150);

        REQUIRE(fts.getActiveCount() == 4);

        const auto& texts = fts.getTexts();
        REQUIRE(texts[0].text == "65");
        REQUIRE(texts[1].text == "CRIT! 130");
        REQUIRE(texts[2].text == "+40 HP");
        REQUIRE(texts[3].text == "+150 XP");
    }

    SECTION("Damage Types Use Distinct Readable Colors") {
        fts.spawnDamage(Vec2{0.0f, 0.0f}, 10.0f);
        fts.spawnDamage(Vec2{0.0f, 0.0f}, 10.0f, false, DamageType::Fire);
        fts.spawnDamage(Vec2{0.0f, 0.0f}, 10.0f, false, DamageType::Frost);

        const auto& texts = fts.getTexts();
        REQUIRE(texts[0].color.r == 255);
        REQUIRE(texts[0].color.g == 255);
        REQUIRE(texts[0].color.b == 255);
        REQUIRE(texts[1].color.r == 255);
        REQUIRE(texts[1].color.g == 145);
        REQUIRE(texts[2].color.r == 70);
        REQUIRE(texts[2].color.b == 255);
    }

    SECTION("Pool Capacity Limit and Recycling") {
        FloatingTextSystem smallFts(5);
        for (int i = 0; i < 10; ++i) {
            smallFts.spawnText(Vec2{0.0f, 0.0f}, std::to_string(i), Color{255, 255, 255, 255});
        }
        REQUIRE(smallFts.getActiveCount() <= 5);

        smallFts.clear();
        REQUIRE(smallFts.getActiveCount() == 0);
    }
}
