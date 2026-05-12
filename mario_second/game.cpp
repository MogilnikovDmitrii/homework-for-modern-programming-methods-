#include "game.hpp"
/* ========== initialisation ========== */

TObject* getNewObj(TObject*& Floor, int& FloorLen) {
    FloorLen++;
    TObject* temp = new TObject[FloorLen];
    for (int i = 0; i < FloorLen - 1; i++) temp[i] = Floor[i];
    delete[] Floor;
    Floor = temp;
    return Floor + FloorLen - 1;
}

TObject* getNewEn(TObject*& enemys, int& enemysLen) {
    enemysLen++;
    TObject* temp = new TObject[enemysLen];
    for (int i = 0; i < enemysLen - 1; i++) temp[i] = enemys[i];
    delete[] enemys;
    enemys = temp;
    return enemys + enemysLen - 1;
}

void initObject(TObject* obj, float xPos, float yPos, float w, float h, char type) {
    obj->x = xPos;
    obj->y = yPos;
    obj->width = w;
    obj->heigth = h;
    obj->VertSpeed = 0;
    obj->IsFly = false;
    obj->ObType = type;
    obj->HorSpeed = 0.2f;
}

void setObjectPos(TObject* obj, float x, float y) {
    obj->x = x;
    obj->y = y;
}

void createLevel(int lvl, TObject& mario, TObject*& Floor, int& FloorLen,
                 TObject*& enemys, int& enemysLen, int& score,
                 const char** MapColor) {
    delete[] Floor;
    delete[] enemys;
    Floor = nullptr;
    enemys = nullptr;
    FloorLen = 0;
    enemysLen = 0;

    initObject(&mario, 39, 10, 3, 3, '@');
    *MapColor = "\033[97;44m";

    if (lvl == 1) {
        score = 0;
        initObject(getNewObj(Floor, FloorLen), 20, 20, 40, 5, '#');
        initObject(getNewObj(Floor, FloorLen), 30, 10, 5, 3, '?');
        initObject(getNewObj(Floor, FloorLen), 50, 10, 5, 3, '?');
        initObject(getNewObj(Floor, FloorLen), 60, 15, 40, 10, '#');
        initObject(getNewObj(Floor, FloorLen), 60, 5, 10, 3, '-');
        initObject(getNewObj(Floor, FloorLen), 70, 5, 5, 3, '?');
        initObject(getNewObj(Floor, FloorLen), 75, 5, 5, 3, '-');
        initObject(getNewObj(Floor, FloorLen), 80, 5, 5, 3, '?');
        initObject(getNewObj(Floor, FloorLen), 85, 5, 10, 3, '-');
        initObject(getNewObj(Floor, FloorLen), 100, 20, 20, 5, '#');
        initObject(getNewObj(Floor, FloorLen), 120, 15, 10, 10, '#');
        initObject(getNewObj(Floor, FloorLen), 150, 20, 40, 5, '#');
        initObject(getNewObj(Floor, FloorLen), 210, 15, 10, 10, '+');
        initObject(getNewEn(enemys, enemysLen), 25, 10, 3, 2, '%');
        initObject(getNewEn(enemys, enemysLen), 80, 10, 3, 2, '%');
    }

    if (lvl == 2) {
        initObject(getNewObj(Floor, FloorLen), 80, 20, 15, 5, '#');
        initObject(getNewObj(Floor, FloorLen), 20, 20, 40, 5, '#');
        initObject(getNewObj(Floor, FloorLen), 120, 15, 15, 10, '#');
        initObject(getNewObj(Floor, FloorLen), 160, 10, 15, 15, '+');
        initObject(getNewEn(enemys, enemysLen), 25, 10, 3, 2, '%');
        initObject(getNewEn(enemys, enemysLen), 50, 10, 3, 2, '%');
        initObject(getNewEn(enemys, enemysLen), 80, 10, 3, 2, '%');
        initObject(getNewEn(enemys, enemysLen), 90, 10, 3, 2, '%');
        initObject(getNewEn(enemys, enemysLen), 120, 10, 3, 2, '%');
        initObject(getNewEn(enemys, enemysLen), 130, 10, 3, 2, '%');
    }

    if (lvl == 3) {
        initObject(getNewObj(Floor, FloorLen), 20, 20, 40, 5, '#');
        initObject(getNewObj(Floor, FloorLen), 60, 15, 10, 10, '#');
        initObject(getNewObj(Floor, FloorLen), 80, 20, 20, 5, '#');
        initObject(getNewObj(Floor, FloorLen), 120, 15, 10, 10, '#');
        initObject(getNewObj(Floor, FloorLen), 150, 20, 40, 5, '#');
        initObject(getNewObj(Floor, FloorLen), 210, 15, 10, 10, '+');
        initObject(getNewEn(enemys, enemysLen), 25, 10, 3, 2, '%');
        initObject(getNewEn(enemys, enemysLen), 85, 10, 3, 2, '%');
        initObject(getNewEn(enemys, enemysLen), 65, 10, 3, 2, '%');
        initObject(getNewEn(enemys, enemysLen), 120, 10, 3, 2, '%');
        initObject(getNewEn(enemys, enemysLen), 160, 10, 3, 2, '%');
        initObject(getNewEn(enemys, enemysLen), 175, 10, 3, 2, '%');
    }
}

