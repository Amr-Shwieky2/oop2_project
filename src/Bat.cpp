#include "Bat.h"
// Constructor implementation
Bat::Bat(float startX, float startY)
{
    m_batShape.setTexture(*(Singleton::instance().getEffect(BAT_a)));
    m_batShape.setPosition(startX, startY);
    // Get the size of the texture
    sf::Vector2u textureSize = m_batShape.getTexture()->getSize();

    // Desired size in pixels
    float desiredWidth = 100.0f;
    float desiredHeight = 100.0f;

    // Calculate the scale factors
    float scaleX = desiredWidth / textureSize.x;
    float scaleY = desiredHeight / textureSize.y;

    m_batShape.setScale(scaleX, scaleY);
}

// Draw Bat on the screen
void Bat::draw(sf::RenderWindow& window)
{
    window.draw(m_batShape);
}

// Update Bat's position
void Bat::update(float deltaTime)
{
    //left-to-right movement
    float movement = m_speed * deltaTime;
    m_batShape.move(movement, 0);

    // Reset position if it moves off-screen
    if (m_batShape.getPosition().x > 800)
    {
        m_batShape.setPosition(-40, m_batShape.getPosition().y);
    }
}

// Reset Bat's position to appear again
void Bat::resetPosition(float x, float y)
{
    m_batShape.setPosition(x, y);
}

sf::Vector2f Bat::getPosition() const
{
    return m_batShape.getPosition();
}

sf::FloatRect Bat::getGlobalBounds() const
{
    return m_batShape.getGlobalBounds();
}