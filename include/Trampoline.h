#pragma once

#include <SFML/Graphics.hpp>

class Trampoline {
public:
    Trampoline(float startX, float startY);

    void draw(sf::RenderWindow& window);
    void resetPosition(float x, float y);

    sf::Vector2f getPosition() const;
    sf::FloatRect getGlobalBounds() const;
    float getEnhancedJumpStrength();
private:
    sf::RectangleShape TrampolineShape;
    float enhancedJumpStrength;  // Increased jump strength when the player hits the trampoline
};
