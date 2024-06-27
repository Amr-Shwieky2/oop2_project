#pragma once

#include "StaticObject.h"

class Trampoline : public StaticObject {
public:
    Trampoline(float startX, float startY);
    void onCollision(Collidable& other) override;

private:
    float m_enhancedJumpStrength;
};
