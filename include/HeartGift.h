#pragma once

#include "StaticObject.h"

class HeartGift : public StaticObject {
public:
    HeartGift(float startX, float startY);
    void onCollision(Collidable& other) override;
};
