#ifndef BACKGROUND_H_
#define BACKGROUND_H_

#include <memory>
#include "../BurningByte/System.h"
#include "../BurningByte/render/util/Position2D.h"

class Background:public bb::System{
	private:
		float speed, x; // translation speed and reset x coordinate

	public:
		Background(const float speed, const float x);

		void update(const float deltaTime);
};

#endif
