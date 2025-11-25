#include <iostream>

#include "menu.hpp"
#include "menu_func.hpp"

int main() {
	DmMog:: MenuItem study_summ { "1 - Хочу научиться складывать!!!", DmMog::study_summ};
	DmMog:: MenuItem study_substract { "2 - Хочу научиться вычитать!!!", DmMog::study_substract};
	DmMog:: MenuItem study_multiple { "3 - Хочу научиться умножать!!!", DmMog::study_multiple};
	DmMog:: MenuItem study_divide { "4 - Хочу научиться делить!!!", DmMog::study_divide};
	DmMog:: MenuItem study_back { "0 - Хочу в главное меню!!!", DmMog::study_back};

	DmMog:: MenuItem* study_children[] = {
		&study_back,
		&study_summ,
		&study_substract,
		&study_multiple,
		&study_divide
	};
	
	const int study_size = sizeof(study_children) / sizeof(study_children[0]);

	DmMog::MenuItem study {"1 - я хочу учиться!!!", DmMog::show_menu, study_children , study_size};
    DmMog::MenuItem exit {"0 - я хочу домой(", DmMog::exit};

    DmMog::MenuItem* mainChildren[] = { &exit, &study};
	const int main_size = sizeof(mainChildren) / sizeof(mainChildren[0]);

	DmMog::MenuItem main = { nullptr , DmMog::show_menu , mainChildren , main_size};
	
	study_summ.parent = &study;
    study_substract.parent = &study;
    study_multiple.parent = &study;
    study_divide.parent = &study;
    study_back.parent = &study;
	
	study.parent = &main;
	exit.parent = &main;


	const DmMog::MenuItem* current = &main;
	do {
		current = current->func(current);
	} while(true);

	return 0;
}
