#include "Bat.h"
#include "Player.h"
#include <iostream>

// Constructor implementation
Bat::Bat(float startX, float startY) : MovableObject(startX, startY, BAT_a) {
    try {
        // Any additional initialization can go here
    }
    catch (const std::exception& e) {
        std::cerr << "Error initializing Bat: " << e.what() << std::endl;
        throw;
    }
    catch (...) {
        std::cerr << "Unknown error initializing Bat" << std::endl;
        throw;
    }
}

// Update Bat's position
void Bat::update(float deltaTime) {
    try {
        //left-to-right movement
        float movement = m_speed * deltaTime;
        m_sprite.move(movement, 0);

        // Reset position if it moves off-screen
        if (m_sprite.getPosition().x > 800) {
            m_sprite.setPosition(-40, m_sprite.getPosition().y);
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error updating Bat: " << e.what() << std::endl;
        throw;
    }
    catch (...) {
        std::cerr << "Unknown error updating Bat" << std::endl;
        throw;
    }
}

// Get the bounds of the bat
sf::FloatRect Bat::getBounds() const {
    try {
        return m_sprite.getGlobalBounds();
    }
    catch (const std::exception& e) {
        std::cerr << "Error getting bounds of Bat: " << e.what() << std::endl;
        throw;
    }
    catch (...) {
        std::cerr << "Unknown error getting bounds of Bat" << std::endl;
        throw;
    }
}

// Handle collision with another game object
void Bat::onCollision(GameObject& other) {
    try {
        if (dynamic_cast<Player*>(&other)) {
            other.onCollision(*this);
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error handling collision in Bat: " << e.what() << std::endl;
        throw;
    }
    catch (...) {
        std::cerr << "Unknown error handling collision in Bat" << std::endl;
        throw;
    }
}

// Draw the bat
void Bat::draw(sf::RenderWindow& window) {
    try {
        window.draw(m_sprite);
    }
    catch (const std::exception& e) {
        std::cerr << "Error drawing Bat: " << e.what() << std::endl;
        throw;
    }
    catch (...) {
        std::cerr << "Unknown error drawing Bat" << std::endl;
        throw;
    }
}
