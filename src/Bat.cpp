#include "Bat.h"

Bat::Bat(float startX, float startY)
    : StaticObject(startX, startY, "BAT_a"), m_speed(100.0f) {}

void Bat::update(float deltaTime) {
    float movement = m_speed * deltaTime;
    m_sprite.move(movement, 0);

    if (m_sprite.getPosition().x > 800) {
        m_sprite.setPosition(-40, m_sprite.getPosition().y);
    }
}

void Bat::onCollision(Collidable& other) {
    if (dynamic_cast<Player*>(&other)) {
        other.onCollision(*this);
    }
}
