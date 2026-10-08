#pragma once

#include "core/Math.hpp"
#include "gameplay/classes/ClassRegistry.hpp"
#include <SDL3/SDL.h>
#include <array>
#include <string>

enum class TitleSlotState {
    Empty,
    Ready,
    Corrupt
};

struct TitleSlotPreview {
    TitleSlotState state{TitleSlotState::Empty};
    std::string playerName;
    std::string className;
    int level{1};
};

struct TitleCharacterChoice {
    std::string name{"Vanguard"};
    ClassType classType{ClassType::Juggernaut};
    Color visorColor{65, 115, 220, 255};
};

enum class TitleActionKind {
    None,
    NewGame,
    Resume,
    Quit
};

struct TitleAction {
    TitleActionKind kind{TitleActionKind::None};
    int slot{0};
};

class TitleFlow {
public:
    explicit TitleFlow(std::array<TitleSlotPreview, 3> slots);

    TitleAction handleKey(SDL_Keycode key);
    void setMessage(std::string message);

    const std::array<TitleSlotPreview, 3>& getSlots() const { return m_slots; }
    int getSelectedSlotIndex() const { return m_selectedSlot; }
    int getSelectedSlotNumber() const { return m_selectedSlot + 1; }
    bool isCreatingCharacter() const { return m_creatingCharacter; }
    const TitleCharacterChoice& getCharacter() const { return m_character; }
    const std::string& getMessage() const { return m_message; }

private:
    static const std::array<ClassType, 9>& classChoices();
    static const std::array<Color, 4>& visorChoices();

    std::array<TitleSlotPreview, 3> m_slots;
    int m_selectedSlot{0};
    int m_selectedClass{0};
    int m_selectedVisor{0};
    bool m_creatingCharacter{false};
    TitleCharacterChoice m_character;
    std::string m_message;
};
