#ifndef LEVEL_HPP
#define LEVEL_HPP

#include "coin.hpp"
#include "enemy.hpp"
#include "gameObject.hpp"
#include "movableObject.hpp"
#include "platform.hpp"
#include "player.hpp"
#include "stableObject.hpp"


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

    GameObject** getFloor();
    GameObject** getEnemies();

    int getFloorLen() const;
    int getEnemiesLen() const;
    void removeEnemy(int index);
};

#endif