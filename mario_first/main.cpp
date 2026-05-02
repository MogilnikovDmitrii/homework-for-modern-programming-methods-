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

typedef struct SObject{
    float x,y;
    float width,heigth;
    float VertSpeed;
    bool IsFly;
    char ObType;
    float HorSpeed;


} TObject;

char map[mapHeight][mapWidth+1];
TObject mario;
TObject *Floor = NULL;
int FloorLen;
int level = 1;
int score;
int needReload = 0;
int maxLevel = 2;

TObject *enemys = NULL;
int enemysLen;
const char* MapColor;

void setNonBlocking() {
    struct termios ttystate;

    tcgetattr(STDIN_FILENO, &ttystate);
    ttystate.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &ttystate);

    fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK);
}

void ClearMap(){
    for (int i = 0; i < mapWidth; i++){
        map[0][i] = ' ';
    }
    map[0][mapWidth] = '\0';

    for ( int j = 1; j < mapHeight; j++){
        sprintf(map[j], "%s", map[0]);
    }
}   

void ShowMap() {
    printf("\033[H");
    printf("%s", MapColor);
    printf("\033[J");   

    for (int j = 0; j < mapHeight; j++){
        printf("%s\n", map[j]);
    }

    // сброс цвета
    printf("\033[0m");
}

void SetObjectPos(TObject *obj, float xPos, float yPos){
    obj->x = xPos;
    obj->y = yPos;
}
void CreateLevel(int lvl);


void InitObject(TObject *obj, float xPos, float yPos, float oWidth, float oHeight,char inType){
    SetObjectPos(obj,xPos,yPos);
    obj->width = oWidth;
    obj->heigth = oHeight;
    obj->VertSpeed = 0; 
    obj->ObType = inType;
    obj->HorSpeed = 0.2;
}



void PlayerDead() {
    MapColor = "\033[41m"; 

    ClearMap();
    ShowMap();             

    usleep(500000);       

    CreateLevel(level);  
}
bool IsCollision(TObject o1, TObject o2);

TObject *GetNewEn();

void FallingOfObject(TObject *obj) {
    obj->VertSpeed += 0.05;
    obj->IsFly = true;
    SetObjectPos(obj, obj->x, obj->y + obj->VertSpeed);
    for(int i = 0; i < FloorLen; i++){
        if (IsCollision(*obj,Floor[i])){


            if((Floor[i].ObType == '?') && (obj[0].VertSpeed < 0) && (obj == &mario)){
                Floor[i].ObType = '-';
                InitObject(GetNewEn(), Floor[i].x, Floor[i].y-3,3,2,'$');
                enemys[enemysLen -1].VertSpeed = -0.3;

            }



            obj->y -= obj->VertSpeed;
            obj->VertSpeed = 0;
            obj->IsFly = false;
            if(Floor[i].ObType == '+'){
                level++;
                if (level > maxLevel){
                    level = 1;
                }
                MapColor = "\033[42m";
                needReload = 1;
                usleep(1000000);

            }
            break;
        }
    }
}

void DeleteObj(int i) {
    enemysLen--;
    enemys[i] = enemys[enemysLen];
    enemys = (TObject*)realloc(enemys, sizeof(*enemys) * enemysLen);

}

void PersonCollision(){
    for(int i = 0; i < enemysLen; i++){
        if(IsCollision(mario,enemys[i])){
            if(enemys[i].ObType == '%'){
                if((mario.IsFly == true) && (mario.VertSpeed > 0) && (mario.y + mario.heigth < enemys[i].y + enemys[i].heigth * 0.5)){
                    DeleteObj(i);
                    i--;
                    score += 5;
                    continue;
                } else {
                    PlayerDead();
                }
            } else if(enemys[i].ObType == '$'){
                DeleteObj(i);
                i--;
                score += 10;
                continue;
            }
        }
    }

}


void HorizObjMove(TObject *obj) {
    obj[0].x += obj[0].HorSpeed;
    for(int i = 0 ; i < FloorLen; i++){
        if (IsCollision(obj[0],Floor[i])){
            obj[0].x -= obj[0].HorSpeed;
            obj[0].HorSpeed *= -1;
            return;
        }
    }
    if(obj[0].ObType == '%'){
        TObject tmp = *obj;
        FallingOfObject(&tmp);
        if(tmp.IsFly == true){
            obj[0].x -= obj[0].HorSpeed;
            obj[0].HorSpeed *= -1;
        }
    }
    
}


bool IsPosOnMap(int x, int y) {
    return  ((x >= 0) && (y >= 0) && (x < mapWidth) && (y < mapHeight));
}
void PutObjectOnMap(TObject obj){
    int ix = (int)round(obj.x);
    int iy = (int)round(obj.y);
    int iWidth = (int)round(obj.width);
    int iHeigth = (int)round(obj.heigth);

    for (int i = ix; i < ix + iWidth; i++){
        for(int j = iy; j < iy + iHeigth;j++){
            if (IsPosOnMap(i,j)){
                map[j][i] = obj.ObType;
            }
        }
    }
}



void HorisontalMapMove(float dx){
    for(int i = 0; i < FloorLen; i++){
        Floor[i].x += dx;
    }
     for(int i = 0; i < enemysLen; i++){
        enemys[i].x += dx;
    }
    for(int i = 0; i < FloorLen; i++){
        if(IsCollision(mario, Floor[i])){
            for(int j = 0; j < FloorLen; j++){
                Floor[j].x -= dx;
            }
            for(int j = 0; j < enemysLen; j++){
                enemys[j].x -= dx;
            }
            return;
        }
    }
}

