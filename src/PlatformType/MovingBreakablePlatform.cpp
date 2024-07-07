#include "MovingBreakablePlatform.h"
#include <iostream>

// Constructor implementation
MovingBreakablePlatform::MovingBreakablePlatform(float x, float y)
    : Platform(x, y, Type::MOVING_BREAKABLE), MovingPlatform(x, y), BreakablePlatform(x, y) {
    try {
        m_platformShape.setFillColor(sf::Color(255, 0, 0)); // RGB for red to differentiate
    }
    catch (const std::exception& e) {
        std::cerr << "Error initializing MovingBreakablePlatform: " << e.what() << std::endl;
        throw;
    }
    catch (...) {
        std::cerr << "Unknown error initializing MovingBreakablePlatform" << std::endl;
        throw;
    }
}

// Update moving breakable platform state
void MovingBreakablePlatform::update(float deltaTime) {
    try {
        MovingPlatform::update(deltaTime);
        if (m_isBrokenPlatform) {
            m_broken = true;
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error updating MovingBreakablePlatform: " << e.what() << std::endl;
        throw;
    }
    catch (...) {
        std::cerr << "Unknown error updating MovingBreakablePlatform" << std::endl;
        throw;
    }
}

// Break the platform
void MovingBreakablePlatform::breakPlatform() {
    try {
        m_isBrokenPlatform = true;
    }
    catch (const std::exception& e) {
        std::cerr << "Error breaking MovingBreakablePlatform: " << e.what() << std::endl;
        throw;
    }
    catch (...) {
        std::cerr << "Unknown error breaking MovingBreakablePlatform" << std::endl;
        throw;
    }
}

// Check if the platform is broken
bool MovingBreakablePlatform::isBroken() const {
    try {
        return BreakablePlatform::isBroken();
    }
    catch (const std::exception& e) {
        std::cerr << "Error checking if MovingBreakablePlatform is broken: " << e.what() << std::endl;
        throw;
    }
    catch (...) {
        std::cerr << "Unknown error checking if MovingBreakablePlatform is broken" << std::endl;
        throw;
    }
}

// Restore the state of the moving breakable platform
void MovingBreakablePlatform::restoreState(float x, float y, bool broken, float direction, float speed) {
    try {
        MovingPlatform::restoreState(x, y, broken, direction, speed);
        m_isBrokenPlatform = broken;
    }
    catch (const std::exception& e) {
        std::cerr << "Error restoring state of MovingBreakablePlatform: " << e.what() << std::endl;
        throw;
    }
    catch (...) {
        std::cerr << "Unknown error restoring state of MovingBreakablePlatform" << std::endl;
        throw;
    }
}
