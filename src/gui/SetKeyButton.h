#ifndef SETKEYBUTTON_H_
#define SETKEYBUTTON_H_

#include "../components/Command.h"

class Settings;

class SetKeyButton:public Command{
	public:
		enum CONTROL{
			NONE,
			JUMP,
			ROLL,
			PAUSE,
			RETRY
		};

	private:
		std::shared_ptr<Settings> settings;
		CONTROL control;

	public:
		SetKeyButton(const std::shared_ptr<Settings> settings, const CONTROL control);

		void call(const std::shared_ptr<bb::Entity> entity);
};

#endif
