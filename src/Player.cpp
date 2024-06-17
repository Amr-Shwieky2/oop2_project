#include "Player.h"

Player::Player(float startX, float startY)
    : velocity(0.2f), gravity(0.1f), jumpStrength(-7.0f), moveSpeed(2.0f) 
{
    playerShape.setSize(sf::Vector2f(50, 50)); // Sets the size of the rectangle
    playerShape.setFillColor(sf::Color::Green); //set color
    playerShape.setPosition(startX, startY);//set position 
}

void Player::draw(sf::RenderWindow& window)
{
    window.draw(playerShape);
}

//updating the player's position
void Player::update(const std::vector<Platform>& platforms)
{
    velocity += gravity;// making the player accelerate downwards over time
    playerShape.move(0, velocity); //player's position is updated 

    // Move left
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        playerShape.move(-moveSpeed, 0);
    }

    // Move right
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        playerShape.move(moveSpeed, 0);
    }

    //to ensures the player wraps around the screen 
    if (playerShape.getPosition().x + playerShape.getSize().x < 0)
    {
        playerShape.setPosition(800, playerShape.getPosition().y); // Wrap to the right
    }

    if (playerShape.getPosition().x > 800)
    {
        playerShape.setPosition(-playerShape.getSize().x, playerShape.getPosition().y); // Wrap to the left
    }

    // Collision detection with platforms
    for (const auto& platform : platforms)
    {
        sf::FloatRect platformBounds = platform.getBounds();
        sf::FloatRect playerBounds = playerShape.getGlobalBounds();

        //checks if the bottom of the player is within the vertical
        // bounds of the platform and if the player is falling
        if (playerBounds.top + playerBounds.height >= platformBounds.top &&
            playerBounds.top + playerBounds.height <= platformBounds.top + platformBounds.height &&
            velocity > 0) // Only check collision if the player is falling
        {
            float minX = platformBounds.left - playerBounds.width;
            float maxX = platformBounds.left + platformBounds.width;
            //if the player is horizontally within the bounds of the platform
            if (playerBounds.left >= minX && playerBounds.left <= maxX)
            {
                //the player is considered to have landed on the platform
                jump();
            }
        }
    }
}

void Player::jump()
{
    if (velocity > 0) // Only jump if the player is falling down
    {
        velocity = jumpStrength; // Set velocity to jumpStrength to make the player jump
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