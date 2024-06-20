#include "Bat.h"
// Constructor implementation
Bat::Bat(float startX, float startY)
{
    BatShape.setSize(sf::Vector2f(40, 40));
    BatShape.setFillColor(sf::Color::Red);
    BatShape.setPosition(startX, startY);
}

// Draw Bat on the screen
void Bat::draw(sf::RenderWindow& window)
{
    window.draw(BatShape);
}

// Update Bat's position
void Bat::update(float deltaTime)
{
    //left-to-right movement
    float movement = speed * deltaTime;
    BatShape.move(movement, 0);

    // Reset position if it moves off-screen
    if (BatShape.getPosition().x > 800)
    {
        BatShape.setPosition(-40, BatShape.getPosition().y);
    }
}

// Reset Bat's position to appear again
void Bat::resetPosition(float x, float y)
{
    BatShape.setPosition(x, y);
}

sf::Vector2f Bat::getPosition() const
{
    return BatShape.getPosition();
}

sf::FloatRect Bat::getGlobalBounds() const
{
    return BatShape.getGlobalBounds();
}