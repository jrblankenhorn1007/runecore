#pragma once
#include <entt/entt.hpp>
#include "core/Math.hpp"
#include "gameplay/combat/ProjectileSystem.hpp"

struct FirearmWeapon {
    int magazineCapacity{6};
    int currentAmmoInMag{6};
    int reserveAmmo{30};
    float reloadDuration{1.2f};
    float reloadTimer{0.0f};
    bool reloading{false};

    bool canFire() const {
        return !reloading && currentAmmoInMag > 0;
    }

    bool fire() {
        if (!canFire()) return false;
        currentAmmoInMag--;
        return true;
    }

    void startReload() {
        if (currentAmmoInMag >= magazineCapacity || reserveAmmo <= 0 || reloading) {
            return;
        }
        reloading = true;
        reloadTimer = reloadDuration;
    }

    bool isReloading() const {
        return reloading;
    }

    void update(float dt) {
        if (reloading) {
            reloadTimer -= dt;
            if (reloadTimer <= 0.0f) {
                int needed = magazineCapacity - currentAmmoInMag;
                int transfer = std::min(needed, reserveAmmo);
                currentAmmoInMag += transfer;
                reserveAmmo -= transfer;
                reloading = false;
                reloadTimer = 0.0f;
            }
        }
    }
};

struct BlockResult {
    bool isParry{false};
    float damageTaken{0.0f};
    float staminaConsumed{0.0f};
};

struct ShieldWeapon {
    float blockMitigation{0.80f};
    float staminaCostPerBlock{15.0f};
    float parryWindow{0.20f};
    float parryTimer{0.0f};
    bool raised{false};

    void raiseShield() {
        raised = true;
        parryTimer = parryWindow;
    }

    void lowerShield() {
        raised = false;
        parryTimer = 0.0f;
    }

    bool isRaised() const {
        return raised;
    }

    bool isParryActive() const {
        return raised && parryTimer > 0.0f;
    }

    void update(float dt) {
        if (parryTimer > 0.0f) {
            parryTimer = std::max(0.0f, parryTimer - dt);
        }
    }

    BlockResult processHit(float incomingDamage, float currentStamina) {
        BlockResult res;
        if (!raised) {
            res.damageTaken = incomingDamage;
            return res;
        }

        if (isParryActive()) {
            res.isParry = true;
            res.damageTaken = 0.0f;
            res.staminaConsumed = 0.0f;
            return res;
        }

        // Standard block
        float staminaToUse = std::min(currentStamina, staminaCostPerBlock);
        res.staminaConsumed = staminaToUse;
        res.damageTaken = incomingDamage * (1.0f - blockMitigation);
        return res;
    }
};

class WeaponArsenal {
public:
    explicit WeaponArsenal(ProjectileSystem& projSystem);

    int fireShotgun(
        entt::registry& registry,
        const Vec2& origin,
        const Vec2& direction,
        int pelletCount,
        float spreadAngleDegrees,
        float pelletDamage,
        entt::entity owner
    );

private:
    ProjectileSystem& m_projSystem;
};
