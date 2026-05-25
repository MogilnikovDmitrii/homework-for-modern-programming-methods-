#include "renderer.hpp"
#include <cstdio>
#include <cstring>
#include <unistd.h>

/* ========== constructor ========== */
Renderer::Renderer() : currentColor("\033[97;44m")   // синий фон, белый текст
{
    clear();
}

/* ========== clear ========== */
void Renderer::clear()
{
    for (int i = 0; i < mapWidth; i++)
        map[0][i] = ' ';
    map[0][mapWidth] = '\0';
    
    for (int j = 1; j < mapHeight; j++)
        sprintf(map[j], "%s", map[0]);
}

/* ========== draw ========== */
void Renderer::drawObject(const GameObject& obj)
{
    obj.draw(map);
}

/* ========== score ========== */
void Renderer::setScore(int score)
{
    char buf[30];
    sprintf(buf, "Score: %d", score);
    int len = strlen(buf);

    for (int i = 0; i < len && i + 5 < mapWidth; i++)
        map[1][i + 5] = buf[i];
}

/* ========== color ========== */
void Renderer::setColor(const char* color)
{
    currentColor = color;
}

/* ========== render map ========== */
void Renderer::render() const
{
    printf("\033[H");           
    printf("%s", currentColor); 
    printf("\033[J");          
    for (int j = 0; j < mapHeight; j++)
        printf("%s\n", map[j]);
    printf("\033[0m");         
    fflush(stdout);
}