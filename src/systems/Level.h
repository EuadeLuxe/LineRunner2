#ifndef LEVEL_H_
#define LEVEL_H_

#include <memory>
#include <stdlib.h>
#include "../BurningByte/System.h"
#include "../BurningByte/render/util/Position2D.h"
#include "../LineRunner2.h"
#include "../entities/Player.h"

class Level:public bb::System{
	private:
		std::shared_ptr<LineRunner2> game;
		std::shared_ptr<bb::Position2D> last; // reference to last position object
		std::shared_ptr<Player> player;
		float speed;

	public:
		Level(const std::shared_ptr<LineRunner2> game, const std::shared_ptr<Player> player, const float speed);

		void reset();
		void update(const float deltaTime);
};

#endif
