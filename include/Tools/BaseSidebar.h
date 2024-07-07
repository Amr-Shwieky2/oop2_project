#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "LoadingManager.h"

class BaseSidebar {
public:
    BaseSidebar(float width, float height);
    virtual ~BaseSidebar() = default;

    virtual void update(int, int) {};
    virtual void draw(sf::RenderWindow& window) = 0;
    bool isPaused(sf::Vector2i mousePos);

protected:
    sf::RectangleShape m_background;
    sf::Text m_scoreText;
    sf::Text m_pauseText;
    sf::RectangleShape m_pauseButton;
    std::vector<sf::Sprite> m_livesSprites;
    sf::Texture m_lifeTexture;
    sf::Font m_font;
    float m_sidebarWidth;
    float m_sidebarHeight;
};
