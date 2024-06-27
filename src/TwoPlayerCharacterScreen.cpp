#include "TwoPlayerCharacterScreen.h"
#include <iostream>

TwoPlayerCharacterScreen::TwoPlayerCharacterScreen()
    : CharacterSelectionScreen(C2_m, {
        {19, 88, 171, 224},
        {252, 89, 164, 215},
        {471, 98, 175, 212},
        {711, 88, 177, 220}
        }, { 232, 387, 155, 25 }),
    m_selectedCharacterIndex1(0),
    m_selectedCharacterIndex2(0),
    m_isPlayerOneDone(false),
    m_isPlayerTwoDone(false)
    {

    updateSelection();
}

Screens_m TwoPlayerCharacterScreen::handleEvents(sf::RenderWindow& window) {
    sf::Event event;
    while (window.pollEvent(event)) {
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
                }
                else if (!m_isPlayerTwoDone) {
                    m_isPlayerTwoDone = true;
                    Singleton::instance().setPlayerName2(m_playerName2);
                    return GAME_m;
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
        }
    }
    return C2_m;
}

void TwoPlayerCharacterScreen::updateSelection() {
    CharacterSelectionScreen::updateSelection(m_selectionRectangle1, m_characterBounds[m_selectedCharacterIndex1]);
    CharacterSelectionScreen::updateSelection(m_selectionRectangle2, m_characterBounds[m_selectedCharacterIndex2]);
}
