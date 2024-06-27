#pragma once
#include "BaseScreen.h"
#include "Singleton.h"
#include <SFML/Graphics.hpp>
#include <vector>

class CharacterSelectionScreen : public BaseScreen {
public:
    CharacterSelectionScreen(Screens_m screenTexture, const std::vector<sf::FloatRect>& characterBounds, const sf::FloatRect& textInputBounds);
    void render(sf::RenderWindow& window) override;
    void updateSelection(sf::RectangleShape& selectionRectangle, const sf::FloatRect& characterBounds);

protected:
    sf::Sprite m_screen;
    sf::RectangleShape m_selectionRectangle1;
    sf::RectangleShape m_selectionRectangle2;
    sf::Text m_playerNameText1;
    sf::Text m_playerNameText2;
    sf::Font m_font;

    std::string m_playerName1;
    std::string m_playerName2;

    sf::FloatRect m_textInputBounds1;
    sf::FloatRect m_textInputBounds2;
    std::vector<sf::FloatRect> m_characterBounds;
};
