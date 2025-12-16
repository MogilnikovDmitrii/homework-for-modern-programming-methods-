#include <gtest/gtest.h>
#include "bubble_sort.hpp"

TEST(BubbleSortTest, AlreadySorted)
{
    int arr[] = {1, 2, 3, 4, 5};
    bubble_sort(arr, 5);

    int expected[] = {1, 2, 3, 4, 5};
    for (int i = 0; i < 5; ++i)
        EXPECT_EQ(arr[i], expected[i]);
}

TEST(BubbleSortTest, ReverseOrder)
{
    int arr[] = {5, 4, 3, 2, 1};
    bubble_sort(arr, 5);

    int expected[] = {1, 2, 3, 4, 5};
    for (int i = 0; i < 5; ++i)
        EXPECT_EQ(arr[i], expected[i]);
}

TEST(BubbleSortTest, RandomValues)
{
    int arr[] = {3, 1, 4, 1, 5};
    bubble_sort(arr, 5);

    int expected[] = {1, 1, 3, 4, 5};
    for (int i = 0; i < 5; ++i)
        EXPECT_EQ(arr[i], expected[i]);
}

TEST(BubbleSortTest, SingleElement)
{
    int arr[] = {42};
    bubble_sort(arr, 1);

    EXPECT_EQ(arr[0], 42);
}

TEST(BubbleSortTest, EmptyArray)
{
    bubble_sort(nullptr, 0);
    SUCCEED();
}

