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

/*system*/

void setNonBlocking() {

    struct termios ttystate;

    tcgetattr(STDIN_FILENO, &ttystate);

    ttystate.c_lflag &= ~(ICANON | ECHO);

    tcsetattr(STDIN_FILENO, TCSANOW, &ttystate);

    fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK);
}

/* initialisation*/

void CreateLevel(int lvl) {

    delete[] Floor;
    delete[] enemys;

    Floor = nullptr;
    enemys = nullptr;

    FloorLen = 0;
    enemysLen = 0;

    InitObject(&mario, 39, 10, 3, 3, '@');

    MapColor = "\033[97;44m";

    if(lvl == 1) {

        score = 0;

        InitObject(GetNewObj(),20,20,40,5,'#');
        InitObject(GetNewObj(),30,10,5,3,'?');

        InitObject(GetNewEn(),25,10,3,2,'%');
    }
}

TObject* GetNewEn() {

    enemysLen++;

    TObject* temp = new TObject[enemysLen];

    for(int i = 0; i < enemysLen - 1; i++)
        temp[i] = enemys[i];

    delete[] enemys;

    enemys = temp;

    return enemys + enemysLen - 1;
}

TObject* GetNewObj() {

    FloorLen++;

    TObject* temp = new TObject[FloorLen];

    for(int i = 0; i < FloorLen - 1; i++)
        temp[i] = Floor[i];

    delete[] Floor;

    Floor = temp;

    return Floor + FloorLen - 1;
}

void InitObject(
    TObject *obj,
    float xPos,
    float yPos,
    float w,
    float h,
    char type
) {
    SetObjectPos(obj, xPos, yPos);

    obj->width = w;
    obj->heigth = h;

    obj->VertSpeed = 0;
    obj->HorSpeed = 0.2f;
    obj->IsFly = false;
    obj->ObType = type;
}

void SetObjectPos(TObject *obj, float x, float y) {
    obj->x = x;
    obj->y = y;
}

/*map renderer*/

void ClearMap() {

    for(int i = 0; i < mapWidth; i++)
        map[0][i] = ' ';

    map[0][mapWidth] = '\0';

    for(int j = 1; j < mapHeight; j++)
        sprintf(map[j], "%s", map[0]);
}

bool IsPosOnMap(int x, int y) {
    return (
        x >= 0 &&
        y >= 0 &&
        x < mapWidth &&
        y < mapHeight
    );
}

void PutObjectOnMap(TObject obj) {

    int ix = (int)round(obj.x);
    int iy = (int)round(obj.y);

    int w = (int)round(obj.width);
    int h = (int)round(obj.heigth);

    for(int i = ix; i < ix + w; i++) {
        for(int j = iy; j < iy + h; j++) {

            if(IsPosOnMap(i, j))
                map[j][i] = obj.ObType;
        }
    }
}

void ShowMap() {

    printf("\033[H");
    printf("%s", MapColor);
    printf("\033[J");

    for(int j = 0; j < mapHeight; j++)
        printf("%s\n", map[j]);

    printf("\033[0m");
}

/* physics */

void FallingOfObject(TObject *obj) {

    obj->VertSpeed += 0.05f;
    obj->IsFly = true;

    SetObjectPos(obj,
        obj->x,
        obj->y + obj->VertSpeed
    );
}

void HorisontalMapMove(float dx) {

    for(int i = 0; i < FloorLen; i++)
        Floor[i].x += dx;

    for(int i = 0; i < enemysLen; i++)
        enemys[i].x += dx;
}

void HorizObjMove(TObject *obj) {

    obj->x += obj->HorSpeed;

    for(int i = 0; i < FloorLen; i++) {

        if(IsCollision(*obj, Floor[i])) {

            obj->x -= obj->HorSpeed;
            obj->HorSpeed *= -1;
            return;
        }
    }
}

/* collision*/

bool IsCollision(TObject o1, TObject o2) {

    return (
        o1.x + o1.width > o2.x &&
        o1.x < o2.x + o2.width &&
        o1.y + o1.heigth > o2.y &&
        o1.y < o2.y + o2.heigth
    );
}

void PersonCollision() {

    for(int i = 0; i < enemysLen; i++) {

        if(IsCollision(mario, enemys[i])) {
            PlayerDead();
        }
    }
}

/* game logic*/

void DeleteObj(int i) {

    enemysLen--;

    enemys[i] = enemys[enemysLen];

    TObject* temp = nullptr;

    if(enemysLen > 0) {

        temp = new TObject[enemysLen];

        for(int j = 0; j < enemysLen; j++)
            temp[j] = enemys[j];
    }

    delete[] enemys;

    enemys = temp;
}

void PlayerDead() {

    MapColor = "\033[41m";

    ClearMap();
    ShowMap();

    usleep(500000);
}

void ShowScore() {

    char c[30];
    sprintf(c, "Score: %d", score);

    for(int i = 0; i < (int)strlen(c); i++)
        map[1][i + 5] = c[i];
}