#include "f_enemy.hpp"

#include <cmath>

using biv::FlyingEnemy;

FlyingEnemy::FlyingEnemy(const Coord& top_left, const int width, const int height, float amplitude, float frequency) 
	: Enemy(top_left, width, height), amplitude_(amplitude), frequency_(frequency), base_y_(top_left.y), start_x_(top_left.x) {
	vspeed = 0;
	hspeed = 0.3f;
	hspeed_ = hspeed;
	left_boundary_ = start_x_ - 50.0f;
	right_boundary_ = start_x_ + 50.0f;
}

void FlyingEnemy::move_map_left() noexcept {
	RectMapMovableAdapter::move_map_left();
	left_boundary_ -= MapMovable::MAP_STEP;
	right_boundary_ -= MapMovable::MAP_STEP;
}

void FlyingEnemy::move_map_right() noexcept {
	RectMapMovableAdapter::move_map_right();
	left_boundary_ += MapMovable::MAP_STEP;
	right_boundary_ += MapMovable::MAP_STEP;
}

void FlyingEnemy::move_horizontally() noexcept {
	top_left.x += hspeed_;

	if (moving_right_) {
		if (top_left.x + width >= right_boundary_) {
			moving_right_ = false;
			top_left.x = right_boundary_ - width;
			hspeed_ = -std::abs(hspeed_);
		}
	} else {
		if (top_left.x <= left_boundary_) {
			moving_right_ = true;
			top_left.x = left_boundary_;
			hspeed_ = std::abs(hspeed_);
		}
	}

	hspeed = hspeed_;
}

void FlyingEnemy::move_vertically() noexcept {
	top_left.y = base_y_;
	vspeed = 0;
}

void FlyingEnemy::update_platform_edge_movement(bool) noexcept {}

void FlyingEnemy::process_vertical_static_collision(Rect*) noexcept {
	// Flying enemy ignores platform collisions and gravity.
}

void FlyingEnemy::update_horizontal_movement() noexcept {
	move_horizontally();
}

void FlyingEnemy::update_vertical_movement() noexcept {
	move_vertically();
}

bool FlyingEnemy::should_die_from_mario_collision(const Speed& mario_speed) const noexcept {
	return mario_speed.v > V_ACCELERATION;
}