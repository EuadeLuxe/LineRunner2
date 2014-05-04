#ifndef CONTROLS_H_
#define CONTROLS_H_

#include <memory>
#include "../LineRunner2.h"

class Controls:public bb::State{
	private:
		std::shared_ptr<LineRunner2> game;

	public:
		Controls(const std::shared_ptr<LineRunner2> game);

		void load();

		void pause();
		void resume();

		void logic(const float deltaTime);
		void render(const float deltaTime);
};

#endif
