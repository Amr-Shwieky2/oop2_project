#pragma once

#include "StaticObject.h"

class WingGift : public StaticObject {
public:
    WingGift(float startX, float startY);
    void onCollision(Collidable& other) override;
};
