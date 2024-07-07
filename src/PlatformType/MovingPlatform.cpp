#include "MovingPlatform.h"
#include <iostream>

// Constructor implementation
MovingPlatform::MovingPlatform(float x, float y)
    : Platform(x, y, Type::MOVING), m_direction(1.0f), m_speed(200.0f) { // Increased speed
    try {
        // Any additional initialization can go here
    }
    catch (const std::exception& e) {
        std::cerr << "Error initializing MovingPlatform: " << e.what() << std::endl;
        throw;
    }
    catch (...) {
        std::cerr << "Unknown error initializing MovingPlatform" << std::endl;
        throw;
    }
}

// Update moving platform state
void MovingPlatform::update(float deltaTime) {
    try {
        float moveAmount = m_direction * m_speed * deltaTime;
        m_platformShape.move(moveAmount, 0);

        if (m_platformShape.getPosition().x < 0 || m_platformShape.getPosition().x + m_platformShape.getSize().x > 800) {
            m_direction *= -1; // Reverse direction
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error updating MovingPlatform: " << e.what() << std::endl;
        throw;
    }
    catch (...) {
        std::cerr << "Unknown error updating MovingPlatform" << std::endl;
        throw;
    }
}

// Restore the state of the moving platform
void MovingPlatform::restoreState(float x, float y, bool broken, float direction, float speed) {
    try {
        Platform::restoreState(x, y, broken);
        m_direction = direction;
        m_speed = speed;
    }
    catch (const std::exception& e) {
        std::cerr << "Error restoring state of MovingPlatform: " << e.what() << std::endl;
        throw;
    }
    catch (...) {
        std::cerr << "Unknown error restoring state of MovingPlatform" << std::endl;
        throw;
    }
}
