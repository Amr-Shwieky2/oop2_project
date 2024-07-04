#pragma once

#include "Platform.h"

class MovingPlatform : public virtual Platform
{
public:
    MovingPlatform(float x, float y);

    void update(float deltaTime) override;
    void restoreState(float x, float y, bool broken, float direction, float speed);

protected:
    float m_direction;
    float m_speed;
};
