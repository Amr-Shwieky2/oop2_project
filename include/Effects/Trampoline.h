#pragma once
#include <SFML/Graphics.hpp>
#include "Singleton.h"
#include "StaticObject.h"

// Class representing a trampoline object in the game
class Trampoline : public StaticObject {
public:
    Trampoline(float startX, float startY); // Constructor

    void resetPosition(Platform platform); // Reset the position of the trampoline based on a platform
    sf::FloatRect getBounds() const override; // Get the bounds of the trampoline
    void onCollision(GameObject& other) override; // Handle collision with another game object
    float getEnhancedJumpStrength() const; // Get the enhanced jump strength of the trampoline
    void draw(sf::RenderWindow& window) override; // Draw the trampoline

    std::string getType() const override { return "Trampoline"; } // Get the type of the object

private:
    float m_enhancedJumpStrength; // Enhanced jump strength provided by the trampoline
};
