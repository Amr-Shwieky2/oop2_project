#include "HeartGift.h"
#include "Player.h"
#include <iostream>

// Constructor implementation
HeartGift::HeartGift(float startX, float startY)
    : StaticObject(startX, startY, HEART_a), m_appearanceInterval(10.0f), m_hide(false) {
    try {
        // Any additional initialization can go here
    }
    catch (const std::exception& e) {
        std::cerr << "Error initializing HeartGift: " << e.what() << std::endl;
        throw;
    }
    catch (...) {
        std::cerr << "Unknown error initializing HeartGift" << std::endl;
        throw;
    }
}

// Get the bounds of the heart gift
sf::FloatRect HeartGift::getBounds() const {
    try {
        return m_sprite.getGlobalBounds();
    }
    catch (const std::exception& e) {
        std::cerr << "Error getting bounds of HeartGift: " << e.what() << std::endl;
        throw;
    }
    catch (...) {
        std::cerr << "Unknown error getting bounds of HeartGift" << std::endl;
        throw;
    }
}

// Handle collision with another game object
void HeartGift::onCollision(GameObject& other) {
    try {
        if (dynamic_cast<Player*>(&other)) {
            other.onCollision(*this);
            m_hide = true;
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error handling collision in HeartGift: " << e.what() << std::endl;
        throw;
    }
    catch (...) {
        std::cerr << "Unknown error handling collision in HeartGift" << std::endl;
        throw;
    }
}

// Draw the heart gift
void HeartGift::draw(sf::RenderWindow& window) {
    try {
        if (!m_hide) {
            window.draw(m_sprite);
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error drawing HeartGift: " << e.what() << std::endl;
        throw;
    }
    catch (...) {
        std::cerr << "Unknown error drawing HeartGift" << std::endl;
        throw;
    }
}
