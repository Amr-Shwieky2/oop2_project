#include "StaticObject.h"
#include <iostream>

// Constructor to initialize the static object
StaticObject::StaticObject(float startX, float startY, const GameEffects& textureKey) {
    try {
        setTexture(textureKey);
        m_sprite.setPosition(startX, startY);
    }
    catch (const std::exception& e) {
        std::cerr << "Error initializing StaticObject: " << e.what() << std::endl;
        throw;
    }
    catch (...) {
        std::cerr << "Unknown error initializing StaticObject" << std::endl;
        throw;
    }
}

// Draw the static object
void StaticObject::draw(sf::RenderWindow& window) {
    try {
        window.draw(m_sprite);
    }
    catch (const std::exception& e) {
        std::cerr << "Error drawing StaticObject: " << e.what() << std::endl;
        throw;
    }
    catch (...) {
        std::cerr << "Unknown error drawing StaticObject" << std::endl;
        throw;
    }
}

// Reset the position of the static object
void StaticObject::resetPosition(float x, float y) {
    try {
        m_sprite.setPosition(x, y);
    }
    catch (const std::exception& e) {
        std::cerr << "Error resetting position of StaticObject: " << e.what() << std::endl;
        throw;
    }
    catch (...) {
        std::cerr << "Unknown error resetting position of StaticObject" << std::endl;
        throw;
    }
}

// Get the position of the static object
sf::Vector2f StaticObject::getPosition() const {
    try {
        return m_sprite.getPosition();
    }
    catch (const std::exception& e) {
        std::cerr << "Error getting position of StaticObject: " << e.what() << std::endl;
        throw;
    }
    catch (...) {
        std::cerr << "Unknown error getting position of StaticObject" << std::endl;
        throw;
    }
}

// Set the texture of the static object
void StaticObject::setTexture(const GameEffects& textureKey) {
    try {
        m_sprite.setTexture(*(LoadingManager::instance().getEffect(textureKey)));
        m_sprite.setScale(0.15f, 0.15f);
    }
    catch (const std::exception& e) {
        std::cerr << "Error setting texture of StaticObject: " << e.what() << std::endl;
        throw;
    }
    catch (...) {
        std::cerr << "Unknown error setting texture of StaticObject" << std::endl;
        throw;
    }
}

// Get the type of the static object
std::string StaticObject::getType() const {
    try {
        return "StaticObject"; // You can adjust this to return specific types like "HeartGift", "BlackHole", etc.
    }
    catch (const std::exception& e) {
        std::cerr << "Error getting type of StaticObject: " << e.what() << std::endl;
        throw;
    }
    catch (...) {
        std::cerr << "Unknown error getting type of StaticObject" << std::endl;
        throw;
    }
}
