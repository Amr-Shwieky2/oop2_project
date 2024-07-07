#include "WingGift.h"
#include "Player.h"
#include <iostream>

// Constructor implementation
WingGift::WingGift(float startX, float startY)
    : StaticObject(startX, startY, WINGS_a) {
    try {
        // Any additional initialization can go here
    }
    catch (const std::exception& e) {
        std::cerr << "Error initializing WingGift: " << e.what() << std::endl;
        throw;
    }
    catch (...) {
        std::cerr << "Unknown error initializing WingGift" << std::endl;
        throw;
    }
}

// Get the bounds of the wing gift
sf::FloatRect WingGift::getBounds() const {
    try {
        return m_sprite.getGlobalBounds();
    }
    catch (const std::exception& e) {
        std::cerr << "Error getting bounds of WingGift: " << e.what() << std::endl;
        throw;
    }
    catch (...) {
        std::cerr << "Unknown error getting bounds of WingGift" << std::endl;
        throw;
    }
}

// Handle collision with another game object
void WingGift::onCollision(GameObject& other) {
    try {
        if (dynamic_cast<Player*>(&other)) {
            other.onCollision(*this);
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error handling collision in WingGift: " << e.what() << std::endl;
        throw;
    }
    catch (...) {
        std::cerr << "Unknown error handling collision in WingGift" << std::endl;
        throw;
    }
}

// Draw the wing gift
void WingGift::draw(sf::RenderWindow& window) {
    try {
        window.draw(m_sprite);
    }
    catch (const std::exception& e) {
        std::cerr << "Error drawing WingGift: " << e.what() << std::endl;
        throw;
    }
    catch (...) {
        std::cerr << "Unknown error drawing WingGift" << std::endl;
        throw;
    }
}
