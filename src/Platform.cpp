#include "Platform.h"

Platform::Platform(float x, float y)
{
    platformShape.setSize(sf::Vector2f(60, 15)); // Sets the size of the platform
    platformShape.setFillColor(sf::Color(100, 255, 100)); // Sets the color of the platform
    platformShape.setPosition(x, y); // Sets the position of the platform
}

void Platform::draw(sf::RenderWindow& window)
{
    window.draw(platformShape);
}

sf::FloatRect Platform::getBounds() const 
{
    return platformShape.getGlobalBounds();
}
