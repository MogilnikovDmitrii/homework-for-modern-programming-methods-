enable_testing()

add_executable(test_bubble
    test_bubble.cpp
)

target_link_libraries(test_bubble PRIVATE
    sort_lib
    gtest
    gtest_main
)

add_test(NAME BubbleSortTest COMMAND test_bubble)

