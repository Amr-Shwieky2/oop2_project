#pragma once

#include "GameObject.h"
#include "Singleton.h"
#include "Platform.h"

class StaticObject : public GameObject {
public:
    StaticObject(float startX, float startY,
        const GameEffects& textureKey);

    void draw(sf::RenderWindow& window);
    void resetPosition(float x, float y) override;
    virtual void resetPosition(Platform) {}
    sf::Vector2f getPosition() const override;

protected:
    void setTexture(const GameEffects& textureKey);
    
};