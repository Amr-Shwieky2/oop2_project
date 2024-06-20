#include "Player.h"

Player::Player(float startX, float startY)
    : velocity(2.0f), gravity(0.1f), jumpStrength(-6.5f), moveSpeed(0.5f), lives(3), currentlyColliding(false)
{
    playerShape.setSize(sf::Vector2f(50, 50));
    playerShape.setFillColor(sf::Color::Green);
    playerShape.setPosition(startX, startY);
}

void Player::draw(sf::RenderWindow& window)
{
    window.draw(playerShape);
}

// Updating the player's position
void Player::update(const std::vector<Platform>& platforms) 
{
    velocity += gravity;  // Apply gravity
    playerShape.move(0, velocity);  // Update vertical position

    handleHorizontalMovement();  // Handle left/right movement

    // Check collision with platforms
    currentlyColliding = false;  // Reset collision flag
    for (const auto& platform : platforms) {
        if (isOnPlatform(platform.getBounds())) {
            if (velocity > 0) {  // Falling down onto the platform
                jump();  // Perform jump
                currentlyColliding = true;
                break;  // No need to check further platforms
            }
        }
    }
}

bool Player::isOnPlatform(const sf::FloatRect& platformBounds) {
    sf::FloatRect playerBounds = playerShape.getGlobalBounds();
    // Check vertical alignment and within bounds horizontally
    return (playerBounds.top + playerBounds.height > platformBounds.top - 10 &&
        playerBounds.top + playerBounds.height < platformBounds.top + 10 &&
        playerBounds.left < platformBounds.left + platformBounds.width &&
        playerBounds.left + playerBounds.width > platformBounds.left);
}

void Player::handleHorizontalMovement() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        playerShape.move(-moveSpeed, 0);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        playerShape.move(moveSpeed, 0);
    }

    // Screen wrap logic
    if (playerShape.getPosition().x + playerShape.getSize().x < 0) {
        playerShape.setPosition(800, playerShape.getPosition().y);
    }
    else if (playerShape.getPosition().x > 800) {
        playerShape.setPosition(-playerShape.getSize().x, playerShape.getPosition().y);
    }
}




sf::FloatRect Player::getGlobalBounds() const
{
    return playerShape.getGlobalBounds();
}


void Player::jump() 
{
    velocity = jumpStrength;  // jumpStrength should be a negative value

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