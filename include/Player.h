#pragma once

#include "Collidable.h"
#include <vector>

class Player : public Collidable {
public:
    Player();
    void setPosition(float startX, float startY);
    void draw(sf::RenderWindow& window) override;
    void update(float deltaTime) override;
    void resetPosition(float , float) {};
    sf::FloatRect getBounds() const override;
    void onCollision(Collidable& other) override;

    sf::Vector2f getPosition() const;

    void jump();
    bool hasFallen() const;
    int getLives() const;
    void decrementLife();
    void increaseLife();
    void boostJump();
    void activateFlying(float duration);

private:
    void resetJumpStrength();
    void updateFlying(float deltaTime);
    void updateInvulnerability(float deltaTime);

    int m_lives;
    float m_velocity;
    float m_gravity;
    float m_jumpStrength;
    float m_moveSpeed;
    bool m_jumpBoosted;
    bool m_isFlying;
    float m_flyingTimer;
    float m_invulnerabilityTimer;
    sf::RectangleShape m_playerShape;
};
