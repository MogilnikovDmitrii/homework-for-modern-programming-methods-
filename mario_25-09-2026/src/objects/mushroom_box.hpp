#pragma once

#include "full_box.hpp"

namespace biv {
	class MushroomBox : public FullBox {
		public:
			MushroomBox(
				const Coord& top_left,
				const int width, const int height,
				UIFactory* ui_factory
			);

			void process_mario_collision(Collisionable*) noexcept override;
	};
}
