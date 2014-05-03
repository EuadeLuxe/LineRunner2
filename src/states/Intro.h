#ifndef INTRO_H_
#define INTRO_H_

#include <memory>
#include <GL/gl3w.h>
#include "../BurningByte/state/State.h"
#include "../BurningByte/state/StateManager.h"
#include "../BurningByte/input/Input.h"
#include "../BurningByte/input/Keyboard.h"
#include "../BurningByte/render/Camera.h"
#include "../BurningByte/res/Texture.h"
#include "../components/Duration.h"
#include "../systems/DurationManager.h"
#include "../systems/Renderer.h"
#include "../intro/Skip.h"

class Intro:public bb::State{
	private:
		unsigned int wndSize[2];
		std::shared_ptr<bb::StateManager> states;
		std::shared_ptr<bb::Input> input;
		std::shared_ptr<bb::Camera> camera;

		std::vector<std::shared_ptr<bb::Texture>> textures;
		std::unique_ptr<DurationManager> duration;
		std::unique_ptr<Renderer> renderer;

		std::shared_ptr<Skip> skip;

	public:
		Intro(const std::shared_ptr<bb::StateManager> states, const std::shared_ptr<bb::Input> input, const std::shared_ptr<bb::Camera> camera, const unsigned int width, const unsigned int height);

		void setViewport(const unsigned int width, const unsigned int height);

		void load();

		void pause();
		void resume();

		void logic(const float deltaTime);
		void render(const float deltaTime);
};

#endif
