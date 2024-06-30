#include "TwoPlayerCharacterScreen.h"
#include <iostream>

TwoPlayerCharacterScreen::TwoPlayerCharacterScreen(Screens_m returnScreen) :
    m_isPlayerOneDone(false),
    m_isPlayerTwoDone(false),
    m_returnScreen(returnScreen),
    m_selectedCharacterIndex1(0),
    m_selectedCharacterIndex2(0),
    m_characterBounds{
        {19, 88, 171, 224},
        {252, 89, 164, 215},
        {471, 98, 175, 212},
        {711, 88, 177, 220}
    },
    m_textInputBounds1(232, 387, 155, 25),
    m_textInputBounds2(727, 379, 154, 29)
{
    m_screen.setTexture(*(Singleton::instance().getScreen(C2_m)));

    m_selectionRectangle1.setSize(sf::Vector2f(m_characterBounds[0].width, m_characterBounds[0].height));
    m_selectionRectangle1.setOutlineThickness(5);
    m_selectionRectangle1.setOutlineColor(sf::Color::Red);
    m_selectionRectangle1.setFillColor(sf::Color::Transparent);
    m_selectionRectangle1.setPosition(m_characterBounds[m_selectedCharacterIndex1].left, m_characterBounds[m_selectedCharacterIndex1].top);

    m_selectionRectangle2.setSize(sf::Vector2f(m_characterBounds[0].width, m_characterBounds[0].height));
    m_selectionRectangle2.setOutlineThickness(5);
    m_selectionRectangle2.setOutlineColor(sf::Color::Blue);
    m_selectionRectangle2.setFillColor(sf::Color::Transparent);
    m_selectionRectangle2.setPosition(m_characterBounds[m_selectedCharacterIndex2].left, m_characterBounds[m_selectedCharacterIndex2].top);

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

     

    std::vector<sf::Vector2f> positions = { sf::Vector2f(440, 496), sf::Vector2f(280, 430) }; // Positions for texts and rectangles
    std::string menuItems[] = { "BACK" ,  "PRESS ENTER TO START THE GAME" };
    for (int i = 0; i < 2; ++i) {
        sf::Text text(menuItems[i], m_font, 28);
        sf::FloatRect textBounds = text.getLocalBounds();
        text.setPosition(positions[i]);
        text.setFillColor(sf::Color::White);
        m_Texts.push_back(text);
    }
    m_Rectangle.setSize(sf::Vector2f(150, 30));
    m_Rectangle.setPosition(405, 500); // Set position
    m_Rectangle.setOutlineThickness(5);
    m_Rectangle.setFillColor(sf::Color::Red);  // Color
    m_Rectangle.setOutlineColor(sf::Color::White);  // Outline color for better visibility  
}

Screens_m TwoPlayerCharacterScreen::handleEvents(sf::RenderWindow& window)
{
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
        case sf::Event::MouseButtonReleased:
            if (event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePos(event.mouseButton.x, event.mouseButton.y);
                if (m_Rectangle.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                    Singleton::instance().getSoundManager().playSound("click"); // Play click sound
                    return PLAY_GAME_m;  // Return to menu screen
                }
            }
            break;
        }
        
    }
    return C2_m;
}

void TwoPlayerCharacterScreen::render(sf::RenderWindow& window) 
{
    window.draw(m_screen);
    window.draw(m_Rectangle);
    for (size_t i = 0; i < m_Texts.size(); ++i) {
        window.draw(m_Texts[i]);

    }
    window.draw(m_selectionRectangle1);
    window.draw(m_selectionRectangle2);
    window.draw(m_playerNameText1);
    window.draw(m_playerNameText2);

}

void TwoPlayerCharacterScreen::updateSelection() {
    m_selectionRectangle1.setPosition(m_characterBounds[m_selectedCharacterIndex1].left, m_characterBounds[m_selectedCharacterIndex1].top);
    m_selectionRectangle1.setSize(sf::Vector2f(m_characterBounds[m_selectedCharacterIndex1].width, m_characterBounds[m_selectedCharacterIndex1].height));

    m_selectionRectangle2.setPosition(m_characterBounds[m_selectedCharacterIndex2].left, m_characterBounds[m_selectedCharacterIndex2].top);
    m_selectionRectangle2.setSize(sf::Vector2f(m_characterBounds[m_selectedCharacterIndex2].width, m_characterBounds[m_selectedCharacterIndex2].height));
}


//the handle is good but the rectangles of the back needs to be better 