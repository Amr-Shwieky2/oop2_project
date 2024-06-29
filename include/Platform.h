#pragma once

#include "MovableObject.h"

class Platform : public MovableObject{
public:

    Platform(float x, float y, Type type);
    void draw(sf::RenderWindow& window) override;
    void update(float deltaTime) override;
    void resetPosition(float x, float y) override;
    sf::FloatRect getBounds() const override;
    bool isBreakable() const;
    void onCollision(Collidable& other) override;

protected:
    sf::RectangleShape m_platformShape;
    Type m_type;
    bool m_broken;
};
