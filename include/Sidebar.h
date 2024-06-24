#ifndef SIDEBAR_H
#define SIDEBAR_H

#include <SFML/Graphics.hpp>
#include <vector>

class Sidebar {
public:
    Sidebar(float width, float height);

    void update(int score, int height, int lives);
    void draw(sf::RenderWindow& window);
    bool isPaused(sf::Vector2i mousePos);
private:
    sf::RectangleShape m_background;
    sf::Text m_scoreText;
    sf::Text m_heightText;
    sf::Text m_pauseText;
    sf::RectangleShape m_pauseButton;
    std::vector<sf::RectangleShape> m_livesRects;

    sf::Font m_font;
    float m_sidebarWidth;
    float m_sidebarHeight;
};

#endif // SIDEBAR_H
