#include "Collidable.h"

bool Collidable::checkCollision(Collidable& other)
{
	return this->getBounds().intersects(other.getBounds());
}
void Collidable::setTexture(const GameEffects& textureKey)
{
    m_sprite.setTexture(*(Singleton::instance().getEffect(textureKey)));

    sf::Vector2u textureSize = m_sprite.getTexture()->getSize();
    float scaleX = 100.0f / textureSize.x;
    float scaleY = 100.0f / textureSize.y;
    m_sprite.setScale(scaleX, scaleY);
}


void Collidable::draw(sf::RenderWindow& window) {
    window.draw(m_sprite);
}

void Collidable::update(float) {
    // Default implementation does nothing
}

void Collidable::resetPosition(float x, float y) {
    m_sprite.setPosition(x, y);
}

sf::FloatRect Collidable::getBounds() const {
    return m_sprite.getGlobalBounds();
}

sf::Vector2f Collidable::getPosition() const
{
    return m_sprite.getPosition();
}
