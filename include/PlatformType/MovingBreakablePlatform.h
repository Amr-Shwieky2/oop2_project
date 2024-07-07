#pragma once

#include "MovingPlatform.h"
#include "BreakablePlatform.h"

// Class representing a moving breakable platform in the game
class MovingBreakablePlatform : public MovingPlatform, public BreakablePlatform {
public:
    MovingBreakablePlatform(float x, float y); // Constructor

    void update(float deltaTime) override; // Update moving breakable platform state
    void breakPlatform(); // Break the platform
    bool isBroken() const; // Check if the platform is broken

    void restoreState(float x, float y, bool broken, float direction, float speed); // Restore the state of the moving breakable platform
};
