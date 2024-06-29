#include "BlackHole.h"
#include "Player.h"

BlackHole::BlackHole(float startX, float startY)
    : StaticObject(startX, startY, HOLE_a) {}

void BlackHole::onCollision(Collidable& other) {
    if (dynamic_cast<Player*>(&other)) {
        other.onCollision(*this);
    }
}
