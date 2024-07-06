#pragma once

#include <SFML/Graphics.hpp>
#include "Platform.h"
#include <vector>
#include "MovableObject.h"

class Player : public MovableObject
{
public:
    Player(const Characters&);

    void update(float deltaTime, sf::Keyboard::Key leftKey, sf::Keyboard::Key rightKey);

    sf::FloatRect getBounds() const override;
    void onCollision(GameObject& other) override;
    void update(float)override {};
    void draw(sf::RenderWindow& window) override;

    float getVelocity() const;
    void setVelocity(const float&);
    void jump();
    bool hasFallen() const;
    int getLives() const;
    void decrementLife();
    void resetCollisionFlag();
    void setCurrentlyColliding(bool status);
    bool isColliding() const;
    void increaseLife();
    void boostJump();  // Method to boost the jump strength temporarily
    void resetJumpStrength();  // Resets the jump strength to normal
    void activateFlying(float duration);
    void updateFlying(float deltaTime);
    void updateInvulnerability(float deltaTime);
    bool getIsFlying() const;

    std::string getType() const override { return "Player"; }
private:
    int m_lives;
    bool m_currentlyColliding;
    float m_velocity;
    float m_gravity;
    float m_jumpStrength;
    float m_moveSpeed;
    bool m_jumpBoosted;  // Indicates if the next jump is boosted
    float m_normalJumpStrength;  // Regular jump strength
    float m_boostedJumpStrength;  // Increased jump strength for trampoline jumps
    bool m_isFlying;
    float m_flyingTimer;

    float m_maxFlyingDuration;
    float m_invulnerabilityTimer; // Timer to track invulnerability duration
    float m_invulnerabilityPeriod; // Period of invulnerability after being hit
};

