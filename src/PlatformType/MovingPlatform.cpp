#include "MovingPlatform.h"

MovingPlatform::MovingPlatform(float x, float y)
    : Platform(x, y, Type::MOVING), m_direction(1.0f), m_speed(200.0f) // Increased speed
{}

void MovingPlatform::update(float deltaTime)
{
    float moveAmount = m_direction * m_speed * deltaTime;
    m_platformShape.move(moveAmount, 0);

    if (m_platformShape.getPosition().x < 0 || m_platformShape.getPosition().x + m_platformShape.getSize().x > 800)
    {
        m_direction *= -1; // Reverse direction
    }
}

void MovingPlatform::restoreState(float x, float y, bool broken, float direction, float speed)
{
    Platform::restoreState(x, y, broken);
    m_direction = direction;
    m_speed = speed;
}
