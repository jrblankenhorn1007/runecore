#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include <fstream>
#include <cstdio>
#include "core/Math.hpp"
#include "core/Random.hpp"
#include "core/Time.hpp"
#include "core/EventBus.hpp"
#include "core/BotTester.hpp"
#include "core/GameSimulation.hpp"
#include "ecs/Components.hpp"
#include "gameplay/ai/BossAI.hpp"
#include "gameplay/ai/EnemyAI.hpp"
#include "gameplay/augmentations/AugmentationMatrix.hpp"
#include "gameplay/building/BuildingSystem.hpp"
#include "gameplay/building/FarmingSystem.hpp"
#include "gameplay/building/WorldInteraction.hpp"
#include "gameplay/classes/ClassRegistry.hpp"
#include "gameplay/combat/CombatSystem.hpp"
#include "gameplay/combat/DamageCalculator.hpp"
#include "gameplay/combat/ProjectileSystem.hpp"
#include "gameplay/combat/StatusEffects.hpp"
#include "gameplay/combat/WeaponArsenal.hpp"
#include "gameplay/crafting/CraftingEngine.hpp"
#include "gameplay/crafting/ModificationForge.hpp"
#include "gameplay/items/Inventory.hpp"
#include "gameplay/items/Item.hpp"
#include "gameplay/items/ItemGenerator.hpp"
#include "gameplay/items/LootSystem.hpp"
#include "gameplay/skills/SkillExecutor.hpp"
#include "gameplay/skills/SkillRegistry.hpp"
#include "gameplay/skills/SkillTree.hpp"
#include "gameplay/stats/Progression.hpp"
#include "gameplay/stats/StatsSystem.hpp"
#include "gameplay/survival/Environment.hpp"
#include "gameplay/survival/Metabolism.hpp"
#include "gameplay/survival/QuestSystem.hpp"
#include "gameplay/survival/SettlementSystem.hpp"
#include "physics/CharacterController.hpp"
#include "physics/CollisionLayers.hpp"
#include "physics/CollisionWorld.hpp"
#include "procgen/BiomeSystem.hpp"
#include "procgen/DungeonGenerator.hpp"
#include "procgen/Tilemap.hpp"
#include "render/Camera.hpp"
#include "render/ParticleSystem.hpp"
#include "save/SaveManager.hpp"

using Catch::Approx;

