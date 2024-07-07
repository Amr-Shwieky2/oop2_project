#pragma once

#include "GameObject.h"
#include "Singleton.h"
#include "Platform.h"

// Class representing a static object in the game
class StaticObject : public GameObject {
public:
    StaticObject(float startX, float startY, const GameEffects& textureKey); // Constructor

    void draw(sf::RenderWindow& window) override; // Draw the static object
    void resetPosition(float x, float y) override; // Reset the position of the static object
    virtual void resetPosition(Platform) {} // Override for reset position with platform, not used
    sf::Vector2f getPosition() const override; // Get the position of the static object
    std::string getType() const override; // Get the type of the static object

protected:
    void setTexture(const GameEffects& textureKey); // Set the texture of the static object
};
