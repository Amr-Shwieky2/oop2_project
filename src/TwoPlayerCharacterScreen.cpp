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
    m_textInputBounds2(727, 379, 154, 29) {

    try {
        m_screen.setTexture(*(Singleton::instance().getScreen(C2_m)));
    }
    catch (const GameException& e) {
        std::cerr << "Error setting texture in TwoPlayerCharacterScreen: " << e.what() << std::endl;
        throw;  // Rethrow the exception after logging it
    }

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

    if (!m_font.loadFromFile("arial.ttf")) { // Make sure to replace with the path to your font file
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

Screens_m TwoPlayerCharacterScreen::handleEvents(sf::RenderWindow& window)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            window.close();
            return m_returnScreen;
        case sf::Event::KeyPressed:
            if (event.key.code == sf::Keyboard::Right) // Choosing character
            {

                if (!m_isPlayerOneDone)
                {
                    Singleton::instance().getSoundManager().playSound("characters");
                    m_selectedCharacterIndex1 = (m_selectedCharacterIndex1 + 1) % 4;
                }
                else if (!m_isPlayerTwoDone)
                {
                    Singleton::instance().getSoundManager().playSound("characters");
                    m_selectedCharacterIndex2 = (m_selectedCharacterIndex2 + 1) % 4;
                }
                updateSelection();
            }
            else if (event.key.code == sf::Keyboard::Left)
            {

                if (!m_isPlayerOneDone)
                {
                    Singleton::instance().getSoundManager().playSound("characters");
                    m_selectedCharacterIndex1 = (m_selectedCharacterIndex1 + 3) % 4; // +3 instead of -1 to handle negative modulus
                }
                else if (!m_isPlayerTwoDone)
                {
                    Singleton::instance().getSoundManager().playSound("characters");
                    m_selectedCharacterIndex2 = (m_selectedCharacterIndex2 + 3) % 4; // +3 instead of -1 to handle negative modulus
                }
                updateSelection();
            }
            else if (event.key.code == sf::Keyboard::Enter)
            {
                if (!m_isPlayerOneDone)
                {
                    m_isPlayerOneDone = true;
                }
                else if (!m_isPlayerTwoDone)
                {
                    m_isPlayerTwoDone = true;
                }
            }
            break;

        case sf::Event::TextEntered:
            if (!m_isPlayerOneDone)
            {
                Singleton::instance().getSoundManager().playSound("names");

                if (event.text.unicode == '\b' && !m_playerName1.empty())
                {
                    m_playerName1.pop_back();
                }
                else if (event.text.unicode < 128 && event.text.unicode != '\b')
                {
                    m_playerName1 += static_cast<char>(event.text.unicode);
                }
                m_playerNameText1.setString(m_playerName1);
            }
            else if (!m_isPlayerTwoDone)
            {
                Singleton::instance().getSoundManager().playSound("names");

                if (event.text.unicode == '\b' && !m_playerName2.empty())
                {
                    m_playerName2.pop_back();
                }
                else if (event.text.unicode < 128 && event.text.unicode != '\b')
                {
                    m_playerName2 += static_cast<char>(event.text.unicode);
                }
                m_playerNameText2.setString(m_playerName2);
            }
            break;
        }
    }
    return m_returnScreen;
}


void TwoPlayerCharacterScreen::render(sf::RenderWindow& window) {
    window.draw(m_screen);
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
