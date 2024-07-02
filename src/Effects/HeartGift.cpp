#include "HeartGift.h"
#include "Player.h"

HeartGift::HeartGift(float startX, float startY) 
    : m_appearanceInterval(10.0f), StaticObject(startX, startY, HEART_a)
{
   
}

sf::FloatRect HeartGift::getBounds() const
{
    return m_sprite.getGlobalBounds();
}

void HeartGift::onCollision(GameObject& other)
{
    if (dynamic_cast<Player*>(&other)) {
        other.onCollision(*this);
    }
}

void HeartGift::draw(sf::RenderWindow& window)
{
    window.draw(m_sprite);
}

