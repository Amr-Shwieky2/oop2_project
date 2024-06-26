#pragma once
#include <SFML/Graphics.hpp>
#include "Singleton.h"

class Bat {
public:
    Bat(float startX, float startY);
    void draw(sf::RenderWindow& window);
    void update(float deltaTime);
    void resetPosition(float x, float y);
    sf::Vector2f getPosition() const;
    sf::FloatRect getGlobalBounds() const;
private:
    sf::Sprite m_batShape;
    float m_speed = 100.0f;  // Speed of the bat across the screen
};