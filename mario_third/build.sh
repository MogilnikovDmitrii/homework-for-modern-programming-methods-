#!/bin/bash

CXX=g++
CXXFLAGS="-Wall -Wextra -pedantic -std=c++17"

INCLUDES="-I. -Ilevel -Iobjects -Irenderer"

SOURCES="main.cpp engine/engine.cpp level/level.cpp objects/gameObject.cpp renderer/renderer.cpp objects/coin.cpp objects/enemy.cpp objects/movableObject.cpp objects/platform.cpp objects/player.cpp objects/stableObject.cpp"

OUTPUT="game"

echo "Компиляция проекта..."
$CXX $CXXFLAGS $INCLUDES $SOURCES -o $OUTPUT

if [ $? -eq 0 ]; then
    echo "Сборка успешна! Запустите ./$OUTPUT"
else
    echo "Ошибка компиляции."
    exit 1
fi