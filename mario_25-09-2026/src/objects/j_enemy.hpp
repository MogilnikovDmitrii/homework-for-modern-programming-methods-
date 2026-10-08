#pragma once

#include "enemy.hpp"

namespace biv {
	class JumpingEnemy : public Enemy {
		private:
			static constexpr float JUMP_SPEED = -0.8f;

		public:
			JumpingEnemy(const Coord& top_left, const int width, const int height);

			void update_platform_edge_movement(bool platform_ahead) noexcept override;

		protected:
			void update_horizontal_movement() noexcept override;
			void update_vertical_movement() noexcept override;
			bool should_die_from_mario_collision(const Speed& mario_speed) const noexcept override;
	};
}
