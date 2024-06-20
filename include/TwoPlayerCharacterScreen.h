#pragma once

#include <SFML/Graphics.hpp>
#include "Singleton.h"
#include "Screens.h"
#include "GameException.h"
#include "BaseScreen.h"
#include <vector>

class TwoPlayerCharacterScreen : public BaseScreen 
{
public:
    TwoPlayerCharacterScreen(Screens_m returnScreen);

    Screens_m handleEvents(sf::RenderWindow& window) override;
    void render(sf::RenderWindow& window) override;

private:
    void updateSelection();

    Screens_m m_returnScreen;

    int m_selectedCharacterIndex1;
    int m_selectedCharacterIndex2;

    sf::RectangleShape m_selectionRectangle1; ////saves the number for character1
    sf::RectangleShape m_selectionRectangle2; ////saves the number for character2

    std::string m_playerName1;////saves the name for character2
    std::string m_playerName2;////saves the name for character2

    sf::Text m_playerNameText1;
    sf::Text m_playerNameText2;

    sf::FloatRect m_textInputBounds1;
    sf::FloatRect m_textInputBounds2;

    sf::Sprite m_screen;
    sf::Font m_font;

    std::vector<sf::FloatRect> m_characterBounds;
    
    bool m_isPlayerOneDone;
    bool m_isPlayerTwoDone;
};
