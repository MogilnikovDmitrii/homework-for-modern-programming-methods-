#ifndef GAME_HPP
#define GAME_HPP

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#include <string.h>
#include <algorithm>

#define mapWidth 80
#define mapHeight 25

struct TObject{
    float x,y;
    float width,heigth;

    float VertSpeed;

    bool IsFly;

    char ObType;

    float HorSpeed;
};

extern char map[mapHeight][mapWidth+1];

extern TObject mario;

extern TObject* Floor;
extern int FloorLen;

extern int level;
extern int score;

extern int needReload;
extern int maxLevel;

extern TObject* enemys;
extern int enemysLen;

extern const char* MapColor;

void setNonBlocking();

void ClearMap();

void ShowMap();

void SetObjectPos(TObject *obj, float xPos, float yPos);

void CreateLevel(int lvl);

void InitObject(
    TObject *obj,
    float xPos,
    float yPos,
    float oWidth,
    float oHeight,
    char inType
);

void PlayerDead();

bool IsCollision(TObject o1, TObject o2);

TObject *GetNewEn();

void FallingOfObject(TObject *obj);

void DeleteObj(int i);

void PersonCollision();

void HorizObjMove(TObject *obj);

bool IsPosOnMap(int x, int y);

void PutObjectOnMap(TObject obj);

void HorisontalMapMove(float dx);

TObject *GetNewObj();

void ShowScore();

#endif