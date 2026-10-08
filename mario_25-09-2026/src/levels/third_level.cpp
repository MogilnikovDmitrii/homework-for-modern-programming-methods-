#include "third_level.hpp"

using biv::ThirdLevel;

ThirdLevel::ThirdLevel(UIFactory* ui_factory) : GameLevel(ui_factory) {
	init_data();
}

biv::GameLevel* ThirdLevel::get_next() {
	return nullptr;
}

bool ThirdLevel::is_final() const noexcept {
	return true;
}

void ThirdLevel::init_data() {
	ui_factory->create_mario({39, 10}, 2, 2);

	ui_factory->create_ship({20, 25}, 60, 2);
	ui_factory->create_ship({84, 23}, 68, 4);
	ui_factory->create_ship({155, 25}, 65, 2);
	ui_factory->create_ship({224, 23}, 65, 4);

#ifdef WINDOWS_CONSOLE
	ui_factory->create_enemy({45, 23}, 3, 2);
	ui_factory->create_enemy({50, 23}, 3, 2);
	ui_factory->create_enemy({57, 23}, 3, 2);
	ui_factory->create_enemy({95, 21}, 3, 2);
	ui_factory->create_enemy({112, 21}, 3, 2);
	ui_factory->create_enemy({166, 23}, 3, 2);
	ui_factory->create_enemy({195, 23}, 3, 2);
	ui_factory->create_enemy({230, 21}, 3, 2);
	ui_factory->create_enemy({236, 21}, 3, 2);
	ui_factory->create_flying_enemy({70, 12}, 3, 2, 2.5f, 0.07f);
	ui_factory->create_flying_enemy({145, 10}, 3, 2, 3.0f, 0.08f);
	ui_factory->create_flying_enemy({215, 12}, 3, 2, 2.5f, 0.07f);
	ui_factory->create_jumping_enemy({108, 21}, 3, 2);
	ui_factory->create_jumping_enemy({128, 21}, 3, 2);
	ui_factory->create_jumping_enemy({208, 23}, 3, 2);
#else
	ui_factory->create_enemy({57, 23}, 3, 2);
	ui_factory->create_enemy({166, 23}, 3, 2);
	ui_factory->create_flying_enemy({145, 12}, 3, 2, 2.0f, 0.05f);
#endif

	ui_factory->create_full_box({244, 15}, 5, 3);
	ui_factory->create_ship({300, 25}, 45, 2);
}
