#ifndef EXITBUTTON_H_
#define EXITBUTTON_H_

#include <iostream>
#include "../components/Command.h"

class ExitButton:public Command{
	public:
		void call();
};

#endif