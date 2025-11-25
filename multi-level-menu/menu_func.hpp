#pragma once
#include "menu.hpp"



namespace DmMog {
	const MenuItem* exit(const MenuItem* current);

	const MenuItem* show_menu(const MenuItem* current);

	const MenuItem* algebra_summ(const MenuItem* current);
        const MenuItem* algebra_substract(const MenuItem* current);
        const MenuItem* algebra_multiple(const MenuItem* current);
        const MenuItem* algebra_divide(const MenuItem* current);
        
        const MenuItem* go_back(const MenuItem* current);

        const MenuItem* integral(const MenuItem* current);
        const MenuItem* differential(const MenuItem* current);



}
