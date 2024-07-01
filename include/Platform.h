#pragma once

#include "MovableObject.h"

class Platform{
public:

    Platform(float x, float y, Type type);
    virtual ~Platform() {};
    void draw(sf::RenderWindow& window) ;
    virtual void update(float deltaTime);
    void resetPosition(float x, float y);
    sf::FloatRect getBounds() const;
    bool isBreakable() const;
    virtual bool checkCollision(Collidable& other);
    void onCollision(Collidable& other);
    sf::Vector2f getPosition() const;

protected:
    sf::RectangleShape m_platformShape;
    Type m_type;
    bool m_broken;
};
