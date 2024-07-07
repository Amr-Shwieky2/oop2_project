#include "Player.h"
#include "BreakablePlatform.h"
#include "HeartGift.h"
#include "BlackHole.h"
#include "Trampoline.h"
#include "WingGift.h"
#include "Bat.h"
#include <iostream>

// Constructor implementation
Player::Player(const Characters& textureKey)
    : MovableObject(textureKey), m_velocity(0.0f), m_gravity(0.5f), m_jumpStrength(-15.0f), m_moveSpeed(8.0f),
    m_currentlyColliding(false), m_jumpBoosted(false), m_normalJumpStrength(-15.0f), m_boostedJumpStrength(-23.0f),
    m_isFlying(false), m_flyingTimer(0.0f), m_maxFlyingDuration(0.0f), m_lives(3), m_invulnerabilityTimer(0),
    m_invulnerabilityPeriod(1.0f) {
    try {
        // Any additional initialization can go here
    }
    catch (const std::exception& e) {
        std::cerr << "Error initializing Player: " << e.what() << std::endl;
        throw;
    }
    catch (...) {
        std::cerr << "Unknown error initializing Player" << std::endl;
        throw;
    }
}

// Update the player's position and state
void Player::update(float deltaTime, sf::Keyboard::Key leftKey, sf::Keyboard::Key rightKey) {
    try {
        updateFlying(deltaTime);
        updateInvulnerability(deltaTime);

        m_velocity += m_gravity;
        m_sprite.move(0, m_velocity);

        if (sf::Keyboard::isKeyPressed(leftKey)) {
            m_sprite.move(-m_moveSpeed, 0);
        }

        if (sf::Keyboard::isKeyPressed(rightKey)) {
            m_sprite.move(m_moveSpeed, 0);
        }

        if (m_sprite.getPosition().x < 0) {
            m_sprite.setPosition(800, m_sprite.getPosition().y);
        }

        if (m_sprite.getPosition().x > 800) {
            m_sprite.setPosition(0, m_sprite.getPosition().y);
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error updating Player: " << e.what() << std::endl;
        throw;
    }
    catch (...) {
        std::cerr << "Unknown error updating Player" << std::endl;
        throw;
    }
}

// Draw the player
void Player::draw(sf::RenderWindow& window) {
    try {
        window.draw(m_sprite);
    }
    catch (const std::exception& e) {
        std::cerr << "Error drawing Player: " << e.what() << std::endl;
        throw;
    }
    catch (...) {
        std::cerr << "Unknown error drawing Player" << std::endl;
        throw;
    }
}

// Get the bounds of the player
sf::FloatRect Player::getBounds() const {
    try {
        return m_sprite.getGlobalBounds();
    }
    catch (const std::exception& e) {
        std::cerr << "Error getting bounds of Player: " << e.what() << std::endl;
        throw;
    }
    catch (...) {
        std::cerr << "Unknown error getting bounds of Player" << std::endl;
        throw;
    }
}

// Handle collision with another game object
void Player::onCollision(GameObject& other) {
    try {
        if (dynamic_cast<HeartGift*>(&other)) {
            increaseLife();
            Singleton::instance().getSoundManager().playSound("coins");
        }

        if (dynamic_cast<BlackHole*>(&other)) {
            m_lives = -1;
            Singleton::instance().getSoundManager().playSound("burned");
        }

        if (dynamic_cast<Trampoline*>(&other)) {
            boostJump();
            Singleton::instance().getSoundManager().playSound("jump");
        }

        if (dynamic_cast<WingGift*>(&other)) {
            activateFlying(3.0f);
            Singleton::instance().getSoundManager().playSound("rock");
        }

        if (dynamic_cast<Bat*>(&other)) {
            decrementLife();
            Singleton::instance().getSoundManager().playSound("burned");
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error handling collision in Player: " << e.what() << std::endl;
        throw;
    }
    catch (...) {
        std::cerr << "Unknown error handling collision in Player" << std::endl;
        throw;
    }
}

// Get the player's velocity
float Player::getVelocity() const {
    try {
        return m_velocity;
    }
    catch (const std::exception& e) {
        std::cerr << "Error getting velocity of Player: " << e.what() << std::endl;
        throw;
    }
    catch (...) {
        std::cerr << "Unknown error getting velocity of Player" << std::endl;
        throw;
    }
}

// Set the player's velocity
void Player::setVelocity(const float& v) {
    try {
        m_velocity = v;
    }
    catch (const std::exception& e) {
        std::cerr << "Error setting velocity of Player: " << e.what() << std::endl;
        throw;
    }
    catch (...) {
        std::cerr << "Unknown error setting velocity of Player" << std::endl;
        throw;
    }
}

// Make the player jump
void Player::jump() {
    try {
        if (m_velocity > 0) {
            m_velocity = m_jumpStrength;
            resetJumpStrength();  // Reset jump strength immediately after jumping
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error making Player jump: " << e.what() << std::endl;
        throw;
    }
    catch (...) {
        std::cerr << "Unknown error making Player jump" << std::endl;
        throw;
    }
}

// Check if the player has fallen
bool Player::hasFallen() const {
    try {
        return m_sprite.getPosition().y > 600;
    }
    catch (const std::exception& e) {
        std::cerr << "Error checking if Player has fallen: " << e.what() << std::endl;
        throw;
    }
    catch (...) {
        std::cerr << "Unknown error checking if Player has fallen" << std::endl;
        throw;
    }
}

// Get the number of lives the player has
int Player::getLives() const {
    try {
        return m_lives;
    }
    catch (const std::exception& e) {
        std::cerr << "Error getting lives of Player: " << e.what() << std::endl;
        throw;
    }
    catch (...) {
        std::cerr << "Unknown error getting lives of Player" << std::endl;
        throw;
    }
}

// Decrement the player's life
void Player::decrementLife() {
    try {
        if (m_invulnerabilityTimer <= 0) { // Only decrement life if not invulnerable
            m_lives--;
            m_invulnerabilityTimer = m_invulnerabilityPeriod; // Reset invulnerability timer
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error decrementing life of Player: " << e.what() << std::endl;
        throw;
    }
    catch (...) {
        std::cerr << "Unknown error decrementing life of Player" << std::endl;
        throw;
    }
}

// Set the collision status
void Player::setCurrentlyColliding(bool status) {
    try {
        m_currentlyColliding = status;
    }
    catch (const std::exception& e) {
        std::cerr << "Error setting collision status of Player: " << e.what() << std::endl;
        throw;
    }
    catch (...) {
        std::cerr << "Unknown error setting collision status of Player" << std::endl;
        throw;
    }
}

// Reset the collision flag
void Player::resetCollisionFlag() {
    try {
        m_currentlyColliding = false;
    }
    catch (const std::exception& e) {
        std::cerr << "Error resetting collision flag of Player: " << e.what() << std::endl;
        throw;
    }
    catch (...) {
        std::cerr << "Unknown error resetting collision flag of Player" << std::endl;
        throw;
    }
}

// Check if the player is colliding
bool Player::isColliding() const {
    try {
        return m_currentlyColliding;
    }
    catch (const std::exception& e) {
        std::cerr << "Error checking collision status of Player: " << e.what() << std::endl;
        throw;
    }
    catch (...) {
        std::cerr << "Unknown error checking collision status of Player" << std::endl;
        throw;
    }
}

// Increase the player's life
void Player::increaseLife() {
    try {
        if (m_invulnerabilityTimer <= 0 && m_lives < 3) { // Only increase life if not invulnerable
            m_lives++;
            m_invulnerabilityTimer = m_invulnerabilityPeriod; // Reset invulnerability timer
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error increasing life of Player: " << e.what() << std::endl;
        throw;
    }
    catch (...) {
        std::cerr << "Unknown error increasing life of Player" << std::endl;
        throw;
    }
}

// Method to boost the jump strength temporarily
void Player::boostJump() {
    try {
        if (m_invulnerabilityTimer <= 0 && !m_jumpBoosted) {
            m_jumpStrength = m_boostedJumpStrength;
            m_jumpBoosted = true;
            m_invulnerabilityTimer = m_invulnerabilityPeriod; // Reset invulnerability timer
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error boosting jump of Player: " << e.what() << std::endl;
        throw;
    }
    catch (...) {
        std::cerr << "Unknown error boosting jump of Player" << std::endl;
        throw;
    }
}

// Resets the jump strength to normal
void Player::resetJumpStrength() {
    try {
        if (m_jumpBoosted) {
            m_jumpStrength = m_normalJumpStrength;
            m_jumpBoosted = false;
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error resetting jump strength of Player: " << e.what() << std::endl;
        throw;
    }
    catch (...) {
        std::cerr << "Unknown error resetting jump strength of Player" << std::endl;
        throw;
    }
}

// Activate flying mode for a duration
void Player::activateFlying(float duration) {
    try {
        if (m_invulnerabilityTimer <= 0) {
            m_isFlying = true;
            m_maxFlyingDuration = duration;
            m_flyingTimer = 0;
            m_invulnerabilityTimer = m_invulnerabilityPeriod; // Reset invulnerability timer
            Singleton::instance().setPlayerCharacter1(Singleton::instance().getCharacterNamber1() + 4);
            setTexture(Singleton::instance().getPlayerCharacter1());
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error activating flying mode for Player: " << e.what() << std::endl;
        throw;
    }
    catch (...) {
        std::cerr << "Unknown error activating flying mode for Player" << std::endl;
        throw;
    }
}

// Update flying state
void Player::updateFlying(float deltaTime) {
    try {
        if (m_isFlying) {
            m_flyingTimer += deltaTime;
            if (m_flyingTimer < m_maxFlyingDuration) {
                m_velocity = -7.0f;  // Negative to move up
            }
            else {
                Singleton::instance().setPlayerCharacter1(Singleton::instance().getCharacterNamber1() - 4);
                setTexture(Singleton::instance().getPlayerCharacter1());
                m_isFlying = false;
            }
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error updating flying state of Player: " << e.what() << std::endl;
        throw;
    }
    catch (...) {
        std::cerr << "Unknown error updating flying state of Player" << std::endl;
        throw;
    }
}

// Update invulnerability state
void Player::updateInvulnerability(float deltaTime) {
    try {
        if (m_invulnerabilityTimer > 0) {
            m_invulnerabilityTimer -= deltaTime;
            m_currentlyColliding = true; // Stay in colliding state during invulnerability
        }
        else {
            m_currentlyColliding = false;
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error updating invulnerability state of Player: " << e.what() << std::endl;
        throw;
    }
    catch (...) {
        std::cerr << "Unknown error updating invulnerability state of Player" << std::endl;
        throw;
    }
}

// Check if the player is flying
bool Player::getIsFlying() const {
    try {
        return m_isFlying;
    }
    catch (const std::exception& e) {
        std::cerr << "Error checking if Player is flying: " << e.what() << std::endl;
        throw;
    }
    catch (...) {
        std::cerr << "Unknown error checking if Player is flying" << std::endl;
        throw;
    }
}
