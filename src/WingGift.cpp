#include "WingGift.h"

WingGift::WingGift(float startX, float startY) {
    m_wingGiftShape.setTexture(*(Singleton::instance().getEffect(WINGS_a)));
    m_wingGiftShape.setPosition(startX, startY);

    // Get the size of the texture
    sf::Vector2u textureSize = m_wingGiftShape.getTexture()->getSize();

    // Desired size in pixels
    float desiredWidth = 100.0f;
    float desiredHeight = 100.0f;

    //// Calculate the scale factors
    //float scaleX = desiredWidth / textureSize.x;
    //float scaleY = desiredHeight / textureSize.y;

    //m_wingGiftShape.setScale(scaleX, scaleY);
    m_wingGiftShape.setScale(0.15f, 0.15f);

}

void WingGift::draw(sf::RenderWindow& window) {
    window.draw(m_wingGiftShape);
}

void WingGift::resetPosition(float x, float y) {
    m_wingGiftShape.setPosition(x, y);
}

sf::FloatRect WingGift::getGlobalBounds() const {
    return m_wingGiftShape.getGlobalBounds();
}
