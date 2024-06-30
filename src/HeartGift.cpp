#include "HeartGift.h"

HeartGift::HeartGift(float startX, float startY) : m_appearanceInterval(10.0f)
{
    m_heartGiftShape.setTexture(*(Singleton::instance().getEffect(HEART_a)));
    m_heartGiftShape.setPosition(startX, startY);

    // Get the size of the texture
    sf::Vector2u textureSize = m_heartGiftShape.getTexture()->getSize();

    // Desired size in pixels
    float desiredWidth = 100.0f;
    float desiredHeight = 100.0f;

    // Calculate the scale factors
    float scaleX = desiredWidth / textureSize.x;
    float scaleY = desiredHeight / textureSize.y;

   // m_heartGiftShape.setScale(scaleX, scaleY);
    m_heartGiftShape.setScale(0.19f, 0.19f);  

}

void HeartGift::draw(sf::RenderWindow& window)
{
    window.draw(m_heartGiftShape);
}

void HeartGift::resetPosition(float x, float y)
{
    m_heartGiftShape.setPosition(x, y);
}

sf::Vector2f HeartGift::getPosition() const
{
    return m_heartGiftShape.getPosition();
}

sf::FloatRect HeartGift::getGlobalBounds() const
{
    return m_heartGiftShape.getGlobalBounds();
}
