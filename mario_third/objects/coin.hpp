#ifndef COIN_HPP
#define COIN_HPP

#include "movableObject.hpp"  

class Coin : public MovableObject {
private:
    bool collectable = false;
    bool justSpawned = true;

public:
    Coin(float xPos = 0, float yPos = 0);

    bool isCollectable() const;

    void onFrame(); 
};


#endif