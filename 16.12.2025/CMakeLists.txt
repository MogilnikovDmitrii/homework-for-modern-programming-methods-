cmake_minimum_required(VERSION 3.20)

project(MultiProject CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)
enable_testing()
add_subdirectory(projects/lib/googletest)
add_subdirectory(projects)

