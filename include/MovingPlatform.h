#ifndef MOVING_PLATFORM_H
#define MOVING_PLATFORM_H

#include "Platform.h"

class MovingPlatform : public Platform
{
public:
    MovingPlatform(float x, float y);

    void update(float deltaTime) override;

private:
    float direction;
    float speed;
};

#endif
