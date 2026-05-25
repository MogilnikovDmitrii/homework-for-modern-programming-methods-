#include "level.hpp"
#include "constants.hpp"
#include <cstring> // для memcpy

/* ========== Level ========== */

Level::Level()
    : floor(nullptr), enemies(nullptr),
      floorLen(0), enemiesLen(0)
{
}

Level::~Level()
{
    for (int i = 0; i < floorLen; ++i)
        delete floor[i];
    for (int i = 0; i < enemiesLen; ++i)
        delete enemies[i];
    delete[] floor;
    delete[] enemies;
}

void Level::addFloor(GameObject* obj)
{
    GameObject** newFloor = new GameObject*[floorLen + 1];
    for (int i = 0; i < floorLen; ++i){
        newFloor[i] = floor[i];
    }
    newFloor[floorLen] = obj;
    delete[] floor;
    floor = newFloor;
    floorLen++;
}

void Level::addEnemy(GameObject* obj)
{
    GameObject** newEnemies = new GameObject*[enemiesLen + 1];
    for (int i = 0; i < enemiesLen; ++i)
        newEnemies[i] = enemies[i];
    newEnemies[enemiesLen] = obj;
    delete[] enemies;
    enemies = newEnemies;
    enemiesLen++;
}

void Level::load(int lvl, int& score)
{
    for (int i = 0; i < floorLen; ++i)
        delete floor[i];
    for (int i = 0; i < enemiesLen; ++i)
        delete enemies[i];
    delete[] floor;
    delete[] enemies;
    floor = nullptr;
    enemies = nullptr;
    floorLen = 0;
    enemiesLen = 0;

    if (lvl == 1)
    {
        score = 0;

        addFloor(new Platform(20, 20, 40, 5, SYM_PLATFORM));
        addFloor(new Platform(30, 10, 5, 3, SYM_QUESTION));
        addFloor(new Platform(50, 10, 5, 3, SYM_QUESTION));
        addFloor(new Platform(60, 15, 40, 10, SYM_PLATFORM));
        addFloor(new Platform(60, 5, 10, 3, SYM_DASH));
        addFloor(new Platform(70, 5, 5, 3, SYM_QUESTION));
        addFloor(new Platform(75, 5, 5, 3, SYM_DASH));
        addFloor(new Platform(80, 5, 5, 3, SYM_QUESTION));
        addFloor(new Platform(85, 5, 10, 3, SYM_DASH));
        addFloor(new Platform(100, 20, 20, 5, SYM_PLATFORM));
        addFloor(new Platform(120, 15, 10, 10, SYM_PLATFORM));
        addFloor(new Platform(150, 20, 40, 5, SYM_PLATFORM));
        addFloor(new Platform(210, 15, 10, 10, SYM_PORTAL));

        addEnemy(new Enemy(25, 10));
        addEnemy(new Enemy(80, 10));
    }

    if (lvl == 2)
    {
        addFloor(new Platform(80, 20, 15, 5, SYM_PLATFORM));
        addFloor(new Platform(20, 20, 40, 5, SYM_PLATFORM));
        addFloor(new Platform(120, 15, 15, 10, SYM_PLATFORM));
        addFloor(new Platform(160, 10, 15, 15, SYM_PORTAL));

        addEnemy(new Enemy(25, 10));
        addEnemy(new Enemy(50, 10));
        addEnemy(new Enemy(80, 10));
        addEnemy(new Enemy(90, 10));
        addEnemy(new Enemy(120, 10));
        addEnemy(new Enemy(130, 10));
    }

    if (lvl == 3)
    {
        addFloor(new Platform(20, 20, 40, 5, SYM_PLATFORM));
        addFloor(new Platform(60, 15, 10, 10, SYM_PLATFORM));
        addFloor(new Platform(80, 20, 20, 5, SYM_PLATFORM));
        addFloor(new Platform(120, 15, 10, 10, SYM_PLATFORM));
        addFloor(new Platform(150, 20, 40, 5, SYM_PLATFORM));
        addFloor(new Platform(210, 15, 10, 10, SYM_PORTAL));

        addEnemy(new Enemy(25, 10));
        addEnemy(new Enemy(85, 10));
        addEnemy(new Enemy(65, 10));
        addEnemy(new Enemy(120, 10));
        addEnemy(new Enemy(160, 10));
        addEnemy(new Enemy(175, 10));
    }
}

/* ========== gettesr ========== */

GameObject** Level::getFloor()
{
    return floor;
}

GameObject** Level::getEnemies()
{
    return enemies;
}

int Level::getFloorLen() const
{
    return floorLen;
}

int Level::getEnemiesLen() const
{
    return enemiesLen;
}

void Level::removeEnemy(int index) {
    if (index < 0 || index >= enemiesLen) return;
    delete enemies[index];
    for (int i = index; i < enemiesLen - 1; ++i)
        enemies[i] = enemies[i + 1];
    enemiesLen--;
    if (enemiesLen == 0) {
        delete[] enemies;
        enemies = nullptr;
    }
}