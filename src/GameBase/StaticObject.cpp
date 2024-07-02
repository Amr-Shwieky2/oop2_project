#include "StaticObject.h"

StaticObject::StaticObject(float startX, float startY, const GameEffects& textureKey)
{
    setTexture(textureKey);
    m_sprite.setPosition(startX, startY);
};

// Draw BlackHole on the screen
void StaticObject::draw(sf::RenderWindow& window)
{
    window.draw(m_sprite);
}



// Reset BlackHole's position to appear again
void StaticObject::resetPosition(float x, float y)
{
    m_sprite.setPosition(x, y);
}

sf::Vector2f StaticObject::getPosition() const
{
    return m_sprite.getPosition();
}

void StaticObject::setTexture(const GameEffects& textureKey)
{
    m_sprite.setTexture(*(Singleton::instance().getEffect(textureKey)));
    m_sprite.setScale(0.15f, 0.15f);
};


