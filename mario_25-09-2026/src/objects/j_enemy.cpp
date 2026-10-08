#include "j_enemy.hpp"

using biv::JumpingEnemy;

JumpingEnemy::JumpingEnemy(const Coord& top_left, const int width, const int height)
	: Enemy(top_left, width, height) {
	vspeed = 0;
	hspeed = 0;
}

void JumpingEnemy::update_platform_edge_movement(bool) noexcept {}

void JumpingEnemy::update_horizontal_movement() noexcept {}

void JumpingEnemy::update_vertical_movement() noexcept {
	if (vspeed > 0) {
		top_left.y -= vspeed;
		vspeed = JUMP_SPEED;
	}
}

bool JumpingEnemy::should_die_from_mario_collision(
	const Speed& mario_speed
) const noexcept {
	return mario_speed.v > V_ACCELERATION;
}
