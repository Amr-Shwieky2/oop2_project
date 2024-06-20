#pragma once
#include <SFML/Graphics.hpp>

class Bat {
public:
    Bat(float startX, float startY);
    void draw(sf::RenderWindow& window);
    void update(float deltaTime);
    void resetPosition(float x, float y);
    sf::Vector2f getPosition() const;
    sf::FloatRect getGlobalBounds() const;
private:
    sf::RectangleShape BatShape;
    float speed = 100.0f;  // Speed of the bat across the screen
};