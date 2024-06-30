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
        std::cerr << "Error setting texture in CharacterScreen: " << e.what() << std::endl;
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

    std::vector<sf::Vector2f> positions= { sf::Vector2f(440, 496), sf::Vector2f(310, 430) }; // Positions for texts and rectangles
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

Screens_m CharacterScreen::handleEvents(sf::RenderWindow& window) {
    sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type) {
        case sf::Event::Closed:
            window.close();
            return m_returnScreen;  // or a specific screen type for closing
        case sf::Event::KeyPressed:
            if (event.key.code == sf::Keyboard::Right)
            {
                Singleton::instance().getSoundManager().playSound("characters");
                m_selectedCharacterIndex = (m_selectedCharacterIndex + 1) % 4;
                updateSelection();
            }
            else if (event.key.code == sf::Keyboard::Left) {
                Singleton::instance().getSoundManager().playSound("characters");
                m_selectedCharacterIndex = (m_selectedCharacterIndex + 3) % 4; // +3 instead of -1 to handle negative modulus
                updateSelection();
            }
            else if (event.key.code == sf::Keyboard::Enter) {
                std::cout << "Enter key pressed. Returning GAME_m." << std::endl;
                Singleton::instance().setPlayerName1(m_playerName);
                return GAME_m;
            }
            break;
        case sf::Event::TextEntered:
            if (event.text.unicode == '\b' && !m_playerName.empty())
            {
                m_playerName.pop_back();
            }
            else if (event.text.unicode < 128 && event.text.unicode != '\b') {
                Singleton::instance().getSoundManager().playSound("names");
                m_playerName += static_cast<char>(event.text.unicode);
            }
            m_playerNameText.setString(m_playerName);
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
    return m_returnScreen;
}

void CharacterScreen::render(sf::RenderWindow& window) {
    window.draw(m_screen);
    window.draw(m_selectionRectangle);
    window.draw(m_playerNameText);
    window.draw(m_Rectangle);
    for (size_t i = 0; i < m_Texts.size(); ++i) {
        window.draw(m_Texts[i]);

    }
}

void CharacterScreen::updateSelection() {
    m_selectionRectangle.setPosition(m_characterBounds[m_selectedCharacterIndex].left, m_characterBounds[m_selectedCharacterIndex].top);
    m_selectionRectangle.setSize(sf::Vector2f(m_characterBounds[m_selectedCharacterIndex].width, m_characterBounds[m_selectedCharacterIndex].height));
}



//here to  deal with the a d left right  