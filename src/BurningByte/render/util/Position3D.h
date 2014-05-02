/*
 * Position3D
 * Author: Marvin Blum
 * Last Update: 2014/04/07 15:53
 * */

#ifndef POSITION3D_H_
#define POSITION3D_H_

#include "../../Component.h"
#include "../../math/Vector.h"

namespace bb{

class Position3D:public Component{
	public:
		bool visible;
		vec3 position, scale, direction, rotationPoint, rotation;

		Position3D(const vec3 &position, const vec3 &rotation, const vec3 &scale, const vec3 &direction, const vec3 &rotationPoint);
		Position3D(const vec3 &position);
		Position3D();
};

};

#endif
