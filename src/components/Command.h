#ifndef COMMAND_H_
#define COMMAND_H_

#include "../BurningByte/Component.h"

class Command:public bb::Component{
	public:
		virtual ~Command(){}
		virtual void call() = 0;
};

#endif
