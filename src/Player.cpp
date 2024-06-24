#include "Player.h"
#include "BreakablePlatform.h"

Player::Player()
    : m_velocity(0.0f), m_gravity(0.5f), m_jumpStrength(-15.0f), m_moveSpeed(5.0f),
    m_currentlyColliding(false), m_jumpBoosted(false), m_normalJumpStrength(-15.0f), m_boostedJumpStrength(-23.0f),
    m_isFlying(false), m_flyingTimer(0.0f), m_maxFlyingDuration(0.0f), m_lives(3)
{
    m_playerShape.setSize(sf::Vector2f(50, 50));
    m_playerShape.setFillColor(sf::Color::Green);
}

void Player::setPosition(float startX, float startY)
{
    m_playerShape.setPosition(startX, startY);
}

void Player::draw(sf::RenderWindow& window)
{
    window.draw(m_playerShape);
}

void Player::update(std::vector<Platform*>& platforms, float deltaTime)
{
    updateFlying(deltaTime);

    m_velocity += m_gravity;
    m_playerShape.move(0, m_velocity);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        m_playerShape.move(-m_moveSpeed, 0);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        m_playerShape.move(m_moveSpeed, 0);
    }

    if (m_playerShape.getPosition().x + m_playerShape.getSize().x < 0)
    {
        m_playerShape.setPosition(800, m_playerShape.getPosition().y);
    }

    if (m_playerShape.getPosition().x > 800)
    {
        m_playerShape.setPosition(-m_playerShape.getSize().x, m_playerShape.getPosition().y);
    }

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
    }
}

sf::FloatRect Player::getGlobalBounds() const
{
    return m_playerShape.getGlobalBounds();
}

void Player::jump()
{
    if (m_velocity > 0)
    {
        m_velocity = m_jumpStrength;
        resetJumpStrength();  // Reset jump strength immediately after jumping
    }
}

sf::Vector2f Player::getPosition() const
{
    return m_playerShape.getPosition();
}

bool Player::hasFallen() const
{
    return m_playerShape.getPosition().y > 600;
}

int Player::getLives() const
{
    return m_lives;
}

void Player::decrementLife()
{
    m_lives--;
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
    if (m_lives < 3)
        m_lives++;
}

void Player::boostJump() {
    if (!m_jumpBoosted) {
        m_jumpStrength = m_boostedJumpStrength;
        m_jumpBoosted = true;
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
    m_isFlying = true;
    m_maxFlyingDuration = duration;
    m_flyingTimer = 0;
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
