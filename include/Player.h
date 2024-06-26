#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include "Platform.h"
#include <vector>

class Player
{
public:
    Player();
    void setPosition(float startX, float startY);
    void draw(sf::RenderWindow& window);
    void update(std::vector<Platform*>& platforms, float deltaTime);
    void jump();
    sf::Vector2f getPosition() const;
    sf::FloatRect getGlobalBounds() const;
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
private:
    int m_lives;
    bool m_currentlyColliding;
    sf::RectangleShape m_playerShape;
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

#endif
