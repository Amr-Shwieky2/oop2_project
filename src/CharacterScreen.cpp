#include "CharacterScreen.h"
#include <iostream>

CharacterScreen::CharacterScreen(Screens_m returnScreen) :
    m_selectedCharacterIndex(0),
    m_returnScreen(returnScreen),
    m_characterBounds{
        {19, 88, 171, 224},
        {252, 89, 164, 215},
        {471, 98, 175, 212},
        {711, 88, 177, 220}
    },
    m_textInputBounds(456, 382, 226, 29) {

    try {
        if (m_returnScreen == C1_m) {
            m_screen.setTexture(*(Singleton::instance().getScreen(C1_m)));
        }
        else {
            m_screen.setTexture(*(Singleton::instance().getScreen(C2_m)));
        }
    }
    catch (const GameException& e) {
        std::cerr << "Error setting texture: " << e.what() << std::endl;
        throw;  // Rethrow the exception after logging it
    }

    m_selectionRectangle.setSize(sf::Vector2f(m_characterBounds[0].width, m_characterBounds[0].height));
    m_selectionRectangle.setOutlineThickness(5);
    m_selectionRectangle.setOutlineColor(sf::Color::Red);
    m_selectionRectangle.setFillColor(sf::Color::Transparent);
    m_selectionRectangle.setPosition(m_characterBounds[m_selectedCharacterIndex].left, m_characterBounds[m_selectedCharacterIndex].top);

    if (!m_font.loadFromFile("arial.ttf")) { // Make sure to replace with the path to your font file
        throw GameException("Error loading font");
    }
    m_playerNameText.setFont(m_font);
    m_playerNameText.setCharacterSize(24);
    m_playerNameText.setFillColor(sf::Color::White);
    m_playerNameText.setPosition(m_textInputBounds.left, m_textInputBounds.top);
}

Screens_m CharacterScreen::handleEvents(sf::RenderWindow& window) {
    sf::Event event;
    while (window.pollEvent(event)) {
        switch (event.type) {
        case sf::Event::Closed:
            window.close();
            return m_returnScreen;  // or a specific screen type for closing
        case sf::Event::KeyPressed:
            if (event.key.code == sf::Keyboard::Right) {
                m_selectedCharacterIndex = (m_selectedCharacterIndex + 1) % 4;
                updateSelection();
            }
            else if (event.key.code == sf::Keyboard::Left) {
                m_selectedCharacterIndex = (m_selectedCharacterIndex + 3) % 4; // +3 instead of -1 to handle negative modulus
                updateSelection();
            }
            break;
        case sf::Event::TextEntered:
            if (event.text.unicode == '\b' && !m_playerName.empty()) {
                m_playerName.pop_back();
            }
            else if (event.text.unicode < 128 && event.text.unicode != '\b') {
                m_playerName += static_cast<char>(event.text.unicode);
            }
            m_playerNameText.setString(m_playerName);
            break;
        }
    }
    return m_returnScreen;
}

void CharacterScreen::render(sf::RenderWindow& window) {
    window.draw(m_screen);
    window.draw(m_selectionRectangle);
    window.draw(m_playerNameText);
}

void CharacterScreen::updateSelection() {
    m_selectionRectangle.setPosition(m_characterBounds[m_selectedCharacterIndex].left, m_characterBounds[m_selectedCharacterIndex].top);
    m_selectionRectangle.setSize(sf::Vector2f(m_characterBounds[m_selectedCharacterIndex].width, m_characterBounds[m_selectedCharacterIndex].height));
}
