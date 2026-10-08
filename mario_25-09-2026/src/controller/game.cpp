#include "game.hpp"

#include <algorithm>

#include "enemy.hpp"
#include "moving_platform.hpp"

using biv::Game;

Game::Game() {}

void Game::add_collisionable(Collisionable* obj) {
	collisionable_objs.push_back(obj);
}

void Game::add_map_movable(MapMovable* obj) {
	map_movable_objs.push_back(obj);
}

void Game::add_mario(Mario* obj) {
	mario = obj;
}

void Game::add_movable(Movable* obj) {
	movable_objs.push_back(obj);
}

void Game::add_moving_platform(MovingPlatform* platform) {
	moving_platforms.push_back(platform);
}

void Game::add_static_obj(Rect* obj) {
	static_objs.push_back(obj);
}

void Game::check_horizontally_static_collisions() noexcept {
	for (Collisionable* obj: collisionable_objs) {
		for (Rect* static_obj: static_objs) {
			if (obj->has_collision(static_obj)) {
				obj->process_horizontal_static_collision(static_obj);
				break;
			}
		}
	}
}

void Game::check_mario_collision() {
	for (int i = 0; i < collisionable_objs.size(); i++) {
		Collisionable* obj = collisionable_objs[i];
		if (obj->has_collision(mario)) {
			obj->process_mario_collision(mario);
			if (!mario->is_active()) {
				break;
			} else if (!obj->is_active()) {
				if (auto* movable = dynamic_cast<Movable*>(obj)) {
					remove_movable(movable);
				}
				if (auto* map_movable = dynamic_cast<MapMovable*>(obj)) {
					remove_map_movable(map_movable);
				}
				remove_collisionable(obj);
				i--;
			}
		}
	}
}

bool Game::check_static_collisions(Collisionable* obj) const noexcept {
	for (Rect* static_obj: static_objs) {
		if (obj->has_collision(static_obj)) {
			return true;
		}
	}
	return false;
}

void Game::check_vertically_static_collisions() noexcept {
	if (mario->has_collision(static_objs[static_objs.size() - 1])) {
		is_level_end_ = true;
	}
	
	for (Collisionable* obj: collisionable_objs) {
		for (Rect* static_obj: static_objs) {
			if (obj->has_collision(static_obj)) {
				obj->process_vertical_static_collision(static_obj);
				break;
			}
		}
	}
}

void Game::finish() noexcept {
	is_finished_ = true;
}

bool Game::is_finished() const noexcept {
	return is_finished_;
}

bool Game::is_level_end() const noexcept {
	return is_level_end_;
}

void Game::move_map_left() noexcept {
	for (MapMovable* obj: map_movable_objs) {
		obj->move_map_left();
	}
}

void Game::move_map_right() noexcept {
	for (MapMovable* obj: map_movable_objs) {
		obj->move_map_right();
	}
}

void Game::move_objs_horizontally() noexcept {
	for (Collisionable* obj: collisionable_objs) {
		auto* enemy = dynamic_cast<Enemy*>(obj);
		if (enemy == nullptr) {
			continue;
		}

		const Rect enemy_rect = enemy->get_rect();
		const Speed enemy_speed = enemy->get_speed();
		const int edge_x = enemy_speed.h > 0
			? enemy_rect.get_right()
			: enemy_rect.get_left() - 1;
		const Rect ground_probe({static_cast<float>(edge_x), static_cast<float>(enemy_rect.get_bottom())}, 1, 1);

		const bool platform_ahead = std::any_of(
			static_objs.begin(), static_objs.end(),
			[&ground_probe](Rect* static_obj) {
				return ground_probe.get_right() > static_obj->get_left()
					&& ground_probe.get_left() < static_obj->get_right()
					&& ground_probe.get_bottom() > static_obj->get_top()
					&& ground_probe.get_top() < static_obj->get_bottom();
			}
		);
		enemy->update_platform_edge_movement(platform_ahead);
	}

	for (Movable* obj: movable_objs) {
		obj->move_horizontally();
	}

	for (MovingPlatform* platform: moving_platforms) {
		const Rect platform_rect = platform->get_rect();
		const float old_x = platform->get_x();
		platform->move_horizontally();
		move_obj_on_moving_collisionable(platform_rect, platform->get_x() - old_x);
	}
}

void Game::move_obj_on_moving_collisionable(
	const Rect& platform_rect,
	const float platform_offset
) noexcept {
	const Rect mario_rect = mario->get_rect();
	const bool mario_is_riding =
		mario->get_speed().v >= 0
		&& mario_rect.get_bottom() >= platform_rect.get_top() - 1
		&& mario_rect.get_bottom() <= platform_rect.get_top() + 1
		&& mario_rect.get_right() > platform_rect.get_left()
		&& mario_rect.get_left() < platform_rect.get_right();

	if (mario_is_riding) {
		mario->move_horizontal_offset(platform_offset);
	}
}

void Game::move_objs_vertically() noexcept {
	for (Movable* obj: movable_objs) {
		obj->move_vertically();
	}
	for (MovingPlatform* platform: moving_platforms) {
		platform->move_vertically();
	}
}

void Game::remove_collisionable(Collisionable* obj) {
	remove_obj(collisionable_objs, obj);
}

void Game::remove_map_movable(MapMovable* obj) {
	remove_obj(map_movable_objs, obj);
}

void Game::remove_mario() noexcept {
	mario = nullptr;
}

void Game::remove_movable(Movable* obj) {
	remove_obj(movable_objs, obj);
}

void Game::remove_objs() {
	collisionable_objs.clear();
	map_movable_objs.clear();
	movable_objs.clear();
	moving_platforms.clear();
	static_objs.clear();
	remove_mario();
}

void Game::remove_static_obj(Rect* obj) {
	remove_obj(static_objs, obj);
}

void Game::start_level() noexcept {
	is_level_end_ = false;
}

// ----------------------------------------------------------------------------
// 									PRIVATE
// ----------------------------------------------------------------------------
template<class T>
void Game::remove_obj(std::vector<T*>& container, T* obj) {
	container.erase(
		std::remove(
			container.begin(), container.end(), obj
		), 
		container.end()
	);
}
