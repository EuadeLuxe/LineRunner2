/*
 * Object2D
 * Author: Marvin Blum
 * Last Update: 2014/04/07 16:55
 * */

#ifndef OBJECT2D_H_
#define OBJECT2D_H_

#include <memory>
#include "../../Component.h"
#include "../../math/Matrix.h"
#include "Position2D.h"

namespace bb{

class Object2D:public Component{
	public:
		mat3 modelMatrix;
		bool visible;

		Object2D();

		void calculateModelMatrix(const std::shared_ptr<Component> positionable);
};

};

#endif
