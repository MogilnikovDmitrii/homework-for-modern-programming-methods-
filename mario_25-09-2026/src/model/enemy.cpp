#include "enemy.hpp"

#include "map_movable.hpp"
#include <cmath>

using biv::Enemy;

Enemy::Enemy(const Coord& top_left, const int width, const int height) 
	: RectMapMovableAdapter(top_left, width, height) {}

biv::Rect Enemy::get_rect() const noexcept {
	return {top_left, width, height};
}

biv::Speed Enemy::get_speed() const noexcept {
	return {vspeed, hspeed};
}

void Enemy::process_horizontal_static_collision(Rect* obj) noexcept {
	update_horizontal_movement();
}

void Enemy::process_mario_collision(Collisionable* mario) noexcept {
	const Rect enemy_rect = get_rect();
	const Rect mario_rect = mario->get_rect();
	const Speed mario_speed = mario->get_speed();

	const bool stomp_from_above =
		mario_speed.v > 0.0f &&
		mario_rect.get_bottom() <= enemy_rect.get_top() + 1 &&
		mario_rect.get_top() < enemy_rect.get_top();

	if (stomp_from_above && should_die_from_mario_collision(mario_speed)) {
		kill();
	} else {
		mario->kill();
	}
}

void Enemy::process_vertical_static_collision(Rect* obj) noexcept {
	update_vertical_movement();
}
