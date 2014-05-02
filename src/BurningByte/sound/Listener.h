/*
 * Listener
 * Author: Marvin Blum
 * Last Update: 2014/05/02 15:47
 * */

#ifndef LISTENER_H_
#define LISTENER_H_

#include <AL/al.h>
#include "../math/Vector.h"

namespace bb{

class Listener{
	public:
		vec3 position, velocity, orientation, up;
		float gain;

		Listener(const vec3 &position, const vec3 &velocity, const vec3 &orientation);
		Listener(const vec3 &position);

		void set();
		void setPosition(const vec3 &position);
		void setVelocity(const vec3 &velocity);
		void setOrientation(const vec3 &orientation);
		void setUp(const vec3 &up);
		void setGain(float gain);
};

};

#endif
