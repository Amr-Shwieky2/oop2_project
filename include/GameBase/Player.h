#pragma once

#include <SFML/Graphics.hpp>
#include "Platform.h"
#include <vector>
#include "MovableObject.h"

// Class representing a player object in the game
class Player : public MovableObject {
public:
    Player(const Characters& textureKey); // Constructor

    void update(float deltaTime, sf::Keyboard::Key leftKey, sf::Keyboard::Key rightKey); // Update the player's position and state

    sf::FloatRect getBounds() const override; // Get the bounds of the player
    void onCollision(GameObject& other) override; // Handle collision with another game object
    void update(float) override {}; // Override for pure virtual function
    void draw(sf::RenderWindow& window) override; // Draw the player

    float getVelocity() const; // Get the player's velocity
    void setVelocity(const float& v); // Set the player's velocity
    void jump(); // Make the player jump
    bool hasFallen() const; // Check if the player has fallen
    int getLives() const; // Get the number of lives the player has
    void decrementLife(); // Decrement the player's life
    void resetCollisionFlag(); // Reset the collision flag
    void setCurrentlyColliding(bool status); // Set the collision status
    bool isColliding() const; // Check if the player is colliding
    void increaseLife(); // Increase the player's life
    void boostJump(); // Method to boost the jump strength temporarily
    void resetJumpStrength(); // Resets the jump strength to normal
    void activateFlying(float duration); // Activate flying mode for a duration
    void updateFlying(float deltaTime); // Update flying state
    void updateInvulnerability(float deltaTime); // Update invulnerability state
    bool getIsFlying() const; // Check if the player is flying

    std::string getType() const override { return "Player"; } // Get the type of the object

private:
    int m_lives; // Number of lives
    bool m_currentlyColliding; // Collision status
    float m_velocity; // Player's velocity
    float m_gravity; // Gravity affecting the player
    float m_jumpStrength; // Jump strength
    float m_moveSpeed; // Movement speed
    bool m_jumpBoosted; // Indicates if the next jump is boosted
    float m_normalJumpStrength; // Regular jump strength
    float m_boostedJumpStrength; // Increased jump strength for trampoline jumps
    bool m_isFlying; // Indicates if the player is flying
    float m_flyingTimer; // Timer for flying duration
    float m_maxFlyingDuration; // Maximum flying duration
    float m_invulnerabilityTimer; // Timer to track invulnerability duration
    float m_invulnerabilityPeriod; // Period of invulnerability after being hit
};
