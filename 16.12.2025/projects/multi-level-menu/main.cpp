#include <iostream>
#include "menu.hpp"
#include "menu_items.hpp"
#include "menu_func.hpp"

int main() {
    const DmMog::MenuItem* current = &DmMog::MAIN;
    do {
        current = current->func(current);
    }while(true);
}