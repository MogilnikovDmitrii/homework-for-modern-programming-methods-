#include "menu.hpp"
#include "menu_func.hpp"

#include <iostream>
#include "cstdlib"

namespace {
    const DmMog:: MenuItem* show_menu(const DmMog::MenuItem* current) {
    for (int i = 1; i < current->children_count;i++){
        std::cout << current->children[i]->title<<std::endl; 
    }
    std::cout << current->children[0]->title<<std::endl; 
    int user_input;
    std:: cin >> user_input;
    return current->children[user_input];
};
}

const DmMog:: MenuItem* DmMog:: show_menu1(const MenuItem* current) {
    std::cout<<"Главное меню:" <<std::endl;
    return show_menu(current);
};

const DmMog:: MenuItem* DmMog:: show_menu2(const MenuItem* current) {
    std::cout<<"Второй уровень меню" <<std::endl;
    return show_menu(current);
};

const DmMog:: MenuItem* DmMog:: show_menu3(const MenuItem* current) {
    std::cout<<"Третий уровень Дальний восток" <<std::endl;
    return show_menu(current);
};

const DmMog:: MenuItem* DmMog:: menu_exit(const MenuItem* current) {
    std::exit(0);
};

const DmMog:: MenuItem* DmMog:: go_back(const MenuItem* current) {
    std::cout << current->title<<std::endl;
    return current->parent->parent;
};

const DmMog:: MenuItem* DmMog:: fe_hab(const MenuItem* current) {
    std::cout << current->title<<std::endl;
    return current->parent;
};
const DmMog:: MenuItem* DmMog:: fe_vlad(const MenuItem* current) {
    std::cout << current->title<<std::endl;
    return current->parent;
};
const DmMog:: MenuItem* DmMog:: fe_sah(const MenuItem* current) {
    std::cout << current->title<<std::endl;
    return current->parent;
};