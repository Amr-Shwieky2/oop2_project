#include "Trampoline.h"
#include "Player.h"

Trampoline::Trampoline(float startX, float startY)
    : StaticObject(startX, startY, TRAMPOLINE_a), m_enhancedJumpStrength(-25.0f) {}

void Trampoline::onCollision(Collidable& other) {
    if (dynamic_cast<Player*>(&other)) {
        other.onCollision(*this);
    }
}
