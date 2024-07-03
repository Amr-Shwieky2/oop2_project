#include "BreakablePlatform.h"

BreakablePlatform::BreakablePlatform(float x, float y)
    : Platform(x, y, Type::BREAKABLE), m_isBrokenPlatform(false)
{
    m_platformShape.setFillColor(sf::Color(0, 0, 255)); // RGB for blue
}

void BreakablePlatform::update(float)
{
    if (m_isBrokenPlatform)
    {
        m_broken = true;
    }
}

void BreakablePlatform::breakPlatform()
{
    m_isBrokenPlatform = true;
}

bool BreakablePlatform::isBroken() const
{
    return m_isBrokenPlatform;
}

void BreakablePlatform::restoreState(float x, float y, bool broken)
{
    Platform::restoreState(x, y, broken);
    m_isBrokenPlatform = broken;
}
