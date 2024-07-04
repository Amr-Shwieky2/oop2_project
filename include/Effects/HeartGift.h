#pragma once
#include <SFML/Graphics.hpp>
#include "Singleton.h"
#include "StaticObject.h"

class HeartGift : public StaticObject {
public:
    HeartGift(float startX, float startY);
    sf::FloatRect getBounds() const override;
    void onCollision(GameObject& other) override;
    void draw(sf::RenderWindow& window) override;

    std::string getType() const override { return "HeartGift"; }

private:
    float m_appearanceInterval; // Time interval for the black hole to appear
    bool m_hide;
};