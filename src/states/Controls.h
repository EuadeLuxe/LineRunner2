#ifndef CONTROLS_H_
#define CONTROLS_H_

#include <memory>
#include <GL/gl3w.h>
#include "../BurningByte/state/State.h"
#include "../BurningByte/render/Camera.h"

class Controls:public bb::State{
	private:
		unsigned int wndSize[2];
		std::shared_ptr<bb::Camera> camera;

	public:
		Controls(const std::shared_ptr<bb::Camera> camera, const unsigned int width, const unsigned int height);

		void setViewport(const unsigned int width, const unsigned int height);

		void load();

		void pause();
		void resume();

		void logic(const float deltaTime);
		void render(const float deltaTime);
};

#endif
