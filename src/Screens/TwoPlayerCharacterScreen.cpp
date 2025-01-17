#include "TwoPlayerCharacterScreen.h"
#include <iostream>

// Constructor to initialize the two player character selection screen
TwoPlayerCharacterScreen::TwoPlayerCharacterScreen()
    : CharacterSelectionScreen(C2_m, {
         {19, 88, 171, 224},
         {252, 89, 164, 215},
         {471, 98, 175, 212},
         {711, 88, 177, 220}
        }, { 232, 387, 155, 25 }),
    m_selectedCharacterIndex1(0),
    m_selectedCharacterIndex2(3),
    m_isPlayerOneDone(false),
    m_isPlayerTwoDone(false) {
    updateSelection();
}

// Handle events for the two player character selection screen
Screens_m TwoPlayerCharacterScreen::handleEvents(sf::RenderWindow& window) {
    sf::Event event;
    while (window.pollEvent(event)) {
        try {
            switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::Right) {
                    if (!m_isPlayerOneDone) {
                        m_selectedCharacterIndex1 = (m_selectedCharacterIndex1 + 1) % 4;
                        Singleton::instance().getSoundManager().playSound("characters");
                    }
                    else if (!m_isPlayerTwoDone) {
                        m_selectedCharacterIndex2 = (m_selectedCharacterIndex2 + 1) % 4;
                        Singleton::instance().getSoundManager().playSound("characters");
                    }
                    updateSelection();
                }
                else if (event.key.code == sf::Keyboard::Left) {
                    if (!m_isPlayerOneDone) {
                        m_selectedCharacterIndex1 = (m_selectedCharacterIndex1 + 3) % 4;
                        Singleton::instance().getSoundManager().playSound("characters");
                    }
                    else if (!m_isPlayerTwoDone) {
                        m_selectedCharacterIndex2 = (m_selectedCharacterIndex2 + 3) % 4;
                        Singleton::instance().getSoundManager().playSound("characters");
                    }
                    updateSelection();
                }
                else if (event.key.code == sf::Keyboard::Enter) {
                    if (!m_isPlayerOneDone) {
                        m_isPlayerOneDone = true;
                        Singleton::instance().setPlayerName1(m_playerName1);
                        Singleton::instance().setPlayerCharacter1(m_selectedCharacterIndex1);
                    }
                    else if (!m_isPlayerTwoDone) {
                        m_isPlayerTwoDone = true;
                        Singleton::instance().setPlayerName2(m_playerName2);
                        Singleton::instance().setPlayerCharacter2(m_selectedCharacterIndex2);
                        m_playerNameText1.setString("");
                        m_playerNameText2.setString("");
                        return GAME_FOR_TWO_m;
                    }
                }
                break;
            case sf::Event::TextEntered:
                if (!m_isPlayerOneDone) {
                    if (event.text.unicode == '\b' && !m_playerName1.empty()) {
                        m_playerName1.pop_back();
                    }
                    else if (event.text.unicode < 128 && event.text.unicode != '\b') {
                        m_playerName1 += static_cast<char>(event.text.unicode);
                        Singleton::instance().getSoundManager().playSound("names");
                    }
                    m_playerNameText1.setString(m_playerName1);
                }
                else if (!m_isPlayerTwoDone) {
                    if (event.text.unicode == '\b' && !m_playerName2.empty()) {
                        m_playerName2.pop_back();
                    }
                    else if (event.text.unicode < 128 && event.text.unicode != '\b') {
                        m_playerName2 += static_cast<char>(event.text.unicode);
                        Singleton::instance().getSoundManager().playSound("names");
                    }
                    m_playerNameText2.setString(m_playerName2);
                }
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
            std::cerr << "Error handling events in TwoPlayerCharacterScreen: " << e.what() << std::endl;
            throw;
        }
        catch (...) {
            std::cerr << "Unknown error handling events in TwoPlayerCharacterScreen" << std::endl;
            throw;
        }
    }
    return C2_m;
}

// Update character selection
void TwoPlayerCharacterScreen::updateSelection() {
    try {
        CharacterSelectionScreen::updateSelection(m_selectionRectangle1, m_characterBounds[m_selectedCharacterIndex1]);
        CharacterSelectionScreen::updateSelection(m_selectionRectangle2, m_characterBounds[m_selectedCharacterIndex2]);
    }
    catch (const std::exception& e) {
        std::cerr << "Error updating selection in TwoPlayerCharacterScreen: " << e.what() << std::endl;
        throw;
    }
    catch (...) {
        std::cerr << "Unknown error updating selection in TwoPlayerCharacterScreen" << std::endl;
        throw;
    }
}
