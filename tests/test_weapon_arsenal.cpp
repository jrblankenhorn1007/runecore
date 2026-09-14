#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include "gameplay/combat/WeaponArsenal.hpp"
#include "gameplay/combat/ProjectileSystem.hpp"
#include "ecs/Components.hpp"

using Catch::Approx;

TEST_CASE("Firearm Magazine Capacity and Reload System", "[combat][firearms]") {
    FirearmWeapon gun;
    gun.magazineCapacity = 6; // Revolver cylinder
    gun.currentAmmoInMag = 6;
    gun.reserveAmmo = 18;
    gun.reloadDuration = 1.2f;

    SECTION("Firing Consumes Magazine Ammo") {
        REQUIRE(gun.canFire() == true);
        REQUIRE(gun.fire() == true);
        REQUIRE(gun.currentAmmoInMag == 5);

        // Fire remaining 5 rounds
        for (int i = 0; i < 5; ++i) {
            REQUIRE(gun.fire() == true);
        }
        REQUIRE(gun.currentAmmoInMag == 0);
        REQUIRE(gun.canFire() == false); // Dry fire
    }

    SECTION("Reload Transfers from Reserve to Magazine") {
        gun.currentAmmoInMag = 1;
        gun.startReload();
        REQUIRE(gun.isReloading() == true);
        REQUIRE(gun.canFire() == false); // Cannot fire while actively reloading

        // Step 0.6s (halfway)
        gun.update(0.6f);
        REQUIRE(gun.isReloading() == true);

        // Step another 0.7s (total 1.3s > 1.2s duration)
        gun.update(0.7f);
        REQUIRE(gun.isReloading() == false);
        REQUIRE(gun.currentAmmoInMag == 6); // Fully reloaded
        REQUIRE(gun.reserveAmmo == 13);     // 18 - 5 = 13
    }
}

TEST_CASE("Shotgun Multi-Pellet Spread Firing Mode", "[combat][shotgun]") {
    entt::registry registry;
    ProjectileSystem projSys;
    WeaponArsenal arsenal(projSys);

    SECTION("Shotgun Blast Fires 8 Directional Pellets in Spread Cone") {
        Vec2 origin{100.0f, 100.0f};
        Vec2 aimDir{1.0f, 0.0f}; // Aiming right

        int pelletsSpawned = arsenal.fireShotgun(registry, origin, aimDir, 8, 30.0f, 12.0f, entt::null);
        REQUIRE(pelletsSpawned == 8);

        auto view = registry.view<ProjectileComponent, VelocityComponent>();
        int count = 0;
        for (auto [e, proj, vel] : view.each()) {
            REQUIRE(vel.linear.x > 0.0f);
            REQUIRE(proj.damage == Approx(12.0f));
            count++;
        }
        REQUIRE(count == 8);
    }
}

TEST_CASE("Shield Blocking and Timed Parry Mechanics", "[combat][shield]") {
    ShieldWeapon shield;
    shield.blockMitigation = 0.85f; // 85% damage mitigation
    shield.staminaCostPerBlock = 15.0f;
    shield.parryWindow = 0.20f;     // 200ms parry window

    SECTION("Timed Parry Within 200ms Window Blocks 100% Damage with Zero Stamina") {
        shield.raiseShield();
        REQUIRE(shield.isRaised() == true);
        REQUIRE(shield.isParryActive() == true);

        BlockResult res = shield.processHit(100.0f, 50.0f); // 100 damage against 50 stamina
        REQUIRE(res.isParry == true);
        REQUIRE(res.damageTaken == Approx(0.0f));
        REQUIRE(res.staminaConsumed == Approx(0.0f));
    }

    SECTION("Standard Block After Parry Window Mitigates Damage and Drains Stamina") {
        shield.raiseShield();
        shield.update(0.30f); // 300ms elapsed (> 200ms parry window)
        REQUIRE(shield.isParryActive() == false);
        REQUIRE(shield.isRaised() == true);

        BlockResult res = shield.processHit(100.0f, 50.0f);
        REQUIRE(res.isParry == false);
        // 100 * (1.0 - 0.85) = 15 damage taken
        REQUIRE(res.damageTaken == Approx(15.0f));
        REQUIRE(res.staminaConsumed == Approx(15.0f));
    }
}
