
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

void createLevel(int lvl, TObject& mario, TObject*& Floor, int& FloorLen,
                 TObject*& enemys, int& enemysLen, int& score,
                 const char** MapColor);

void initObject(TObject *obj, float xPos, float yPos, float w, float h, char type);

TObject* getNewObj(TObject*& Floor, int& FloorLen);
TObject* getNewEn(TObject*& enemys, int& enemysLen);

void setObjectPos(TObject *obj, float x, float y);

void clearMap(char map[mapHeight][mapWidth+1]);

bool isPosOnMap(int x, int y);

void showMap(char map[mapHeight][mapWidth+1], const char* MapColor);

void putObjectOnMap(TObject obj, char map[mapHeight][mapWidth+1]);

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

bool isCollision(TObject o1, TObject o2);

void personCollision(TObject* mario, TObject*& enemys, int& enemysLen,
                     int& score, TObject*& Floor, int& FloorLen,
                     int level, const char** MapColor,
                     char map[mapHeight][mapWidth+1]);

void deleteObj(int i, TObject*& enemys, int& enemysLen);

void playerDead(TObject& mario, TObject*& Floor, int& FloorLen,
                TObject*& enemys, int& enemysLen, int level, int& score,
                const char** MapColor, char map[mapHeight][mapWidth+1]);

void showScore(char map[mapHeight][mapWidth+1], int score);

void setNonBlocking();

#endif