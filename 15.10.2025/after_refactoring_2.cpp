#include <cmath>
#include <iostream>

int main(){
    const int n = 10;
    int my_array[n];
    for (int i = 0; i < n; i++){
        std::cout << "Введите " << i << " элемент" << std::endl;
        std::cin >>my_array[i];
    }

    bool is_increasing = true;
    int i = 0;
    while (i < n-1){
        if (my_array[i] >= my_array[i+1]){
            is_increasing = false;
            break;
        }
        i++;
    }
    
    if (is_increasing) {
        std::cout << "Последовательность возрастающая";
        std::cout << std::endl;
    } else {
        std::cout << "Последовательность не возрастающая";
        std::cout << std::endl;
    }

    return 0;
}
