#include "ui/TitleFlow.hpp"
#include <utility>

TitleFlow::TitleFlow(std::array<TitleSlotPreview, 3> slots)
    : m_slots(std::move(slots)) {}

const std::array<ClassType, 9>& TitleFlow::classChoices() {
    static constexpr std::array<ClassType, 9> choices{
        ClassType::Juggernaut,
        ClassType::Berserker,
        ClassType::Gunslinger,
        ClassType::Phantom,
        ClassType::Technomancer,
        ClassType::Medic,
        ClassType::Symbiote,
        ClassType::Warden,
        ClassType::Reanimator
    };
    return choices;
}

const std::array<Color, 4>& TitleFlow::visorChoices() {
    static constexpr std::array<Color, 4> choices{
        Color{65, 115, 220, 255},
        Color{65, 225, 220, 255},
        Color{245, 105, 145, 255},
        Color{250, 205, 90, 255}
    };
    return choices;
}

TitleAction TitleFlow::handleKey(SDL_Keycode key) {
    m_message.clear();

    if (!m_creatingCharacter) {
        if (key == SDLK_UP || key == SDLK_W) {
            m_selectedSlot = (m_selectedSlot + static_cast<int>(m_slots.size()) - 1) %
                             static_cast<int>(m_slots.size());
        } else if (key == SDLK_DOWN || key == SDLK_S) {
            m_selectedSlot = (m_selectedSlot + 1) % static_cast<int>(m_slots.size());
        } else if (key == SDLK_ESCAPE) {
            return {TitleActionKind::Quit, 0};
        } else if (key == SDLK_RETURN || key == SDLK_KP_ENTER) {
            const int slotNumber = getSelectedSlotNumber();
            switch (m_slots[m_selectedSlot].state) {
                case TitleSlotState::Empty:
                    m_creatingCharacter = true;
                    m_selectedClass = 0;
                    m_selectedVisor = 0;
                    m_character = TitleCharacterChoice{};
                    break;
                case TitleSlotState::Ready:
                    return {TitleActionKind::Resume, slotNumber};
                case TitleSlotState::Corrupt:
                    m_message = "SAVE UNREADABLE - SELECT ANOTHER SLOT";
                    break;
            }
        }
        return {};
    }

    if (key == SDLK_ESCAPE) {
        m_creatingCharacter = false;
        return {};
    }
    if (key == SDLK_LEFT) {
        m_selectedClass = (m_selectedClass + static_cast<int>(classChoices().size()) - 1) %
                          static_cast<int>(classChoices().size());
        m_character.classType = classChoices()[m_selectedClass];
    } else if (key == SDLK_RIGHT) {
        m_selectedClass = (m_selectedClass + 1) % static_cast<int>(classChoices().size());
        m_character.classType = classChoices()[m_selectedClass];
    } else if (key == SDLK_V) {
        m_selectedVisor = (m_selectedVisor + 1) % static_cast<int>(visorChoices().size());
        m_character.visorColor = visorChoices()[m_selectedVisor];
    } else if (key == SDLK_RETURN || key == SDLK_KP_ENTER) {
        return {TitleActionKind::NewGame, getSelectedSlotNumber()};
    }
    return {};
}

void TitleFlow::setMessage(std::string message) {
    m_message = std::move(message);
}
