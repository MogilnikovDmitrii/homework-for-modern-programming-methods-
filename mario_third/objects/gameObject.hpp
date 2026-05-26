#ifndef OBJECTS_HPP
#define OBJECTS_HPP

#include <unistd.h>
#include "./constants.hpp"

#define mapWidth 80
#define mapHeight 25

// ===================== BASE =====================
class GameObject {
protected:
    float x, y;
    float width, height;
    char objType;

public:
    GameObject(float xPos, float yPos, float w, float h, char type);
    virtual ~GameObject();

    virtual void draw(char map[mapHeight][mapWidth + 1]) const;
    virtual void update(GameObject** Floor, int FloorLen,
                        GameObject** Enemies, int EnemiesLen);

    bool isCollision(const GameObject& other) const;

    float getX() const;
    float getY() const;
    char getType() const;
    float getWidth() const;     
    float getHeight() const;
    void setType(char newType);

    void setPos(float nx, float ny);
};


#endif