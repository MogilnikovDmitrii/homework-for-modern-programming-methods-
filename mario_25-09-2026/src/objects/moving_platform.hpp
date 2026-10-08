#pragma once

#include "MovingCollisianable.hpp"
#include "rect_map_movable_adapter.hpp"

namespace biv {
	class MovingPlatform : public MovingCollisianable, public RectMapMovableAdapter {
		public:
			MovingPlatform(
				const Coord& top_left,
				const int width,
				const int height,
				float patrol_range = 50.0f
			);

			void move_map_left() noexcept override;
			void move_map_right() noexcept override;
			void move_horizontally() noexcept override;
			void move_vertically() noexcept override;

			Rect get_rect() const noexcept override;
			Speed get_speed() const noexcept override;
			void process_horizontal_static_collision(Rect*) noexcept override;
			void process_mario_collision(Collisionable*) noexcept override;
			void process_vertical_static_collision(Rect*) noexcept override;

		private:
			float left_boundary_;
			float right_boundary_;
			bool moving_right_ = true;
	};
}
