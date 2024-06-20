#pragma once
#include <SFML/Graphics.hpp>

class HeartGift {
public:
    HeartGift(float startX, float startY);
    void draw(sf::RenderWindow& window);
    void resetPosition(float x, float y);
    sf::Vector2f getPosition() const;
    sf::FloatRect getGlobalBounds() const;

private:
    sf::RectangleShape HeartGiftShape;
    float appearanceInterval; // Time interval for the black hole to appear
};