#pragma once

#include "Platform.h"

class BreakablePlatform : public Platform
{
public:
    BreakablePlatform(float x, float y);

    void update(float deltaTime) override;
    void breakPlatform();
    bool isBroken() const;

    void restoreState(float x, float y, bool broken);

private:
    bool m_isBrokenPlatform;
};


