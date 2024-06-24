#include "Player.h"
#include "BreakablePlatform.h"

Player::Player()
    : m_velocity(0.0f), m_gravity(0.5f), m_jumpStrength(-15.0f), m_moveSpeed(5.0f), m_lives(3), m_currentlyColliding(false)
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
    if (!m_currentlyColliding)
    {
        m_lives--;
        m_currentlyColliding = true;
    }
}

void Player::resetCollisionFlag()
{
    m_currentlyColliding = false;
}

bool Player::isColliding() const
{
    return m_currentlyColliding;
}
