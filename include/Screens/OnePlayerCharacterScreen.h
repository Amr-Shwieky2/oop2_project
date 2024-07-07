#pragma once
#include "CharacterSelectionScreen.h"

// Class representing the character selection screen for one player
class OnePlayerCharacterScreen : public CharacterSelectionScreen {
public:
    OnePlayerCharacterScreen(); // Constructor

    Screens_m handleEvents(sf::RenderWindow& window) override; // Handle events for the one player character selection screen

private:
    int m_selectedCharacterIndex; // Index of the selected character
    void updateSelection(); // Update character selection
};
