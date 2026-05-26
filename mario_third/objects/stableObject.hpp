#ifndef STABLE_OBJ_HPP
#define STABLE_OBJ_HPP

#include "gameObject.hpp"  

class StableObject : public GameObject {
public:
    StableObject(float xPos, float yPos, float w, float h, char sym);
};

#endif