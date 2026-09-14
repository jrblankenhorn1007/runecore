#include <catch2/catch_test_macros.hpp>
#include "physics/CollisionLayers.hpp"

TEST_CASE("CollisionLayers Category and Mask Constants", "[physics][layers]") {
    REQUIRE(CollisionLayer::None == 0);
    REQUIRE(CollisionLayer::Terrain == (1 << 0));
    REQUIRE(CollisionLayer::Player == (1 << 1));
    REQUIRE(CollisionLayer::Enemy == (1 << 2));
    REQUIRE(CollisionLayer::PlayerProjectile == (1 << 3));
    REQUIRE(CollisionLayer::EnemyProjectile == (1 << 4));
    REQUIRE(CollisionLayer::DroppedItem == (1 << 5));
    REQUIRE(CollisionLayer::SensorTrigger == (1 << 6));
    REQUIRE(CollisionLayer::All == 0xFFFF);

    REQUIRE((CollisionLayer::PlayerMask & CollisionLayer::Terrain) != 0);
    REQUIRE((CollisionLayer::PlayerMask & CollisionLayer::PlayerProjectile) == 0);
    REQUIRE((CollisionLayer::EnemyMask & CollisionLayer::PlayerProjectile) != 0);
}
