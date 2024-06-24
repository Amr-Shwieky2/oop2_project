#include "BreakablePlatform.h"

BreakablePlatform::BreakablePlatform(float x, float y)
    : Platform(x, y, Type::BREAKABLE), isBrokenPlatform(false)
{}

void BreakablePlatform::update(float deltaTime)
{
    if (isBrokenPlatform)
    {
        broken = true;
    }
    static_cast<void>(deltaTime);
}

void BreakablePlatform::breakPlatform()
{
    isBrokenPlatform = true;
}

bool BreakablePlatform::isBroken() const
{
    return isBrokenPlatform;
}
