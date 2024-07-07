#pragma once

#include "Platform.h"

// Class representing a breakable platform in the game
class BreakablePlatform : public virtual Platform {
public:
    BreakablePlatform(float x, float y); // Constructor

    void update(float deltaTime) override; // Update breakable platform state
    void breakPlatform(); // Break the platform
    bool isBroken() const; // Check if the platform is broken

    void restoreState(float x, float y, bool broken); // Restore the state of the breakable platform

protected:
    bool m_isBrokenPlatform; // Flag indicating if the platform is broken
};
