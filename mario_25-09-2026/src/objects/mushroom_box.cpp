#include "mushroom_box.hpp"

using biv::MushroomBox;

MushroomBox::MushroomBox(
	const Coord& top_left,
	const int width, const int height,
	UIFactory* ui_factory
) : FullBox(top_left, width, height, ui_factory) {}

void MushroomBox::process_mario_collision(Collisionable* mario) noexcept {
	if (!is_used_ && mario->get_speed().v < 0) {
		is_used_ = true;
		ui_factory->create_mushroom({top_left.x, top_left.y - 3}, 3, 2);
	}
}
