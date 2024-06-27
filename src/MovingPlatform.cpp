#include "MovingPlatform.h"

MovingPlatform::MovingPlatform(float x, float y)
    : Platform(x, y, Type::MOVING), m_direction(1.0f), m_speed(100.0f) {}

void MovingPlatform::update(float deltaTime) {
    float moveAmount = m_direction * m_speed * deltaTime;
    m_sprite.move(moveAmount, 0);

    if (m_sprite.getPosition().x < 0 || m_sprite.getPosition().x + m_sprite.getSize().x > 800) {
        m_direction *= -1; // Reverse direction
    }
}
