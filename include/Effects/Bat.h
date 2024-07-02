#pragma once
#include <SFML/Graphics.hpp>
#include "Singleton.h"
#include "Collidable.h"
#include "GameObject.h"

class Bat : public Collidable, public GameObject {
public:
    Bat(float startX, float startY);
    void draw(sf::RenderWindow& window) override;
    void update(float deltaTime) override;
    void resetPosition(float x, float y) override;
    sf::Vector2f getPosition() const override;
    sf::FloatRect getBounds() const override;
    void onCollision(Collidable& other) override;
private:
    float m_speed = 100.0f;  // Speed of the bat across the screen
};