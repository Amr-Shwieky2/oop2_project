#include "Platform.h"

Platform::Platform(float x, float y, Type type)
    : m_type(type), m_broken(false) {
    m_platformShape.setSize(sf::Vector2f(60, 15));
    m_platformShape.setFillColor(sf::Color(100, 255, 100));
    m_platformShape.setPosition(x, y);
}

void Platform::draw(sf::RenderWindow& window) {
    if (!m_broken)
        window.draw(m_platformShape);
}

void Platform::update(float deltaTime) {
    static_cast<void>(deltaTime);
}

void Platform::resetPosition(float x, float y) {
    m_sprite.setPosition(x, y);
}

sf::FloatRect Platform::getBounds() const {
    return m_platformShape.getGlobalBounds();
}

bool Platform::isBreakable() const {
    return m_type == Type::BREAKABLE;
}

void Platform::onCollision(Collidable&) {
    // No specific collision response for basic platforms
}
