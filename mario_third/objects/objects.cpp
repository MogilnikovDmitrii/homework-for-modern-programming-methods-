#include "objects.hpp"
// ===================== GAMEOBJECT =====================

GameObject::GameObject(float xPos, float yPos,
                       float w, float h,
                       char type)
{
    x = xPos;
    y = yPos;
    width = w;
    height = h;
    objType = type;
}

GameObject::~GameObject() {}

void GameObject::draw(char map[mapHeight][mapWidth + 1]) const
{
    for (int iy = 0; iy < (int)height; iy++) {
        for (int ix = 0; ix < (int)width; ix++) {

            int dx = (int)x + ix;
            int dy = (int)y + iy;

            if (dx >= 0 && dx < mapWidth &&
                dy >= 0 && dy < mapHeight)
            {
                map[dy][dx] = objType;
            }
        }
    }
}

void GameObject::update(GameObject**, int, GameObject**, int) {}

bool GameObject::isCollision(const GameObject& o) const
{
    return x < o.x + o.width &&
           x + width > o.x &&
           y < o.y + o.height &&
           y + height > o.y;
}

float GameObject::getX() const { return x; }
float GameObject::getY() const { return y; }

char GameObject::getType() const{
    return objType;
}
float GameObject::getHeight() const{
    return height;
}
float GameObject::getWidth() const{
    return width;
}

void GameObject::setType(char newType) {
    objType = newType;
}

void GameObject::setPos(float nx, float ny)
{
    x = nx;
    y = ny;
}

// ===================== MOVABLE =====================

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

// ===================== ENTITIES =====================

Player::Player(float xPos, float yPos)
    : MovableObject(xPos, yPos, 3, 3, SYM_PLAYER) {}

Enemy::Enemy(float xPos, float yPos)
    : MovableObject(xPos, yPos, 3, 2, SYM_ENEMY) {}

Coin::Coin(float xPos, float yPos)
    : MovableObject(xPos, yPos, 3, 2, SYM_COIN)
{
    setHorSpeed(0.2f);
}

void Coin::onFrame() {
    if (justSpawned) {
        justSpawned = false;
        return;
    }

    collectable = true;
}
bool Coin::isCollectable() const {
    return collectable;
}

Platform::Platform(float xPos, float yPos,
                   float w, float h, char sym)
    : StableObject(xPos, yPos, w, h, sym) {}

StableObject::StableObject(float xPos, float yPos,
                           float w, float h, char sym)
    : GameObject(xPos, yPos, w, h, sym) {}



// ===================== getters and setters =====================


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