#ifndef CONTROLS_H_
#define CONTROLS_H_

#include <GL/gl3w.h>
#include "../BurningByte/state/State.h"

class Controls:public bb::State{
	private:
		unsigned int wndSize[2];

	public:
		Controls(const unsigned int width, const unsigned int height);

		void setViewport(const unsigned int width, const unsigned int height);

		void load();

		void pause();
		void resume();

		void logic(const float deltaTime);
		void render(const float deltaTime);
};

#endif
