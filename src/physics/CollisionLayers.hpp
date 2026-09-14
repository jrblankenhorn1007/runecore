#pragma once
#include <cstdint>

namespace CollisionLayer {
    constexpr uint16_t None             = 0;
    constexpr uint16_t Terrain          = 1 << 0;
    constexpr uint16_t Player           = 1 << 1;
    constexpr uint16_t Enemy            = 1 << 2;
    constexpr uint16_t PlayerProjectile = 1 << 3;
    constexpr uint16_t EnemyProjectile  = 1 << 4;
    constexpr uint16_t DroppedItem      = 1 << 5;
    constexpr uint16_t SensorTrigger    = 1 << 6;
    constexpr uint16_t All              = 0xFFFF;

    constexpr uint16_t PlayerMask = Terrain | Enemy | EnemyProjectile | DroppedItem | SensorTrigger;
    constexpr uint16_t EnemyMask = Terrain | Player | PlayerProjectile | SensorTrigger;
    constexpr uint16_t PlayerProjectileMask = Terrain | Enemy;
    constexpr uint16_t EnemyProjectileMask = Terrain | Player;
}
