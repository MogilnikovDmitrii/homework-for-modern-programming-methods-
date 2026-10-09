#include "mario.hpp"

#include "map_movable.hpp"

using biv::Mario;

Mario::Mario(const Coord& top_left, const int width, const int height) 
	: Movable(top_left, width, height, 0, 0) {}

biv::Rect Mario::get_rect() const noexcept {
	return {top_left, width, height};
}

biv::Speed Mario::get_speed() const noexcept {
	return {vspeed, hspeed};
}

void Mario::jump() noexcept {
	if (vspeed == 0) {
		if (powered_up_) {
			vspeed = -1.1f;
		} else {
			vspeed = JUMP_SPEED;
		}
	}
}

void Mario::eat_mushroom() noexcept {
	if (!powered_up_) {
		const float bottom = top_left.y + height;
		width = 3;
		height = 3;
		top_left.y = bottom - height;
		powered_up_ = true;
	}
}

void Mario::move_map_left() noexcept {
	move_horizontal_offset(biv::MapMovable::MAP_STEP);
}

void Mario::move_map_right() noexcept {
	move_horizontal_offset(-biv::MapMovable::MAP_STEP);
}

void Mario::process_horizontal_static_collision(Rect* obj) noexcept {
	hspeed = -hspeed;
	move_horizontally();
}

void Mario::process_mario_collision(Collisionable* obj) noexcept {
	if (obj != nullptr && obj->get_mario_collision_effect() == MarioCollisionEffect::MUSHROOM) {
		eat_mushroom();
	}
}

void Mario::process_vertical_static_collision(Rect* obj) noexcept {
	if (vspeed > 0) {
		// Марио упал на корабль.
		top_left.y -= vspeed;
	} else if (vspeed < 0) {
		// Марио ударился головой о полку и после этого должен падать вниз.
		top_left.y -= vspeed;
	}
	vspeed = 0;
}