TEST_CASE("Comprehensive Edge Cases for Complete Code Coverage", "[coverage][exhaustive]") {
    SECTION("Random and Math Edge Cases") {
        Random rng(123);
        rng.setSeed(456);

        // Clamped range calls
        REQUIRE(rng.rangeInt(10, 5) == 10);
        REQUIRE(rng.rangeFloat(10.0f, 5.0f) == Approx(10.0f));
        REQUIRE(rng.chance(0.0f) == false);
        REQUIRE(rng.chance(1.0f) == true);

        // Vec2 division and operations
        Vec2 v{10.0f, 20.0f};
        v += Vec2{1.0f, 2.0f};
        v -= Vec2{1.0f, 2.0f};
        v *= 2.0f;
        REQUIRE(v.x == Approx(20.0f));
        REQUIRE(v.y == Approx(40.0f));

        Vec2 zeroV{0.0f, 0.0f};
        REQUIRE(zeroV.normalized().length() == Approx(0.0f));

        // Rect center and bounds
        Rect r{10.0f, 20.0f, 30.0f, 40.0f};
        REQUIRE(r.center().x == Approx(25.0f));
        REQUIRE(r.center().y == Approx(40.0f));
        REQUIRE(r.contains(Vec2{10.0f, 20.0f}) == true);
        REQUIRE(r.contains(Vec2{40.0f, 60.0f}) == true);
        REQUIRE(r.contains(Vec2{5.0f, 20.0f}) == false);
        REQUIRE(r.contains(Vec2{45.0f, 20.0f}) == false);
        REQUIRE(r.contains(Vec2{20.0f, 15.0f}) == false);
        REQUIRE(r.contains(Vec2{20.0f, 65.0f}) == false);

        // Color struct
        Color c1;
        REQUIRE(c1.r == 255);
        Color c2{10, 20, 30};
        REQUIRE(c2.a == 255);
    }

    SECTION("Time and EventBus Edge Cases") {
        TimeStep ts(-10.0f); // Fallback to 60Hz
        REQUIRE(ts.getFixedDelta() == Approx(1.0f / 60.0f));
        REQUIRE(ts.getTotalTime() == Approx(0.0f));

        EventBus bus;
        bus.clear();
        struct CustomEvent { int val; };
        bus.publish(CustomEvent{10}); // Publishing to empty bus
    }

    SECTION("Components and Health/Mana/Power Edge Cases") {
        HealthComponent hc(100.0f, 100.0f, 2.0f);
        hc.takeDamage(-5.0f); // Negative damage ignored
        REQUIRE(hc.current == Approx(100.0f));

        hc.heal(-10.0f); // Negative heal ignored
        REQUIRE(hc.current == Approx(100.0f));

        hc.invulnTimer = 0.5f;
        hc.update(0.2f);
        REQUIRE(hc.invulnTimer == Approx(0.3f));

        hc.takeDamage(100.0f);
        REQUIRE(hc.isDead == true);
        hc.takeDamage(10.0f); // Damage while dead ignored
        hc.heal(50.0f); // Revive
        REQUIRE(hc.isDead == false);

        ManaComponent mc(50.0f, 50.0f, 1.0f);
        REQUIRE(mc.consume(-5.0f) == false);
        mc.restore(-10.0f);
        mc.current = 40.0f;
        mc.update(2.0f);
        REQUIRE(mc.current == Approx(42.0f));

        PowerComponent pc(50.0f, 100.0f, 2.0f);
        REQUIRE(pc.consume(-5.0f) == false);
        pc.charge(-10.0f);
        pc.update(1.0f);
        REQUIRE(pc.current == Approx(52.0f));
    }

    SECTION("ClassRegistry and Exception Handling") {
        ClassRegistry cr;
        REQUIRE(cr.getAllClasses().size() == 9);
        REQUIRE_THROWS_AS(cr.getClass(static_cast<ClassType>(999)), std::runtime_error);
    }

    SECTION("Damage Calculator Armor Penetration and Mitigation Bounds") {
        DamageInstance di;
        di.baseDamage = 100.0f;
        di.type = DamageType::Physical;
        di.armorPenetration = 0.50f; // 50% pen

        DamageResult res = DamageCalculator::calculate(di, 200.0f, 0.0f);
        // Effective armor = 100 -> mitigation 50%
        REQUIRE(res.finalDamage == Approx(50.0f));

        // High resistance clamp
        di.type = DamageType::Cold;
        DamageResult resCold = DamageCalculator::calculate(di, 0.0f, 0.99f); // Clamps to 90%
        REQUIRE(resCold.finalDamage == Approx(10.0f));
    }

    SECTION("Status Effects Refresh and Query") {
        StatusEffectsManager sem;
        StatusEffectsComponent sec;

        sem.applyEffect(sec, StatusType::Bleed, 5.0f, 1.0f, 10.0f);
        REQUIRE(sem.hasEffect(sec, StatusType::Bleed) == true);
        REQUIRE(sem.hasEffect(sec, StatusType::Poison) == false);

        // Refresh with longer duration
        sem.applyEffect(sec, StatusType::Bleed, 8.0f, 1.0f, 15.0f);
        REQUIRE(sec.effects[0].duration == Approx(8.0f));
        REQUIRE(sec.effects[0].damagePerTick == Approx(15.0f));
    }

    SECTION("Inventory Edge Cases: Full Inventory and Empty Slots") {
        Inventory inv(2);
        Item it1; it1.id = "i1"; it1.stackable = false; it1.weight = 5.0f;
        Item it2; it2.id = "i2"; it2.stackable = false; it2.weight = 5.0f;
        Item it3; it3.id = "i3"; it3.stackable = false; it3.weight = 5.0f;

        REQUIRE(inv.addItem(it1) == true);
        REQUIRE(inv.addItem(it2) == true);
        REQUIRE(inv.addItem(it3) == false); // Full

        REQUIRE(inv.removeItem("nonexistent", 1) == false);
        REQUIRE(inv.getSlot(-1).has_value() == false);
        REQUIRE(inv.getSlot(99).has_value() == false);
        REQUIRE(inv.equipItem(EquipSlot::MainHand, -1) == false);
        REQUIRE(inv.equipItem(EquipSlot::MainHand, 99) == false);
        REQUIRE(inv.unequipItem(EquipSlot::Helmet) == false); // Nothing equipped
    }

    SECTION("Item Generator All Rarity Tiers") {
        Random rng(555);
        ItemGenerator ig(rng);
        BaseItemTemplate tmpl;
        tmpl.id = "sword";
        tmpl.minBaseDamage = 20.0f;
        tmpl.maxBaseDamage = 30.0f;
        tmpl.minBaseArmor = 5.0f;
        tmpl.maxBaseArmor = 10.0f;

        Item uncom = ig.generateItem(tmpl, ItemRarity::Uncommon);
        REQUIRE(uncom.rarity == ItemRarity::Uncommon);

        Item epic = ig.generateItem(tmpl, ItemRarity::Epic);
        REQUIRE(epic.rarity == ItemRarity::Epic);
        REQUIRE(epic.affixes.size() == 3);

        Item mythic = ig.generateItem(tmpl, ItemRarity::Mythic);
        REQUIRE(mythic.rarity == ItemRarity::Mythic);
        REQUIRE(mythic.affixes.size() == 6);

        Item prism = ig.generateItem(tmpl, ItemRarity::Prismatic);
        REQUIRE(prism.rarity == ItemRarity::Prismatic);
        REQUIRE(prism.affixes.size() == 8);
        REQUIRE(prism.getEffectiveArmor() >= 5.0f);
    }

    SECTION("Modification Forge Sockets and Tier 7 Max") {
        Random rng(777);
        ModificationForge mf(rng);
        Item maxSword;
        maxSword.id = "max_sword";
        maxSword.tier = 7; // Already max tier
        maxSword.sockets = 3;

        REQUIRE(mf.upgradeTier(maxSword).success == false);
        REQUIRE(mf.punchSocket(maxSword).success == false);
    }

    SECTION("Skill Registry and Executor Resource Fallback") {
        SkillRegistry sr;
        REQUIRE(sr.getSkill("unknown") == nullptr);

        SkillExecutor se(sr);
        REQUIRE(se.isOnCooldown(HotbarSlot::Q) == false);
        REQUIRE(se.getCooldownRemaining(HotbarSlot::Q) == Approx(0.0f));

        float sta = 10.0f; float mp = 10.0f; float pwr = 10.0f;
        CastResult cr = se.tryCast(HotbarSlot::Q, sta, mp, pwr);
        REQUIRE(cr.success == false);
        REQUIRE(cr.failReason == CastFailReason::EmptySlot);
    }

    SECTION("Metabolism Temperature Extremes") {
        Metabolism met;
        met.eat(100.0f);
        met.drink(100.0f);

        // Hyperthermia at +100°C ambient
        for (int i = 0; i < 50; ++i) {
            met.update(20.0f, 100.0f);
        }
        REQUIRE(met.isHyperthermic() == true);
    }

    SECTION("SaveManager Malformed and Nonexistent Files") {
        SaveData sd;
        REQUIRE(SaveManager::loadFromFile("nonexistent_file_path_123.sav", sd) == false);

        // Malformed json test
        std::string malformedPath = "test_malformed.sav";
        std::ofstream out(malformedPath);
        out << "{ not valid json";
        out.close();

        REQUIRE(SaveManager::loadFromFile(malformedPath, sd) == false);
        std::remove(malformedPath.c_str());
    }

    SECTION("BotTester Phase Names and Summaries") {
        BotTester bt;
        bt.reset();
        REQUIRE(bt.getCurrentPhaseName() == "Testing Ground Movement & Sprint");
        BotReport rep = bt.getReport();
        rep.printSummary(); // Tests printout logic
    }

    SECTION("WorldInteraction and BiomeSystem Out of Bounds") {
        CollisionWorld cw(16.0f);
        Tilemap tm(16.0f);
        LootSystem ls;
        WorldInteraction wi(cw, tm, ls);
        Inventory inv;
        entt::registry reg;

        // Mining empty tile
        REQUIRE(wi.mineTile(reg, Vec2{0.0f, 0.0f}, Vec2{0.0f, 0.0f}) == false);
        // Placing without inventory
        REQUIRE(wi.placeBlock(inv, "nonexistent", Vec2{0.0f, 0.0f}, Vec2{0.0f, 0.0f}) == false);

        // Biome fallbacks
        BiomeSystem bs;
        BiomeData farWest = bs.getBiomeAt(-99999.0f);
        REQUIRE(!farWest.id.empty());
    }

    SECTION("WeaponArsenal Zero Pellets and Shield Lowering") {
        ProjectileSystem ps;
        WeaponArsenal wa(ps);
        entt::registry reg;
        REQUIRE(wa.fireShotgun(reg, Vec2{0.0f, 0.0f}, Vec2{1.0f, 0.0f}, 0, 30.0f, 10.0f, entt::null) == 0);

        ShieldWeapon sw;
        sw.raiseShield();
        sw.lowerShield();
        REQUIRE(sw.isRaised() == false);
        BlockResult br = sw.processHit(50.0f, 50.0f);
        REQUIRE(br.isParry == false);
        REQUIRE(br.damageTaken == Approx(50.0f));
    }
}
