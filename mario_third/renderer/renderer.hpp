#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "objects.hpp"  

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