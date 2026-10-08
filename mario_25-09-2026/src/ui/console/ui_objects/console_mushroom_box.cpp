#include "console_mushroom_box.hpp"

using biv::ConsoleMushroomBox;

ConsoleMushroomBox::ConsoleMushroomBox(
	const Coord& top_left,
	const int width, const int height,
	UIFactory* ui_factory
) : MushroomBox(top_left, width, height, ui_factory) {}

char ConsoleMushroomBox::get_brush() const noexcept {
	if (is_used()) {
		return '-';
	}
	return '?';
}
