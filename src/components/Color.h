#ifndef COLOR_H_
#define COLOR_H_

#include "../BurningByte/Component.h"
#include "../BurningByte/math/Vector.h"

class Color:public bb::Component{
	public:
		bb::vec3 color;

		Color(const bb::vec3 &color);
		Color();
};

#endif
