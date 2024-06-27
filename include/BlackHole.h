#pragma once

#include "StaticObject.h"

class BlackHole : public StaticObject {
public:
    BlackHole(float startX, float startY);
    void onCollision(Collidable& other) override;
};
