#include "BlackHole.h"

// Constructor implementation
BlackHole::BlackHole(float startX, float startY) : m_appearanceInterval(10.0f)
{
    m_blackHoleShape.setTexture(*(Singleton::instance().getEffect(HOLE_a)));
    m_blackHoleShape.setPosition(startX, startY);

    // Get the size of the texture
    sf::Vector2u textureSize = m_blackHoleShape.getTexture()->getSize();

    // Desired size in pixels
    float desiredWidth = 100.0f;
    float desiredHeight = 100.0f;

    //// Calculate the scale factors
    //float scaleX = desiredWidth / textureSize.x;
    //float scaleY = desiredHeight / textureSize.y;

    //m_blackHoleShape.setScale(scaleX, scaleY);
    m_blackHoleShape.setScale(0.15f, 0.15f);

}

// Draw BlackHole on the screen
void BlackHole::draw(sf::RenderWindow& window)
{
    window.draw(m_blackHoleShape);
}

// Reset BlackHole's position to appear again
void BlackHole::resetPosition(float x, float y)
{
    m_blackHoleShape.setPosition(x, y);
}

sf::Vector2f BlackHole::getPosition() const
{
    return m_blackHoleShape.getPosition();
}

sf::FloatRect BlackHole::getGlobalBounds() const
{
    return m_blackHoleShape.getGlobalBounds();
}
