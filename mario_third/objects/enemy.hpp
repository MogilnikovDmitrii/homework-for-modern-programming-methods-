#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "movableObject.hpp"  

class Enemy : public MovableObject {
public:
    Enemy(float xPos = 0, float yPos = 0);
};



#endif