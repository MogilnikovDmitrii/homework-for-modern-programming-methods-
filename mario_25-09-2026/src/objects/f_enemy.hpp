#pragma once

#include "enemy.hpp"

namespace biv {
	class FlyingEnemy : public Enemy {
		public:
			FlyingEnemy(const Coord& top_left, const int width, const int height, float amplitude = 2.0f, float frequency = 0.05f);
			void move_map_left() noexcept override;
			void move_map_right() noexcept override;
			void move_horizontally() noexcept override;
			void move_vertically() noexcept override;
			void update_platform_edge_movement(bool platform_ahead) noexcept override;
			void process_vertical_static_collision(Rect*) noexcept override;
		protected:
			void update_horizontal_movement() noexcept override;
			void update_vertical_movement() noexcept override;
			bool should_die_from_mario_collision(const Speed& mario_speed) const noexcept override;
		private:
			float amplitude_;
			float frequency_;
			float time_ = 0.0f;
			float base_y_;
			float start_x_ = 0.0f;
			float hspeed_ = 0.15f;
			float left_boundary_ = -100.0f;
			float right_boundary_ = 100.0f;
			bool moving_right_ = true;
	};
}
