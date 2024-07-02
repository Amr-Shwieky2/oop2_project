#pragma once
#include <SFML/Graphics.hpp>
#include "Singleton.h"
#include "Collidable.h"
#include "StaticObject.h"

class HeartGift : public Collidable, public StaticObject {
public:
    HeartGift(float startX, float startY);
    sf::FloatRect getBounds() const override;
    void onCollision(Collidable& other) override;

private:
    float m_appearanceInterval; // Time interval for the black hole to appear
};