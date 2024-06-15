

// Implementation
#include "Player.h"

Player::Player(float startX, float startY)
    : velocity(0), gravity(0.0003f), jumpStrength(-0.2f), moveSpeed(0.02f)
{
    playerShape.setSize(sf::Vector2f(50, 50)); // Sets the size of the rectangle
    playerShape.setFillColor(sf::Color::Green);
    playerShape.setPosition(startX, startY);
}

void Player::draw(sf::RenderWindow& window)
{
    window.draw(playerShape);
}

void Player::update()
{
    velocity += gravity;
    playerShape.move(0, velocity);

    // If the player hits the bottom of the window
    if (playerShape.getPosition().y + playerShape.getSize().y > 600)
    {
        // Preventing it from moving further down.
        playerShape.setPosition(playerShape.getPosition().x, 600 - playerShape.getSize().y);
        velocity = 0;
    }

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

    // Screen wrapping logic
    if (playerShape.getPosition().x + playerShape.getSize().x < 0) 
    {
        playerShape.setPosition(800, playerShape.getPosition().y); // Wrap to the right
    }

    if (playerShape.getPosition().x > 800) 
    {
        playerShape.setPosition(-playerShape.getSize().x, playerShape.getPosition().y); // Wrap to the left
    }
}

void Player::jump()
{
    velocity = jumpStrength; // Set velocity to jumpStrength to make the player jump
}

sf::Vector2f Player::getPosition() const
{
    return playerShape.getPosition();
}