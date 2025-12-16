#include <cassert>
#include <vector>
#include <iostream>

#include "bubble_sort.hpp"

void test_sorted_array()
{
    std::vector<int> v = {1, 2, 3, 4, 5};
    bubble_sort(v);

    assert((v == std::vector<int>{1, 2, 3, 4, 5}));
}

void test_reverse_array()
{
    std::vector<int> v = {5, 4, 3, 2, 1};
    bubble_sort(v);

    assert((v == std::vector<int>{1, 2, 3, 4, 5}));
}

void test_random_array()
{
    std::vector<int> v = {3, 1, 4, 1, 5};
    bubble_sort(v);

    assert((v == std::vector<int>{1, 1, 3, 4, 5}));
}

void test_empty_array()
{
    std::vector<int> v;
    bubble_sort(v);

    assert(v.empty());
}

void test_single_element()
{
    std::vector<int> v = {42};
    bubble_sort(v);

    assert(v[0] == 42);
}

int main()
{
    test_sorted_array();
    test_reverse_array();
    test_random_array();
    test_empty_array();
    test_single_element();

    std::cout << "All bubble_sort tests passed ✅" << std::endl;
    return 0;
}

