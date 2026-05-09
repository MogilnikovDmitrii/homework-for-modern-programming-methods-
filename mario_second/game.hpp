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

    float HorSpeed;
    float VertSpeed;

    bool IsFly;

    char ObType;
};


extern TObject* enemys;
extern int enemysLen;

extern TObject* Floor;
extern int FloorLen;

extern TObject mario;

extern char map[mapHeight][mapWidth+1];

extern const char* MapColor;

extern int level;

extern int maxLevel;

extern int needReload;

extern int score;

/* initialisation*/

void CreateLevel(int lvl);

void InitObject(
    TObject *obj,
    float xPos,
    float yPos,
    float w,
    float h,
    char type
);

TObject* GetNewObj();
TObject* GetNewEn();

void SetObjectPos(TObject *obj, float x, float y);

/*map render*/
void ClearMap();

bool IsPosOnMap(int x, int y);


void ShowMap();

void PutObjectOnMap(TObject obj);


/*physics*/
void FallingOfObject(TObject *obj);

void HorizObjMove(TObject *obj);

void HorisontalMapMove(float dx);

/*collision*/
bool IsCollision(TObject o1, TObject o2);

void PersonCollision();
/* game logic*/
void DeleteObj(int i);

void PlayerDead();


void ShowScore();

/*system*/
void SetNonBlocking();

#endif