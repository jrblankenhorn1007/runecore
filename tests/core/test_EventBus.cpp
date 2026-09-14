#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include "core/EventBus.hpp"

using Catch::Approx;

struct SampleDamageEvent {
    int targetId;
    float amount;
};

struct SampleHealEvent {
    int targetId;
    float amount;
};

TEST_CASE("EventBus Publish, Subscribe, and Unsubscribe", "[core][eventbus]") {
    EventBus bus;

    int dmgCount = 0;
    float lastDmg = 0.0f;
    auto subId = bus.subscribe<SampleDamageEvent>([&](const SampleDamageEvent& ev) {
        dmgCount++;
        lastDmg = ev.amount;
    });

    SECTION("Publish Delivers to Typed Subscriber") {
        bus.publish(SampleDamageEvent{1, 50.0f});
        REQUIRE(dmgCount == 1);
        REQUIRE(lastDmg == Approx(50.0f));

        // Publishing unrelated event doesn't trigger damage handler
        bus.publish(SampleHealEvent{1, 30.0f});
        REQUIRE(dmgCount == 1);
    }

    SECTION("Unsubscribe Prevents Future Invocations") {
        bus.unsubscribe<SampleDamageEvent>(subId);
        bus.publish(SampleDamageEvent{2, 100.0f});
        REQUIRE(dmgCount == 0);

        // Unsubscribing nonexistent ID does not crash
        bus.unsubscribe<SampleDamageEvent>(9999);
    }

    SECTION("Clear Removes All Subscriptions") {
        bus.clear();
        bus.publish(SampleDamageEvent{1, 25.0f});
        REQUIRE(dmgCount == 0);
    }
}
