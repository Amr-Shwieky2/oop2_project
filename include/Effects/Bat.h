#pragma once
#include <SFML/Graphics.hpp>
#include "Singleton.h"
#include "MovableObject.h"

class Bat : public MovableObject {
public:
    Bat(float startX, float startY);
    void update(float deltaTime) override;
    sf::FloatRect getBounds() const override;
    void onCollision(GameObject& other) override;
    void draw(sf::RenderWindow& window) override;
private:
    float m_speed = 100.0f;  // Speed of the bat across the screen
};