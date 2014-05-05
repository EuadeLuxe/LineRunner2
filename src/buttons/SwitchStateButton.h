#ifndef STARTBUTTON_H_
#define STARTBUTTON_H_

#include <memory>
#include <string>
#include "../BurningByte/state/StateManager.h"
#include "../BurningByte/res/buffer/Sound.h"
#include "../BurningByte/sound/SoundSource.h"
#include "../components/Command.h"

class SwitchStateButton:public Command{
	private:
		std::shared_ptr<bb::StateManager> states;
		std::string switchTo;
		std::shared_ptr<bb::SoundSource> sound;

	public:
		SwitchStateButton(const std::shared_ptr<bb::StateManager> states, const std::string &switchTo);

		void addSound(const std::shared_ptr<bb::Sound> sound);

		void call();
};

#endif
