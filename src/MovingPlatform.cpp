#include "MovingPlatform.h"

MovingPlatform::MovingPlatform(float x, float y)
    : Platform(x, y, Type::MOVING), direction(1.0f), speed(200.0f) // Increased speed
{}

void MovingPlatform::update(float deltaTime)
{
    float moveAmount = direction * speed * deltaTime;
    platformShape.move(moveAmount, 0);

    if (platformShape.getPosition().x < 0 || platformShape.getPosition().x + platformShape.getSize().x > 800)
    {
        direction *= -1; // Reverse direction
    }
}
