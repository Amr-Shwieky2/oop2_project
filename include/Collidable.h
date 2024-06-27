#pragma once

#include "GameObject.h"

class Collidable : public GameObject {
public:
    virtual void onCollision(Collidable& other) = 0;
    virtual bool checkCollision(Collidable& other) 
    { return this->getBounds().intersects(other.getBounds()); };
};
