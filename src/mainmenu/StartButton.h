#ifndef STARTBUTTON_H_
#define STARTBUTTON_H_

#include <iostream>
#include "../components/Command.h"

class StartButton:public Command{
	public:
		void call();
};

#endif
