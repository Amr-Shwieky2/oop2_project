#pragma once
#include "BaseScreen.h"
#include "Singleton.h"
#include "GameException.h"
#include <string>
#include <SFML/Graphics.hpp>
#include <vector>

// Class representing the character selection screen
class CharacterSelectionScreen : public BaseScreen {
public:
    CharacterSelectionScreen(Screens_m screenTexture, const std::vector<sf::FloatRect>& characterBounds, const sf::FloatRect& textInputBounds);

    void render(sf::RenderWindow& window) override; // Render the character selection screen
    void updateSelection(sf::RectangleShape& selectionRectangle, const sf::FloatRect& characterBounds); // Update character selection

protected:
    sf::Sprite m_screen; // Background sprite for the screen
    sf::RectangleShape m_selectionRectangle1; // Selection rectangle for player 1
    sf::RectangleShape m_selectionRectangle2; // Selection rectangle for player 2
    sf::Text m_playerNameText1; // Text for player 1 name input
    sf::Text m_playerNameText2; // Text for player 2 name input
    sf::Font m_font; // Font for the text

    std::string m_playerName1; // Player 1 name
    std::string m_playerName2; // Player 2 name

    sf::FloatRect m_textInputBounds1; // Bounds for player 1 name input
    sf::FloatRect m_textInputBounds2; // Bounds for player 2 name input
    std::vector<sf::FloatRect> m_characterBounds; // Bounds for character selection
    sf::RectangleShape m_Rectangle; // Rectangle shape for UI elements
    std::vector<sf::Text> m_Texts; // Texts for UI elements
};
