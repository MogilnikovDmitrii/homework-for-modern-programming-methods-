#include "gameObject.hpp"
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