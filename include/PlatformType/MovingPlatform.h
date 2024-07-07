#pragma once

#include "Platform.h"

// Class representing a moving platform in the game
class MovingPlatform : public virtual Platform {
public:
    MovingPlatform(float x, float y); // Constructor

    void update(float deltaTime) override; // Update moving platform state
    void restoreState(float x, float y, bool broken, float direction, float speed); // Restore the state of the moving platform

protected:
    float m_direction; // Direction of movement
    float m_speed; // Speed of movement
};
