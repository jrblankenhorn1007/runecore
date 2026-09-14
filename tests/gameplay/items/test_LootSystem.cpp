#include <catch2/catch_test_macros.hpp>
#include "gameplay/items/LootSystem.hpp"
#include "physics/CollisionWorld.hpp"
#include "gameplay/items/Inventory.hpp"
#include "ecs/Components.hpp"

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
}
