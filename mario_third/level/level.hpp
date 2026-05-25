#ifndef LEVEL_HPP
#define LEVEL_HPP

#include "objects.hpp"

class Level {
private:
    GameObject** floor;
    GameObject** enemies;

    int floorLen;
    int enemiesLen;

public:
    Level();
    ~Level();

    void load(int lvl, int& score);

    void addFloor(GameObject* obj);
    void addEnemy(GameObject* obj);
    void removeEnemy(int index);

    GameObject** getFloor();
    GameObject** getEnemies();

    int getFloorLen() const;
    int getEnemiesLen() const;
};

#endif