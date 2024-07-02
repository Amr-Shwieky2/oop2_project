#pragma once
#include <SFML/Graphics.hpp>
#include "Singleton.h"
#include "Collidable.h"
#include "StaticObject.h"

class WingGift : public Collidable, public StaticObject {
public:
    WingGift(float startX, float startY);
    
    sf::FloatRect getBounds() const override;
    void onCollision(Collidable& other) override;

private:
    sf::Sprite m_wingGiftShape;
};
