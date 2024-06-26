#pragma once
#include <SFML/Graphics.hpp>
#include "Platform.h"  // Ensure this include is correct
#include "Singleton.h"

class Trampoline {
public:
    Trampoline(float startX, float startY);
    void draw(sf::RenderWindow& window);
    void resetPosition(Platform* platform);

    sf::Vector2f getPosition() const;
    sf::FloatRect getGlobalBounds() const;
    float getEnhancedJumpStrength() const;

private:
    sf::Sprite m_trampolineShape;
    float m_enhancedJumpStrength;
};
