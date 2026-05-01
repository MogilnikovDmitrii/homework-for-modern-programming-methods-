#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
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
int needReload = 0;
int maxLevel = 2;

TObject *enemys = NULL;
int enemysLen;

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
    printf("\033[H\033[J"); // очистка экрана

    // фон + текст (аналог 9F: яркий белый + синий фон)
    printf("\033[97;44m");

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

void InitObject(TObject *obj, float xPos, float yPos, float oWidth, float oHeight,char inType){
    SetObjectPos(obj,xPos,yPos);
    obj->width = oWidth;
    obj->heigth = oHeight;
    obj->VertSpeed = 0; 
    obj->ObType = inType;
    obj->HorSpeed = 0.2;
}
bool IsCollision(TObject o1, TObject o2);
void CreateLevel(int lvl);

void FallingOfObject(TObject *obj) {
    obj->VertSpeed += 0.05;
    obj->IsFly = true;
    SetObjectPos(obj, obj->x, obj->y + obj->VertSpeed);
    for(int i = 0; i < FloorLen; i++){
        if (IsCollision(*obj,Floor[i])){
            obj->y -= obj->VertSpeed;
            obj->VertSpeed = 0;
            obj->IsFly = false;
            if(Floor[i].ObType == '+'){
                level++;

                if (level > maxLevel){
                    level = 1;
                }
                needReload = 1;
            }
            break;
        }
    }
}

void PersonCollision(){
    for(int i = 0; i < enemysLen; i++){
        if(IsCollision(mario,enemys[i])){
            CreateLevel(level);
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
    TObject tmp = *obj;
    FallingOfObject(&tmp);
    if(tmp.IsFly == true){
        obj[0].x -= obj[0].HorSpeed;
        obj[0].HorSpeed *= -1;
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
            return;
        }
    }
}

bool IsCollision(TObject o1, TObject o2) {
    return ((o1.x + o1.width > o2.x) && (o1.x < o2.x + o2.width) && 
    (o1.y + o1.heigth > o2.y) && (o1.y < o2.y + o2.heigth));
}

void CreateLevel(int lvl) {
    InitObject(&mario,39,10, 3, 3,'$');
    if (lvl == 2){
        FloorLen = 4;
        Floor = (TObject*)realloc(Floor, sizeof(*Floor) * FloorLen);
        InitObject(Floor+0,20,20,40,5,'#');
        InitObject(Floor+1,80,20,15,5,'#');
        InitObject(Floor+2,120,15,15,10,'#');
        InitObject(Floor+3,160,10,15,15,'+');
        

    }
    if (lvl == 1){
        FloorLen = 6;
        Floor = (TObject*)realloc(Floor, sizeof(TObject) * FloorLen);
        InitObject(Floor+0,20,20,40,5,'#');
        InitObject(Floor+1,60,15,10,10,'#');
        InitObject(Floor+2,80,20,20,5,'#');
        InitObject(Floor+3,120,15,10,10,'#');
        InitObject(Floor+4,150,20,40,5,'#');
        InitObject(Floor+5,210,15,10,10,'+');
        enemysLen = 1;
        enemys = (TObject*)realloc(enemys, sizeof(*enemys) * enemysLen);
        InitObject(enemys+0,25,10,3,2,'%');
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
        if (needReload || mario.y > mapHeight) {
            needReload = 0;
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

        }
        PutObjectOnMap(mario);
        ShowMap();

        usleep(25000);

    } while (1);

    return 0;
}