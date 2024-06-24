#ifndef SIDEBAR_H
#define SIDEBAR_H

#include <SFML/Graphics.hpp>
#include <vector>

class Sidebar {
public:
    Sidebar(float width, float height, const sf::Font& font);

    void update(int score, int height, int lives);
    void draw(sf::RenderWindow& window);
    bool isPaused(sf::Vector2i mousePos);
private:
    sf::RectangleShape background;
    sf::Text scoreText;
    sf::Text heightText;
    sf::Text pauseText;
    sf::RectangleShape pauseButton;
    std::vector<sf::RectangleShape> livesRects;

    const sf::Font& font;
    float sidebarWidth;
    float sidebarHeight;
};

#endif // SIDEBAR_H
