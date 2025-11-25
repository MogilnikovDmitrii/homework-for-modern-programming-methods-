#include "menu_func.hpp"
#include <iostream>
#include <cstdlib>


const DmMog:: MenuItem* DmMog:: show_menu(const MenuItem* current) {
	std:: cout << "приветливый текст)" << std:: endl;
	for (int i = 1; i < current->childrenCount; i++ ) {
		std:: cout << current->children[i]->title << std::endl;
	}
	std:: cout << current->children[0]->title << std:: endl;
	std:: cout << "Обучайка: ";

	int user_input;
	std:: cin >> user_input;
	std:: cout << std:: endl;

	return current->children[user_input];
}
const DmMog:: MenuItem* DmMog:: study_back(const MenuItem* current) {
    return current->parent->parent;
}

const DmMog:: MenuItem* DmMog:: exit(const MenuItem* current) {
	std:: exit(0);
}
const DmMog:: MenuItem* DmMog:: study_summ(const MenuItem* current) {
	std:: cout << current->title << std::endl;
	return current->parent;
}
const DmMog:: MenuItem* DmMog:: study_substract(const MenuItem* current) {
    std:: cout << current->title << std::endl;
    return current->parent;
}
const DmMog:: MenuItem* DmMog:: study_multiple(const MenuItem* current) {
    std:: cout << current->title << std::endl;
    return current->parent;
}
const DmMog:: MenuItem* DmMog:: study_divide(const MenuItem* current) {
    std:: cout << current->title << std::endl;
    return current->parent;
}

