#pragma once

#include "collisionable.hpp"
#include "movable.hpp"

namespace biv {
	class MovingCollisianable: public Movable, public Collisionable{
	};
}
