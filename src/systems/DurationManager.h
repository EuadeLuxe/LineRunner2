#ifndef DURATIONMANAGER_H_
#define DURATIONMANAGER_H_

#include <iostream>
#include "../BurningByte/System.h"
#include "../components/Duration.h"

class DurationManager:public bb::System{
	public:
		unsigned int screen; // current screen

		DurationManager();

		void update(const float deltaTime);
};

#endif
