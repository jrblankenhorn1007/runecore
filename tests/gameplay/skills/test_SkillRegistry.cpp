#include <catch2/catch_test_macros.hpp>
#include "gameplay/skills/SkillRegistry.hpp"

TEST_CASE("SkillRegistry Registration and Query Functions", "[gameplay][skills]") {
    SkillRegistry sr;

    SkillDefinition def;
    def.id = "sk_slash";
    def.name = "Heavy Slash";
    def.baseDamage = 60.0f;

    sr.registerSkill(def);

    REQUIRE(sr.getSkill("sk_slash") != nullptr);
    REQUIRE(sr.getSkill("sk_slash")->name == "Heavy Slash");
    REQUIRE(sr.getSkill("unknown") == nullptr);
}
