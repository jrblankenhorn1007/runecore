#include <catch2/catch_test_macros.hpp>
#include "ui/TitleFlow.hpp"

TEST_CASE("TitleFlow selects save slots and creates a configured character", "[ui][title]") {
    SECTION("Empty slot opens character creation with class and visor selection") {
        TitleFlow flow(std::array<TitleSlotPreview, 3>{});

        REQUIRE(flow.getSelectedSlotNumber() == 1);
        REQUIRE(flow.handleKey(SDLK_RETURN).kind == TitleActionKind::None);
        REQUIRE(flow.isCreatingCharacter());

        flow.handleKey(SDLK_RIGHT);
        REQUIRE(flow.getCharacter().classType == ClassType::Berserker);
        const Color originalVisor = flow.getCharacter().visorColor;
        flow.handleKey(SDLK_V);
        REQUIRE((flow.getCharacter().visorColor.r != originalVisor.r ||
                 flow.getCharacter().visorColor.g != originalVisor.g ||
                 flow.getCharacter().visorColor.b != originalVisor.b));

        const TitleAction start = flow.handleKey(SDLK_RETURN);
        REQUIRE(start.kind == TitleActionKind::NewGame);
        REQUIRE(start.slot == 1);
    }

    SECTION("Occupied slot resumes and corrupt slot remains unavailable") {
        std::array<TitleSlotPreview, 3> slots{};
        slots[1] = TitleSlotPreview{TitleSlotState::Ready, "Astra", "Medic", 12};
        slots[2].state = TitleSlotState::Corrupt;
        TitleFlow flow(slots);

        flow.handleKey(SDLK_UP);
        REQUIRE(flow.getSelectedSlotNumber() == 3);
        flow.handleKey(SDLK_RETURN);
        REQUIRE(flow.getSelectedSlotNumber() == 3);
        REQUIRE(flow.getMessage() == "SAVE UNREADABLE - SELECT ANOTHER SLOT");

        flow.handleKey(SDLK_UP);
        REQUIRE(flow.getSelectedSlotNumber() == 2);
        const TitleAction resume = flow.handleKey(SDLK_RETURN);
        REQUIRE(resume.kind == TitleActionKind::Resume);
        REQUIRE(resume.slot == 2);
    }

    SECTION("Escape returns to slots from character creation and quits from title") {
        TitleFlow flow(std::array<TitleSlotPreview, 3>{});
        flow.handleKey(SDLK_RETURN);
        REQUIRE(flow.isCreatingCharacter());
        REQUIRE(flow.handleKey(SDLK_ESCAPE).kind == TitleActionKind::None);
        REQUIRE_FALSE(flow.isCreatingCharacter());
        REQUIRE(flow.handleKey(SDLK_ESCAPE).kind == TitleActionKind::Quit);
    }
}
