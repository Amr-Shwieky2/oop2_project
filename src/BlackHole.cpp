#include "BlackHole.h"

BlackHole::BlackHole(float startX, float startY) : appearanceInterval(10.0f)
{
    blackHoleShape.setSize(sf::Vector2f(50, 50)); // Size can be adjusted
    blackHoleShape.setFillColor(sf::Color::White);
    blackHoleShape.setPosition(startX, startY);
}

void BlackHole::draw(sf::RenderWindow& window)
{
    window.draw(blackHoleShape);
}


void BlackHole::resetPosition(float x, float y)
{
    blackHoleShape.setPosition(x, y);
}

sf::Vector2f BlackHole::getPosition() const
{
    return blackHoleShape.getPosition();
}

sf::FloatRect BlackHole::getGlobalBounds() const
{
    return blackHoleShape.getGlobalBounds();
}