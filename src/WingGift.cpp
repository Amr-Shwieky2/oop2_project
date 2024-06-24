#include "WingGift.h"

WingGift::WingGift(float startX, float startY) {
    WingGiftShape.setSize(sf::Vector2f(50, 50));
    WingGiftShape.setFillColor(sf::Color::Blue);  // Color to distinguish it from other gifts
    WingGiftShape.setPosition(startX, startY);
}

void WingGift::draw(sf::RenderWindow& window) {
    window.draw(WingGiftShape);
}

void WingGift::resetPosition(float x, float y) {
    WingGiftShape.setPosition(x, y);
}

sf::FloatRect WingGift::getGlobalBounds() const {
    return WingGiftShape.getGlobalBounds();
}
