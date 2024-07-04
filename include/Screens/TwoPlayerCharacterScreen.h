#pragma once
#include "CharacterSelectionScreen.h"

class TwoPlayerCharacterScreen : public CharacterSelectionScreen {
public:
    TwoPlayerCharacterScreen();

    Screens_m handleEvents(sf::RenderWindow& window) override;

private:
    void updateSelection();
    int m_selectedCharacterIndex1;
    int m_selectedCharacterIndex2;

    bool m_isPlayerOneDone;
    bool m_isPlayerTwoDone;
};
