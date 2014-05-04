#ifndef EXITBUTTON_H_
#define EXITBUTTON_H_

#include <GL/freeglut.h>
#include "../components/Command.h"

class ExitButton:public Command{
	public:
		void call();
};

#endif
