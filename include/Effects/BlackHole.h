#pragma once
#include <SFML/Graphics.hpp>
#include "Singleton.h"
#include "StaticObject.h"

class BlackHole : public StaticObject {
public:
    BlackHole(float startX, float startY);
    sf::FloatRect getBounds() const override;

    void onCollision(GameObject& other) override;
    void draw(sf::RenderWindow& window) override;


private:
    float m_appearanceInterval; // Time interval for the black hole to appear
};