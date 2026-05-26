#include "coin.hpp"


Coin::Coin(float xPos, float yPos)
    : MovableObject(xPos, yPos, 3, 2, SYM_COIN)
{
    setHorSpeed(0.2f);
}

void Coin::onFrame() {
    if (justSpawned) {
        justSpawned = false;
        return;
    }

    collectable = true;
}
bool Coin::isCollectable() const {
    return collectable;
}

