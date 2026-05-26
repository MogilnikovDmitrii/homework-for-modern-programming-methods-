#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "movableObject.hpp"  

class Player : public MovableObject {
public:
    Player(float xPos = 0, float yPos = 0);
};

#endif