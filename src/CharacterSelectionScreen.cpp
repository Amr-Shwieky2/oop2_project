#include "CharacterSelectionScreen.h"
#include <iostream>

CharacterSelectionScreen::CharacterSelectionScreen
 (Screens_m screenTexture,
     const std::vector<sf::FloatRect>& characterBounds,
    const sf::FloatRect& textInputBounds)
    : m_characterBounds(characterBounds), 
    m_textInputBounds1(textInputBounds),
    m_textInputBounds2(727, 379, 154, 29)
{

    try {
        m_screen.setTexture(*(Singleton::instance().getScreen(screenTexture)));
    }
    catch (const GameException& e) {
        std::cerr << "Error setting texture in CharacterSelectionScreen: " << e.what() << std::endl;
        throw;  // Rethrow the exception after logging it
    }

    m_selectionRectangle1.setOutlineThickness(5);
    m_selectionRectangle1.setFillColor(sf::Color::Transparent);
    m_selectionRectangle1.setOutlineColor(sf::Color::Red);

    m_selectionRectangle2.setOutlineThickness(5);
    m_selectionRectangle2.setFillColor(sf::Color::Transparent);
    m_selectionRectangle2.setOutlineColor(sf::Color::Blue);

    if (!m_font.loadFromFile("arial.ttf")) {
        throw GameException("Error loading font");
    }

    m_playerNameText1.setFont(m_font);
    m_playerNameText1.setCharacterSize(24);
    m_playerNameText1.setFillColor(sf::Color::White);
    m_playerNameText1.setPosition(m_textInputBounds1.left, m_textInputBounds1.top);

    m_playerNameText2.setFont(m_font);
    m_playerNameText2.setCharacterSize(24);
    m_playerNameText2.setFillColor(sf::Color::White);
    m_playerNameText2.setPosition(m_textInputBounds2.left, m_textInputBounds2.top);
}

void CharacterSelectionScreen::render(sf::RenderWindow& window) {
    window.draw(m_screen);
    window.draw(m_selectionRectangle1);
    window.draw(m_selectionRectangle2);
    window.draw(m_playerNameText1);
    window.draw(m_playerNameText2);
}

void CharacterSelectionScreen::updateSelection(sf::RectangleShape& selectionRectangle, const sf::FloatRect& characterBounds) {
    selectionRectangle.setPosition(characterBounds.left, characterBounds.top);
    selectionRectangle.setSize(sf::Vector2f(characterBounds.width, characterBounds.height));
}
