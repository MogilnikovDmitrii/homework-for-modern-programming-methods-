#ifndef ENGINE_HPP
#define ENGINE_HPP

#include "level.hpp"
#include "renderer.hpp"
#include "objects.hpp"

class GameEngine {
private:
    Level level;
    Renderer renderer;
    Player player;
    int currentLevel;
    int score;
    int needReload;
    const int maxLevel;
    const char* mapColor;
    bool running;

    void handleInput();
    void applyGravityAndMove(MovableObject& obj);
    void moveCamera(float dx);
    void updateEnemies();
    void checkCollisions();
    void render();

public:
    GameEngine();
    void run();
};

#endif