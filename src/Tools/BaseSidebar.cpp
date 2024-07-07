#include "BaseSidebar.h"
#include <iostream>

BaseSidebar::BaseSidebar(float width, float height)
    : m_sidebarWidth(width), m_sidebarHeight(height)
{
    try {
        if (!m_font.loadFromFile("arial.ttf")) {
            std::cerr << "Couldn't load the font!" << std::endl;
            std::exit(-1);
        }

        if (!m_lifeTexture.loadFromFile("heart.png")) {
            std::cerr << "Couldn't load the heart texture!" << std::endl;
            std::exit(-1);
        }

        m_background.setSize(sf::Vector2f(width, height));
        m_background.setFillColor(sf::Color(178, 34, 34));  // Dark fiery red

        m_scoreText.setFont(m_font);
        m_scoreText.setCharacterSize(24);
        m_scoreText.setFillColor(sf::Color::Black);

        m_pauseButton.setSize(sf::Vector2f(70, 30));
        m_pauseButton.setFillColor(sf::Color::Transparent);
        m_pauseButton.setOutlineThickness(5);
        m_pauseButton.setOutlineColor(sf::Color::Black);  // Outline color for better visibility  

        m_pauseText.setFont(m_font);
        m_pauseText.setString("PAUSE");
        m_pauseText.setCharacterSize(24);
        m_pauseText.setFillColor(sf::Color::Black);
    }
    catch (const std::exception& e) {
        std::cerr << "Error initializing Sidebar: " << e.what() << std::endl;
        std::exit(-1);
    }
    catch (...) {
        std::cerr << "Unknown error initializing Sidebar" << std::endl;
        std::exit(-1);
    }
}



bool BaseSidebar::isPaused(sf::Vector2i mousePos)
{
    return m_pauseButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos));
}
