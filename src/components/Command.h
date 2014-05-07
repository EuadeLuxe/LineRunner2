#ifndef COMMAND_H_
#define COMMAND_H_

#include <memory>
#include "../BurningByte/Component.h"
#include "../BurningByte/Entity.h"

class Command:public bb::Component{
	public:
		virtual ~Command(){}
		virtual void call(const std::shared_ptr<bb::Entity> entity) = 0;
};

#endif
