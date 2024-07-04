#pragma once

#include "MovingPlatform.h"
#include "BreakablePlatform.h"

class MovingBreakablePlatform : public MovingPlatform, public BreakablePlatform {
public:
    MovingBreakablePlatform(float x, float y);

    void update(float deltaTime) override;
    void breakPlatform();
    bool isBroken() const;

    void restoreState(float x, float y, bool broken, float direction, float speed);
};
