#include "Trampoline.h"
#include "Trampoline.h"

Trampoline::Trampoline(float startX, float startY) : enhancedJumpStrength(-25.0f) {  // More negative for a higher jump
    TrampolineShape.setSize(sf::Vector2f(50, 50));  // Size can be adjusted
    TrampolineShape.setFillColor(sf::Color::Green);  // Visually distinctive color
    TrampolineShape.setPosition(startX, startY);
}

void Trampoline::draw(sf::RenderWindow& window) {
    window.draw(TrampolineShape);
}

void Trampoline::resetPosition(float x, float y) {
    TrampolineShape.setPosition(x, y);
}

sf::Vector2f Trampoline::getPosition() const {
    return TrampolineShape.getPosition();
}

sf::FloatRect Trampoline::getGlobalBounds() const {
    return TrampolineShape.getGlobalBounds();
}

float Trampoline::getEnhancedJumpStrength()
{
    return enhancedJumpStrength;
}
