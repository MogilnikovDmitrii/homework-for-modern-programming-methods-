cmake_minimum_required(VERSION 3.14)
project(LongNumberProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(vector src/vector.cpp)
add_library(doubly_list src/doubly_linked_list.cpp)

target_include_directories(vector PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_include_directories(doubly_list PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
)

# отключаем установку тестов gtest (не обязательно)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(list_tests tests/list_test.cpp)
add_executable(vector_tests tests/vector_test.cpp)

target_link_libraries(list_tests
    doubly_list
    gtest
    gtest_main
)

target_link_libraries(vector_tests
    vector
    gtest
    gtest_main
)

add_test(NAME ListTests COMMAND list_tests)
add_test(NAME VectorTests COMMAND vector_tests)