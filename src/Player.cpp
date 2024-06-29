#include "Player.h"
#include "BreakablePlatform.h"

Player::Player()
    : m_velocity(0.0f), m_gravity(0.5f), m_jumpStrength(-15.0f), m_moveSpeed(5.0f),
    m_jumpBoosted(false), m_isFlying(false), m_flyingTimer(0.0f),
    m_lives(3), m_invulnerabilityTimer(0.0f) {
    m_playerShape.setSize(sf::Vector2f(50, 50));
    m_playerShape.setFillColor(sf::Color::Green);
}

void Player::setPosition(float startX, float startY) {
    m_playerShape.setPosition(startX, startY);
}

void Player::draw(sf::RenderWindow& window) {
    window.draw(m_playerShape);
}

void Player::update(float deltaTime) {
    updateFlying(deltaTime);
    updateInvulnerability(deltaTime);

    m_velocity += m_gravity;
    m_playerShape.move(0, m_velocity);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        m_playerShape.move(-m_moveSpeed, 0);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        m_playerShape.move(m_moveSpeed, 0);
    }

    if (m_playerShape.getPosition().x + m_playerShape.getSize().x < 0) {
        m_playerShape.setPosition(800, m_playerShape.getPosition().y);
    }

    if (m_playerShape.getPosition().x > 800) {
        m_playerShape.setPosition(-m_playerShape.getSize().x, m_playerShape.getPosition().y);
    }
}

sf::FloatRect Player::getBounds() const {
    return m_playerShape.getGlobalBounds();
}

void Player::onCollision(Collidable& other) {
    // Implement specific collision responses
    if (dynamic_cast<BreakablePlatform*>(&other)) {
        jump();
    }
    // Other collision responses can be added here
}

sf::Vector2f Player::getPosition() const
{
    return m_playerShape.getPosition();
}

bool Player::hasFallen() const {
    return m_playerShape.getPosition().y > 600;
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
