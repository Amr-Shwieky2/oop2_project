#pragma once

#include "StaticObject.h"

class Bat : public StaticObject {
public:
    Bat(float startX, float startY);
    void update(float deltaTime) override;
    void onCollision(Collidable& other) override;

private:
    float m_speed;
};
