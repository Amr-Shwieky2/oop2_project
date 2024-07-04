#pragma once
#include <SFML/Graphics.hpp>
 
#include "Singleton.h"
#include "StaticObject.h"


class Trampoline : public StaticObject {
public:
    Trampoline(float startX, float startY);
    void resetPosition(Platform platform);
    sf::FloatRect getBounds() const override;
    void onCollision(GameObject& other) override;
    float getEnhancedJumpStrength() const;
    void draw(sf::RenderWindow& window) override;

    std::string getType() const override { return "Trampoline"; }
private:
    float m_enhancedJumpStrength;
};
