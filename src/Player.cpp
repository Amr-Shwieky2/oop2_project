#include "Player.h"
#include "BreakablePlatform.h"
#include "HeartGift.h"
#include "BlackHole.h"
#include "Trampoline.h"
#include "WingGift.h"
#include "Bat.h"

Player::Player(const GameEffects& textureKey)
    : m_velocity(0.0f), m_gravity(0.5f), m_jumpStrength(-15.0f), m_moveSpeed(5.0f),
    m_jumpBoosted(false), m_isFlying(false), m_flyingTimer(0.0f),
    m_lives(3), m_invulnerabilityTimer(0.0f), MovableObject(textureKey)
{
}

void Player::update(float deltaTime) {
    updateFlying(deltaTime);
    updateInvulnerability(deltaTime);

    m_velocity += m_gravity;
    m_sprite.move(0, m_velocity);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        m_sprite.move(-m_moveSpeed, 0);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        m_sprite.move(m_moveSpeed, 0);
    }

    if (m_sprite.getPosition().x + m_sprite.getGlobalBounds().width < 0) {
        m_sprite.setPosition(800, m_sprite.getPosition().y);
    }

    if (m_sprite.getPosition().x > 800) {
        m_sprite.setPosition(-m_sprite.getGlobalBounds().width, m_sprite.getPosition().y);
    } // v

    /*std::vector<Platform*>::iterator it = platforms.begin();

    for (auto platform : platforms)
    {
        sf::FloatRect platformBounds = platform->getBounds();
        sf::FloatRect playerBounds = m_playerShape.getGlobalBounds();

        if (playerBounds.top + playerBounds.height >= platformBounds.top &&
            playerBounds.top + playerBounds.height <= platformBounds.top + platformBounds.height &&
            m_velocity > 0)
        {
            float minX = platformBounds.left - playerBounds.width;
            float maxX = platformBounds.left + platformBounds.width;
            if (playerBounds.left >= minX && playerBounds.left <= maxX)
            {
                if (platform->isBreakable())
                {
                    static_cast<BreakablePlatform*>(platform)->breakPlatform();
                }
                jump();
            }
        }

        platform->update(deltaTime);
    }*/


}

void Player::onCollision(Collidable& other) {
    // Implement specific collision responses
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
        activateFlying(1.0f);
        other.resetPosition(m_sprite.getPosition().x, m_sprite.getPosition().y);
    }

    if (dynamic_cast<Bat*>(&other)) {
        decrementLife();
    }
    // Other collision responses can be added here
}

void Player::onCollision(Platform& other)
{
    if (dynamic_cast<BreakablePlatform*>(&other)) {
        jump();
    }

    if (dynamic_cast<Platform*>(&other)) {
        jump();
    }
}

bool Player::hasFallen() const {
    return m_sprite.getPosition().y > 600;
}

int Player::getLives() const {
    return m_lives;
}

void Player::decrementLife() {
    
    if (m_invulnerabilityTimer <= 0) {
        m_lives--;
        m_invulnerabilityTimer = 1.0f;  // Reset invulnerability timer
    }
}

void Player::increaseLife() {
    if (m_invulnerabilityTimer <= 0 && m_lives < 3) {
        m_lives++;
        m_invulnerabilityTimer = 1.0f;  // Reset invulnerability timer
    }
}

void Player::boostJump() {
    if (m_invulnerabilityTimer <= 0 && !m_jumpBoosted) {
        m_jumpStrength = -23.0f;  // Boosted jump strength
        m_jumpBoosted = true;
        m_invulnerabilityTimer = 1.0f;  // Reset invulnerability timer
    }
}

void Player::activateFlying(float) {
    if (m_invulnerabilityTimer <= 0) {
        m_isFlying = true;
        m_flyingTimer = 0;
        m_invulnerabilityTimer = 1.0f;  // Reset invulnerability timer
    }
}

float Player::getVelocity() const
{
    return m_velocity;
}

void Player::jump() {
    if (m_velocity > 0) {
        m_velocity = m_jumpStrength;
        resetJumpStrength();
    }
}

void Player::resetJumpStrength() {
    if (m_jumpBoosted) {
        m_jumpStrength = -15.0f;
        m_jumpBoosted = false;
    }
}

void Player::updateFlying(float deltaTime) {
    if (m_isFlying) {
        m_flyingTimer += deltaTime;
        if (m_flyingTimer < 1.0f) {
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
    }
}
