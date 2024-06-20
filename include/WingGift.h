#pragma once
#include <SFML/Graphics.hpp>

class WingGift {
public:
    WingGift(float startX, float startY);
    void draw(sf::RenderWindow& window);
    void resetPosition(float x, float y);
    sf::FloatRect getGlobalBounds() const;

private:
    sf::RectangleShape WingGiftShape;
};
