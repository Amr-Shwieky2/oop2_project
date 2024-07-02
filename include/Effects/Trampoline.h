#pragma once
#include <SFML/Graphics.hpp>
#include "Platform.h" 
#include "Singleton.h"
#include "Collidable.h"
#include "StaticObject.h"


class Trampoline : public Collidable, public StaticObject {
public:
    Trampoline(float startX, float startY);
    void resetPosition(Platform* platform);
    sf::FloatRect getBounds() const override;
    void onCollision(Collidable& other) override;
    float getEnhancedJumpStrength() const;

private:
    float m_enhancedJumpStrength;
};
