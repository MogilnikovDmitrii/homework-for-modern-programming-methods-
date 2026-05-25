#include "engine.hpp"
#include "constants.hpp"
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#include <iostream>

static void setNonBlocking() {
    struct termios ttystate;
    tcgetattr(STDIN_FILENO, &ttystate);
    ttystate.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &ttystate);
    fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK);
}

GameEngine::GameEngine()
    : player(39, 10), currentLevel(1), score(0), needReload(0),
      maxLevel(3), mapColor("\033[97;44m"), running(true)
{
    level.load(currentLevel, score);
    setNonBlocking();
}

void GameEngine::handleInput() {
    char key;
    int moveLeft = 0, moveRight = 0;
    while (read(STDIN_FILENO, &key, 1) > 0) {
        if (key == 27) running = false;
        if (key == ' ' && !player.getIsFly()) {
            player.setVertSpeed(-1.3f);
            player.setIsFly(true);   // важно!
        }
        if (key == 'a') moveLeft = 1;
        if (key == 'd') moveRight = 1;
    }
    if (moveRight) moveCamera(-2);
    if (moveLeft) moveCamera(2);
}

void GameEngine::moveCamera(float dx) {
    // Сдвигаем все платформы
    for (int i = 0; i < level.getFloorLen(); ++i) {
        GameObject* obj = level.getFloor()[i];
        obj->setPos(obj->getX() + dx, obj->getY());
    }
    // Сдвигаем всех врагов
    for (int i = 0; i < level.getEnemiesLen(); ++i) {
        GameObject* obj = level.getEnemies()[i];
        obj->setPos(obj->getX() + dx, obj->getY());
    }
    // Проверяем, не столкнулся ли игрок с платформой после сдвига
    for (int i = 0; i < level.getFloorLen(); ++i) {
        if (player.isCollision(*level.getFloor()[i])) {
            // Откат: сдвигаем всё обратно
            for (int j = 0; j < level.getFloorLen(); ++j) {
                level.getFloor()[j]->setPos(level.getFloor()[j]->getX() - dx, level.getFloor()[j]->getY());
            }
            for (int j = 0; j < level.getEnemiesLen(); ++j) {
                level.getEnemies()[j]->setPos(level.getEnemies()[j]->getX() - dx, level.getEnemies()[j]->getY());
            }
            return;
        }
    }
}

void GameEngine::applyGravityAndMove(MovableObject& obj) {
    // Проверка "на земле"
    if (!obj.getIsFly()) {
        obj.setPos(obj.getX(), obj.getY() + 1);

        bool onGround = false;
        for (int i = 0; i < level.getFloorLen(); ++i) {
            if (obj.isCollision(*level.getFloor()[i])) {
                onGround = true;
                break;
            }
        }

        obj.setPos(obj.getX(), obj.getY() - 1);

        if (!onGround) {
            obj.setIsFly(true);
            obj.setVertSpeed(0);
        } else {
            return;
        }
    }

    // Гравитация
    obj.setVertSpeed(obj.getVertSpeed() + 0.05f);
    obj.setPos(obj.getX(), obj.getY() + obj.getVertSpeed());

    // Коллизии с блоками
    for (int i = 0; i < level.getFloorLen(); ++i) {
        GameObject* floorObj = level.getFloor()[i];

        if (!obj.isCollision(*floorObj))
            continue;

        bool specialQuestion = false;

        // --- SPECIAL: блок '?' ---
        if (floorObj->getType() == SYM_QUESTION &&
            obj.getVertSpeed() < 0 &&
            &obj == &player)
        {
            floorObj->setType(SYM_DASH);

            Coin* coin = new Coin(
                floorObj->getX() + floorObj->getWidth() / 2 - 1.5f,
                floorObj->getY() - 5
            );
            coin->setVertSpeed(-0.2f);
            coin->setIsFly(true);
            level.addEnemy(coin);

            // корректно выталкиваем игрока вниз
            obj.setPos(obj.getX(), floorObj->getY() + floorObj->getHeight());
            obj.setVertSpeed(0);

            specialQuestion = true;
        }

        if (specialQuestion)
            break;

        // --- обычные коллизии ---
        if (obj.getVertSpeed() > 0) {
            obj.setPos(obj.getX(), floorObj->getY() - obj.getHeight());
            obj.setVertSpeed(0);
            obj.setIsFly(false);
        }
        else if (obj.getVertSpeed() < 0) {
            obj.setPos(obj.getX(), floorObj->getY() + floorObj->getHeight());
            obj.setVertSpeed(0);
        }

        // портал
        if (floorObj->getType() == SYM_PORTAL) {
            currentLevel++;
            if (currentLevel > maxLevel)
                currentLevel = 1;

            mapColor = "\033[42m";
            needReload = 1;
        }

        break;
    }
}


