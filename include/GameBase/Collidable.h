#pragma once

#include "Singleton.h"

class Collidable {
public:
    Collidable() = default;
    virtual ~Collidable() = default;

    virtual void draw(sf::RenderWindow& window) = 0;
    virtual void onCollision(Collidable& other) = 0;
    virtual sf::FloatRect getBounds() const = 0;
    virtual bool checkCollision(Collidable& other) 
    { return this->getBounds().intersects(other.getBounds()); };
    
};