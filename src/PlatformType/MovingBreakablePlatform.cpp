#include "MovingBreakablePlatform.h"

MovingBreakablePlatform::MovingBreakablePlatform(float x, float y)
    : Platform(x, y, Type::MOVING_BREAKABLE), MovingPlatform(x, y), BreakablePlatform(x, y)
{
    m_platformShape.setFillColor(sf::Color(255, 0, 0)); // RGB for red to differentiate
}

void MovingBreakablePlatform::update(float deltaTime) {
    MovingPlatform::update(deltaTime);
    if (m_isBrokenPlatform) {
        m_broken = true;
    }
}

void MovingBreakablePlatform::breakPlatform() {
    m_isBrokenPlatform = true;
}

bool MovingBreakablePlatform::isBroken() const {
    return BreakablePlatform::isBroken();
}

void MovingBreakablePlatform::restoreState(float x, float y, bool broken, float direction, float speed) {
    MovingPlatform::restoreState(x, y, broken, direction, speed);
    m_isBrokenPlatform = broken;
}
