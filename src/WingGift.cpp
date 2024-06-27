#include "WingGift.h"

WingGift::WingGift(float startX, float startY)
    : StaticObject(startX, startY, "WINGS_a") {}

void WingGift::onCollision(Collidable& other) {
    if (dynamic_cast<Player*>(&other)) {
        other.onCollision(*this);
    }
}
