//#include "TwoplayerSidebar.h"
//#include <iostream>
//
//TwoplayerSidebar::TwoplayerSidebar(float width, float height)
//    : m_sidebarWidth(width), m_sidebarHeight(height)
//{
//    if (!m_font.loadFromFile("arial.ttf")) {
//        std::cerr << "Couldn't load the font!" << std::endl;
//        std::exit(-1);
//    }
//
//    if (!m_lifeTexture.loadFromFile("heart.png")) {
//        std::cerr << "Couldn't load the heart texture!" << std::endl;
//        std::exit(-1);
//    }
//
//    m_background.setSize(sf::Vector2f(width, height));
//    m_background.setFillColor(sf::Color(178, 34, 34));  // Dark fiery red
//
//    m_scoreText.setFont(m_font);
//    m_scoreText.setCharacterSize(24);
//    m_scoreText.setFillColor(sf::Color::Black);
//
//    m_pauseButton.setSize(sf::Vector2f(70, 30));
//    m_pauseButton.setFillColor(sf::Color::Transparent);
//    m_pauseButton.setOutlineThickness(5);
//    m_pauseButton.setOutlineColor(sf::Color::Black);  // Outline color for better visibility  
//
//
//    m_pauseText.setFont(m_font);
//    m_pauseText.setString("PAUSE");
//    m_pauseText.setCharacterSize(24);
//    m_pauseText.setFillColor(sf::Color::Black);
//}
//
//void TwoplayerSidebar::update(int score, int height, int lives)
//{
//    m_scoreText.setString("Score: " + std::to_string(score));
//
//    m_livesSprites.clear();
//    for (int i = 0; i < lives; ++i)
//    {
//        sf::Sprite lifeSprite;
//        lifeSprite.setTexture(m_lifeTexture);
//        lifeSprite.setScale(0.1f, 0.1f);  // Scale down the heart image to 10% of its original size
//        lifeSprite.setPosition(static_cast<float>(300 + i * 50), 0.f);
//        m_livesSprites.push_back(lifeSprite);
//    }
//
//    m_background.setPosition(0, 0);
//    m_scoreText.setPosition(10, 10);
//    m_pauseButton.setPosition(700, 10);
//    m_pauseText.setPosition(705, 12);
//}
//
//void TwoplayerSidebar::draw(sf::RenderWindow& window)
//{
//    window.draw(m_background);
//    window.draw(m_scoreText);
//    window.draw(m_pauseButton);
//    window.draw(m_pauseText);
//    for (auto& sprite : m_livesSprites)
//    {
//        window.draw(sprite);
//    }
//}
//
//bool TwoplayerSidebar::isPaused(sf::Vector2i mousePos)
//{
//    return m_pauseButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos));
//}