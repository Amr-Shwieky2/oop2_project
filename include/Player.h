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
    bool isColliding() const;
    void increaseLife();
    void boostJump();  // Method to boost the jump strength temporarily
    void resetJumpStrength();  // Resets the jump strength to normal
    void activateFlying(float duration);
    void updateFlying(float deltaTime);

private:
    int lives;
    bool currentlyColliding;
    sf::RectangleShape playerShape;
    float velocity;
    float gravity;
    float jumpStrength;
    float moveSpeed;
    bool jumpBoosted;  // Indicates if the next jump is boosted
    float normalJumpStrength;  // Regular jump strength
    float boostedJumpStrength;  // Increased jump strength for trampoline jumps
    bool isFlying;
    float flyingTimer;
    float maxFlyingDuration;


};

#endif
