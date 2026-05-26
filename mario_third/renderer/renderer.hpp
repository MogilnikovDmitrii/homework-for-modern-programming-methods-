#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "coin.hpp"
#include "enemy.hpp"
#include "gameObject.hpp"
#include "movableObject.hpp"
#include "platform.hpp"
#include "player.hpp"
#include "stableObject.hpp"


class Renderer {
private:
    char map[mapHeight][mapWidth + 1];   
    const char* currentColor;            

public:
    Renderer();
    
    void clear();
    
    void drawObject(const GameObject& obj);    
    void setScore(int score);
    void setColor(const char* color);
    
    void render() const;
};

#endif