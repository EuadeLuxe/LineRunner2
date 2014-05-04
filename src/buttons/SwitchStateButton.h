#ifndef STARTBUTTON_H_
#define STARTBUTTON_H_

#include <memory>
#include <string>
#include "../BurningByte/state/StateManager.h"
#include "../components/Command.h"

class SwitchStateButton:public Command{
	private:
		std::shared_ptr<bb::StateManager> states;
		std::string switchTo;

	public:
		SwitchStateButton(const std::shared_ptr<bb::StateManager> states, const std::string &switchTo);

		void call();
};

#endif
