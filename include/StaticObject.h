#pragma once

#include "Collidable.h"
#include "Singleton.h"

class StaticObject : public Collidable {
public:
    StaticObject(float startX, float startY, const std::string& textureKey);
    void draw(sf::RenderWindow& window) override;
    void update(float deltaTime) override;
    void resetPosition(float x, float y) override;
    sf::FloatRect getBounds() const override;

protected:
    void setTexture(const std::string& textureKey);
};
