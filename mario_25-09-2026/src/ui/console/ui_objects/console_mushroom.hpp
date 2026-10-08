#pragma once

#include "console_ui_obj_rect_adapter.hpp"
#include "mushroom.hpp"

namespace biv {
	class ConsoleMushroom : public Mushroom, public ConsoleUIObjectRectAdapter {
		public:
			ConsoleMushroom(const Coord& top_left, const int width, const int height);
			char get_brush() const noexcept override;
	};
}
