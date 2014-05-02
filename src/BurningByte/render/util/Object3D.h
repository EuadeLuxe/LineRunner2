/*
 * Object3D
 * Author: Marvin Blum
 * Last Update: 17/03/2014 18:43
 * */

#ifndef OBJECT3D_H_
#define OBJECT3D_H_

#include <memory>
#include "../../Component.h"
#include "../../math/Matrix.h"
#include "../../math/Vector.h"
#include "Position3D.h"

namespace bb{

class Object3D:public Component{
	public:
		mat4 modelMatrix;
		bool visible;

		Object3D();

		void calculateModelMatrix(const std::shared_ptr<Component> positionable);
};

};

#endif
