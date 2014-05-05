#ifndef BUTTON_H_
#define BUTTON_H_

#include <memory>
#include "../BurningByte/Entity.h"
#include "../BurningByte/input/Device.h"
#include "../BurningByte/render/util/Position2D.h"
#include "../components/Command.h"

class Button:public bb::Entity, public bb::Device{
	private:
		std::shared_ptr<Command> command;

	public:
		Button(const std::string &name, const std::shared_ptr<Command> command);
		Button(const std::shared_ptr<Command> command);

		void mouseClicked(BUTTON button, int x, int y);
};

#endif
