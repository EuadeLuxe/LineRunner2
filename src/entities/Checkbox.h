#ifndef CHECKBOX_H_
#define CHECKBOX_H_

#include <memory>
#include "../BurningByte/Entity.h"
#include "../BurningByte/input/Device.h"
#include "../BurningByte/render/util/Position2D.h"
#include "../components/Command.h"

class Checkbox:public std::enable_shared_from_this<Checkbox>, public bb::Entity, public bb::Device{
	private:
		std::shared_ptr<Command> command;
		bool check;

	public:
		Checkbox(const std::string &name, const std::shared_ptr<Command> command, const bool check = false);
		Checkbox(const std::shared_ptr<Command> command, const bool check = false);

		void mouseClicked(BUTTON button, int x, int y);

		bool checked();
};

#endif
