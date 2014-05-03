#ifndef MAINMENU_H_
#define MAINMENU_H_

#include <memory>
#include <vector>
#include <GL/gl3w.h>
#include "../BurningByte/state/State.h"
#include "../BurningByte/state/StateManager.h"
#include "../BurningByte/render/Camera.h"
#include "../BurningByte/res/Shader.h"
#include "../BurningByte/res/Texture.h"
#include "../systems/Renderer.h"

class MainMenu:public bb::State{
	private:
		unsigned int wndSize[2];
		std::shared_ptr<bb::StateManager> states;
		std::shared_ptr<bb::Camera> camera;

		std::vector<std::shared_ptr<bb::Texture>> textures;
		std::unique_ptr<Renderer> renderer;

	public:
		MainMenu(const std::shared_ptr<bb::StateManager> states, const std::shared_ptr<bb::Camera> camera, const unsigned int width, const unsigned int height);

		void setViewport(const unsigned int width, const unsigned int height);

		void load();

		void pause();
		void resume();

		void logic(const float deltaTime);
		void render(const float deltaTime);
};

#endif
