#include "StaticObject.h"

StaticObject::StaticObject(float startX, float startY, const GameEffects& textureKey) {
    setTexture(textureKey);
    m_sprite.setPosition(startX, startY);
}

void StaticObject::draw(sf::RenderWindow& window) {
    window.draw(m_sprite);
}

void StaticObject::resetPosition(float x, float y) {
    m_sprite.setPosition(x, y);
}

sf::Vector2f StaticObject::getPosition() const {
    return m_sprite.getPosition();
}

void StaticObject::setTexture(const GameEffects& textureKey) {
    m_sprite.setTexture(*(LoadingManager::instance().getEffect(textureKey)));
    m_sprite.setScale(0.15f, 0.15f);
}

std::string StaticObject::getType() const {
    return "StaticObject"; // You can adjust this to return specific types like "HeartGift", "BlackHole", etc.
}
