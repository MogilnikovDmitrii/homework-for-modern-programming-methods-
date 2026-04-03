#include <gtest/gtest.h>
#include "vector.hpp"
using DmMog::Vector;
TEST(VectorTest, PushBackAndSize) {
    Vector<int> v;
    EXPECT_EQ(v.get_size(), 0);

    v.push_back(10);
    EXPECT_EQ(v.get_size(), 1);
    EXPECT_TRUE(v.has_item(10));

    v.push_back(20);
    EXPECT_EQ(v.get_size(), 2);
    EXPECT_TRUE(v.has_item(20));
}

TEST(VectorTest, Insert) {
    Vector<int> v;
    v.push_back(1);
    v.push_back(3);

    EXPECT_TRUE(v.insert(1, 2));
    EXPECT_EQ(v.get_size(), 3);
    EXPECT_TRUE(v.has_item(2));

    EXPECT_TRUE(v.insert(0, 0));
    EXPECT_EQ(v.get_size(), 4);
    EXPECT_TRUE(v.has_item(0));

    EXPECT_TRUE(v.insert(4, 4));
    EXPECT_EQ(v.get_size(), 5);
    EXPECT_TRUE(v.has_item(4));

    EXPECT_FALSE(v.insert(10, 99));
}

TEST(VectorTest, RemoveFirst) {
    Vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(2);

    EXPECT_TRUE(v.remove_first(2));
    EXPECT_EQ(v.get_size(), 3);
    EXPECT_TRUE(v.has_item(2)); 

    EXPECT_FALSE(v.remove_first(99));
}

// Тестируем has_item
TEST(VectorTest, HasItem) {
    Vector<int> v;
    v.push_back(5);
    v.push_back(10);

    EXPECT_TRUE(v.has_item(5));
    EXPECT_TRUE(v.has_item(10));
    EXPECT_FALSE(v.has_item(7));
}