#pragma once

#include "GameObject.h"
#include "Singleton.h"

// Class representing a movable object in the game
class MovableObject : public GameObject {
public:
    MovableObject(float startX, float startY, const GameEffects& textureKey); // Constructor for GameEffects texture
    MovableObject(const Characters& textureKey); // Constructor for Characters texture

    virtual ~MovableObject() = default;

    void draw(sf::RenderWindow& window) override; // Draw the movable object
    void resetPosition(float x, float y) override; // Reset the position of the movable object
    sf::Vector2f getPosition() const override; // Get the position of the movable object
    virtual void update(float deltaTime) = 0; // Pure virtual function to update the movable object
    std::string getType() const override { return "MovableObject"; } // Get the type of the object

    void setTexture(const GameEffects& textureKey); // Set the texture using GameEffects
    void setTexture(const Characters& textureKey); // Set the texture using Characters
};
