#include "w_enemy.hpp"

using biv::WalkingEnemy;

WalkingEnemy::WalkingEnemy(const Coord& top_left, const int width, const int height) 
	: Enemy(top_left, width, height) {
	vspeed = 0;
	hspeed = 0.2f;
}

void WalkingEnemy::update_platform_edge_movement(
	const bool platform_ahead
) noexcept {
	if (vspeed == 0 && !platform_ahead) {
		hspeed = -hspeed;
	}
}

void WalkingEnemy::update_horizontal_movement() noexcept {
	hspeed = -hspeed;
	move_horizontally();
}

void WalkingEnemy::update_vertical_movement() noexcept {
	if (vspeed > 0) {
		top_left.y -= vspeed;
		vspeed = 0;
	}
}

bool WalkingEnemy::should_die_from_mario_collision(const Speed& mario_speed) const noexcept {
	return mario_speed.v > V_ACCELERATION;
}
