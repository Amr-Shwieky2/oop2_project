#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "LoadingManager.h"

class Sidebar {
public:
    Sidebar(float width, float height);

    void update(int score, int lives);
    void draw(sf::RenderWindow& window);
    bool isPaused(sf::Vector2i mousePos);

private:
    sf::RectangleShape m_background;
    sf::Text m_scoreText;
    sf::Text m_pauseText;
    sf::RectangleShape m_pauseButton;
    std::vector<sf::Sprite> m_livesSprites;
    std::vector<high_score> m_highScore;
    sf::Texture m_lifeTexture;
    sf::Font m_font;
    float m_sidebarWidth;
    float m_sidebarHeight;

    int findNextHigherScore(int currentScore);
};
