#include "MovableObject.h"

MovableObject::MovableObject(float startX, float startY,
	const GameEffects& textureKey) 
{
    setTexture(textureKey);
    m_sprite.setPosition(startX, startY);
}

MovableObject::MovableObject(const Characters& textureKey)
{
    setTexture(textureKey);
}

// Draw BlackHole on the screen
void MovableObject::draw(sf::RenderWindow& window)
{
    window.draw(m_sprite);
}

// Reset BlackHole's position to appear again
void MovableObject::resetPosition(float x, float y)
{
    m_sprite.setPosition(x, y);
}

sf::Vector2f MovableObject::getPosition() const
{
    return m_sprite.getPosition();
}

void MovableObject::setTexture(const GameEffects& textureKey)
{
    m_sprite.setTexture(*(LoadingManager::instance().getEffect(textureKey)));
    m_sprite.setScale(0.15f, 0.15f);
};

void MovableObject::setTexture(const Characters& textureKey)
{
    m_sprite.setTexture(*(LoadingManager::instance().getCharacter(textureKey)));
    m_sprite.setScale(0.15f, 0.15f);
};

