#pragma once

#include "GameObject.h"
#include "Singleton.h"

class Collidable : public GameObject {
public:
    virtual void onCollision(Collidable& other) = 0;
    virtual bool checkCollision(Collidable& other);
    void draw(sf::RenderWindow& window) override;
    void update(float deltaTime) override;
    void resetPosition(float x, float y) override;
    sf::FloatRect getBounds() const override;
    sf::Vector2f getPosition() const override;
    
protected:
    void setTexture(const GameEffects& textureKey);
    
};
