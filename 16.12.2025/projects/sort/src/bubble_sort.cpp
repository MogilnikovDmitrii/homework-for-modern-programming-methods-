#include "bubble_sort.hpp"
#include <utility>

void bubble_sort(int* data, std::size_t size)
{
    if (data == nullptr || size < 2)
        return;

    for (std::size_t i = 0; i < size - 1; ++i)
    {
        bool swapped = false;

        for (std::size_t j = 0; j < size - 1 - i; ++j)
        {
            if (data[j] > data[j + 1])
            {
                std::swap(data[j], data[j + 1]);
                swapped = true;
            }
        }

        if (!swapped)
            break;
    }
}

