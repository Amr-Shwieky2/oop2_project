#include "Trampoline.h"
#include "Player.h"


Trampoline::Trampoline(float startX, float startY) 
    : m_enhancedJumpStrength(-25.0f), StaticObject(startX, startY, TRAMPOLINE_a) {
}

void Trampoline::resetPosition(Platform platform) {
        sf::FloatRect bounds = platform.getBounds();
        float x = bounds.left + (bounds.width - m_sprite.getGlobalBounds().width) / 2;
        float y = bounds.top - m_sprite.getGlobalBounds().height;
        m_sprite.setPosition(x, y);
}

sf::FloatRect Trampoline::getBounds() const
{
    return m_sprite.getGlobalBounds();
}

void Trampoline::onCollision(GameObject& other)
{
    if (dynamic_cast<Player*>(&other)) {
        other.onCollision(*this);
    }
}

float Trampoline::getEnhancedJumpStrength() const {
    return m_enhancedJumpStrength;
}

void Trampoline::draw(sf::RenderWindow& window)
{
    window.draw(m_sprite);
}
