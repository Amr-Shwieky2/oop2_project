#include "HeartGift.h"

HeartGift::HeartGift(float startX, float startY) : appearanceInterval(10.0f)
{
    HeartGiftShape.setSize(sf::Vector2f(50, 50)); // Size can be adjusted
    HeartGiftShape.setFillColor(sf::Color::Yellow);
    HeartGiftShape.setPosition(startX, startY);
}

void HeartGift::draw(sf::RenderWindow& window)
{
    window.draw(HeartGiftShape);
}


void HeartGift::resetPosition(float x, float y)
{
    HeartGiftShape.setPosition(x, y);
}

sf::Vector2f HeartGift::getPosition() const
{
    return HeartGiftShape.getPosition();
}

sf::FloatRect HeartGift::getGlobalBounds() const
{
    return HeartGiftShape.getGlobalBounds();
}