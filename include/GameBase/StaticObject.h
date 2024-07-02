#pragma once

#include "GameObject.h"
#include "Singleton.h"

class StaticObject : public GameObject {
public:
    StaticObject(float startX, float startY,
        const GameEffects& textureKey);

    void draw(sf::RenderWindow& window) override;
    void resetPosition(float x, float y) override;
    sf::Vector2f getPosition() const override;

protected:
    void setTexture(const GameEffects& textureKey);
    
};