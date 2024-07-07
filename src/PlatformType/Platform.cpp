#include "Platform.h"
#include <iostream>

// Constructor implementation
Platform::Platform(float x, float y, Type type)
    : m_type(type), m_broken(false) {
    try {
        m_platformShape.setSize(sf::Vector2f(60, 15));
        m_platformShape.setFillColor(sf::Color(100, 255, 100));
        m_platformShape.setPosition(x, y);
    }
    catch (const std::exception& e) {
        std::cerr << "Error initializing Platform: " << e.what() << std::endl;
        throw;
    }
    catch (...) {
        std::cerr << "Unknown error initializing Platform" << std::endl;
        throw;
    }
}

// Update platform state
void Platform::update(float) {}

// Draw the platform
void Platform::draw(sf::RenderWindow& window) {
    try {
        if (!m_broken)
            window.draw(m_platformShape);
    }
    catch (const std::exception& e) {
        std::cerr << "Error drawing Platform: " << e.what() << std::endl;
        throw;
    }
    catch (...) {
        std::cerr << "Unknown error drawing Platform" << std::endl;
        throw;
    }
}

// Get the bounds of the platform
sf::FloatRect Platform::getBounds() const {
    try {
        return m_platformShape.getGlobalBounds();
    }
    catch (const std::exception& e) {
        std::cerr << "Error getting bounds of Platform: " << e.what() << std::endl;
        throw;
    }
    catch (...) {
        std::cerr << "Unknown error getting bounds of Platform" << std::endl;
        throw;
    }
}

// Check if the platform is breakable
bool Platform::isBreakable() const {
    try {
        return m_type == Type::BREAKABLE;
    }
    catch (const std::exception& e) {
        std::cerr << "Error checking if Platform is breakable: " << e.what() << std::endl;
        throw;
    }
    catch (...) {
        std::cerr << "Unknown error checking if Platform is breakable" << std::endl;
        throw;
    }
}

// Get the position of the platform
sf::Vector2f Platform::getPosition() const {
    try {
        return m_platformShape.getPosition();
    }
    catch (const std::exception& e) {
        std::cerr << "Error getting position of Platform: " << e.what() << std::endl;
        throw;
    }
    catch (...) {
        std::cerr << "Unknown error getting position of Platform" << std::endl;
        throw;
    }
}

// Get the type of the platform
Platform::Type Platform::getType() const {
    try {
        return m_type;
    }
    catch (const std::exception& e) {
        std::cerr << "Error getting type of Platform: " << e.what() << std::endl;
        throw;
    }
    catch (...) {
        std::cerr << "Unknown error getting type of Platform" << std::endl;
        throw;
    }
}

// Get the type of the platform as a string
std::string Platform::getTypeAsString() const {
    try {
        switch (m_type) {
        case Type::NORMAL:
            return "NORMAL";
        case Type::MOVING:
            return "MOVING";
        case Type::BREAKABLE:
            return "BREAKABLE";
        case Type::MOVING_BREAKABLE:
            return "MOVING_BREAKABLE";
        default:
            return "UNKNOWN";
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error getting type of Platform as string: " << e.what() << std::endl;
        throw;
    }
    catch (...) {
        std::cerr << "Unknown error getting type of Platform as string" << std::endl;
        throw;
    }
}

// Restore the state of the platform
void Platform::restoreState(float x, float y, bool broken) {
    try {
        m_platformShape.setPosition(x, y);
        m_broken = broken;
    }
    catch (const std::exception& e) {
        std::cerr << "Error restoring state of Platform: " << e.what() << std::endl;
        throw;
    }
    catch (...) {
        std::cerr << "Unknown error restoring state of Platform" << std::endl;
        throw;
    }
}
