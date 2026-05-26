#include "movableObject.hpp"

MovableObject::MovableObject(float xPos, float yPos,
                             float w, float h, char sym)
    : GameObject(xPos, yPos, w, h, sym)
{
    vertSpeed = 0;
    horSpeed = 0.2f;
    isFly = true;
}

void MovableObject::update(GameObject** Floor, int FloorLen,
                           GameObject** Enemies, int EnemiesLen)
{
    if (isFly)
        vertSpeed += 0.1f;

    y += vertSpeed;
    x += horSpeed;

    isFly = true;

    for (int i = 0; i < FloorLen; i++) {
        if (isCollision(*Floor[i])) {
            y = Floor[i]->getY() - height;
            vertSpeed = 0;
            isFly = false;
        }
    }

    if (x < 0) x = 0;
    if (x + width > mapWidth) x = mapWidth - width;
    if (y > mapHeight) y = 0;
}

float MovableObject::getVertSpeed() const
{
    return vertSpeed;
}

void MovableObject::setVertSpeed(float v)
{
    vertSpeed = v;
}

float MovableObject::getHorSpeed() const
{
    return horSpeed;
}

void MovableObject::setHorSpeed(float v)
{
    horSpeed = v;
}

bool MovableObject::getIsFly() const
{
    return isFly;
}

void MovableObject::setIsFly(bool fly)
{
    isFly = fly;
}