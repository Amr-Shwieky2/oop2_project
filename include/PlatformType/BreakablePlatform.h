#pragma once

#include "Platform.h"

class BreakablePlatform : public virtual Platform
{
public:
    BreakablePlatform(float x, float y);

    void update(float deltaTime) override;
    void breakPlatform();
    bool isBroken() const;

    void restoreState(float x, float y, bool broken);

protected:
    bool m_isBrokenPlatform;
};
