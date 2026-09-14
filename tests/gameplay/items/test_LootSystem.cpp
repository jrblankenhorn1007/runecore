#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include "gameplay/items/LootSystem.hpp"
#include "physics/CollisionWorld.hpp"
#include "gameplay/items/Inventory.hpp"
#include "ecs/Components.hpp"

using Catch::Approx;

TEST_CASE("LootSystem Spawning, Physics Bouncing, and Magnet Collection", "[gameplay][items]") {
    entt::registry reg;
    CollisionWorld world(16.0f);
    for (int x = -10; x <= 10; ++x) {
        world.setTile(x, 10, TileType::Solid); // Y = 160px
    }

    LootSystem ls;
    Inventory inv(10);

    Item item;
    item.id = "mat_iron";
    item.name = "Iron Ore";
    item.stackable = true;
    item.quantity = 2;

    DroppedItemComponent dc;
    REQUIRE(dc.pickupDelay == Approx(0.25f));
    REQUIRE(dc.despawnTimer == Approx(300.0f));

    SECTION("Spawning and Gravity Simulation") {
        auto loot = ls.spawnLoot(reg, Vec2{0.0f, 100.0f}, item);
        REQUIRE(reg.valid(loot));

        ls.update(reg, world, inv, Vec2{500.0f, 500.0f}, 0.2f); // Player far away
        REQUIRE(reg.get<TransformComponent>(loot).position.y > 100.0f);
    }

    SECTION("Proximity Vacuum Pickup Into Inventory") {
        auto loot = ls.spawnLoot(reg, Vec2{15.0f, 155.0f}, item);

        // Step updates with player within magnet radius
        for (int i = 0; i < 25; ++i) {
            ls.update(reg, world, inv, Vec2{10.0f, 155.0f}, 1.0f / 60.0f, 64.0f);
        }

        REQUIRE(inv.getItemCount("mat_iron") == 2);
        REQUIRE_FALSE(reg.valid(loot));
    }

    SECTION("Loot Despawn Timer Expiration") {
        auto loot = ls.spawnLoot(reg, Vec2{0.0f, 155.0f}, item);
        REQUIRE(reg.valid(loot));

        // Advance past 300s despawn timer
        ls.update(reg, world, inv, Vec2{500.0f, 500.0f}, 305.0f);
        REQUIRE_FALSE(reg.valid(loot));
    }

    SECTION("Loot Remains in World When Inventory Is Full") {
        Inventory fullInv(1);
        Item dummy; dummy.id = "dummy"; dummy.stackable = false;
        fullInv.addItem(dummy);

        auto loot = ls.spawnLoot(reg, Vec2{10.0f, 155.0f}, item);
        ls.update(reg, world, fullInv, Vec2{10.0f, 155.0f}, 1.0f); // Right next to player
        REQUIRE(reg.valid(loot)); // Not collected
    }

    SECTION("Loot Wall Collision") {
        world.setTile(2, 9, TileType::Solid); // Wall at X=32..48, Y=144..160
        auto loot = ls.spawnLoot(reg, Vec2{20.0f, 150.0f}, item, Vec2{200.0f, 0.0f});

        ls.update(reg, world, inv, Vec2{500.0f, 500.0f}, 0.2f);
        REQUIRE(reg.valid(loot));
        REQUIRE(reg.get<VelocityComponent>(loot).linear.x == Approx(0.0f));
    }
}
