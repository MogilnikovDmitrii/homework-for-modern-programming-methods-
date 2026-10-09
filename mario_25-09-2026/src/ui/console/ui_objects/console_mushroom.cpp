#include "console_mushroom.hpp"

using biv::ConsoleMushroom;

ConsoleMushroom::ConsoleMushroom(const Coord& top_left, const int width, const int height)
	: Mushroom(top_left, width, height) {}

char ConsoleMushroom::get_brush() const noexcept {
	return 'W';
}
