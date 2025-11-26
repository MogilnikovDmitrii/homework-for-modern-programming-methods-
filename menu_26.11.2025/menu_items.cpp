#include "menu.hpp"
#include "menu_items.hpp"
#include "menu_func.hpp"

#include <iostream>
#include <cstddef>

const DmMog::MenuItem DmMog:: EXIT = {
    "0 - Закончить путешествие",DmMog::menu_exit, &MAIN
};

const DmMog::MenuItem DmMog::VLAD = {
    "1 - Владивосток",DmMog::fe_vlad, &FAR_EAST
};
const DmMog::MenuItem DmMog::SAH = {
    "2 - Сахалин",DmMog::fe_sah, &FAR_EAST
};
const DmMog::MenuItem DmMog::HAB = {
    "3 - Хабаровск",DmMog::fe_hab, &FAR_EAST
};
const DmMog::MenuItem DmMog::FE_EXIT = {
    "0 - Выйти в предыдущее меню",DmMog::go_back, &FAR_EAST
};

namespace {
    const DmMog::MenuItem* fe_children[] = {
        &DmMog::FE_EXIT,
        &DmMog::VLAD,
        &DmMog::SAH,
        &DmMog::HAB
    };
    const int fe_count = sizeof(fe_children) / sizeof(fe_children[0]);
}



const DmMog::MenuItem DmMog:: FAR_EAST = {
    "1 - Дальний восток",DmMog::show_menu3, &TRAVEL , fe_children, fe_count
};
const DmMog::MenuItem DmMog:: ALTAI = {
    "2 - Алтай",DmMog::show_menu3, &TRAVEL
};
const DmMog::MenuItem DmMog:: GOLD_RING = {
    "3 - Золотое Кольцо России",DmMog::show_menu3, &TRAVEL
};
const DmMog::MenuItem DmMog::TR_EXIT = {
    "0 - Выйти в главное меню",DmMog::go_back, &TRAVEL
};






namespace {
    const DmMog::MenuItem* travel_children[] = {
        &DmMog::TR_EXIT,
        &DmMog::FAR_EAST,
        &DmMog::ALTAI,
        &DmMog::GOLD_RING
    };
    const int travel_count = sizeof(travel_children) / sizeof(travel_children[0]);
}
const DmMog::MenuItem DmMog:: TRAVEL = {
    "1 - Путешествовать по России",DmMog::show_menu2, &MAIN , travel_children , travel_count
};


namespace {
    const DmMog::MenuItem* children_main[] = {
        &DmMog::EXIT,
        &DmMog::TRAVEL
    };
    const int main_count = sizeof(children_main) / sizeof(children_main[0]);
}


const DmMog::MenuItem DmMog::MAIN = {
    "Главное меню:",DmMog::show_menu1, &MAIN,children_main , main_count
};

