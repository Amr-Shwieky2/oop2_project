#pragma once
#include "CharacterSelectionScreen.h"

class OnePlayerCharacterScreen : public CharacterSelectionScreen {
public:
    OnePlayerCharacterScreen();

    Screens_m handleEvents(sf::RenderWindow& window) override;

private:
    int m_selectedCharacterIndex;
    void updateSelection();
};
