#include <iostream>
#include <vector>
#include <utility> 

void bubble_sort(std::vector<int>& data)
{
    bool swapped;
    for (std::size_t i = 0; i < data.size(); ++i)
    {
        swapped = false;
        for (std::size_t j = 0; j + 1 < data.size() - i; ++j)
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

int main()
{
    std::vector<int> v = {5, 1, 4, 2, 8};

    bubble_sort(v);

    for (int x : v)
        std::cout << x << " ";

    std::cout << std::endl;
    return 0;
}

