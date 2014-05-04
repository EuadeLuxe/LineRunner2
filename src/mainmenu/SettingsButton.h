#ifndef SETTINGSBUTTON_H_
#define SETTINGSBUTTON_H_

#include <iostream>
#include "../components/Command.h"

class SettingsButton:public Command{
	public:
		void call();
};

#endif
