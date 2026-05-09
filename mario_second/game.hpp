#ifndef GAME_HPP
#define GAME_HPP

#include <algorithm>
#include <fcntl.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

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

void ClearMap();
void CreateLevel(int lvl);

void DeleteObj(int i);
void FallingOfObject(TObject *obj);

TObject *GetNewEn();
TObject *GetNewObj();

void HorizObjMove(TObject *obj);
void HorisontalMapMove(float dx);

void InitObject(
    TObject *obj,
    float xPos,
    float yPos,
    float oWidth,
    float oHeight,
    char inType
);

bool IsCollision(TObject o1, TObject o2);
bool IsPosOnMap(int x, int y);
void PersonCollision();

void PlayerDead();
void PutObjectOnMap(TObject obj);
void SetObjectPos(TObject *obj, float xPos, float yPos);
void SetNonBlocking();

void ShowMap();
void ShowScore();
#endif