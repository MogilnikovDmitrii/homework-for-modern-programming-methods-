#ifndef PLATFORM_HPP
#define PLATFORM_HPP

#include "stableObject.hpp"  

class Platform : public StableObject {
public:
    Platform(float xPos, float yPos, float w, float h, char sym = SYM_PLATFORM);
};

#endif