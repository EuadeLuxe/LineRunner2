/*
 * Material
 * Author: Marvin Blum
 * Last Update: 2014/03/24 15:49
 * */

#ifndef MATERIAL_H_
#define MATERIAL_H_

#include "../../Component.h"
#include "../../math/Vector.h"

namespace bb{

class Material:public Component{
	public:
		vec4 emissive, diffuse, specular;
		float shininess;

		Material();
		Material(const vec4 &emissive, const vec4 &diffuse, const vec4 &specular, const float shininess);
};

};

#endif
