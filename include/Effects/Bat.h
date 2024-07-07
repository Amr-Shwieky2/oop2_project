#pragma once
#include <SFML/Graphics.hpp>
#include "Singleton.h"
#include "MovableObject.h"

// Class representing a bat object in the game
class Bat : public MovableObject {
public:
    Bat(float startX, float startY); // Constructor

    void update(float deltaTime) override; // Update the bat's position
    sf::FloatRect getBounds() const override; // Get the bounds of the bat
    void onCollision(GameObject& other) override; // Handle collision with another game object
    void draw(sf::RenderWindow& window) override; // Draw the bat

    std::string getType() const override { return "Bat"; } // Get the type of the object

private:
    float m_speed = 100.0f;  // Speed of the bat across the screen
};
