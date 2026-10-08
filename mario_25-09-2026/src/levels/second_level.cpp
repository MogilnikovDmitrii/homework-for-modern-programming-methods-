#include "second_level.hpp"

#include "third_level.hpp"

using biv::SecondLevel;

SecondLevel::SecondLevel(UIFactory* ui_factory) : GameLevel(ui_factory) {
	init_data();
}

bool SecondLevel::is_final() const noexcept {
	return false;
}

biv::GameLevel* SecondLevel::get_next() {
	if (!next) {
		clear_data();
		next = new biv::ThirdLevel(ui_factory);
	}
	return next;
}

// ----------------------------------------------------------------------------
// 									PROTECTED
// ----------------------------------------------------------------------------
void SecondLevel::init_data() {
	ui_factory->create_mario({39, 10}, 2, 2);

	ui_factory->create_ship({20, 25}, 35, 2);
	ui_factory->create_ship({160, 25}, 35, 2);
	ui_factory->create_ship({300, 22}, 40, 5);

	for (const int x : {62, 88, 114, 140, 202, 228, 254, 280, 373, 399, 425}) {
		ui_factory->create_moving_platform({static_cast<float>(x), 20}, 14, 2, 3.0f);
	}

	ui_factory->create_flying_enemy({100, 12}, 3, 2, 2.0f, 0.05f);
	ui_factory->create_flying_enemy({240, 11}, 3, 2, 2.5f, 0.07f);
	ui_factory->create_flying_enemy({380, 10}, 3, 2, 2.0f, 0.06f);
	ui_factory->create_jumping_enemy({175, 23}, 3, 2);

	ui_factory->create_mushroom_box({315, 13}, 5, 3);

	ui_factory->create_ship({445, 25}, 45, 2);
}
