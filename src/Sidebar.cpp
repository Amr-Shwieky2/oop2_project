#include "Sidebar.h"
#include <iostream>

Sidebar::Sidebar(float width, float height)
    : m_sidebarWidth(width), m_sidebarHeight(height)
{
    if (!m_font.loadFromFile("arial.ttf")) {
        std::cerr << "Couldn't load the font!" << std::endl;
        std::exit(-1);
    }
    m_background.setSize(sf::Vector2f(width, height));
    m_background.setFillColor(sf::Color(150, 150, 150, 255));  // Light grey

    m_scoreText.setFont(m_font);
    m_scoreText.setCharacterSize(24);
    m_scoreText.setFillColor(sf::Color::Black);

    m_heightText.setFont(m_font);
    m_heightText.setCharacterSize(24);
    m_heightText.setFillColor(sf::Color::Black);

    m_pauseButton.setSize(sf::Vector2f(70, 30));
    m_pauseButton.setFillColor(sf::Color::Black);

    m_pauseText.setFont(m_font);
    m_pauseText.setString("PAUSE");
    m_pauseText.setCharacterSize(24);
    m_pauseText.setFillColor(sf::Color::White);
}

void Sidebar::update(int score, int height, int lives)
{
    m_scoreText.setString("Score: " + std::to_string(score));
    if(static_cast<float>(height) >= 0 )
        m_heightText.setString("Height: " + std::to_string(height));
    else
        m_heightText.setString("Height: " + std::to_string(0));


    m_livesRects.clear();
    for (int i = 0; i < lives; ++i)
    {
        sf::RectangleShape life(sf::Vector2f(20, 20));
        life.setFillColor(sf::Color::Red);
        life.setPosition(300 + i * 30, 20);
        m_livesRects.push_back(life);
    }

    m_background.setPosition(0, 0);
    m_scoreText.setPosition(10, 10);
    m_heightText.setPosition(100, 10);
    m_pauseButton.setPosition(700, 10);
    m_pauseText.setPosition(705, 15);
}

void Sidebar::draw(sf::RenderWindow& window)
{
    window.draw(m_background);
    window.draw(m_scoreText);
    window.draw(m_heightText);
    window.draw(m_pauseButton);
    window.draw(m_pauseText);
    for (auto& rect : m_livesRects)
    {
        window.draw(rect);
    }
}

bool Sidebar::isPaused(sf::Vector2i mousePos)
{
    return m_pauseButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos));
}