bool IsCollision(TObject o1, TObject o2) {
    return ((o1.x + o1.width > o2.x) && (o1.x < o2.x + o2.width) && 
    (o1.y + o1.heigth > o2.y) && (o1.y < o2.y + o2.heigth));
}


TObject *GetNewObj() {
    FloorLen++;
    Floor = (TObject*)realloc(Floor,sizeof(*Floor)*FloorLen);
    return Floor + FloorLen -1;
}
TObject *GetNewEn() {
    enemysLen++;
    enemys = (TObject*)realloc(enemys,sizeof(*enemys)*enemysLen);
    return enemys + enemysLen -1;
}

void ShowScore() {
    char c[30];
    sprintf(c, "Score: %d", score);
    int len = strlen(c);
    for(int i = 0; i < len; i++){
        map[1][i+5] = c[i];
    }
}
void CreateLevel(int lvl) {
    FloorLen = 0;
    Floor = (TObject*)realloc(Floor,0);
    enemysLen = 0;
    enemys = (TObject*)realloc(enemys,0);
    InitObject(&mario,39,10, 3, 3,'@');
    MapColor = "\033[97;44m";


    if(lvl == 1){
        score = 0;
        Floor = (TObject*)realloc(Floor, sizeof(*Floor) * FloorLen);
        InitObject(GetNewObj(),20,20,40,5,'#');
            InitObject(GetNewObj(),30,10,5,3,'?');
            InitObject(GetNewObj(),50,10,5,3,'?');
        InitObject(GetNewObj(),60,15,40,10,'#');
            InitObject(GetNewObj(),60,5,10,3,'-');
            InitObject(GetNewObj(),70,5,5,3,'?');
            InitObject(GetNewObj(),75,5,5,3,'-');
            InitObject(GetNewObj(),80,5,5,3,'?');
            InitObject(GetNewObj(),85,5,10,3,'-');

        InitObject(GetNewObj(),100,20,20,5,'#');
        InitObject(GetNewObj(),120,15,10,10,'#');
        InitObject(GetNewObj(),150,20,40,5,'#');
        InitObject(GetNewObj(),210,15,10,10,'+');

        InitObject(GetNewEn(),25,10,3,2,'%');
        InitObject(GetNewEn(),80,10,3,2,'%');
        
    }

    if (lvl == 2){
        InitObject(GetNewObj(),80,20,15,5,'#');
        InitObject(GetNewObj(),20,20,40,5,'#');
        InitObject(GetNewObj(),120,15,15,10,'#');
        
        InitObject(GetNewObj(),160,10,15,15,'+');

        InitObject(GetNewEn(),25,10,3,2,'%');
        InitObject(GetNewEn(),50,10,3,2,'%');
        InitObject(GetNewEn(),80,10,3,2,'%');
        InitObject(GetNewEn(),90,10,3,2,'%');
        InitObject(GetNewEn(),120,10,3,2,'%');
        InitObject(GetNewEn(),130,10,3,2,'%');
        

    }
    if (lvl == 3){
        InitObject(GetNewObj(),20,20,40,5,'#');
        InitObject(GetNewObj(),60,15,10,10,'#');
        InitObject(GetNewObj(),80,20,20,5,'#');
        InitObject(GetNewObj(),120,15,10,10,'#');
        InitObject(GetNewObj(),150,20,40,5,'#');

        InitObject(GetNewObj(),210,15,10,10,'+');

        InitObject(GetNewEn(),25,10,3,2,'%');
        InitObject(GetNewEn(),85,10,3,2,'%');
        InitObject(GetNewEn(),65,10,3,2,'%');
        InitObject(GetNewEn(),120,10,3,2,'%');
        InitObject(GetNewEn(),160,10,3,2,'%');
        InitObject(GetNewEn(),175,10,3,2,'%');

    }

}



int main() {
    CreateLevel(level);
    system("color 9F");
    setNonBlocking();

    char key;
    int moveLeft = 0, moveRight = 0;

    do {
        moveLeft = 0;
        moveRight = 0;

        while (read(STDIN_FILENO, &key, 1) > 0) {
            if (key == 27) return 0;

            if (key == ' ') {
                if (!mario.IsFly) {
                    mario.VertSpeed = -1.3;
                }
            }

            if (key == 'a') moveLeft = 1;
            if (key == 'd') moveRight = 1;
        }
        if (moveRight > 0) {
            HorisontalMapMove(-2);
        }

        if (moveLeft > 0) {
            HorisontalMapMove(2);
        }
        if (mario.y > mapHeight) {
            PlayerDead();
        }

        if (needReload) {
            needReload = 0;

            MapColor = "\033[42m"; // зелёный (победа)
            ClearMap();
            ShowMap();
            usleep(500000);

            CreateLevel(level);
        }
        ClearMap();
        FallingOfObject(&mario);

        PersonCollision();

        for(int i = 0; i < FloorLen;i++){
            PutObjectOnMap(Floor[i]);        
        }
        for(int i = 0; i < enemysLen;i++){
            FallingOfObject(enemys + i);
            HorizObjMove(enemys + i);
            PutObjectOnMap(enemys[i]);
            if(enemys[i].y > mapHeight){
                DeleteObj(i);
                i--;
                continue;
            } 

        }
        PutObjectOnMap(mario);
        ShowScore();
        ShowMap();

        usleep(25000);

    } while (1);

    return 0;
}