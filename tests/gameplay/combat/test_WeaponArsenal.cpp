#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include "gameplay/combat/WeaponArsenal.hpp"
#include "gameplay/combat/ProjectileSystem.hpp"
#include "ecs/Components.hpp"

using Catch::Approx;

TEST_CASE("WeaponArsenal Firearms, Shotguns, and Shields", "[gameplay][combat]") {
    SECTION("Firearm Ammo, Firing, and Reload Cycles") {
        FirearmWeapon gun;
        gun.magazineCapacity = 5;
        gun.currentAmmoInMag = 5;
        gun.reserveAmmo = 10;
        gun.reloadDuration = 1.0f;

        for (int i = 0; i < 5; ++i) {
            REQUIRE(gun.fire() == true);
        }
        REQUIRE(gun.fire() == false); // Empty
        REQUIRE(gun.canFire() == false);

        gun.startReload();
        REQUIRE(gun.isReloading() == true);
        gun.startReload(); // Calling again does nothing

        gun.update(0.5f);
        REQUIRE(gun.isReloading() == true);

        gun.update(0.6f);
        REQUIRE(gun.isReloading() == false);
        REQUIRE(gun.currentAmmoInMag == 5);
        REQUIRE(gun.reserveAmmo == 5);

        // Calling startReload when magazine is already full does nothing
        gun.startReload();
        REQUIRE(gun.isReloading() == false);
    }

    SECTION("Shotgun Spread Firing") {
        entt::registry reg;
        ProjectileSystem ps;
        WeaponArsenal wa(ps);

        REQUIRE(wa.fireShotgun(reg, Vec2{0.0f, 0.0f}, Vec2{1.0f, 0.0f}, 0, 30.0f, 10.0f, entt::null) == 0);

        int spawned = wa.fireShotgun(reg, Vec2{0.0f, 0.0f}, Vec2{1.0f, 0.0f}, 6, 25.0f, 15.0f, entt::null);
        REQUIRE(spawned == 6);
    }

    SECTION("Shield Raise, Lower, Parry, and Standard Block") {
        ShieldWeapon shield;
        shield.blockMitigation = 0.80f;
        shield.parryWindow = 0.20f;
        shield.staminaCostPerBlock = 10.0f;

        BlockResult unblocked = shield.processHit(50.0f, 50.0f);
        REQUIRE(unblocked.isParry == false);
        REQUIRE(unblocked.damageTaken == Approx(50.0f));

        shield.raiseShield();
        REQUIRE(shield.isRaised() == true);
        REQUIRE(shield.isParryActive() == true);

        // Timed parry
        BlockResult parry = shield.processHit(100.0f, 50.0f);
        REQUIRE(parry.isParry == true);
        REQUIRE(parry.damageTaken == Approx(0.0f));
        REQUIRE(parry.staminaConsumed == Approx(0.0f));

        // Let parry timer expire
        shield.update(0.30f);
        REQUIRE(shield.isParryActive() == false);

        // Standard block
        BlockResult block = shield.processHit(100.0f, 50.0f);
        REQUIRE(block.isParry == false);
        REQUIRE(block.damageTaken == Approx(20.0f)); // 100 * (1 - 0.8)
        REQUIRE(block.staminaConsumed == Approx(10.0f));

        shield.lowerShield();
        REQUIRE(shield.isRaised() == false);
    }
}
