#pragma once
#include "CharacterSelectionScreen.h"

// Class representing the character selection screen for two players
class TwoPlayerCharacterScreen : public CharacterSelectionScreen {
public:
    TwoPlayerCharacterScreen(); // Constructor

    Screens_m handleEvents(sf::RenderWindow& window) override; // Handle events for the two player character selection screen

private:
    void updateSelection(); // Update character selection
    int m_selectedCharacterIndex1; // Index of the selected character for player 1
    int m_selectedCharacterIndex2; // Index of the selected character for player 2

    bool m_isPlayerOneDone; // Flag indicating if player 1 has finished selecting
    bool m_isPlayerTwoDone; // Flag indicating if player 2 has finished selecting
};
