#pragma once
#include "BaseScreen.h"
#include "Singleton.h"
#include "GameException.h"
#include <string>
#include <SFML/Graphics.hpp>

class CharacterScreen : public BaseScreen {
public:
    CharacterScreen(Screens_m returnScreen);
    Screens_m handleEvents(sf::RenderWindow& window) override;
    void render(sf::RenderWindow& window) override;

private:
    sf::Sprite m_screen;
    sf::RectangleShape m_selectionRectangle;
    sf::Text m_playerNameText;
    sf::Font m_font;
    std::string m_playerName;//////saves the name for character
    sf::FloatRect m_characterBounds[4];
    int m_selectedCharacterIndex;///////saves the number for character
    sf::FloatRect m_textInputBounds;
    Screens_m m_returnScreen;

    void updateSelection();
};
