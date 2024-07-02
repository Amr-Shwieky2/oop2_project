#include "BlackHole.h"
#include "Player.h"

// Constructor implementation
BlackHole::BlackHole(float startX, float startY) 
    : m_appearanceInterval(10.0f), StaticObject(startX, startY, HOLE_a)
{
    
}


void BlackHole::onCollision(Collidable& other)
{
    if (dynamic_cast<Player*>(&other)) {
        other.onCollision(*this);
    }
}

void BlackHole::draw(sf::RenderWindow& window)
{
    window.draw(m_sprite);

}

sf::FloatRect BlackHole::getBounds() const
{
    return m_sprite.getGlobalBounds();
}
