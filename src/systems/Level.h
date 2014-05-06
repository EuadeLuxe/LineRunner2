#ifndef LEVEL_H_
#define LEVEL_H_

#include <memory>
#include <stdlib.h>
#include "../BurningByte/System.h"
#include "../BurningByte/render/util/Position2D.h"
#include "../LineRunner2.h"

class Level:public bb::System{
	private:
		std::shared_ptr<LineRunner2> game;
		float speed;

	public:
		Level(const std::shared_ptr<LineRunner2> game, const float speed);

		void update(const float deltaTime);
};

#endif
