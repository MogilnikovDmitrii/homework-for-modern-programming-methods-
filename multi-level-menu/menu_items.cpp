#include "menu_items.hpp"
#include "menu_func.hpp"

#include <cstddef>

const DmMog::MenuItem DmMog::ALG_GO_BACK = {
    "0 - Хочу в главное меню!!!", DmMog::go_back, &ALGEBRA
};
const DmMog::MenuItem DmMog::ALG_SUMM = {
    "1 - Хочу научиться складывать!!!", DmMog::algebra_summ, &ALGEBRA
};
const DmMog::MenuItem DmMog::ALG_SUBSTRACT = {
    "2 - Хочу научиться вычитать!!!", DmMog::algebra_substract, &ALGEBRA
};
const DmMog::MenuItem DmMog::ALG_MULTIPLE = {
    "3 - Хочу научиться умножать!!!", DmMog::algebra_multiple, &ALGEBRA
};
const DmMog::MenuItem DmMog::ALG_DIVIDE = {
    "4 - Хочу научиться делить!!!", DmMog::algebra_divide, &ALGEBRA
};

const DmMog::MenuItem DmMog::MAN_GO_BACK = {
    "0 - Хочу выбирать предмет!!!", DmMog::go_back, &MANALYSIS
};
const DmMog::MenuItem DmMog::DIFFERENTIAL= {
    "1 - Хочу дифференциальные исчисления!!!", DmMog::algebra_summ, &MANALYSIS
};
const DmMog::MenuItem DmMog::INTEGRAL = {
    "2 - Хочу интергальные исчисления!!!", DmMog::algebra_substract, &MANALYSIS
};



namespace {
    const DmMog::MenuItem* subject_children[] = {
        &DmMog::GO_MENU,
        &DmMog::MANALYSIS,
        &DmMog::ALGEBRA
    };
    const int subject_size = sizeof(subject_children) / sizeof(subject_children[0]);
} 
const DmMog::MenuItem DmMog::SUBJECT = {
    "1 - я хочу учиться!!!", DmMog::show_menu,&DmMog:: MAIN, subject_children , subject_size
};
const DmMog::MenuItem DmMog::EXIT = {
    "0 - я хочу домой(", DmMog::exit
};
const DmMog::MenuItem DmMog::GO_MENU = {
    "0 - выйти в меню!!!", DmMog::go_back,&DmMog::SUBJECT 
};
namespace {
    const DmMog::MenuItem* algebra_children[] = {
        &DmMog::ALG_GO_BACK,
        &DmMog::ALG_SUMM,
        &DmMog::ALG_SUBSTRACT,
        &DmMog::ALG_MULTIPLE,
        &DmMog::ALG_DIVIDE
    };
    const int algebra_size = sizeof(algebra_children) / sizeof(algebra_children[0]);
} 
const DmMog::MenuItem DmMog::ALGEBRA = {
    "2 - я хочу учить алгебру!!!", DmMog::show_menu,&DmMog:: SUBJECT, algebra_children , algebra_size
};

namespace {
    const DmMog::MenuItem* matan_children[] = {
        &DmMog::MAN_GO_BACK,
        &DmMog::DIFFERENTIAL,
        &DmMog::INTEGRAL
    };
    const int matan_size = sizeof(matan_children) / sizeof(matan_children[0]);
} 

const DmMog::MenuItem DmMog::MANALYSIS = {
    "1 - я хочу учить матан!!!", DmMog::show_menu,&DmMog:: SUBJECT, matan_children , matan_size
};


namespace {
    const DmMog::MenuItem* main_children[] = {
        &DmMog::EXIT,
        &DmMog::SUBJECT
    };
    const int main_size = sizeof(main_children) / sizeof(main_children[0]);  
} ;


const DmMog::MenuItem DmMog::MAIN = {
    nullptr , DmMog::show_menu , nullptr, main_children , main_size
};