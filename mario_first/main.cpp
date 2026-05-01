#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>

#define mapWidth 80
#define mapHeight 25

typedef struct SObject{
    float x,y;
    float width,heigth;
    float VertSpeed;

} TObject;

char map[mapHeight][mapWidth+1];
TObject mario;
TObject Floor[1];

// --- ДОБАВЛЯЕМ ---
void setNonBlocking() {
    struct termios ttystate;

    tcgetattr(STDIN_FILENO, &ttystate);
    ttystate.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &ttystate);

    fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK);
}
// ------------------

void ClearMap(){
    for (int i = 0; i < mapWidth; i++){
        map[0][i] = '.';
    }
    map[0][mapWidth] = '\0';

    for ( int j = 1; j < mapHeight; j++){
        sprintf(map[j], "%s", map[0]);
    }
}   

void ShowMap() {
    printf("\033[H\033[J"); // очистка экрана
    for (int j = 0; j < mapHeight; j++){
        printf("%s\n", map[j]);
    }
}

void SetObjectPos(TObject *obj, float xPos, float yPos){
    obj->x = xPos;
    obj->y = yPos;
}

void InitObject(TObject *obj, float xPos, float yPos, float oWidth, float oHeight){
    SetObjectPos(obj,xPos,yPos);
    obj->width = oWidth;
    obj->heigth = oHeight;
    obj->VertSpeed = 0; 
}

bool IsCollision(TObject o1, TObject o2);

void FallingOfObject(TObject *obj) {
    obj->VertSpeed += 0.05;
    SetObjectPos(obj, obj->x, obj->y + obj->VertSpeed);
    if (IsCollision(*obj,Floor[0])){
        obj->y -= obj->VertSpeed;
        obj->VertSpeed = 0;
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
                map[j][i] = '$';
            }
        }
    }
}

bool IsCollision(TObject o1, TObject o2) {
    return ((o1.x + o1.width > o2.x) && (o1.x < o2.x + o2.width) && 
    (o1.y + o1.heigth > o2.y) && (o1.y < o2.y + o2.heigth));
}

int main() {
    InitObject(&mario,39 ,10 ,3 ,3);
    InitObject(Floor, 20,20,40,5);
    setNonBlocking(); // <-- важно

    char key;

    do {
        ClearMap();
        FallingOfObject(&mario);
        PutObjectOnMap(Floor[0]);
        PutObjectOnMap(mario);
        ShowMap();

        // читаем клавишу (если есть)
        if (read(STDIN_FILENO, &key, 1) > 0) {
            if (key == 27) break; // ESC
        }
        usleep(50000); // 50 мс
    } while (true);
    
    
    return 0;
}