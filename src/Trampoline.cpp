#include "Trampoline.h"

Trampoline::Trampoline(float startX, float startY) : enhancedJumpStrength(-25.0f) {
    TrampolineShape.setSize(sf::Vector2f(50, 50));
    TrampolineShape.setFillColor(sf::Color::Green);
    TrampolineShape.setPosition(startX, startY);
}

void Trampoline::draw(sf::RenderWindow& window) {
    window.draw(TrampolineShape);
}

void Trampoline::resetPosition(Platform* platform) {
    if (platform != nullptr) {
        sf::FloatRect bounds = platform->getBounds();
        float x = bounds.left + (bounds.width - TrampolineShape.getSize().x) / 2;
        float y = bounds.top - TrampolineShape.getSize().y;
        TrampolineShape.setPosition(x, y);
    }  // Ensure this closing brace matches the opening brace for the 'if' statement
}


sf::Vector2f Trampoline::getPosition() const {
    return TrampolineShape.getPosition();
}

sf::FloatRect Trampoline::getGlobalBounds() const {
    return TrampolineShape.getGlobalBounds();
}

float Trampoline::getEnhancedJumpStrength() {
    return enhancedJumpStrength;
}
