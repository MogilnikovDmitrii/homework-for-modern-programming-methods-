#!/bin/bash

CXX=g++
CXXFLAGS="-Wall -Wextra -pedantic -std=c++17"

# Пути к заголовочным файлам (папки)
INCLUDES="-I. -Ilevel -Iobjects -Irenderer"

# Исходные файлы (без game.cpp/game.hpp)
SOURCES="main.cpp engine/engine.cpp level/level.cpp objects/objects.cpp renderer/renderer.cpp"

OUTPUT="game"

echo "Компиляция проекта..."
$CXX $CXXFLAGS $INCLUDES $SOURCES -o $OUTPUT

if [ $? -eq 0 ]; then
    echo "Сборка успешна! Запустите ./$OUTPUT"
else
    echo "Ошибка компиляции."
    exit 1
fi