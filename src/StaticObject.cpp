#include "StaticObject.h"

StaticObject::StaticObject(float startX, float startY, const std::string& textureKey) {
    setTexture(textureKey);
    m_sprite.setPosition(startX, startY);
}

void StaticObject::draw(sf::RenderWindow& window) {
    window.draw(m_sprite);
}

void StaticObject::update(float deltaTime) {
    // Default implementation does nothing
}

void StaticObject::resetPosition(float x, float y) {
    m_sprite.setPosition(x, y);
}

sf::FloatRect StaticObject::getBounds() const {
    return m_sprite.getGlobalBounds();
}

void StaticObject::setTexture(const std::string& textureKey) {
    m_sprite.setTexture(*(Singleton::instance().getEffect(textureKey)));

    sf::Vector2u textureSize = m_sprite.getTexture()->getSize();
    float scaleX = 100.0f / textureSize.x;
    float scaleY = 100.0f / textureSize.y;
    m_sprite.setScale(scaleX, scaleY);
}
