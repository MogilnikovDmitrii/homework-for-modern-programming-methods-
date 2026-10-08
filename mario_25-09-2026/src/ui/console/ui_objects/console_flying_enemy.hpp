#pragma once

#include "console_ui_obj_rect_adapter.hpp"
#include "enemy.hpp"
#include "f_enemy.hpp"
namespace biv {
	class ConsoleFlyingEnemy : public FlyingEnemy, public ConsoleUIObjectRectAdapter {
		public:
			ConsoleFlyingEnemy(const Coord& top_left, const int width, const int height, float amplitude = 2.0f, float frequency = 0.05f);

			char get_brush() const noexcept override;
	};
}