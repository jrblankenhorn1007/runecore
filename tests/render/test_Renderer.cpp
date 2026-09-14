#include <catch2/catch_test_macros.hpp>
#include "render/Renderer.hpp"
#include "core/GameSimulation.hpp"
#include "input/InputManager.hpp"
#include "render/Camera.hpp"

TEST_CASE("Renderer Complete Drawing Functions and Offscreen Pipeline", "[render][renderer]") {
    Renderer renderer;
    bool ok = renderer.init("TestRenderer", 640, 360, 640, 360, SDL_WINDOW_HIDDEN);
    if (!ok) return;

    REQUIRE(renderer.getWindow() != nullptr);
    REQUIRE(renderer.getSDLRenderer() != nullptr);

    Camera camera;
    camera.setPosition(Vec2{100.0f, 160.0f});
    CanvasMetrics metrics = Camera::calculateCanvasMetrics(640, 360);

    GameSimulation sim;
    sim.initialize(ClassType::Juggernaut);

    RawInputState input;
    input.hotbarSelected = 0;

    SECTION("Render Pass and Frame Drawing") {
        renderer.beginFrame();
        renderer.drawParallaxBackground(240.0f, 1, metrics);

        // 1. Draw tiles (Air, Stone, Ore, Wood, Platform, Default, Culled)
        renderer.drawTile(0, 0, 0, camera, metrics); // Air
        renderer.drawTile(6, 10, 1, camera, metrics); // Stone
        renderer.drawTile(7, 10, 2, camera, metrics); // Iron Ore
        renderer.drawTile(8, 10, 3, camera, metrics); // Wood
        renderer.drawTile(9, 7, 5, camera, metrics);  // Platform
        renderer.drawTile(11, 10, 6, camera, metrics); // Left slope
        renderer.drawTile(12, 10, 7, camera, metrics); // Right slope
        renderer.drawTile(10, 10, 99, camera, metrics); // Default
        renderer.drawBossTelegraph(Vec2{120.0f, 96.0f}, 32.0f, camera, metrics);
        renderer.drawBossTelegraph(Vec2{120.0f, 96.0f}, 48.0f, camera, metrics, true);
        renderer.drawTile(999, 999, 1, camera, metrics); // Culled

        // 2. Draw Entities
        renderer.drawEntity(Vec2{100.0f, 160.0f}, Vec2{16.0f, 24.0f}, Color{65, 115, 220, 255}, camera, metrics, 1, true, 1.0f); // Player facing right
        renderer.drawWeapon(Vec2{100.0f, 160.0f}, Vec2{140.0f, 140.0f}, true, camera, metrics);
        renderer.drawEntity(Vec2{100.0f, 160.0f}, Vec2{16.0f, 24.0f}, Color{65, 115, 220, 255}, camera, metrics, -1, true, 0.8f); // Player facing left
        renderer.drawEntity(Vec2{150.0f, 160.0f}, Vec2{16.0f, 16.0f}, Color{200, 45, 55, 255}, camera, metrics, 1, false, 0.5f); // Enemy with HP bar
        renderer.drawEntity(Vec2{200.0f, 160.0f}, Vec2{16.0f, 16.0f}, Color{200, 45, 55, 255}, camera, metrics, -1, false, 1.0f); // Enemy full HP
        renderer.drawEntity(Vec2{9999.0f, 9999.0f}, Vec2{16.0f, 16.0f}, Color{255, 0, 0, 255}, camera, metrics, 1, false, 1.0f); // Culled

        // 3. Draw Slash Arc
        Hitbox box;
        box.bounds = Rect{100.0f, 150.0f, 28.0f, 18.0f};
        renderer.drawSlashArc(box, camera, metrics, 1);
        renderer.drawSlashArc(box, camera, metrics, -1);

        // 4. Draw Projectile & Loot
        renderer.drawProjectile(Vec2{120.0f, 150.0f}, Vec2{100.0f, 0.0f}, Color{255, 200, 50, 255}, camera, metrics);
        renderer.drawLoot(Vec2{130.0f, 155.0f}, "Iron Ore", camera, metrics);

        // 5. Draw HUD & Lighting Overlay
        renderer.drawHUD(sim, metrics, input);
        renderer.drawLightingOverlay(Vec2{100.0f, 160.0f}, 0.0f, camera, metrics); // Skips if 0.0
        renderer.drawLightingOverlay(Vec2{100.0f, 160.0f}, 0.6f, camera, metrics); // Active lighting

        // 6. Draw Modal Screens
        DungeonConfig dConfig{60, 40, 6, 12, 4};
        Random rng(123);
        DungeonLayout layout = DungeonGenerator(rng).generate(dConfig);
        renderer.drawMinimap(layout, Vec2{100.0f, 160.0f}, metrics);
        DungeonLayout emptyLayout;
        renderer.drawMinimap(emptyLayout, Vec2{0.0f, 0.0f}, metrics);

        Item potion;
        potion.id = "potion";
        potion.name = "Health Potion";
        potion.category = ItemCategory::Consumable;
        sim.getInventory().addItem(potion);

        renderer.drawInventoryScreen(sim.getInventory(), metrics);
        renderer.drawCraftingScreen(sim.getCraftingEngine(), sim.getInventory(), metrics);
        renderer.drawAugmentationScreen(sim.getAugmentations(), metrics);

        renderer.endFrame(metrics);
    }

    renderer.shutdown();
}
