#include <catch2/catch_test_macros.hpp>
#include "core/EngineContext.hpp"

TEST_CASE("EngineContext Initialization and Subsystems", "[core][context]") {
    EngineContext ctx;

    REQUIRE(ctx.physicsWorld.getTileSize() == 16.0f);
    REQUIRE(ctx.tilemap.getTileSize() == 16.0f);
    REQUIRE(ctx.classRegistry.getAllClasses().size() == 9);
    REQUIRE(ctx.dayNight.getTimeOfDay() > 0.0f);

    auto entity = ctx.registry.create();
    REQUIRE(ctx.registry.valid(entity));
}
