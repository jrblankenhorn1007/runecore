#pragma once
#include <entt/entt.hpp>
#include "core/EventBus.hpp"
#include "core/Random.hpp"
#include "physics/CollisionWorld.hpp"
#include "procgen/Tilemap.hpp"
#include "gameplay/survival/Environment.hpp"
#include "gameplay/classes/ClassRegistry.hpp"
#include "gameplay/skills/SkillRegistry.hpp"

struct EngineContext {
    entt::registry registry;
    EventBus eventBus;
    Random rng{1337};
    CollisionWorld physicsWorld{16.0f};
    Tilemap tilemap{16.0f};
    DayNightCycle dayNight{1440.0f};
    ClassRegistry classRegistry;
    SkillRegistry skillRegistry;
};
