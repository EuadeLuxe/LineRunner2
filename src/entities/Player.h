#ifndef PLAYER_H_
#define PLAYER_H_

#include <memory>
#include "../BurningByte/Entity.h"
#include "../BurningByte/input/Device.h"
#include "../BurningByte/render/util/Position2D.h"

class Player:public bb::Entity, public bb::Device{
	public:
		bool jump, jumping, roll, rolling;
		unsigned char jumpKey, rollKey;

		Player(const std::string &name, const unsigned char jumpKey, const unsigned char rollKey);

		void keyPressed(unsigned char key, int x, int y);
		void keyReleased(unsigned char key, int x, int y);
};

#endif