/* ========== map render ========== */

void clearMap(char map[mapHeight][mapWidth+1]) {
    for (int i = 0; i < mapWidth; i++) map[0][i] = ' ';
    map[0][mapWidth] = '\0';
    for (int j = 1; j < mapHeight; j++) sprintf(map[j], "%s", map[0]);
}

bool isPosOnMap(int x, int y) {
    return x >= 0 && y >= 0 && x < mapWidth && y < mapHeight;
}

void putObjectOnMap(TObject obj, char map[mapHeight][mapWidth+1]) {
    int ix = (int)round(obj.x);
    int iy = (int)round(obj.y);
    int iw = (int)round(obj.width);
    int ih = (int)round(obj.heigth);
    for (int i = ix; i < ix + iw; i++) {
        for (int j = iy; j < iy + ih; j++) {
            if (isPosOnMap(i, j)) map[j][i] = obj.ObType;
        }
    }
}

void showMap(char map[mapHeight][mapWidth+1], const char* MapColor) {
    printf("\033[H");
    printf("%s", MapColor);
    printf("\033[J");
    for (int j = 0; j < mapHeight; j++) printf("%s\n", map[j]);
    printf("\033[0m");
}

void showScore(char map[mapHeight][mapWidth+1], int score) {
    char buf[30];
    sprintf(buf, "Score: %d", score);
    int len = strlen(buf);
    for (int i = 0; i < len; i++) map[1][i + 5] = buf[i];
}

/* ========== physics ========== */

void fallingOfObject(TObject *obj, TObject* Floor, int FloorLen,
                     TObject*& enemys, int& enemysLen, TObject* mario,
                     int& level, int maxLevel, int& needReload,
                     const char** MapColor) {
    obj->VertSpeed += 0.05f;
    obj->IsFly = true;
    obj->y += obj->VertSpeed;
    for (int i = 0; i < FloorLen; i++) {
        if (isCollision(*obj, Floor[i])) {
            if (Floor[i].ObType == '?' && obj->VertSpeed < 0 && obj == mario) {
                Floor[i].ObType = '-';
                TObject* newEn = getNewEn(enemys, enemysLen);
                initObject(newEn, Floor[i].x, Floor[i].y - 3, 3, 2, '$');
                newEn->VertSpeed = -0.3f;
            }
            obj->y -= obj->VertSpeed;
            obj->VertSpeed = 0;
            obj->IsFly = false;
            if (Floor[i].ObType == '+') {
                level++;
                if (level > maxLevel) level = 1;
                *MapColor = "\033[42m";
                needReload = 1;
                usleep(1000000);
            }
            break;
        }
    }
}

