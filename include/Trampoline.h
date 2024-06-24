#pragma once
#include <SFML/Graphics.hpp>
#include "Platform.h"  // Ensure this include is correct

class Trampoline {
public:
    Trampoline(float startX, float startY);
    void draw(sf::RenderWindow& window);
    void resetPosition(Platform* platform);

    sf::Vector2f getPosition() const;
    sf::FloatRect getGlobalBounds() const;
    float getEnhancedJumpStrength();

private:
    sf::RectangleShape TrampolineShape;
    float enhancedJumpStrength;
};
