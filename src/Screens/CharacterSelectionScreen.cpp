#include "CharacterSelectionScreen.h"
#include "LoadingManager.h"
#include <iostream>

// Constructor to initialize the character selection screen
CharacterSelectionScreen::CharacterSelectionScreen(Screens_m screenTexture, const std::vector<sf::FloatRect>& characterBounds, const sf::FloatRect& textInputBounds)
    : m_characterBounds(characterBounds),
    m_textInputBounds1(textInputBounds),
    m_textInputBounds2(727, 379, 154, 29) {
    try {
        m_screen.setTexture(*(LoadingManager::instance().getScreen(screenTexture)));
    }
    catch (const GameException& e) {
        std::cerr << "Error setting texture in CharacterSelectionScreen: " << e.what() << std::endl;
        throw; // Rethrow the exception after logging it
    }

    m_selectionRectangle1.setOutlineThickness(5);
    m_selectionRectangle1.setFillColor(sf::Color::Transparent);
    m_selectionRectangle1.setOutlineColor(sf::Color::Red);

    m_selectionRectangle2.setOutlineThickness(5);
    m_selectionRectangle2.setFillColor(sf::Color::Transparent);
    m_selectionRectangle2.setOutlineColor(sf::Color::Blue);

    try {
        if (!m_font.loadFromFile("arial.ttf")) {
            throw GameException("Error loading font");
        }
    }
    catch (const GameException& e) {
        std::cerr << "Error loading font: " << e.what() << std::endl;
        throw;
    }

    m_playerNameText1.setFont(m_font);
    m_playerNameText1.setCharacterSize(24);
    m_playerNameText1.setFillColor(sf::Color::White);
    m_playerNameText1.setPosition(m_textInputBounds1.left, m_textInputBounds1.top);

    m_playerNameText2.setFont(m_font);
    m_playerNameText2.setCharacterSize(24);
    m_playerNameText2.setFillColor(sf::Color::White);
    m_playerNameText2.setPosition(m_textInputBounds2.left, m_textInputBounds2.top);

    std::vector<sf::Vector2f> positions = { sf::Vector2f(440, 496), sf::Vector2f(200, 430) }; // Positions for texts and rectangles
    std::string menuItems[] = { "BACK", "PRESS ENTER TO START THE GAME" };
    for (int i = 0; i < 2; ++i) {
        sf::Text text(menuItems[i], m_font, 28);
        text.setPosition(positions[i]);
        text.setFillColor(sf::Color::White);
        m_Texts.push_back(text);
    }

    m_Rectangle.setSize(sf::Vector2f(150, 30));
    m_Rectangle.setPosition(405, 500); // Set position
    m_Rectangle.setOutlineThickness(5);
    m_Rectangle.setFillColor(sf::Color::Red); // Color
    m_Rectangle.setOutlineColor(sf::Color::White);
}

// Render the character selection screen
void CharacterSelectionScreen::render(sf::RenderWindow& window) {
    try {
        window.draw(m_screen);
        window.draw(m_selectionRectangle1);
        window.draw(m_selectionRectangle2);
        window.draw(m_playerNameText1);
        window.draw(m_playerNameText2);
        window.draw(m_Rectangle);
        for (const auto& text : m_Texts) {
            window.draw(text);
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error rendering CharacterSelectionScreen: " << e.what() << std::endl;
        throw;
    }
    catch (...) {
        std::cerr << "Unknown error rendering CharacterSelectionScreen" << std::endl;
        throw;
    }
}

// Update character selection
void CharacterSelectionScreen::updateSelection(sf::RectangleShape& selectionRectangle, const sf::FloatRect& characterBounds) {
    try {
        selectionRectangle.setPosition(characterBounds.left, characterBounds.top);
        selectionRectangle.setSize(sf::Vector2f(characterBounds.width, characterBounds.height));
    }
    catch (const std::exception& e) {
        std::cerr << "Error updating selection: " << e.what() << std::endl;
        throw;
    }
    catch (...) {
        std::cerr << "Unknown error updating selection" << std::endl;
        throw;
    }
}
