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
		std::shared_ptr<bb::Position2D> last, player; // reference to last position object, player position
		float speed;

	public:
		Level(const std::shared_ptr<LineRunner2> game, const std::shared_ptr<bb::Position2D> player, const float speed);

		void update(const float deltaTime);
};

#endif
