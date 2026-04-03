#include <gtest/gtest.h>
#include "doubly_linked_list.hpp"

using DmMog::DoublyLinkedList;

TEST(ListTest, PushBackAndSize) {
    DoublyLinkedList<int> lst;

    EXPECT_EQ(lst.get_size(), 0);

    lst.push_back(10);
    EXPECT_EQ(lst.get_size(), 1);

    lst.push_back(20);
    lst.push_back(30);
    EXPECT_EQ(lst.get_size(), 3);
}

TEST(ListTest, HasItem) {
    DoublyLinkedList<int> lst;

    lst.push_back(1);
    lst.push_back(2);
    lst.push_back(3);

    EXPECT_TRUE(lst.has_item(1));
    EXPECT_TRUE(lst.has_item(2));
    EXPECT_TRUE(lst.has_item(3));
    EXPECT_FALSE(lst.has_item(100));
}

TEST(ListTest, RemoveFirstBasic) {
    DoublyLinkedList<int> lst;

    lst.push_back(5);
    lst.push_back(10);
    lst.push_back(15);

    EXPECT_TRUE(lst.remove_first(10));
    EXPECT_EQ(lst.get_size(), 2);
    EXPECT_FALSE(lst.has_item(10));
}

TEST(ListTest, RemoveFirstHead) {
    DoublyLinkedList<int> lst;

    lst.push_back(1);
    lst.push_back(2);
    lst.push_back(3);

    EXPECT_TRUE(lst.remove_first(1)); 
    EXPECT_EQ(lst.get_size(), 2);
    EXPECT_FALSE(lst.has_item(1));
}

TEST(ListTest, RemoveFirstTail) {
    DoublyLinkedList<int> lst;

    lst.push_back(1);
    lst.push_back(2);
    lst.push_back(3);

    EXPECT_TRUE(lst.remove_first(3));
    EXPECT_EQ(lst.get_size(), 2);
    EXPECT_FALSE(lst.has_item(3));
}

TEST(ListTest, RemoveFirstDuplicate) {
    DoublyLinkedList<int> lst;

    lst.push_back(7);
    lst.push_back(8);
    lst.push_back(7);

    EXPECT_TRUE(lst.remove_first(7)); 
    EXPECT_EQ(lst.get_size(), 2);

    EXPECT_TRUE(lst.has_item(7)); 
}

TEST(ListTest, RemoveFirstNotFound) {
    DoublyLinkedList<int> lst;

    lst.push_back(1);
    lst.push_back(2);

    EXPECT_FALSE(lst.remove_first(100));
    EXPECT_EQ(lst.get_size(), 2);
}

TEST(ListTest, EmptyList) {
    DoublyLinkedList<int> lst;

    EXPECT_EQ(lst.get_size(), 0);
    EXPECT_FALSE(lst.has_item(1));
    EXPECT_FALSE(lst.remove_first(1));
}