#include "MovableObject.h"
#include <iostream>

// Constructor for GameEffects texture
MovableObject::MovableObject(float startX, float startY, const GameEffects& textureKey) {
    try {
        setTexture(textureKey);
        m_sprite.setPosition(startX, startY);
    }
    catch (const std::exception& e) {
        std::cerr << "Error initializing MovableObject with GameEffects: " << e.what() << std::endl;
        throw;
    }
    catch (...) {
        std::cerr << "Unknown error initializing MovableObject with GameEffects" << std::endl;
        throw;
    }
}

// Constructor for Characters texture
MovableObject::MovableObject(const Characters& textureKey) {
    try {
        setTexture(textureKey);
    }
    catch (const std::exception& e) {
        std::cerr << "Error initializing MovableObject with Characters: " << e.what() << std::endl;
        throw;
    }
    catch (...) {
        std::cerr << "Unknown error initializing MovableObject with Characters" << std::endl;
        throw;
    }
}

// Draw the movable object
void MovableObject::draw(sf::RenderWindow& window) {
    try {
        window.draw(m_sprite);
    }
    catch (const std::exception& e) {
        std::cerr << "Error drawing MovableObject: " << e.what() << std::endl;
        throw;
    }
    catch (...) {
        std::cerr << "Unknown error drawing MovableObject" << std::endl;
        throw;
    }
}

// Reset the position of the movable object
void MovableObject::resetPosition(float x, float y) {
    try {
        m_sprite.setPosition(x, y);
    }
    catch (const std::exception& e) {
        std::cerr << "Error resetting position of MovableObject: " << e.what() << std::endl;
        throw;
    }
    catch (...) {
        std::cerr << "Unknown error resetting position of MovableObject" << std::endl;
        throw;
    }
}

// Get the position of the movable object
sf::Vector2f MovableObject::getPosition() const {
    try {
        return m_sprite.getPosition();
    }
    catch (const std::exception& e) {
        std::cerr << "Error getting position of MovableObject: " << e.what() << std::endl;
        throw;
    }
    catch (...) {
        std::cerr << "Unknown error getting position of MovableObject" << std::endl;
        throw;
    }
}

// Set the texture using GameEffects
void MovableObject::setTexture(const GameEffects& textureKey) {
    try {
        m_sprite.setTexture(*(LoadingManager::instance().getEffect(textureKey)));
        m_sprite.setScale(0.15f, 0.15f);
    }
    catch (const std::exception& e) {
        std::cerr << "Error setting texture of MovableObject with GameEffects: " << e.what() << std::endl;
        throw;
    }
    catch (...) {
        std::cerr << "Unknown error setting texture of MovableObject with GameEffects" << std::endl;
        throw;
    }
}

// Set the texture using Characters
void MovableObject::setTexture(const Characters& textureKey) {
    try {
        m_sprite.setTexture(*(LoadingManager::instance().getCharacter(textureKey)));
        m_sprite.setScale(0.15f, 0.15f);
    }
    catch (const std::exception& e) {
        std::cerr << "Error setting texture of MovableObject with Characters: " << e.what() << std::endl;
        throw;
    }
    catch (...) {
        std::cerr << "Unknown error setting texture of MovableObject with Characters" << std::endl;
        throw;
    }
}
