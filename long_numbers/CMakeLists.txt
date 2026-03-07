cmake_minimum_required(VERSION 3.14)
project(LongNumberProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(long_numbers long_numbers.cpp)
target_include_directories(long_numbers PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(googletest/googletest)  

enable_testing()

add_executable(long_numbers_tests tests/long_numbers_test.cpp)

target_link_libraries(long_numbers_tests
    long_numbers
    gtest
    gtest_main
)

# target_link_libraries(new_tests
#     long_numbers
#     gtest
#     gtest_main
# )



add_test(NAME LongNumberTests COMMAND long_numbers_tests)
# add_test(NAME Newtests COMMAND new_tests)
