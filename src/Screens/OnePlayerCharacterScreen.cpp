#include "OnePlayerCharacterScreen.h"
#include <iostream>

// Constructor to initialize the one player character selection screen
OnePlayerCharacterScreen::OnePlayerCharacterScreen()
    : CharacterSelectionScreen(C1_m, {
        {19, 88, 171, 224},
        {252, 89, 164, 215},
        {471, 98, 175, 212},
        {711, 88, 177, 220}
        }, { 456, 382, 226, 29 }),
    m_selectedCharacterIndex(0) {
    updateSelection();
}

// Handle events for the one player character selection screen
Screens_m OnePlayerCharacterScreen::handleEvents(sf::RenderWindow& window) {
    sf::Event event;
    while (window.pollEvent(event)) {
        try {
            switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::Right) {
                    m_selectedCharacterIndex = (m_selectedCharacterIndex + 1) % 4;
                    Singleton::instance().getSoundManager().playSound("characters");
                    updateSelection();
                }
                else if (event.key.code == sf::Keyboard::Left) {
                    m_selectedCharacterIndex = (m_selectedCharacterIndex + 3) % 4;
                    Singleton::instance().getSoundManager().playSound("characters");
                    updateSelection();
                }
                else if (event.key.code == sf::Keyboard::Enter) {
                    Singleton::instance().setPlayerName1(m_playerName1);
                    Singleton::instance().setPlayerCharacter1(m_selectedCharacterIndex);
                    m_playerNameText1.setString("");
                    return GAME_m;
                }
                break;
            case sf::Event::TextEntered:
                if (event.text.unicode == '\b' && !m_playerName1.empty()) {
                    m_playerName1.pop_back();
                }
                else if (event.text.unicode < 128 && event.text.unicode != '\b') {
                    m_playerName1 += static_cast<char>(event.text.unicode);
                    Singleton::instance().getSoundManager().playSound("names");
                }
                m_playerNameText1.setString(m_playerName1);
                break;
            case sf::Event::MouseButtonReleased:
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePos(event.mouseButton.x, event.mouseButton.y);
                    if (m_Rectangle.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                        Singleton::instance().getSoundManager().playSound("click"); // Play click sound
                        return PLAY_GAME_m; // Return to menu screen
                    }
                }
                break;
            }
        }
        catch (const std::exception& e) {
            std::cerr << "Error handling events in OnePlayerCharacterScreen: " << e.what() << std::endl;
            throw;
        }
        catch (...) {
            std::cerr << "Unknown error handling events in OnePlayerCharacterScreen" << std::endl;
            throw;
        }
    }
    return C1_m;
}

// Update character selection
void OnePlayerCharacterScreen::updateSelection() {
    try {
        CharacterSelectionScreen::updateSelection(m_selectionRectangle1, m_characterBounds[m_selectedCharacterIndex]);
    }
    catch (const std::exception& e) {
        std::cerr << "Error updating selection in OnePlayerCharacterScreen: " << e.what() << std::endl;
        throw;
    }
    catch (...) {
        std::cerr << "Unknown error updating selection in OnePlayerCharacterScreen" << std::endl;
        throw;
    }
}
