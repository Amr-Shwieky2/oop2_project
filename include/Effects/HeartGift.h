#pragma once
#include <SFML/Graphics.hpp>
#include "Singleton.h"
#include "StaticObject.h"

// Class representing a heart gift object in the game
class HeartGift : public StaticObject {
public:
    HeartGift(float startX, float startY); // Constructor

    sf::FloatRect getBounds() const override; // Get the bounds of the heart gift
    void onCollision(GameObject& other) override; // Handle collision with another game object
    void draw(sf::RenderWindow& window) override; // Draw the heart gift

    std::string getType() const override { return "HeartGift"; } // Get the type of the object

private:
    float m_appearanceInterval; // Time interval for the heart gift to appear
    bool m_hide; // Flag to hide the heart gift after collision
};
