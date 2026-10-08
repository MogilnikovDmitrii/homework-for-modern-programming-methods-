/**
	- Если создавать класс FlyableEenemy, JumpableEnemy и другие виды врагов, 
		то почему их нельзя наследовать от Enemy?
*/

#pragma once

#include "collisionable.hpp"
#include "movable.hpp"
#include "rect.hpp"
#include "rect_map_movable_adapter.hpp"
#include "speed.hpp"

namespace biv {
	class Enemy : public RectMapMovableAdapter, public Movable, public Collisionable {
		public:
			Enemy(const Coord& top_left, const int width, const int height);
			virtual ~Enemy() = default;

			Rect get_rect() const noexcept override;
			Speed get_speed() const noexcept override;

			void process_horizontal_static_collision(Rect*) noexcept override;
			void process_mario_collision(Collisionable*) noexcept override;
			void process_vertical_static_collision(Rect*) noexcept override;
			virtual void update_platform_edge_movement(bool platform_ahead) noexcept = 0;

		protected:
			virtual void update_horizontal_movement() noexcept = 0;
			virtual void update_vertical_movement() noexcept = 0;
			virtual bool should_die_from_mario_collision(const Speed& mario_speed) const noexcept = 0;
	};
}
