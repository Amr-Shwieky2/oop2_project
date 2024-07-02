#include "Bat.h"
#include "Player.h"

// Constructor implementation
Bat::Bat(float startX, float startY)
{
    m_sprite.setTexture(*(Singleton::instance().getEffect(BAT_a)));
    m_sprite.setPosition(startX, startY);
    // Get the size of the texture
    sf::Vector2u textureSize = m_sprite.getTexture()->getSize();

    // Desired size in pixels
    float desiredWidth = 100.0f;
    float desiredHeight = 100.0f;

    // Calculate the scale factors
    float scaleX = desiredWidth / textureSize.x;
    float scaleY = desiredHeight / textureSize.y;

    m_sprite.setScale(scaleX, scaleY);
}

// Draw Bat on the screen
void Bat::draw(sf::RenderWindow& window)
{
    window.draw(m_sprite);
}

// Update Bat's position
void Bat::update(float deltaTime)
{
    //left-to-right movement
    float movement = m_speed * deltaTime;
    m_sprite.move(movement, 0);

    // Reset position if it moves off-screen
    if (m_sprite.getPosition().x > 800)
    {
        m_sprite.setPosition(-40, m_sprite.getPosition().y);
    }
}

// Reset Bat's position to appear again
void Bat::resetPosition(float x, float y)
{
    m_sprite.setPosition(x, y);
}

sf::Vector2f Bat::getPosition() const
{
    return m_sprite.getPosition();
}

sf::FloatRect Bat::getBounds() const
{
    return m_sprite.getGlobalBounds();
}

void Bat::onCollision(Collidable& other) {
    if (dynamic_cast<Player*>(&other)) {
        other.onCollision(*this);
    }
}
