#pragma once
#include "menu.hpp"



namespace DmMog {
	const MenuItem* exit(const MenuItem* current);

	const MenuItem* show_menu(const MenuItem* current);

	const MenuItem* study_summ(const MenuItem* current);
        const MenuItem* study_substract(const MenuItem* current);
        const MenuItem* study_multiple(const MenuItem* current);
        const MenuItem* study_divide(const MenuItem* current);
        const MenuItem* study_back(const MenuItem* current);
}
