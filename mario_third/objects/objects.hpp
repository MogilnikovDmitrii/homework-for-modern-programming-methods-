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

// ===================== MOVABLE =====================
class MovableObject : public GameObject {
protected:
    float vertSpeed;
    float horSpeed;
    bool isFly;

public:
    MovableObject(float xPos, float yPos, float w, float h, char sym);

    void update(GameObject** Floor, int FloorLen,
                GameObject** Enemies, int EnemiesLen) override;

    float getVertSpeed() const;
    void setVertSpeed(float v);

    float getHorSpeed() const;
    void setHorSpeed(float v);

    bool getIsFly() const;
    void setIsFly(bool fly);
};

// ===================== STATIC =====================
class StableObject : public GameObject {
public:
    StableObject(float xPos, float yPos, float w, float h, char sym);
};

// ===================== ENTITIES =====================
class Player : public MovableObject {
public:
    Player(float xPos = 0, float yPos = 0);
};

class Enemy : public MovableObject {
public:
    Enemy(float xPos = 0, float yPos = 0);
};

class Coin : public MovableObject {
private:
    bool collectable = false;
    bool justSpawned = true;

public:
    Coin(float xPos = 0, float yPos = 0);

    bool isCollectable() const;

    void onFrame(); 
};

class Platform : public StableObject {
public:
    Platform(float xPos, float yPos, float w, float h, char sym = SYM_PLATFORM);
};

#endif