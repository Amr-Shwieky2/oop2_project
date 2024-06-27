#pragma once

#include "Platform.h"

class MovingPlatform : public Platform {
public:
    MovingPlatform(float x, float y);

    void update(float deltaTime) override;

private:
    float m_direction;
    float m_speed;
};
