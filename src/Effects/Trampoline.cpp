#include "Trampoline.h"
#include "Player.h"
#include <iostream>

// Constructor implementation
Trampoline::Trampoline(float startX, float startY)
    : StaticObject(startX, startY, TRAMPOLINE_a), m_enhancedJumpStrength(-25.0f) {
    try {
        // Any additional initialization can go here
    }
    catch (const std::exception& e) {
        std::cerr << "Error initializing Trampoline: " << e.what() << std::endl;
        throw;
    }
    catch (...) {
        std::cerr << "Unknown error initializing Trampoline" << std::endl;
        throw;
    }
}

// Reset the position of the trampoline based on a platform
void Trampoline::resetPosition(Platform platform) {
    try {
        sf::FloatRect bounds = platform.getBounds();
        float x = bounds.left + (bounds.width - m_sprite.getGlobalBounds().width) / 2;
        float y = bounds.top - m_sprite.getGlobalBounds().height;
        m_sprite.setPosition(x, y);
    }
    catch (const std::exception& e) {
        std::cerr << "Error resetting position of Trampoline: " << e.what() << std::endl;
        throw;
    }
    catch (...) {
        std::cerr << "Unknown error resetting position of Trampoline" << std::endl;
        throw;
    }
}

// Get the bounds of the trampoline
sf::FloatRect Trampoline::getBounds() const {
    try {
        return m_sprite.getGlobalBounds();
    }
    catch (const std::exception& e) {
        std::cerr << "Error getting bounds of Trampoline: " << e.what() << std::endl;
        throw;
    }
    catch (...) {
        std::cerr << "Unknown error getting bounds of Trampoline" << std::endl;
        throw;
    }
}

// Handle collision with another game object
void Trampoline::onCollision(GameObject& other) {
    try {
        if (dynamic_cast<Player*>(&other)) {
            other.onCollision(*this);
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error handling collision in Trampoline: " << e.what() << std::endl;
        throw;
    }
    catch (...) {
        std::cerr << "Unknown error handling collision in Trampoline" << std::endl;
        throw;
    }
}

// Get the enhanced jump strength of the trampoline
float Trampoline::getEnhancedJumpStrength() const {
    try {
        return m_enhancedJumpStrength;
    }
    catch (const std::exception& e) {
        std::cerr << "Error getting enhanced jump strength of Trampoline: " << e.what() << std::endl;
        throw;
    }
    catch (...) {
        std::cerr << "Unknown error getting enhanced jump strength of Trampoline" << std::endl;
        throw;
    }
}

// Draw the trampoline
void Trampoline::draw(sf::RenderWindow& window) {
    try {
        window.draw(m_sprite);
    }
    catch (const std::exception& e) {
        std::cerr << "Error drawing Trampoline: " << e.what() << std::endl;
        throw;
    }
    catch (...) {
        std::cerr << "Unknown error drawing Trampoline" << std::endl;
        throw;
    }
}
