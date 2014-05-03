#ifndef PLAYING_H_
#define PLAYING_H_

#include <memory>
#include <math.h>
#include <iostream>
#include <GL/gl3w.h>
#include "../BurningByte/state/State.h"
#include "../BurningByte/state/StateManager.h"
#include "../BurningByte/res/Shader.h"
#include "../BurningByte/render/Camera.h"
#include "../BurningByte/res/Texture.h"
#include "../systems/Renderer.h"

class Playing:public bb::State{
	private:
		unsigned int wndSize[2];
		std::shared_ptr<bb::StateManager> states;
		std::shared_ptr<bb::Camera> camera;

		std::vector<std::shared_ptr<bb::Texture>> textures;
		std::unique_ptr<Renderer> renderer;

	public:
		Playing(const std::shared_ptr<bb::StateManager> states, const std::shared_ptr<bb::Camera> camera, const unsigned int width, const unsigned int height);

		void setViewport(const unsigned int wndWidth, const unsigned int wndHeight);

		void load();

		void pause();
		void resume();

		void logic(const float deltaTime);
		void render(const float deltaTime);
};

#endif
