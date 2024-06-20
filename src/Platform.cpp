#include "Platform.h"

Platform::Platform(float x, float y, Type type)
    : type(type), broken(false)
{
    platformShape.setSize(sf::Vector2f(60, 15));
    platformShape.setFillColor(sf::Color(100, 255, 100));
    platformShape.setPosition(x, y);
}

void Platform::update(float deltaTime) {}

void Platform::draw(sf::RenderWindow& window)
{
    if (!broken)
        window.draw(platformShape);
}

sf::FloatRect Platform::getBounds() const
{
    return platformShape.getGlobalBounds();
}

bool Platform::isBreakable() const
{
    return type == Type::BREAKABLE;
}
