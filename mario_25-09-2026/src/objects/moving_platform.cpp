#include "moving_platform.hpp"

#include <cmath>

using biv::MovingPlatform;

MovingPlatform::MovingPlatform(
	const Coord& top_left, const int width, const int height, const float patrol_range
) : RectMapMovableAdapter(top_left, width, height),
	left_boundary_(top_left.x - patrol_range),
	right_boundary_(top_left.x + patrol_range) {
	hspeed = 0.15f;
}

void MovingPlatform::move_map_left() noexcept {
	RectMapMovableAdapter::move_map_left();
	left_boundary_ -= MapMovable::MAP_STEP;
	right_boundary_ -= MapMovable::MAP_STEP;
}

void MovingPlatform::move_map_right() noexcept {
	RectMapMovableAdapter::move_map_right();
	left_boundary_ += MapMovable::MAP_STEP;
	right_boundary_ += MapMovable::MAP_STEP;
}

void MovingPlatform::move_horizontally() noexcept {
	top_left.x += hspeed;

	if (moving_right_) {
		if (top_left.x >= right_boundary_) {
			moving_right_ = false;
			top_left.x = right_boundary_;
			hspeed = -std::abs(hspeed);
		}
	} else if (top_left.x <= left_boundary_) {
		moving_right_ = true;
		top_left.x = left_boundary_;
		hspeed = std::abs(hspeed);
	}
}

void MovingPlatform::move_vertically() noexcept {}

biv::Rect MovingPlatform::get_rect() const noexcept {
	return {top_left, width, height};
}

biv::Speed MovingPlatform::get_speed() const noexcept {
	return {vspeed, hspeed};
}

void MovingPlatform::process_horizontal_static_collision(Rect*) noexcept {}

void MovingPlatform::process_mario_collision(Collisionable*) noexcept {}

void MovingPlatform::process_vertical_static_collision(Rect*) noexcept {}
