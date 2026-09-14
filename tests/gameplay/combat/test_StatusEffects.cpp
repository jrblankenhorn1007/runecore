#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include "gameplay/combat/StatusEffects.hpp"

using Catch::Approx;

TEST_CASE("StatusEffectsManager Application, Periodic Ticks, and Cleansing", "[gameplay][combat]") {
    StatusEffectsManager sem;
    StatusEffectsComponent sec;

    SECTION("Applying and Querying Effects") {
        REQUIRE(sem.hasEffect(sec, StatusType::Poison) == false);
        sem.applyEffect(sec, StatusType::Poison, 4.0f, 1.0f, 10.0f);
        REQUIRE(sem.hasEffect(sec, StatusType::Poison) == true);
        REQUIRE(sem.hasEffect(sec, StatusType::Freeze) == false);

        // Refresh extends duration
        sem.applyEffect(sec, StatusType::Poison, 6.0f, 1.0f, 15.0f);
        REQUIRE(sec.effects[0].duration == Approx(6.0f));
        REQUIRE(sec.effects[0].damagePerTick == Approx(15.0f));
    }

    SECTION("Periodic Damage Ticks and Expiration") {
        sem.applyEffect(sec, StatusType::Burn, 2.5f, 1.0f, 20.0f);

        float dmg1 = sem.update(sec, 0.5f);
        REQUIRE(dmg1 == Approx(0.0f));

        float dmg2 = sem.update(sec, 0.6f); // 1.1s total -> 1st tick
        REQUIRE(dmg2 == Approx(20.0f));

        float dmg3 = sem.update(sec, 1.0f); // 2.1s total -> 2nd tick
        REQUIRE(dmg3 == Approx(20.0f));

        float dmg4 = sem.update(sec, 1.0f); // Expires
        REQUIRE(dmg4 == Approx(20.0f));
        REQUIRE(sec.effects.empty() == true);
    }

    SECTION("Cleanse All Effects") {
        sem.applyEffect(sec, StatusType::Bleed, 5.0f, 1.0f, 5.0f);
        sem.applyEffect(sec, StatusType::Rot, 5.0f, 1.0f, 8.0f);
        REQUIRE(sec.effects.size() == 2);

        sem.cleanseAll(sec);
        REQUIRE(sec.effects.empty() == true);
    }
}
