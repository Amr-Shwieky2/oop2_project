#include "BreakablePlatform.h"

BreakablePlatform::BreakablePlatform(float x, float y)
    : Platform(x, y, Type::BREAKABLE), m_isBroken(false) {
    m_platformShape.setFillColor(sf::Color(0, 0, 255)); // Blue
}

void BreakablePlatform::update(float) {
    if (m_isBroken) {
        m_broken = true; // Mark platform as broken
    }
}

void BreakablePlatform::breakPlatform() {
    m_isBroken = true;
}

bool BreakablePlatform::isBroken() const {
    return m_isBroken;
}

void BreakablePlatform::onCollision(Collidable&) {
    breakPlatform();
}
