#ifndef SKIP_H_
#define SKIP_H_

#include <memory>
#include "../BurningByte/state/StateManager.h"
#include "../BurningByte/input/Keyboard.h"

class Skip:public bb::Keyboard{
	private:
		std::shared_ptr<bb::StateManager> states;

	public:
		Skip(const std::shared_ptr<bb::StateManager> states);

		void typed(const unsigned char c);
};

#endif