void GameEngine::updateEnemies() {
    for (int i = 0; i < level.getEnemiesLen(); ++i) {

        GameObject* obj = level.getEnemies()[i];

        MovableObject* enemy = dynamic_cast<MovableObject*>(obj);
        if (!enemy) continue;

        if (Coin* coin = dynamic_cast<Coin*>(enemy)) {
            coin->onFrame();  
        }

        applyGravityAndMove(*enemy);

        float oldX = enemy->getX();
        float newX = oldX + enemy->getHorSpeed();

        enemy->setPos(newX, enemy->getY());

        bool collision = false;

        for (int j = 0; j < level.getFloorLen(); ++j) {
            if (enemy->isCollision(*level.getFloor()[j])) {
                collision = true;
                break;
            }
        }

        if (collision) {
            enemy->setPos(oldX, enemy->getY());
            enemy->setHorSpeed(-enemy->getHorSpeed());
        }
        else {
            enemy->setPos(newX, enemy->getY() + 1);

            bool groundBelow = false;

            for (int j = 0; j < level.getFloorLen(); ++j) {
                if (enemy->isCollision(*level.getFloor()[j])) {
                    groundBelow = true;
                    break;
                }
            }

            enemy->setPos(newX, enemy->getY() - 1);

            if (!groundBelow) {
                if (!dynamic_cast<Coin*>(enemy)) {
                    enemy->setPos(oldX, enemy->getY());
                    enemy->setHorSpeed(-enemy->getHorSpeed());
                }
            }
        }

        if (enemy->getY() + enemy->getHeight() > mapHeight) {
            level.removeEnemy(i);
            i--;
        }
    }
}

void GameEngine::checkCollisions() {
    for (int i = level.getEnemiesLen() - 1; i >= 0; --i) {
        GameObject* obj = level.getEnemies()[i];
        
       if (Coin* coin = dynamic_cast<Coin*>(obj)) {
            if (coin->isCollectable() && player.isCollision(*coin)) {
                level.removeEnemy(i);
                score += 10;
            }
            continue;
        }       

        MovableObject* enemy = dynamic_cast<MovableObject*>(obj);
        if (!enemy) continue;

        if (player.isCollision(*enemy)) {
            if (player.getIsFly() && player.getVertSpeed() > 0 &&
                player.getY() + player.getHeight() < enemy->getY() + enemy->getHeight() * 0.5f) {
                level.removeEnemy(i);
                score += 5;
            }else {
                mapColor = "\033[41m";
                needReload = 1;
                renderer.setColor(mapColor);
                renderer.render();
                usleep(500000);
                return;
            }
        }
    }
}

void GameEngine::render() {
    renderer.clear();
    for (int i = 0; i < level.getFloorLen(); ++i)
        renderer.drawObject(*level.getFloor()[i]);
    for (int i = 0; i < level.getEnemiesLen(); ++i)
        renderer.drawObject(*level.getEnemies()[i]);
    renderer.drawObject(player);
    renderer.setScore(score);
    renderer.setColor(mapColor);
    renderer.render();
}

void GameEngine::run() {
    while (running) {
        handleInput();
        applyGravityAndMove(player);
        
        if (player.getY() + player.getHeight() > mapHeight) {
            mapColor = "\033[41m";
            needReload = 1;
            renderer.setColor(mapColor);
            renderer.render();
            usleep(500000);
        }
        
        if (needReload) {
        renderer.setColor(mapColor);
        renderer.render();
        usleep(500000);
        
        needReload = 0;
        mapColor = "\033[97;44m";
        level.load(currentLevel, score);
        player.setPos(39, 10);
        player.setVertSpeed(0);
        player.setIsFly(false);
        continue;  
        }
        updateEnemies();
        checkCollisions();
        render();
        usleep(25000);
    }
}