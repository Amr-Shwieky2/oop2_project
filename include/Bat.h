#pragma once

#include "MovableObject.h"

class Bat : public MovableObject
{
public:
    Bat(float startX, float startY);
    void update(float deltaTime) override;
    void onCollision(Collidable& other) override;

private:
    float m_speed;
};
