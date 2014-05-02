/*
 * LightSource
 * Author: Marvin Blum
 * Last Update: 2014/04/30 17:01
 * */

#ifndef LIGHTSOURCE_H_
#define LIGHTSOURCE_H_

#include "../../Entity.h"
#include "../../math/Vector.h"

namespace bb{

class LightSource:public Entity{
	public:
		vec3 position, direction;
		vec4 diffuse, specular;
		float constantAttenuation, linearAttenuation, quadraticAttenuation, cutoff, spot;

		LightSource(const vec3 &position, const vec3 &direction, const vec4 &diffuse, const vec4 &specular, const float cA, const float lA, const float qA, const float cutoff, const float spot); // spot light
		LightSource(const vec3 &position, const vec4 &diffuse, const vec4 &specular, const float cA, const float lA, const float qA); // point light
		LightSource(const vec3 &direction, const vec4 &diffuse, const vec4 &specular); // directional light
		LightSource();
};

};

#endif
