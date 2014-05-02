#ifndef MAINMENU_H_
#define MAINMENU_H_

#include <GL/gl3w.h>
#include "../BurningByte/state/State.h"

class MainMenu:public bb::State{
	private:
		unsigned int wndSize[2];

	public:
		MainMenu(const unsigned int width, const unsigned int height);

		void setViewport(const unsigned int width, const unsigned int height);

		void load();

		void pause();
		void resume();

		void logic(const float deltaTime);
		void render(const float deltaTime);
};

#endif
