#include "HeartGift.h"

HeartGift::HeartGift(float startX, float startY)
    : StaticObject(startX, startY, "HEART_a") {}

void HeartGift::onCollision(Collidable& other) {
    if (dynamic_cast<Player*>(&other)) {
        other.onCollision(*this);
    }
}
