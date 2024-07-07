#pragma once
#include <SFML/Graphics.hpp>
#include "Singleton.h"
#include "StaticObject.h"

// Class representing a black hole object in the game
class BlackHole : public StaticObject {
public:
    BlackHole(float startX, float startY); // Constructor

    sf::FloatRect getBounds() const override; // Get the bounds of the black hole
    void onCollision(GameObject& other) override; // Handle collision with another game object
    void draw(sf::RenderWindow& window) override; // Draw the black hole

    std::string getType() const override { return "BlackHole"; } // Get the type of the object

private:
    float m_appearanceInterval; // Time interval for the black hole to appear
};
