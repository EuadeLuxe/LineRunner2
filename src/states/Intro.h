#ifndef INTRO_H_
#define INTRO_H_

#include <memory>
#include <GL/gl3w.h>
#include "../BurningByte/state/State.h"
#include "../BurningByte/render/Camera.h"
#include "../BurningByte/res/Texture.h"
#include "../systems/Renderer2D.h"

class Intro:public bb::State{
	private:
		unsigned int wndSize[2];

		std::vector<std::shared_ptr<bb::Texture>> textures;
		std::shared_ptr<bb::Camera> camera;
		std::unique_ptr<Renderer2D> renderer2D;

	public:
		Intro(const std::shared_ptr<bb::Camera> camera, const unsigned int width, const unsigned int height);

		void setViewport(const unsigned int width, const unsigned int height);

		void load();

		void pause();
		void resume();

		void logic(const float deltaTime);
		void render(const float deltaTime);
};

#endif
