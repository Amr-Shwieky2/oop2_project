#pragma once
#include <SFML/Graphics.hpp>
#include "Singleton.h"
#include "StaticObject.h"

class WingGift :public StaticObject {
public:
    WingGift(float startX, float startY);
    
    sf::FloatRect getBounds() const override;
    void onCollision(GameObject& other) override;
    void draw(sf::RenderWindow& window) override;


private:
    sf::Sprite m_wingGiftShape;
};
