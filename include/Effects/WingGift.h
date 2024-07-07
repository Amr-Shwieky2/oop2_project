#pragma once
#include <SFML/Graphics.hpp>
#include "Singleton.h"
#include "StaticObject.h"

// Class representing a wing gift object in the game
class WingGift : public StaticObject {
public:
    WingGift(float startX, float startY); // Constructor

    sf::FloatRect getBounds() const override; // Get the bounds of the wing gift
    void onCollision(GameObject& other) override; // Handle collision with another game object
    void draw(sf::RenderWindow& window) override; // Draw the wing gift

    std::string getType() const override { return "WingGift"; } // Get the type of the object
};
