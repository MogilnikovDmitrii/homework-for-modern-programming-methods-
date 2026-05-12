#include "game.hpp"

int main() {
    char map[mapHeight][mapWidth+1];
    TObject mario;
    TObject* Floor = nullptr;
    int FloorLen = 0;
    int level = 1;
    int score = 0;
    int needReload = 0;
    int maxLevel = 2;
    TObject* enemys = nullptr;
    int enemysLen = 0;
    const char* MapColor = "\033[97;44m";

    createLevel(level, mario, Floor, FloorLen,
                enemys, enemysLen, score, &MapColor);
    setNonBlocking();

    char key;
    int moveLeft = 0;
    int moveRight = 0;

    do {
        moveLeft = 0;
        moveRight = 0;

        while (read(STDIN_FILENO, &key, 1) > 0) {
            if (key == 27) {
                return 0;
            }
            if (key == ' ') {
                if (!mario.IsFly) {
                    mario.VertSpeed = -1.3f;
                }
            }
            if (key == 'a') {
                moveLeft = 1;
            }
            if (key == 'd') {
                moveRight = 1;
            }
        }

        if (moveRight > 0) {
            horisontalMapMove(-2, Floor, FloorLen, enemys,
                             enemysLen, &mario);
        }
        if (moveLeft > 0) {
            horisontalMapMove(2, Floor, FloorLen, enemys,
                             enemysLen, &mario);
        }

        if (mario.y > mapHeight) {
            playerDead(mario, Floor, FloorLen, enemys,
                             enemysLen, level, score, &MapColor, map);
        }

        if (needReload) {
            needReload = 0;
            MapColor = "\033[42m";
            clearMap(map);
            showMap(map, MapColor);
            usleep(500000);
            createLevel(level, mario, Floor, FloorLen,
                             enemys, enemysLen, score, &MapColor);
        }

        clearMap(map);
        fallingOfObject(&mario, Floor, FloorLen, enemys,
                        enemysLen, &mario, level, maxLevel,
                        needReload, &MapColor);
        personCollision(&mario, enemys, enemysLen, score,
                         Floor, FloorLen, level, &MapColor, map);

        for (int i = 0; i < FloorLen; i++) {
            putObjectOnMap(Floor[i], map);
        }

        for (int i = 0; i < enemysLen; i++) {
            fallingOfObject(enemys + i, Floor, FloorLen, enemys,
                            enemysLen, &mario, level, maxLevel,
                            needReload, &MapColor);
            horizObjMove(enemys + i, Floor, FloorLen, enemys,
                             enemysLen, &mario, level, maxLevel,
                            needReload, &MapColor);
            putObjectOnMap(enemys[i], map);

            if (enemys[i].y > mapHeight) {
                deleteObj(i, enemys, enemysLen);
                i--;
                continue;
            }
        }

        putObjectOnMap(mario, map);
        showScore(map, score);
        showMap(map, MapColor);
        usleep(25000);

    } while (1);

    return 0;
}