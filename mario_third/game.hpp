#ifndef GAME_HPP
#define GAME_HPP

#include <algorithm>
#include <fcntl.h>
#include <math.h>
#include <map>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

#define mapWidth 80
#define mapHeight 25

// ===================== it is base =====================
class GameObject {
protected:
    float x, y;
    float width, height;
    char objType;

public:
    GameObject(float xPos, float yPos, float w, float h, char type);
    virtual ~GameObject();

    virtual void draw(char map[mapHeight][mapWidth + 1]);
    virtual void update() {}  

    bool isCollision(const GameObject& other) const;

    float getX() const;
    float getY() const;

    void setPos(float nx, float ny);
};

// ===================== movable =====================
class MovableObject : public GameObject {
protected:
    float vertSpeed;
    float horSpeed;
    bool isFly;

public:
    MovableObject(float xPos, float yPos, float w, float h, char sym);

    virtual void update() override;

    float getVertSpeed() const;
    void setVertSpeed(float v);

    float getHorSpeed() const;
    void setHorSpeed(float v);

    bool getIsFly() const;
    void setIsFly(bool fly);
};

// ===================== stable =====================
class StableObject : public GameObject {
public:
    StableObject(float xPos, float yPos, float w, float h, char sym);
};

// ===================== game entities =====================
class Player : public MovableObject {
public:
    Player(float xPos = 0, float yPos = 0);
};

class Enemy : public MovableObject {
public:
    Enemy(float xPos = 0, float yPos = 0);
};

class Coin : public MovableObject {
public:
    Coin(float xPos = 0, float yPos = 0);
};

class Platform : public StableObject {
public:
    Platform(float xPos, float yPos, float w, float h, char sym = '#');
};

// ===================== legacy =====================

struct TObject {
    float x, y;
    float width, heigth;
    float HorSpeed;
    float VertSpeed;
    bool IsFly;
    char ObType;
};

// ===================== level show =====================

void createLevel(int lvl, TObject& mario, TObject*& Floor, int& FloorLen,
                 TObject*& enemys, int& enemysLen, int& score,
                 const char** MapColor);

void clearMap(char map[mapHeight][mapWidth + 1]);

bool isPosOnMap(int x, int y);

void showMap(char map[mapHeight][mapWidth + 1], const char* MapColor);

// ===================== old ctructure =====================

void initObject(TObject *obj, float xPos, float yPos, float w, float h, char type);

void setObjectPos(TObject *obj, float x, float y);

TObject* getNewObj(TObject*& Floor, int& FloorLen);
TObject* getNewEn(TObject*& enemys, int& enemysLen);

// physics (legacy)
void fallingOfObject(TObject *obj, TObject* Floor, int FloorLen,
                     TObject*& enemys, int& enemysLen, TObject* mario,
                     int& level, int maxLevel, int& needReload,
                     const char** MapColor);

void horizObjMove(TObject *obj, TObject* Floor, int FloorLen,
                  TObject*& enemys, int& enemysLen, TObject* mario,
                  int& level, int maxLevel, int& needReload,
                  const char** MapColor);

void horisontalMapMove(float dx, TObject* Floor, int FloorLen,
                       TObject* enemys, int enemysLen, TObject* mario);

// collision
bool isCollision(TObject o1, TObject o2);

void personCollision(TObject* mario, TObject*& enemys, int& enemysLen,
                     int& score, TObject*& Floor, int& FloorLen,
                     int level, const char** MapColor,
                     char map[mapHeight][mapWidth + 1]);

void deleteObj(int i, TObject*& enemys, int& enemysLen);

void playerDead(TObject& mario, TObject*& Floor, int& FloorLen,
                TObject*& enemys, int& enemysLen, int level, int& score,
                const char** MapColor, char map[mapHeight][mapWidth + 1]);

void showScore(char map[mapHeight][mapWidth + 1], int score);

void setNonBlocking();

#endif
