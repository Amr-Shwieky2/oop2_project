#include "WingGift.h"
#include "Player.h"


WingGift::WingGift(float startX, float startY) 
    :StaticObject(startX, startY, WINGS_a){
    
}

sf::FloatRect WingGift::getBounds() const {
    return m_sprite.getGlobalBounds();
}

void WingGift::onCollision(Collidable& other)
{
    if (dynamic_cast<Player*>(&other)) {
        other.onCollision(*this);
    }
}
