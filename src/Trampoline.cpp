#include "Trampoline.h"

Trampoline::Trampoline(float startX, float startY) : m_enhancedJumpStrength(-25.0f) {
    m_trampolineShape.setTexture(*(Singleton::instance().getEffect(TRAMPOLINE_a)));
    m_trampolineShape.setPosition(startX, startY);

    // Get the size of the texture
    sf::Vector2u textureSize = m_trampolineShape.getTexture()->getSize();

    // Desired size in pixels
    float desiredWidth = 100.0f;
    float desiredHeight = 100.0f;

    // Calculate the scale factors
    float scaleX = desiredWidth / textureSize.x;
    float scaleY = desiredHeight / textureSize.y;

    m_trampolineShape.setScale(scaleX, scaleY);
}

void Trampoline::draw(sf::RenderWindow& window) {
    window.draw(m_trampolineShape);
}

void Trampoline::resetPosition(Platform* platform) {
    if (platform != nullptr) {
        sf::FloatRect bounds = platform->getBounds();
        float x = bounds.left + (bounds.width - m_trampolineShape.getGlobalBounds().width) / 2;
        float y = bounds.top - m_trampolineShape.getGlobalBounds().height;
        m_trampolineShape.setPosition(x, y);
    }
}

sf::Vector2f Trampoline::getPosition() const {
    return m_trampolineShape.getPosition();
}

sf::FloatRect Trampoline::getGlobalBounds() const {
    return m_trampolineShape.getGlobalBounds();
}

float Trampoline::getEnhancedJumpStrength() const {
    return m_enhancedJumpStrength;
}
