#include <iostream>

#include "menu.hpp"
#include "menu_func.hpp"

int main() {
	DmMog:: MenuItem study {"1 - я хочу учиться!!!", DmMog::study};
        DmMog:: MenuItem exit {"0 - я хочу домой(", DmMog::exit};

        DmMog:: MenuItem* mainChildren[] = { &exit, &study};
		const int mainSize = sizeof(mainChildren) / sizeof(mainChildren[0]);

	int user_input;
	do {
		std:: cout << "приветственный текст" << std::endl;
		for(int i = 1; i < mainSize; i++){
			std:: cout << mainChildren[i]->title << std::endl;
		}
		std:: cout << mainChildren[0]->title<< std::endl;
		std:: cout <<"Обучайка:";
		
		std:: cin >> user_input;
		mainChildren[user_input]->func();

	        std:: cout << std:: endl;
	} while(true);

	return 0;
}