void horizObjMove(TObject *obj, TObject* Floor, int FloorLen,
                  TObject*& enemys, int& enemysLen, TObject* mario,
                  int& level, int maxLevel, int& needReload,
                  const char** MapColor) {
    obj->x += obj->HorSpeed;
    for (int i = 0; i < FloorLen; i++) {
        if (isCollision(*obj, Floor[i])) {
            obj->x -= obj->HorSpeed;
            obj->HorSpeed *= -1;
            return;
        }
    }
    if (obj->ObType == '%') {
        TObject tmp = *obj;
        fallingOfObject(&tmp, Floor, FloorLen, enemys, enemysLen, mario,
                        level, maxLevel, needReload, MapColor);
        if (tmp.IsFly) {
            obj->x -= obj->HorSpeed;
            obj->HorSpeed *= -1;
        }
    }
}

void horisontalMapMove(float dx, TObject* Floor, int FloorLen,
                       TObject* enemys, int enemysLen, TObject* mario) {
    for (int i = 0; i < FloorLen; i++) Floor[i].x += dx;
    for (int i = 0; i < enemysLen; i++) enemys[i].x += dx;
    for (int i = 0; i < FloorLen; i++) {
        if (isCollision(*mario, Floor[i])) {
            for (int j = 0; j < FloorLen; j++) Floor[j].x -= dx;
            for (int j = 0; j < enemysLen; j++) enemys[j].x -= dx;
            return;
        }
    }
}

/* ========== collision ========== */

bool isCollision(TObject o1, TObject o2) {
    return (o1.x + o1.width > o2.x) &&
           (o1.x < o2.x + o2.width) &&
           (o1.y + o1.heigth > o2.y) &&
           (o1.y < o2.y + o2.heigth);
}

void personCollision(TObject* mario, TObject*& enemys, int& enemysLen,
                     int& score, TObject*& Floor, int& FloorLen,
                     int level, const char** MapColor,
                     char map[mapHeight][mapWidth+1]) {
    for (int i = 0; i < enemysLen; i++) {
        if (isCollision(*mario, enemys[i])) {
            if (enemys[i].ObType == '%') {
                if (mario->IsFly && mario->VertSpeed > 0 &&
                    mario->y + mario->heigth < enemys[i].y + enemys[i].heigth * 0.5f) {
                    deleteObj(i, enemys, enemysLen);
                    i--;
                    score += 5;
                    continue;
                } else {
                    playerDead(*mario, Floor, FloorLen, enemys, enemysLen,
                               level, score, MapColor, map);
                }
            } else if (enemys[i].ObType == '$') {
                deleteObj(i, enemys, enemysLen);
                i--;
                score += 10;
            }
        }
    }
}

/* ========== game logic ========== */

void deleteObj(int i, TObject*& enemys, int& enemysLen) {
    enemysLen--;
    enemys[i] = enemys[enemysLen];
    TObject* temp = nullptr;
    if (enemysLen > 0) {
        temp = new TObject[enemysLen];
        for (int j = 0; j < enemysLen; j++) temp[j] = enemys[j];
    }
    delete[] enemys;
    enemys = temp;
}

void playerDead(TObject& mario, TObject*& Floor, int& FloorLen,
                TObject*& enemys, int& enemysLen, int level, int& score,
                const char** MapColor, char map[mapHeight][mapWidth+1]) {
    *MapColor = "\033[41m";
    clearMap(map);
    showMap(map, *MapColor);
    usleep(500000);
    createLevel(level, mario, Floor, FloorLen, enemys, enemysLen, score, MapColor);
}

/* ========== system ========== */

void setNonBlocking() {
    struct termios ttystate;
    tcgetattr(STDIN_FILENO, &ttystate);
    ttystate.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &ttystate);
    fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK);
}