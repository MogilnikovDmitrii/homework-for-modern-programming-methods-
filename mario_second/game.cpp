#include "game.hpp"

char map[mapHeight][mapWidth+1];

TObject mario;

TObject *Floor = nullptr;
int FloorLen = 0;

int level = 1;
int score = 0;

int needReload = 0;
int maxLevel = 2;

TObject *enemys = nullptr;
int enemysLen = 0;

const char* MapColor;

void ClearMap() {

    for (int i = 0; i < mapWidth; i++){
        map[0][i] = ' ';
    }

    map[0][mapWidth] = '\0';

    for (int j = 1; j < mapHeight; j++){
        sprintf(map[j], "%s", map[0]);
    }
}

void CreateLevel(int lvl) {

    delete[] Floor;
    delete[] enemys;

    Floor = nullptr;
    enemys = nullptr;

    FloorLen = 0;
    enemysLen = 0;

    InitObject(&mario,39,10,3,3,'@');

    MapColor = "\033[97;44m";

    if(lvl == 1){

        score = 0;

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
}

void DeleteObj(int i) {

    enemysLen--;

    enemys[i] = enemys[enemysLen];

    TObject* temp = nullptr;

    if(enemysLen > 0){

        temp = new TObject[enemysLen];

        for(int j = 0; j < enemysLen; j++){
            temp[j] = enemys[j];
        }
    }

    delete[] enemys;

    enemys = temp;
}

void FallingOfObject(TObject *obj) {

    obj->VertSpeed += 0.05f;
    obj->IsFly = true;

    SetObjectPos(obj, obj->x, obj->y + obj->VertSpeed);

    for(int i = 0; i < FloorLen; i++){

        if (IsCollision(*obj,Floor[i])){

            if((Floor[i].ObType == '?') &&
               (obj->VertSpeed < 0) &&
               (obj == &mario)){

                Floor[i].ObType = '-';

                InitObject(GetNewEn(),
                           Floor[i].x,
                           Floor[i].y - 3,
                           3,2,'$');

                enemys[enemysLen -1].VertSpeed = -0.3f;
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

bool IsCollision(TObject o1, TObject o2) {

    return (
        (o1.x + o1.width > o2.x) &&
        (o1.x < o2.x + o2.width) &&
        (o1.y + o1.heigth > o2.y) &&
        (o1.y < o2.y + o2.heigth)
    );
}

bool IsPosOnMap(int x, int y) {

    return (
        x >= 0 &&
        y >= 0 &&
        x < mapWidth &&
        y < mapHeight
    );
}

void HorizObjMove(TObject *obj) {

    obj->x += obj->HorSpeed;

    for(int i = 0 ; i < FloorLen; i++){

        if (IsCollision(*obj,Floor[i])){

            obj->x -= obj->HorSpeed;
            obj->HorSpeed *= -1;
            return;
        }
    }

    if(obj->ObType == '%'){

        TObject tmp = *obj;

        FallingOfObject(&tmp);

        if(tmp.IsFly == true){

            obj->x -= obj->HorSpeed;
            obj->HorSpeed *= -1;
        }
    }
}

void HorisontalMapMove(float dx) {

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

void InitObject(TObject *obj,
                float xPos,
                float yPos,
                float oWidth,
                float oHeight,
                char inType) {

    SetObjectPos(obj,xPos,yPos);

    obj->width = oWidth;
    obj->heigth = oHeight;

    obj->VertSpeed = 0;
    obj->ObType = inType;
    obj->HorSpeed = 0.2f;
}

void PersonCollision() {

    for(int i = 0; i < enemysLen; i++){

        if(IsCollision(mario,enemys[i])){

            if(enemys[i].ObType == '%'){

                if(mario.IsFly &&
                   mario.VertSpeed > 0 &&
                   mario.y + mario.heigth <
                   enemys[i].y + enemys[i].heigth * 0.5f){

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

void PlayerDead() {

    MapColor = "\033[41m";

    ClearMap();
    ShowMap();

    usleep(500000);

    CreateLevel(level);
}

void PutObjectOnMap(TObject obj) {

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

void SetObjectPos(TObject *obj, float xPos, float yPos) {

    obj->x = xPos;
    obj->y = yPos;
}

void ShowMap() {

    printf("\033[H");
    printf("%s", MapColor);
    printf("\033[J");

    for (int j = 0; j < mapHeight; j++){
        printf("%s\n", map[j]);
    }

    printf("\033[0m");
}

void ShowScore() {

    char c[30];

    sprintf(c, "Score: %d", score);

    int len = strlen(c);

    for(int i = 0; i < len; i++){
        map[1][i+5] = c[i];
    }
}

void SetNonBlocking() {

    struct termios ttystate;

    tcgetattr(STDIN_FILENO, &ttystate);
    ttystate.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &ttystate);

    fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK);
}