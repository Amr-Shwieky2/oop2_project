#include "BlackHole.h"
#include "Player.h"
#include <iostream>

// Constructor implementation
BlackHole::BlackHole(float startX, float startY)
    : StaticObject(startX, startY, HOLE_a), m_appearanceInterval(10.0f) {
    try {
        // Any additional initialization can go here
    }
    catch (const std::exception& e) {
        std::cerr << "Error initializing BlackHole: " << e.what() << std::endl;
        throw;
    }
    catch (...) {
        std::cerr << "Unknown error initializing BlackHole" << std::endl;
        throw;
    }
}

// Handle collision with another game object
void BlackHole::onCollision(GameObject& other) {
    try {
        if (dynamic_cast<Player*>(&other)) {
            other.onCollision(*this);
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error handling collision in BlackHole: " << e.what() << std::endl;
        throw;
    }
    catch (...) {
        std::cerr << "Unknown error handling collision in BlackHole" << std::endl;
        throw;
    }
}

// Draw the black hole
void BlackHole::draw(sf::RenderWindow& window) {
    try {
        window.draw(m_sprite);
    }
    catch (const std::exception& e) {
        std::cerr << "Error drawing BlackHole: " << e.what() << std::endl;
        throw;
    }
    catch (...) {
        std::cerr << "Unknown error drawing BlackHole" << std::endl;
        throw;
    }
}

// Get the bounds of the black hole
sf::FloatRect BlackHole::getBounds() const {
    try {
        return m_sprite.getGlobalBounds();
    }
    catch (const std::exception& e) {
        std::cerr << "Error getting bounds of BlackHole: " << e.what() << std::endl;
        throw;
    }
    catch (...) {
        std::cerr << "Unknown error getting bounds of BlackHole" << std::endl;
        throw;
    }
}
