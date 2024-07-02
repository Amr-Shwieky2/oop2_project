#include "Bat.h"
#include "Player.h"

// Constructor implementation
Bat::Bat(float startX, float startY):MovableObject(startX, startY, BAT_a)
{
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

sf::FloatRect Bat::getBounds() const
{
    return m_sprite.getGlobalBounds();
}

void Bat::onCollision(Collidable& other) {
    if (dynamic_cast<Player*>(&other)) {
        other.onCollision(*this);
    }
}

void Bat::draw(sf::RenderWindow& window)
{
    window.draw(m_sprite);
}


