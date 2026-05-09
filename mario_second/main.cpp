#include "game.hpp"

int main() {

    CreateLevel(level);

    SetNonBlocking();

    char key;

    int moveLeft = 0;
    int moveRight = 0;

    do {

        moveLeft = 0;
        moveRight = 0;

        while (read(STDIN_FILENO, &key, 1) > 0) {

            if (key == 27){
                return 0;
            }

            if (key == ' ') {

                if (!mario.IsFly) {
                    mario.VertSpeed = -1.3f;
                }
            }

            if (key == 'a'){
                moveLeft = 1;
            }

            if (key == 'd'){
                moveRight = 1;
            }
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

            MapColor = "\033[42m";

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