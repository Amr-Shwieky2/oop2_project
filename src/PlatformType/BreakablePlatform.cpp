#include "BreakablePlatform.h"
#include <iostream>

// Constructor implementation
BreakablePlatform::BreakablePlatform(float x, float y)
    : Platform(x, y, Type::BREAKABLE), m_isBrokenPlatform(false) {
    try {
        m_platformShape.setFillColor(sf::Color(0, 0, 255)); // RGB for blue
    }
    catch (const std::exception& e) {
        std::cerr << "Error initializing BreakablePlatform: " << e.what() << std::endl;
        throw;
    }
    catch (...) {
        std::cerr << "Unknown error initializing BreakablePlatform" << std::endl;
        throw;
    }
}

// Update breakable platform state
void BreakablePlatform::update(float) {
    try {
        if (m_isBrokenPlatform) {
            m_broken = true;
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error updating BreakablePlatform: " << e.what() << std::endl;
        throw;
    }
    catch (...) {
        std::cerr << "Unknown error updating BreakablePlatform" << std::endl;
        throw;
    }
}

// Break the platform
void BreakablePlatform::breakPlatform() {
    try {
        m_isBrokenPlatform = true;
    }
    catch (const std::exception& e) {
        std::cerr << "Error breaking BreakablePlatform: " << e.what() << std::endl;
        throw;
    }
    catch (...) {
        std::cerr << "Unknown error breaking BreakablePlatform" << std::endl;
        throw;
    }
}

// Check if the platform is broken
bool BreakablePlatform::isBroken() const {
    try {
        return m_isBrokenPlatform;
    }
    catch (const std::exception& e) {
        std::cerr << "Error checking if BreakablePlatform is broken: " << e.what() << std::endl;
        throw;
    }
    catch (...) {
        std::cerr << "Unknown error checking if BreakablePlatform is broken" << std::endl;
        throw;
    }
}

// Restore the state of the breakable platform
void BreakablePlatform::restoreState(float x, float y, bool broken) {
    try {
        Platform::restoreState(x, y, broken);
        m_isBrokenPlatform = broken;
    }
    catch (const std::exception& e) {
        std::cerr << "Error restoring state of BreakablePlatform: " << e.what() << std::endl;
        throw;
    }
    catch (...) {
        std::cerr << "Unknown error restoring state of BreakablePlatform" << std::endl;
        throw;
    }
}
