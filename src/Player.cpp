#include "Player.h"
#include "BreakablePlatform.h"

Player::Player(float startX, float startY)
    : velocity(0.0f), gravity(0.5f), jumpStrength(-15.0f), moveSpeed(5.0f) , lives(3), currentlyColliding(false)
{
    playerShape.setSize(sf::Vector2f(50, 50));
    playerShape.setFillColor(sf::Color::Green);
    playerShape.setPosition(startX, startY);
}

void Player::draw(sf::RenderWindow& window)
{
    window.draw(playerShape);
}


void Player::update(std::vector<Platform*>& platforms, float deltaTime)
{
    velocity += gravity;
    playerShape.move(0, velocity);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        playerShape.move(-moveSpeed, 0);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        playerShape.move(moveSpeed, 0);
    }

    if (playerShape.getPosition().x + playerShape.getSize().x < 0)
    {
        playerShape.setPosition(800, playerShape.getPosition().y);
    }

    if (playerShape.getPosition().x > 800)
    {
        playerShape.setPosition(-playerShape.getSize().x, playerShape.getPosition().y);
    }
   for (auto platform : platforms)
    {
        sf::FloatRect platformBounds = platform->getBounds();
        sf::FloatRect playerBounds = playerShape.getGlobalBounds();

        if (playerBounds.top + playerBounds.height >= platformBounds.top &&
            playerBounds.top + playerBounds.height <= platformBounds.top + platformBounds.height &&
            velocity > 0)
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
    return playerShape.getGlobalBounds();
}
   


void Player::jump() 
{
    if (velocity > 0)
    {
        velocity = jumpStrength;
    }
}


sf::Vector2f Player::getPosition() const
{
    return playerShape.getPosition();
}

bool Player::hasFallen() const
{
    return playerShape.getPosition().y > 600;
}


int Player::getLives()
{
    return lives;
}

void Player::decrementLife()
{
    if (!currentlyColliding) {
        lives--;
        currentlyColliding = true;
    }
}

void Player::resetCollisionFlag()
{
    currentlyColliding = false;
}

bool Player::isColliding() const
{
    return currentlyColliding;
}
