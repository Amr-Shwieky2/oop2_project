#include "Player.h"
#include "BreakablePlatform.h"
#include "HeartGift.h"
#include "BlackHole.h"
#include "Trampoline.h"
#include "WingGift.h"
#include "Bat.h"
#include <iostream>

Player::Player(const Characters& textureKey)
    : m_velocity(0.0f), m_gravity(0.5f), m_jumpStrength(-15.0f), m_moveSpeed(8.0f),
    m_currentlyColliding(false), m_jumpBoosted(false), m_normalJumpStrength(-15.0f), m_boostedJumpStrength(-23.0f),
    m_isFlying(false), m_flyingTimer(0.0f), m_maxFlyingDuration(0.0f), m_lives(3),
     m_invulnerabilityTimer(0), m_invulnerabilityPeriod(1.0f), MovableObject(textureKey)
{
   
}

void Player::update(float deltaTime)
{
    updateFlying(deltaTime);
    updateInvulnerability(deltaTime);

    m_velocity += m_gravity;
    m_sprite.move(0, m_velocity);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        m_sprite.move(-m_moveSpeed, 0);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        m_sprite.move(m_moveSpeed, 0);
    }

    if (m_sprite.getPosition().x < 0)
    {
        m_sprite.setPosition(800, m_sprite.getPosition().y);
    }

    if (m_sprite.getPosition().x > 800)
    {
        m_sprite.setPosition(0, m_sprite.getPosition().y);
    }

    
}

void Player::draw(sf::RenderWindow& window)
{
    window.draw(m_sprite);
}

sf::FloatRect Player::getBounds() const
{
    return m_sprite.getGlobalBounds();
}

void Player::onCollision(GameObject& other)
{
    if (dynamic_cast<HeartGift*>(&other)) {
        increaseLife();
    }

    if (dynamic_cast<BlackHole*>(&other)) {
        m_lives = -1;
    }

    if (dynamic_cast<Trampoline*>(&other)) {
        boostJump();
    }

    if (dynamic_cast<WingGift*>(&other)) {
        activateFlying(3.0f);
    }

    if (dynamic_cast<Bat*>(&other)) {
        decrementLife();
    }
}

float Player::getVelocity() const
{
    return m_velocity;
}

void Player::jump()
{
    if (m_velocity > 0)
    {
        m_velocity = m_jumpStrength;
        resetJumpStrength();  // Reset jump strength immediately after jumping
    }
}

bool Player::hasFallen() const
{
    return m_sprite.getPosition().y > 600;
}

int Player::getLives() const
{
    return m_lives;
}

void Player::decrementLife() {
    if (m_invulnerabilityTimer <= 0) { // Only decrement life if not invulnerable
        m_lives--;
        m_invulnerabilityTimer = m_invulnerabilityPeriod; // Reset invulnerability timer
    }
}

void Player::setCurrentlyColliding(bool status)
{
    m_currentlyColliding = status;
}

void Player::resetCollisionFlag()
{
    m_currentlyColliding = false;
}

bool Player::isColliding() const
{
    return m_currentlyColliding;
}

void Player::increaseLife()
{
    if (m_invulnerabilityTimer <= 0 && m_lives < 3) { // Only increase life if not invulnerable
        m_lives++;
        m_invulnerabilityTimer = m_invulnerabilityPeriod; // Reset invulnerability timer
    }
}

void Player::boostJump() {
    if (m_invulnerabilityTimer <= 0 && !m_jumpBoosted) { 
        m_jumpStrength = m_boostedJumpStrength;
        m_jumpBoosted = true;        m_invulnerabilityTimer = m_invulnerabilityPeriod; // Reset invulnerability timer
    }

}

void Player::resetJumpStrength() {
    if (m_jumpBoosted) {
        m_jumpStrength = m_normalJumpStrength;
        m_jumpBoosted = false;
    }
}

void Player::activateFlying(float duration)
{
    if (m_invulnerabilityTimer <= 0) { 
        m_isFlying = true;
        m_maxFlyingDuration = duration;
        m_flyingTimer = 0;  
        m_invulnerabilityTimer = m_invulnerabilityPeriod; 
        // Reset invulnerability timer
    }

}

void Player::updateFlying(float deltaTime)
{
    if (m_isFlying) {
        m_flyingTimer += deltaTime;
        if (m_flyingTimer < m_maxFlyingDuration) {
            m_velocity = -7.0f;  // Negative to move up
        }
        else {
            m_isFlying = false;
        }
    }
}

void Player::updateInvulnerability(float deltaTime) {
    if (m_invulnerabilityTimer > 0) {
        m_invulnerabilityTimer -= deltaTime;
        m_currentlyColliding = true; // Stay in colliding state during invulnerability
    }
    else {
        m_currentlyColliding = false;
    }
}

bool Player::getIsFlying() const
{
    return m_isFlying;
}
