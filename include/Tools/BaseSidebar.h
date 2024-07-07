#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

class BaseSidebar {
public:
    BaseSidebar(float width, float height);

    virtual void update(int score, int height, int lives) = 0;
    virtual void draw(sf::RenderWindow& window);
    bool isPaused(sf::Vector2i mousePos);

protected:
    sf::RectangleShape m_background;
    sf::Text m_scoreText;
    sf::Text m_heightText;
    sf::Text m_pauseText;
    sf::RectangleShape m_pauseButton;
    std::vector<sf::Sprite> m_livesSprites;
    sf::Texture m_lifeTexture;
    sf::Font m_font;
    float m_sidebarWidth;
    float m_sidebarHeight;
};