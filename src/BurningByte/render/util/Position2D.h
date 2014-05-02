/*
 * Position2D
 * Author: Marvin Blum
 * Last Update: 2014/04/07 15:53
 * */

#ifndef POSITION2D_H_
#define POSITION2D_H_

#include "../../Component.h"
#include "../../math/Vector.h"

namespace bb{

class Position2D:public Component{
	public:
		enum ROTATIONPOINT{
			CENTER,
			BOTTOMLEFT,
			BOTTOMRIGHT,
			TOPLEFT,
			TOPRIGHT
		};

		bool visible;
		vec2 position, scale, direction, size, rotationPoint;
		float rotation;

		Position2D(const vec2 &position, const float rotation, const vec2 &scale, const vec2 &direction, const vec2 &size);
		Position2D(const vec2 &position, const vec2 &size);
		Position2D(const vec2 &size);
		Position2D();

		void setRotationPoint(const ROTATIONPOINT rotationPoint);
};

};

#endif
