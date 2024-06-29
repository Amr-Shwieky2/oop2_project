#pragma once

#include "MovableObject.h"
#include <vector>

class Player : public MovableObject {
public:
    Player(const GameEffects&);
    void update(float deltaTime) override;
    void onCollision(Collidable& other) override;


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
};
