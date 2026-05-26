#ifndef MOVABLE_OBJ_HPP
#define MOVABLE_OBJ_HPP

#include <unistd.h>
#include "gameObject.hpp"  

class MovableObject : public GameObject {
protected:
    float vertSpeed;
    float horSpeed;
    bool isFly;

public:
    MovableObject(float xPos, float yPos, float w, float h, char sym);

    void update(GameObject** Floor, int FloorLen,
                GameObject** Enemies, int EnemiesLen) override;

    float getVertSpeed() const;
    void setVertSpeed(float v);

    float getHorSpeed() const;
    void setHorSpeed(float v);

    bool getIsFly() const;
    void setIsFly(bool fly);

    void removeEnemy(int index);
};

#endif