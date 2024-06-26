#pragma once
#include <SFML/Graphics.hpp>
#include "Singleton.h"

class BlackHole {
public:
    BlackHole(float startX, float startY);
    void draw(sf::RenderWindow& window);
    void resetPosition(float x, float y);
    sf::Vector2f getPosition() const;
    sf::FloatRect getGlobalBounds() const;

private:
    sf::Sprite m_blackHoleShape;
    float m_appearanceInterval; // Time interval for the black hole to appear
};