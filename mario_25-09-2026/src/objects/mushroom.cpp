#include "mushroom.hpp"

using biv::Mushroom;

Mushroom::Mushroom(const Coord& top_left, const int width, const int height)
	: RectMapMovableAdapter(top_left, width, height), Movable(top_left, width, height, 0, 0.2f) {}

biv::Rect Mushroom::get_rect() const noexcept {
	return {top_left, width, height};
}

biv::Speed Mushroom::get_speed() const noexcept {
	return {vspeed, hspeed};
}

biv::MarioCollisionEffect Mushroom::get_mario_collision_effect() const noexcept {
	return biv::MarioCollisionEffect::MUSHROOM;
}

void Mushroom::process_horizontal_static_collision(Rect*) noexcept {
	hspeed = -hspeed;
	move_horizontally();
}

void Mushroom::process_mario_collision(Collisionable* mario) noexcept {
	kill();
}

void Mushroom::process_vertical_static_collision(Rect*) noexcept {
	if (vspeed > 0) {
		top_left.y -= vspeed;
		vspeed = 0;
	}
}
