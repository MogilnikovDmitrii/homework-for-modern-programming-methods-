#include "console_flying_enemy.hpp"

using biv::ConsoleFlyingEnemy;

ConsoleFlyingEnemy::ConsoleFlyingEnemy(const Coord& top_left, const int width, const int height, float amplitude, float frequency) 
	: FlyingEnemy(top_left, width, height, amplitude, frequency) {}

char ConsoleFlyingEnemy::get_brush() const noexcept {
	return 'E';
}